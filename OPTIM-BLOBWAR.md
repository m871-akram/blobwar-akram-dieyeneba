# Idées d'optimisation IA pour Blobwar

Ce document propose des améliorations pour les IA du projet Blobwar, en reliant chaque idée aux notions du cours
d'Algorithmique Avancée présentes dans `COURSE.md` : **travail/profondeur** $W,D$, **fork-join**, **for//**, *
*algorithmes en cascade**, **work-stealing**, **early termination**, **Monte-Carlo**, **Las Vegas**, **dérandomisation**
et **analyse probabiliste**.

Le code actuel calcule les coups dans `Strategy::computeBestMove()` avec un état `bidiarray<Sint16> _blobs`, un masque
de trous `_holes`, et un joueur courant `_current_player`. Le moteur de règles applique les règles suivantes :

- déplacement en distance de Chebyshev $1$ : duplication ;
- déplacement en distance de Chebyshev $2$ : saut, donc suppression de l'ancien pion ;
- après arrivée, conversion des pions adverses adjacents à distance $1$ ;
- plateau $8 \times 8$, donc au plus $64$ cases.

Cette petite taille rend possible des optimisations très efficaces : **bitboards 64 bits**, tables de voisinage
pré-calculées, tables de transposition, recherche exacte en fin de partie et parallélisation contrôlée.

---

## 1. Amélioration de l'Heuristique

### 1.1. Fonction d'évaluation multi-critères et dépendante de la phase

L'évaluation actuelle est essentiellement :

$$
score = \#pions_{moi} - \#pions_{adversaire}
$$

Cette métrique est correcte en fin de partie, mais trop pauvre au début et au milieu. Dans Blobwar, gagner un pion
maintenant peut être mauvais si cela donne à l'adversaire une zone de conversion massive au coup suivant.

Une évaluation plus robuste :

$$
Eval(s) =
w_m(\phi) \cdot Material

+ w_{mob}(\phi) \cdot Mobility
+ w_c(\phi) \cdot Center
+ w_t(\phi) \cdot Territory
+ w_s(\phi) \cdot Stability

- w_v(\phi) \cdot Vulnerability

+ w_g(\phi) \cdot ImmediateGain
  $$

où $\phi$ est la phase :

$$
\phi = \frac{\#cases\_vides}{\#cases\_jouables}
$$

- début de partie : $\phi$ élevé, favoriser mobilité, centre, territoire ;
- milieu : favoriser mobilité, sécurité, potentiel de conversion ;
- fin : favoriser matériel exact et coups qui réduisent les réponses adverses.

Lien avec le cours : c'est une forme d'**approximation contrôlée**. On ne peut pas explorer tout l'arbre à grande
profondeur, donc on approxime la valeur réelle d'un état par une combinaison de critères calculables en temps faible.

Implémentation C++ :

```cpp
struct Features {
    int material;
    int mobility;
    int center;
    int territory;
    int stability;
    int vulnerability;
    int immediateGain;
};

Sint32 evaluate(const Position& p, int me) {
    int empty = popcount(p.empty());
    int playable = popcount(~p.holes & BOARD_MASK);
    double phase = static_cast<double>(empty) / playable;

    Weights w = weightsForPhase(phase);
    Features f = computeFeatures(p, me);

    return w.material * f.material
         + w.mobility * f.mobility
         + w.center * f.center
         + w.territory * f.territory
         + w.stability * f.stability
         - w.vulnerability * f.vulnerability
         + w.immediateGain * f.immediateGain;
}
```

Même sans introduire une nouvelle classe `Position` tout de suite, ces métriques peuvent être calculées depuis `_blobs`
et `_holes`. Mais pour les performances, les bitboards sont fortement recommandés.

---

### 1.2. Matériel pondéré : copie, saut, conversion

Dans Blobwar, un coup a une valeur matérielle immédiate :

- duplication : $+1$ pion ;
- saut : $0$ pion net avant conversion ;
- conversion de $k$ pions adverses : chaque pion converti vaut $+2$ dans la différence de score, car l'adversaire
  perd $1$ et moi je gagne $1$.

Donc le gain immédiat d'un coup est approximativement :

$$
gain(mv) =
\begin{cases}
1 + 2k & \text{si duplication} \\
2k & \text{si saut}
\end{cases}
$$

Pertinence : cette formule est idéale pour un **glouton fort** et pour le **tri des coups** en alpha-beta.

Calcul efficace :

```cpp
int immediateGain(const Position& p, const Move& mv, int me) {
    bool copy = chebyshevDistance(mv.src, mv.dst) == 1;
    uint64_t captured = NEAR1[mv.dst] & p.occupiedBy(opponent(me));
    return (copy ? 1 : 0) + 2 * popcount(captured);
}
```

Dans le code actuel sans bitboard :

```cpp
int countCapturedAfter(Uint8 nx, Uint8 ny, Uint16 me) {
    int k = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int x = nx + dx;
            int y = ny + dy;
            if (x < 0 || x > 7 || y < 0 || y > 7) continue;
            Sint16 owner = _blobs.get(x, y);
            if (owner != -1 && owner != me) ++k;
        }
    }
    return k;
}
```

---

### 1.3. Mobilité : nombre de coups possibles

La mobilité mesure :

$$
Mobility = legalMoves(moi) - legalMoves(adversaire)
$$

Pertinence pour Blobwar :

- un joueur sans coup est sauté par `rules::next_turn()` ;
- priver l'adversaire de coups peut faire gagner même avec un matériel temporairement inférieur ;
- la mobilité est souvent un meilleur signal que le score brut en début/milieu de partie.

Calcul actuel possible :

```cpp
int countValidMovesFor(Uint16 player) const {
    int count = 0;
    for (int ox = 0; ox < 8; ++ox) {
        for (int oy = 0; oy < 8; ++oy) {
            if (_blobs.get(ox, oy) != player) continue;
            for (int nx = std::max(0, ox - 2); nx <= std::min(7, ox + 2); ++nx) {
                for (int ny = std::max(0, oy - 2); ny <= std::min(7, oy + 2); ++ny) {
                    if (nx == ox && ny == oy) continue;
                    if (_holes.get(nx, ny)) continue;
                    if (_blobs.get(nx, ny) == -1) ++count;
                }
            }
        }
    }
    return count;
}
```

Version plus fine :

- `moveMobility` : nombre de coups ;
- `destinationMobility` : nombre de cases vides atteignables distinctes ;
- `copyMobility` : nombre de duplications ;
- `jumpMobility` : nombre de sauts.

Les duplications sont généralement plus sûres, car elles augmentent le matériel. Les sauts sont utiles pour atteindre
une zone forte ou échapper à une menace.

---

### 1.4. Vulnérabilité : pions convertibles au prochain coup adverse

Un pion à moi situé en case $p$ est vulnérable si l'adversaire peut jouer sur une case vide $q$ adjacente à $p$. Après
son arrivée en $q$, il convertira $p$.

Critère :

$$
Vulnerable(p) =
\exists q,\ dist_\infty(p,q) \le 1,\ q\ vide,\ q\ non\ trou,\ q\ atteignable\ par\ un\ pion\ adverse
$$

Pertinence :

- évite les coups gloutons qui capturent beaucoup mais exposent encore plus ;
- permet de construire une IA plus "positionnelle".

Calcul efficace avec bitboards :

```cpp
uint64_t opponentReach = 0;
forEachBit(p.occupiedBy(opp), [&](int src) {
    opponentReach |= NEAR2[src];
});
opponentReach &= p.empty();

int vulnerable = 0;
forEachBit(p.occupiedBy(me), [&](int cell) {
    if ((NEAR1[cell] & opponentReach) != 0) {
        ++vulnerable;
    }
});
```

Sans bitboard, on peut scanner les $64$ cases : le plateau est petit, donc $O(64 \cdot 25)$ reste acceptable.

---

### 1.5. Stabilité : pions difficiles à convertir

Un pion stable est un pion qui ne peut pas être converti immédiatement, souvent parce que les cases voisines sont
occupées, des trous, ou hors plateau.

Approximation :

$$
Stability = \#\{pions\_moi\ non\ vulnérables\}
- \#\{pions\_adv\ non\ vulnérables\}
$$

Version plus positionnelle :

- coins et bords ont moins de voisins, donc moins de cases d'atterrissage adverses ;
- zones entourées de trous sont plus sûres ;
- groupes compacts réduisent les cases d'infiltration.

Table de poids statique possible :

```text
Coins          : +6
Bords          : +3
Cases près trou: +1 à +4 selon protection
Centre         : +2 au début, moins en fin
```

Mais il vaut mieux calculer la stabilité dynamiquement, car les trous dépendent de la map.

---

### 1.6. Contrôle du centre et poids positionnels dépendants de la map

Dans beaucoup de jeux de plateau, le centre donne plus d'options. Pour Blobwar, le centre est surtout utile en début de
partie car il maximise les destinations à distance $1$ ou $2$.

Poids simple :

$$
CenterScore =
\sum_{p \in moi} centerWeight[p]

- \sum_{p \in adv} centerWeight[p]
  $$

où :

$$
centerWeight[x,y] = 7 - |2x-7| - |2y-7|
$$

À adapter avec les trous :

- une case centrale entourée de trous peut être mauvaise ;
- une case de bord peut être excellente si elle est stable.

Pré-calcul au chargement de la map :

```cpp
int positionalWeight[64];

for (int i = 0; i < 64; ++i) {
    if (hole(i)) {
        positionalWeight[i] = 0;
        continue;
    }
    int degree1 = popcount(NEAR1[i] & playableMask);
    int degree2 = popcount(NEAR2[i] & playableMask);
    int edgeBonus = isEdge(i) ? 2 : 0;
    positionalWeight[i] = 2 * degree1 + degree2 + edgeBonus;
}
```

Lien avec le cours : c'est une forme de **pré-calcul** pour réduire le travail $W$ de chaque évaluation. On paie une
fois au début, puis chaque feuille de l'arbre coûte moins cher.

---

### 1.7. Territoire par distance : Voronoï sur plateau 8x8

Une case vide est "contrôlée" par moi si je peux l'atteindre plus vite que l'adversaire.

On calcule deux distances :

$$
d_{moi}(c),\quad d_{adv}(c)
$$

puis :

$$
Territory =
\#\{c : d_{moi}(c) < d_{adv}(c)\}

- \#\{c : d_{adv}(c) < d_{moi}(c)\}
  $$

Pour Blobwar, une arête du graphe relie deux cases non-trous si leur distance de Chebyshev est $\le 2$.

Implémentation :

- construire une liste d'adjacence de $64$ cases une fois par map ;
- BFS multi-source depuis tous les pions du joueur ;
- plateau petit, donc coût faible.

```cpp
std::array<int, 64> distancesFrom(uint64_t sources, uint64_t playable) {
    std::array<int, 64> dist;
    dist.fill(INF);
    std::queue<int> q;

    forEachBit(sources, [&](int s) {
        dist[s] = 0;
        q.push(s);
    });

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        uint64_t next = NEAR2[u] & playable;
        forEachBit(next, [&](int v) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        });
    }
    return dist;
}
```

Cette heuristique est intéressante pour les maps avec trous (`fortress`, `island`, `rings`, etc.).

---

### 1.8. Potentiel de menace et pièges

Un coup peut être évalué non seulement par ce qu'il gagne maintenant, mais par ce qu'il menace au coup suivant.

Définition simple :

$$
Threat(mv) = \max_{mv' \in coups(moi\ après\ mv)} immediateGain(mv')
$$

Pour éviter un coût trop élevé, on calcule une approximation :

- après avoir simulé `mv`, regarder les cases vides proches des pions à moi ;
- compter combien de pions adverses seraient adjacents à chaque destination ;
- garder le maximum ou la somme des meilleurs $k$.

Pertinence :

- Blobwar a des renversements locaux forts ;
- préparer une case de conversion à $4$ ou $5$ pions peut être plus fort qu'un gain immédiat de $1$.

Lien avec le cours : c'est une **recherche limitée** ou une approximation d'un sous-arbre. On réduit le travail par un
calcul local au lieu d'explorer complètement.

---

### 1.9. Bitboards 64 bits : optimisation structurelle majeure

Le plateau $8 \times 8$ tient exactement dans un `uint64_t`. On peut représenter :

```cpp
struct Position {
    uint64_t red;
    uint64_t blue;
    uint64_t holes;
    int sideToMove;
};
```

Les cases vides :

```cpp
uint64_t occupied = red | blue | holes;
uint64_t empty = ~occupied & BOARD_MASK;
```

Pré-calcul :

```cpp
uint64_t NEAR1[64]; // distance de Chebyshev exactement <= 1, sans soi-même
uint64_t NEAR2[64]; // distance <= 2, sans soi-même
uint64_t RING2[64]; // distance exactement 2
```

Génération de coups :

```cpp
void generateMoves(const Position& p, int me, std::vector<Move>& out) {
    out.clear();
    uint64_t mine = p.occupiedBy(me);
    uint64_t empty = p.empty();

    forEachBit(mine, [&](int src) {
        uint64_t copyDests = NEAR1[src] & empty;
        uint64_t jumpDests = RING2[src] & empty;

        forEachBit(copyDests, [&](int dst) {
            out.push_back(Move{src, dst, true});
        });
        forEachBit(jumpDests, [&](int dst) {
            out.push_back(Move{src, dst, false});
        });
    });
}
```

Application d'un coup :

```cpp
Position applyMove(Position p, Move mv, int me) {
    int opp = 1 - me;
    uint64_t srcBit = 1ULL << mv.src;
    uint64_t dstBit = 1ULL << mv.dst;
    uint64_t captured = NEAR1[mv.dst] & p.occupiedBy(opp);

    if (!mv.isCopy) {
        p.clearBit(me, srcBit);
    }

    p.setBit(me, dstBit);
    p.clearBits(opp, captured);
    p.setBits(me, captured);
    p.sideToMove = opp;
    return p;
}
```

Impact :

- évaluation beaucoup plus rapide ;
- hashing plus simple ;
- copies de position très peu coûteuses ;
- idéal pour paralléliser car chaque tâche manipule une position par valeur, sans écriture partagée.

---

## 2. Optimisations Séquentielles Min-Max / Alpha-Beta

### 2.1. Tri des coups : Move Ordering

Alpha-beta dépend fortement de l'ordre des coups. Avec un ordre mauvais, le coût reste proche de :

$$
O(b^d)
$$

où $b$ est le facteur de branchement et $d$ la profondeur. Avec un ordre presque parfait, alpha-beta approche :

$$
O(b^{d/2})
$$

C'est un gain énorme : à profondeur égale, on explore presque comme si la profondeur était divisée par deux.

Critères de tri adaptés à Blobwar :

1. coup de la table de transposition ;
2. coup de la variation principale précédente ;
3. gain immédiat : duplication + conversions ;
4. coups qui réduisent la mobilité adverse ;
5. coups qui augmentent la stabilité ;
6. killer moves : coups ayant déjà causé une coupure au même niveau ;
7. history heuristic : statistiques globales de bons coups.

Score de tri :

```cpp
int moveOrderingScore(const Position& p, Move mv, int me, int ply) {
    int score = 0;
    score += 10000 * isTranspositionMove(mv);
    score += 8000  * isPrincipalVariationMove(mv, ply);
    score += 500   * immediateGain(p, mv, me);
    score += 80    * mobilityDeltaAfter(p, mv, me);
    score += 20    * positionalWeight[mv.dst];
    score += killerBonus(mv, ply);
    score += historyScore[mv.src][mv.dst];
    return score;
}
```

Lien avec le cours : on agit directement sur la taille effective de l'arbre de calcul. On ne change pas la correction
d'alpha-beta, mais on réduit le **travail** $W$.

---

### 2.2. Iterative Deepening : profondeur progressive et sauvegarde du meilleur coup

Le code `launchStrategy` est tué par un timer externe après `compute_time_IA` secondes. Donc l'IA doit toujours avoir
sauvegardé un coup valide avant la limite.

Principe :

```text
best = premier coup légal
saveBestMove(best)

pour depth = 1, 2, 3, ... tant qu'il reste du temps :
    best = alphaBetaRoot(depth)
    saveBestMove(best)
```

Avantages :

- si le processus est tué, le dernier coup complet est déjà en mémoire partagée ;
- la profondeur $d-1$ donne une variation principale pour trier les coups à profondeur $d$ ;
- permet les aspiration windows.

Pseudo-code :

```cpp
void Strategy::computeBestMove() {
    std::vector<Move> moves;
    generateMoves(position, _current_player, moves);
    if (moves.empty()) return;

    Move best = moves[0];
    save(best);

    SearchTimer timer(timeLimitMs - safetyMarginMs);
    for (int depth = 1; !timer.expired(); ++depth) {
        SearchResult r = searchRoot(depth, timer);
        if (r.completed) {
            best = r.bestMove;
            save(best);
            principalVariation = r.pv;
        } else {
            break;
        }
    }
}
```

---

### 2.3. Tables de transposition avec Zobrist Hashing

Un même état peut être atteint par plusieurs ordres de coups. Sans table de transposition, on recalcule le même
sous-arbre.

On associe à chaque état un hash :

$$
H(s) =
\bigoplus_{case,occupant} Z[case][occupant]
\oplus ZSide[sideToMove]
\oplus ZMap[holes]
$$

Implémentation :

```cpp
struct TTEntry {
    uint64_t key;
    int depth;
    Sint32 score;
    enum Bound { EXACT, LOWER, UPPER } bound;
    Move bestMove;
    uint8_t age;
};

std::vector<TTEntry> table(1 << 20);
```

Utilisation dans alpha-beta :

```cpp
bool probeTT(uint64_t key, int depth, Sint32 alpha, Sint32 beta, Sint32& score, Move& best) {
    TTEntry& e = table[key & (table.size() - 1)];
    if (e.key != key || e.depth < depth) return false;

    best = e.bestMove;
    if (e.bound == TTEntry::EXACT) {
        score = e.score;
        return true;
    }
    if (e.bound == TTEntry::LOWER && e.score >= beta) {
        score = e.score;
        return true;
    }
    if (e.bound == TTEntry::UPPER && e.score <= alpha) {
        score = e.score;
        return true;
    }
    return false;
}
```

Lien avec le cours :

- idée proche du **hachage probabiliste** ;
- avec un hash 64 bits, les collisions sont extrêmement rares ;
- pour une version **Las Vegas**, on stocke aussi une signature complète ou les bitboards, et on vérifie l'état avant d'
  utiliser l'entrée. Comme Rabin-Karp Monte-Carlo devient Las Vegas par vérification, Zobrist devient sans erreur si on
  vérifie les candidats.

---

### 2.4. Aspiration Windows

Avec iterative deepening, le score à profondeur $d$ est souvent proche du score à profondeur $d-1$. Au lieu de chercher
dans :

$$
[-\infty, +\infty]
$$

on cherche dans une fenêtre :

$$
[score_{prev} - \Delta,\ score_{prev} + \Delta]
$$

Si le vrai score sort de la fenêtre, on relance avec une fenêtre plus large.

Pertinence :

- fenêtres plus petites donnent plus de coupures alpha-beta ;
- fonctionne très bien avec move ordering et table de transposition.

---

### 2.5. Principal Variation Search / NegaScout

Après avoir trié les coups, on suppose que le premier est le meilleur. On le cherche avec une fenêtre normale. Les
suivants sont testés avec une fenêtre nulle :

$$
[\alpha, \alpha + 1]
$$

S'ils ne battent pas alpha, on les coupe vite. S'ils battent alpha, on les recherche avec une vraie fenêtre.

Pseudo-code :

```cpp
score = -search(firstChild, -beta, -alpha);
alpha = max(alpha, score);

for each other child:
    score = -search(child, -alpha - 1, -alpha); // null window
    if (score > alpha && score < beta) {
        score = -search(child, -beta, -alpha);  // re-search
    }
    alpha = max(alpha, score);
```

Lien avec le cours : on exploite une dépendance de données au lieu de la nier. Le premier fils crée une borne forte ;
les autres deviennent beaucoup moins coûteux.

---

### 2.6. Quiescence Search adaptée à Blobwar

Un arrêt brutal à profondeur $d$ peut évaluer une position instable juste avant une grosse conversion adverse. C'est l'
effet horizon.

Idée :

- à profondeur $0$, si la position est "bruyante", prolonger seulement les coups tactiques ;
- un coup est bruyant si `immediateGain >= 4`, ou s'il convertit plusieurs pions, ou s'il sauve un pion très vulnérable.

Pseudo-code :

```cpp
Sint32 quiescence(Position p, Sint32 alpha, Sint32 beta) {
    Sint32 standPat = evaluate(p);
    if (standPat >= beta) return beta;
    alpha = std::max(alpha, standPat);

    std::vector<Move> noisy;
    generateNoisyMoves(p, noisy);
    orderMoves(noisy);

    for (Move mv : noisy) {
        Sint32 score = -quiescence(apply(p, mv), -beta, -alpha);
        if (score >= beta) return beta;
        alpha = std::max(alpha, score);
    }
    return alpha;
}
```

Attention : il faut borner cette recherche, sinon le coût explose.

---

### 2.7. Recherche exacte de fin de partie

Quand le nombre de cases vides est faible, on peut chercher jusqu'à la fin :

```cpp
if (emptyCount <= ENDGAME_THRESHOLD) {
    return solveExactlyWithTT(p, alpha, beta);
}
```

Pertinence :

- Blobwar a un plateau de $64$ cases ;
- la fin de partie est souvent décisive ;
- le matériel devient l'objectif exact.

On peut commencer avec un seuil $10$ ou $12$, puis mesurer.

---

### 2.8. Symétries de la map

Certaines maps sont symétriques. Deux positions équivalentes par rotation ou miroir ont la même valeur.

Idée :

- au chargement de la map, tester quelles transformations de $D_4$ préservent les trous ;
- pour le hash de transposition, prendre le minimum des hashes transformés ;
- stocker aussi la transformation pour convertir le meilleur coup.

Pertinence :

- réduit le nombre d'états distincts ;
- améliore la table de transposition ;
- particulièrement utile sur `standard`, `chess`, `rings`, `cross`.

---

## 3. Parallélisation Avancée

### 3.1. Diagnostic du `strategy_op.cc` actuel

La version actuelle de `strategy_op.cc` parallélise uniquement le premier niveau :

```cpp
for (const movement& mv : valid_moves) {
    futures.push_back(std::async(std::launch::async, ...));
}
```

Limites :

- crée potentiellement beaucoup trop de tâches ;
- pas de pool de threads ;
- pas de work-stealing ;
- pas d'alpha-beta, seulement min-max parallèle ;
- profondeur fixée à $4$ ;
- aucun mécanisme de deadline interne ;
- aucun partage de table de transposition ;
- pas de `global alpha`, donc pas de coupures entre tâches.

C'est un bon prototype, mais l'évaluation peut valoriser une approche plus structurée inspirée du cours.

---

### 3.2. Min-Max parallèle pur : fork-join et réduction max

Min-max sans élagage est naturellement parallèle : tous les enfants d'un nœud peuvent être évalués indépendamment.

Au root :

```text
scores = for// mv dans coups:
    -minimax(apply(mv), depth - 1)

best = reduce(max, scores)
```

Analyse :

- travail inchangé : $W = O(b^d)$ ;
- profondeur idéale : $D = O(d)$ si tous les niveaux sont suffisamment parallélisés ;
- sur $p$ processeurs :

$$
T_p \approx \frac{W}{p} + D
$$

Lien direct avec le cours : c'est exactement le modèle **fork-join** et la loi de Brent.

Implémentation réaliste :

- ne pas créer une tâche par nœud ;
- utiliser un **seuil de cascade** :

```cpp
if (depth <= sequentialDepth || moves.size() < minBranching) {
    return minimaxSequential(p, depth);
}
return minimaxParallel(p, depth);
```

Ce seuil applique l'idée du cours : ne pas payer le coût d'un `fork` pour un sous-problème trop petit.

---

### 3.3. Thread pool au lieu de `std::async`

`std::async` est simple, mais ne donne pas assez de contrôle sur :

- le nombre de threads ;
- la file de tâches ;
- l'annulation ;
- la granularité ;
- les statistiques.

Mieux :

```cpp
class ThreadPool {
public:
    explicit ThreadPool(int nThreads);
    template<class F>
    auto submit(F&& f) -> FutureResult;
    void waitAll();
};
```

Au root :

```cpp
std::atomic<Sint32> globalBest(-INF);
std::mutex bestMutex;
Move bestMove = moves[0];

for (Move mv : moves) {
    pool.submit([&, mv] {
        Sint32 score = -alphaBeta(apply(p, mv), depth - 1, -INF, INF);
        Sint32 old = globalBest.load();
        while (score > old && !globalBest.compare_exchange_weak(old, score)) {}

        if (score >= globalBest.load()) {
            std::lock_guard<std::mutex> lock(bestMutex);
            if (score > bestScore) {
                bestScore = score;
                bestMove = mv;
            }
        }
    });
}
pool.waitAll();
```

---

### 3.4. Work-Stealing : équilibrer des sous-arbres de tailles variables

Dans alpha-beta, deux coups de même profondeur peuvent coûter très différemment :

- un coup peut provoquer une coupure rapide ;
- un autre peut ouvrir un sous-arbre énorme.

Une répartition statique des coups entre threads est donc mauvaise. Le cours recommande le **work-stealing** :

- chaque worker a une deque locale ;
- il dépile localement en LIFO pour garder la localité cache ;
- s'il n'a plus de travail, il vole une tâche chez un autre worker ;
- idéalement, il vole une tâche ancienne/grosse, ou une fraction de la file (**thief splitting**).

Tâche de recherche :

```cpp
struct SearchTask {
    Position p;
    int depth;
    Sint32 alpha;
    Sint32 beta;
    int ply;
};
```

Stratégie :

- au-dessus d'un certain depth, créer des tâches ;
- en dessous, chercher séquentiellement ;
- si une coupure beta est trouvée, poser un flag d'annulation pour les tâches soeurs.

Lien cours :

- **work-stealing** pour approcher $T_p \approx W/p + D$ ;
- **early termination** pour éviter le gaspillage quand une coupure beta rend des tâches inutiles.

---

### 3.5. Le problème d'Alpha-Beta parallèle

Alpha-beta n'est pas un simple `for//`, car les bornes dépendent des coups déjà explorés :

```text
pour chaque fils:
    score = search(fils, alpha, beta)
    alpha = max(alpha, score)
    si alpha >= beta: break
```

Le `break` montre une dépendance séquentielle. Le cours insiste sur ce piège : une boucle `for//` naïve ne peut pas
contenir un arrêt séquentiel sans surtravail.

Il faut donc paralléliser de façon **spéculative mais contrôlée**.

---

### 3.6. Shared Alpha au root

Première amélioration simple :

- les coups root sont lancés en parallèle ;
- tous les workers lisent un `globalAlpha` atomique ;
- quand un worker trouve un meilleur score, il met à jour `globalAlpha`.

Correction :

- utiliser un alpha trop bas est sûr mais moins efficace ;
- utiliser un alpha mis à jour est sûr et coupe plus.

Pseudo-code :

```cpp
std::atomic<Sint32> globalAlpha(initialAlpha);

pool.submit([&, mv] {
    Sint32 localAlpha = globalAlpha.load();
    Sint32 score = -alphaBeta(child, depth - 1, -beta, -localAlpha);
    updateAtomicMax(globalAlpha, score);
});
```

Pertinence :

- facile à intégrer ;
- bon premier pas vers alpha-beta parallèle ;
- améliore nettement `strategy_op.cc`.

---

### 3.7. Young Brothers Wait Concept (YBWC)

Principe :

1. trier les coups ;
2. chercher le premier fils séquentiellement ;
3. utiliser son score pour améliorer alpha ;
4. lancer les autres fils en parallèle.

Pourquoi ?

- le premier fils, s'il est bien choisi, est souvent la variation principale ;
- il donne une borne forte ;
- les "jeunes frères" peuvent alors être explorés en parallèle avec plus de coupures.

Pseudo-code :

```text
alphaBetaYBWC(node, depth, alpha, beta):
    moves = orderedMoves(node)

    first = moves[0]
    score = -alphaBetaYBWC(first, depth-1, -beta, -alpha)
    alpha = max(alpha, score)
    if alpha >= beta: return alpha

    parallel for each mv in moves[1..]:
        score = -alphaBetaYBWC(mv, depth-1, -beta, -alpha_shared)
        update alpha_shared
        if alpha_shared >= beta:
            signal cancellation

    return alpha_shared
```

Lien avec le cours :

- le premier fils est la partie séquentielle du DAG, donc il augmente $D$ ;
- les frères restants forment un `for//` spéculatif ;
- l'annulation correspond à l'**early termination**.

---

### 3.8. Principal Variation Splitting (PVS parallèle)

Le **Principal Variation Splitting** généralise YBWC.

Idée :

- les nœuds situés sur la variation principale sont traités prudemment ;
- on cherche d'abord le fils principal ;
- les autres fils sont parallélisés ;
- aux nœuds non-PV, on peut être plus agressif.

Dans Blobwar :

- l'iterative deepening fournit une PV de profondeur précédente ;
- à profondeur $d$, on suit cette PV pour choisir le premier fils ;
- ensuite seulement on parallélise les autres.

Implémentation :

```cpp
bool isPVNode = (ply < previousPV.size() && move == previousPV[ply]);
```

---

### 3.9. Jamboree Search : hybride cascade pour alpha-beta

Le **Jamboree Search** est une idée très adaptée au cours : c'est un **algorithme en cascade** appliqué à alpha-beta.

Principe :

1. chercher séquentiellement les $k$ meilleurs coups pour améliorer alpha ;
2. paralléliser le reste ;
3. si un coup parallèle dépasse alpha, le re-chercher proprement.

Choix de $k$ inspiré des cascades :

$$
k = \max(1, \lfloor \sqrt{b} \rfloor)
$$

où $b$ est le nombre de coups.

Pourquoi $\sqrt{b}$ ?

- comme dans les cascades du cours, on donne un traitement coûteux à un sous-ensemble contrôlé ;
- on obtient une bonne borne alpha sans explorer tout séquentiellement ;
- le reste est parallélisable.

Pseudo-code :

```text
moves = orderedMoves(node)
k = sqrt(len(moves))

pour i = 0..k-1:
    search moves[i] séquentiellement
    update alpha
    if alpha >= beta: return beta

for// i = k..len(moves)-1:
    search moves[i] avec alpha partagé
```

Cette idée est originale et facile à justifier avec les **algorithmes en cascade**.

---

### 3.10. Lazy SMP : plusieurs alpha-beta indépendants avec table partagée

Idée utilisée dans beaucoup de moteurs modernes :

- lancer $p$ recherches alpha-beta en parallèle ;
- chaque thread a un ordre de coups légèrement différent ;
- tous partagent une table de transposition ;
- le meilleur résultat terminé est choisi.

Avantages :

- très simple ;
- évite les problèmes fins de synchronisation alpha-beta ;
- la redondance n'est pas forcément perdue grâce à la table partagée ;
- la randomisation des ordres évite certains pires cas.

Lien avec le cours :

- c'est un parallélisme grossier, donc le graphe fork-join est simple ;
- la randomisation rejoint les algorithmes probabilistes ;
- si chaque thread fait une recherche exacte à profondeur fixée, la randomisation affecte le temps, pas la correction.

Implémentation :

```cpp
for (int t = 0; t < nThreads; ++t) {
    pool.submit([&, t] {
        SearchParams params;
        params.seed = baseSeed + t;
        params.moveOrderingNoise = t;
        SearchResult r = iterativeDeepening(params, sharedTT);
        publishIfBetter(r);
    });
}
```

---

### 3.11. Early Termination par annulation coopérative

Un `for//` ne peut pas faire un `break` proprement, mais on peut utiliser un flag atomique.

```cpp
std::atomic<bool> cancelled(false);

Sint32 search(...) {
    if (cancelled.load(std::memory_order_relaxed)) {
        return evaluateFast(p);
    }
    ...
    if (score >= beta) {
        cancelled.store(true);
        return beta;
    }
}
```

Attention :

- l'annulation doit être locale à un groupe de frères, pas forcément globale à toute la recherche ;
- sinon une coupure dans un sous-arbre peut arrêter des tâches qui ne sont pas logiquement concernées.

Lien avec le cours : c'est l'adaptation directe de l'**early termination** à une recherche de jeu.

---

### 3.12. Évaluation parallèle des feuilles par map-reduce

Dans certaines configurations, l'heuristique devient plus chère : territoire BFS, vulnérabilité, stabilité, MCTS local.
On peut paralléliser l'évaluation des coups root :

```text
features[mv] = for// mv:
    evaluate(apply(mv))

best = reduce(max, features)
```

C'est particulièrement utile pour :

- un glouton parallèle ;
- un pré-tri des coups ;
- une phase de "scouting" avant alpha-beta.

Mais pour un plateau $8 \times 8$, il faut garder une granularité suffisante. Appliquer le principe de cascade :

```cpp
if (moves.size() < 16) {
    scoreSequentially();
} else {
    scoreInParallel();
}
```

---

## 4. Idées Créatives / Probabilistes

### 4.1. Monte Carlo Tree Search (MCTS / UCT)

MCTS construit un arbre asymétrique guidé par des simulations.

Formule UCT :

$$
UCT(i) =
\bar{X_i}

+ C \sqrt{\frac{\ln N}{n_i}}
  $$

où :

- $\bar{X_i}$ est le score moyen du coup $i$ ;
- $N$ est le nombre de visites du parent ;
- $n_i$ est le nombre de visites du fils ;
- $C$ contrôle exploration/exploitation.

Pertinence pour Blobwar :

- le facteur de branchement varie beaucoup ;
- certaines positions ont des tactiques locales fortes ;
- le temps est borné par `compute_time_IA`, donc MCTS est naturellement anytime ;
- parallélisation facile par simulations indépendantes.

Rollout adapté :

```text
tant que partie non terminée et profondeur rollout non atteinte:
    avec probabilité 0.7: jouer un coup glouton selon immediateGain
    avec probabilité 0.2: jouer un coup qui maximise mobilité
    avec probabilité 0.1: jouer un coup aléatoire
retourner score final ou heuristique
```

Type probabiliste :

- si MCTS remplace la recherche exacte : algorithme Monte-Carlo, résultat approximatif ;
- si MCTS sert seulement au move ordering d'un alpha-beta complet : pas d'erreur de correction, seulement un choix
  d'ordre probabiliste.

Parallélisation :

- root parallel MCTS : chaque thread construit son arbre, puis fusion des statistiques ;
- shared-tree MCTS : arbre partagé avec mutex/atomiques et virtual loss ;
- leaf parallelism : plusieurs rollouts depuis la même feuille.

---

### 4.2. Alpha-Beta + Monte-Carlo aux feuilles

Au lieu d'évaluer une feuille uniquement par heuristique, on peut faire $K$ rollouts rapides :

$$
Eval_{hybride}(s) =
\lambda \cdot Eval_{heuristique}(s)

+ (1-\lambda) \cdot \frac{1}{K}\sum_{i=1}^{K} Rollout_i(s)
  $$

Pertinence :

- améliore les évaluations de positions instables ;
- utile quand la profondeur alpha-beta est limitée par le temps ;
- parallélisable car les rollouts sont indépendants.

Lien avec le cours :

- c'est un algorithme **Monte-Carlo** ;
- l'erreur décroît par amplification quand $K$ augmente ;
- Hoeffding justifie que la moyenne se stabilise :

$$
Pr(|\bar{X} - E[X]| \ge \epsilon) \le 2e^{-2K\epsilon^2}
$$

---

### 4.3. ProbCut et Multi-ProbCut

ProbCut utilise une recherche peu profonde pour prédire qu'une recherche profonde dépassera beta.

Idée :

1. faire une recherche à profondeur réduite $d'$ ;
2. obtenir un score $s'$ ;
3. si $s'$ est très au-dessus de beta, couper avec forte probabilité ;
4. si $s'$ est très en dessous d'alpha, couper aussi.

Forme :

$$
s_{deep} \approx a \cdot s_{shallow} + b + \epsilon
$$

On estime $a,b,\sigma$ par expérience.

Coupe :

```cpp
if (shallowScore >= beta + margin(depth)) {
    return beta; // coupe probabiliste
}
```

Pertinence :

- original ;
- très intéressant expérimentalement ;
- peut être activé seulement en mode "agressif".

Attention :

- ce n'est plus exact ;
- il faut mesurer le taux d'erreur ;
- présenter cela comme une optimisation probabiliste, pas comme alpha-beta exact.

---

### 4.4. Échantillonnage en cascade pour choisir la variation principale

Inspiré du **maximum probabiliste** de la séance 6 :

1. parmi les $b$ coups, tirer $\sqrt{b}$ coups au hasard ;
2. les évaluer rapidement ;
3. prendre le meilleur score échantillonné comme seuil ;
4. scorer tous les coups par heuristique légère ;
5. placer en tête les coups proches du seuil ;
6. lancer alpha-beta exact avec cet ordre.

Si on l'utilise seulement pour trier, la recherche reste exacte.

Pseudo-code :

```cpp
int sampleSize = std::max(1, static_cast<int>(std::sqrt(moves.size())));
std::vector<Move> sample = randomSample(moves, sampleSize);

Sint32 threshold = -INF;
for (Move mv : sample) {
    threshold = std::max(threshold, shallowEvaluate(apply(p, mv)));
}

sort(moves.begin(), moves.end(), [&](Move a, Move b) {
    return cascadeScore(a, threshold) > cascadeScore(b, threshold);
});
```

Lien avec le cours :

- même philosophie que le max probabiliste : on utilise un petit échantillon pour trouver un "champion" ;
- puis on filtre/réordonne le reste ;
- travail faible, profondeur faible, bonne efficacité pratique.

---

### 4.5. Randomisation contrôlée du move ordering

Un ordre déterministe peut tomber dans des pires cas. Ajouter un bruit faible dans les égalités permet d'explorer des
variations différentes.

```cpp
score += randomTieBreaker(seed, mv) % 8;
```

Utilisations :

- Lazy SMP : chaque thread a un seed différent ;
- self-play : éviter que deux IA identiques répètent toujours les mêmes parties ;
- benchmark probabiliste : mesurer la robustesse moyenne.

Lien avec le cours :

- l'aléatoire vient de l'algorithme, pas de l'entrée ;
- on peut fixer les seeds pour rendre les expériences reproductibles.

---

### 4.6. Dérandomisation des rollouts

Si une idée probabiliste marche bien, on peut la rendre déterministe par une méthode inspirée des **espérances
conditionnelles**.

Exemple :

- rollout aléatoire choisit entre plusieurs politiques : `gain`, `mobility`, `stability`;
- au lieu de tirer au hasard, on calcule l'espérance approximative du résultat de chaque choix ;
- on prend le choix qui conserve la meilleure espérance.

Version pratique :

```text
pour chaque coup candidat:
    score = moyenne pondérée déterministe de plusieurs politiques
choisir le max
```

Cela transforme une politique de rollout aléatoire en politique déterministe stable, tout en gardant l'idée qui l'a
produite.

---

### 4.7. Las Vegas pour les hashs : vérifier les collisions

Zobrist Hashing avec 64 bits est presque sûr, mais pas mathématiquement impossible à collisionner.

Version Monte-Carlo :

- on fait confiance au hash.

Version Las Vegas :

- on stocke le hash ;
- on stocke aussi les bitboards complets ou une signature secondaire ;
- au moment du `probe`, on vérifie que l'entrée correspond vraiment.

Analogie directe avec Rabin-Karp :

- Rabin-Karp Monte-Carlo signale des candidats par hash ;
- la version Las Vegas vérifie les candidats ;
- ici, la table de transposition signale une position candidate par hash, puis on vérifie.

---

## Plan d'implémentation recommandé

### Étape 1 : moteur d'évaluation fort

Priorité :

1. `immediateGain`;
2. mobilité moi/adversaire ;
3. vulnérabilité ;
4. stabilité ;
5. poids positionnels dépendants de la map ;
6. pondération par phase.

Même sans bitboard, cette étape améliore immédiatement le glouton et alpha-beta.

---

### Étape 2 : move ordering + iterative deepening

Modifier `Strategy::computeBestMove()` pour :

- sauvegarder un coup valide immédiatement ;
- chercher profondeur $1,2,3,\ldots$ ;
- sauvegarder après chaque profondeur terminée ;
- trier les coups avec `immediateGain`, mobilité, PV précédente.

C'est probablement le meilleur ratio effort/gain.

---

### Étape 3 : table de transposition

Ajouter :

- Zobrist Hashing ;
- `TTEntry`;
- stockage `EXACT`, `LOWER`, `UPPER`;
- best move de TT utilisé en premier dans le tri.

---

### Étape 4 : bitboards

Refactoriser les calculs internes de l'IA seulement. Il n'est pas obligatoire de changer `rules` ou `board`.

Conversion au début de `Strategy` :

```cpp
Position p = Position::fromBidiarrays(_blobs, _holes, _current_player);
```

Puis toute la recherche utilise `Position`.

---

### Étape 5 : parallélisme propre

Remplacer `std::async` massif par :

- root parallel avec thread pool ;
- shared atomic alpha ;
- seuil de cascade ;
- annulation coopérative ;
- éventuellement YBWC/Jamboree.

---

### Étape 6 : expérimentation originale

Comparer au moins :

| IA                   | Description                                 |
|----------------------|---------------------------------------------|
| `GreedyMaterial`     | gain immédiat seulement                     |
| `GreedyHeuristic`    | évaluation multi-critères après un coup     |
| `MinMax`             | profondeur fixe                             |
| `AlphaBeta`          | alpha-beta simple                           |
| `AlphaBeta+Ordering` | tri des coups                               |
| `AlphaBeta+TT+ID`    | table + iterative deepening                 |
| `ParallelRoot`       | root parallel                               |
| `YBWC/Jamboree`      | alpha-beta parallèle contrôlé               |
| `MCTS`               | approche probabiliste                       |
| `Hybrid AB+MCTS`     | rollouts aux feuilles ou move ordering MCTS |

Mesures à logger :

- temps moyen par coup ;
- nombre de nœuds visités ;
- nombre de coupures beta ;
- taux de hit de table de transposition ;
- profondeur atteinte ;
- facteur de branchement effectif :

$$
EBF = nodes^{1/depth}
$$

- win-rate en self-play sur plusieurs maps ;
- score final moyen ;
- stabilité des résultats selon les seeds.

---

## Idées les plus originales à valoriser dans le rapport

1. **Jamboree Search en cascade** : chercher $\sqrt{b}$ coups séquentiellement puis paralléliser le reste. Lien très
   fort avec la séance sur les algorithmes en cascade.
2. **YBWC + early termination** : paralléliser alpha-beta malgré sa dépendance de données.
3. **Bitboard + Zobrist Las Vegas** : hash probabiliste mais vérifié.
4. **Échantillonnage en cascade pour le move ordering** : inspiré du maximum probabiliste.
5. **MCTS hybride** : utiliser Monte-Carlo comme estimateur ou comme pré-tri, puis alpha-beta exact.
6. **Work-stealing par sous-arbres** : montrer que les sous-arbres alpha-beta sont déséquilibrés et que le vol de
   travail est plus pertinent qu'un découpage statique.
7. **Heuristique phase-dependent** : matériel en fin de partie, mobilité/territoire/stabilité avant.

---

## Conclusion

Le meilleur chemin technique est :

1. améliorer l'évaluation ;
2. ajouter move ordering + iterative deepening ;
3. ajouter transposition table ;
4. passer en bitboards ;
5. paralléliser avec root parallel puis YBWC/Jamboree ;
6. ajouter une branche probabiliste MCTS ou ProbCut pour l'originalité expérimentale.

Cette progression permet d'obtenir rapidement une IA plus forte, tout en construisant un rapport solide relié aux
concepts du cours : $W,D$, loi de Brent, fork-join, cascade, work-stealing, early termination, Monte-Carlo, Las Vegas et
dérandomisation.
