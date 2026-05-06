# Algorithmique avancée — Single Source of Truth

> Document généré à partir de `course.txt` sans omission volontaire du contenu source.
> Source : `7416` lignes physiques, SHA-256 `03de5b4c269f735045ae8c6620d40d23b0b420ceaf5080192c30838d14a84e37`.
> Les trois premières lignes forment un préambule ; les lignes 4 à 7416 sont structurées en 12 séances.

## Table des matières

- [Séance 1 — Introduction aux algorithmes d'approximation et parallélisme](#seance-1)
    - [Exercice 1 : Sac à dos binaire (Knapsack)](#seance-1-exercice-1)
    - [Exercice 2 : Bin-Packing (Rangement dans des boîtes)](#seance-1-exercice-2)
    - [Exercice 1 — Sac à dos binaire et PTAS](#seance-1-exercice-3)
    - [Exercice 2 — Bin-Packing et First-Fit](#seance-1-exercice-4)
- [Séance 2 — Algorithmes parallèles : modèles, fork-join, travail et profondeur](#seance-2)
    - [Exercice 1 (Le for parallèle) : Vous allez devoir recréer vous-même l'opérateur for// en utilisant un algorithme diviser pour régner. Le but est d'appliquer une fonction sur une plage d'entiers en parallèle et de calculer les métriques $W$ et $D$.](#seance-2-exercice-1)
    - [Exercice 2 (Mélange de tableau) : On part d'un algorithme séquentiel de mélange qui contient des dépendances de données. L'objectif est de trouver une astuce pour paralléliser le calcul en pré-tirant les nombres aléatoires dans un tableau annexe $B$.](#seance-2-exercice-2)
    - [Exercice 3 (Bin-packing et First-Fit) : Vous chercherez à paralléliser l'algorithme de rangement de boîtes (vu à la séance 1) avec une approche diviser pour régner et des fusions parallèles.](#seance-2-exercice-3)
    - [Exercice 1 — For Parallèle](#seance-2-exercice-4)
    - [Exercice 2 — Mélange aléatoire d'un tableau](#seance-2-exercice-5)
    - [Exercice 3 — Bin-packing First-Fit en diviser pour régner](#seance-2-exercice-6)
- [Séance 3 — Tri fusion parallèle et calcul de préfixe](#seance-3)
    - [Exercice 1 : Le marché boursier](#seance-3-exercice-1)
    - [Exercice 2 : Parenthésage](#seance-3-exercice-2)
    - [Exercice 1 — Le Marché](#seance-3-exercice-3)
    - [Exercice 2 — Parenthésage](#seance-3-exercice-4)
- [Séance 4 — Ordonnancement par vol de travail et interruptions parallèles](#seance-4)
    - [Exercice 1 — Le Premier Élément](#seance-4-exercice-1)
    - [Exercice 2 — Addition Parallèle Binaire](#seance-4-exercice-2)
- [Séance 5 — OpenMP, MapReduce et modèles de filtrage](#seance-5)
    - [Exercice 1 : Count and Say](#seance-5-exercice-1)
    - [Exercice 2 : Le cache LRU](#seance-5-exercice-2)
    - [Exercice 1 — Count and Say](#seance-5-exercice-3)
    - [Exercice 2 — Le cache LRU](#seance-5-exercice-4)
- [Séance 6 — Algorithmes en cascade et optimisation extrême](#seance-6)
    - [Exercice 1 : Toutes les puissances](#seance-6-exercice-1)
    - [Exercice 2 : Préfixe de Ladner-Fisher](#seance-6-exercice-2)
    - [Exercice 1 : Toutes les puissances ($x^0, x^1, x^2, \dots, x^n$)](#seance-6-exercice-3)
    - [Exercice 2 : Préfixe de Ladner-Fisher](#seance-6-exercice-4)
    - [Exercice 1 — Toutes les Puissances](#seance-6-exercice-5)
    - [Exercice 2 — Préfixe parallèle en profondeur log n](#seance-6-exercice-6)
- [Séance 7 — Algorithmes probabilistes : Las Vegas, Monte-Carlo, Atlantic City](#seance-7)
- [Séance 8 — Techniques d'analyse probabiliste, chaînes de Markov et vol de travail](#seance-8)
- [Séance 9 — Dérandomisation et complexité interactive](#seance-9)
    - [Exercice 1 – Recherche probabiliste de chaîne (Rabin-Karp)](#seance-9-exercice-1)
    - [Exercice 2 – Fonction de hachage parfaite](#seance-9-exercice-2)
    - [Exercice 3 – Approximation de MAX-3-LIN](#seance-9-exercice-3)
    - [Exercice 1 — Rabin-Karp](#seance-9-exercice-4)
    - [Exercice 2 — Hachage parfait à 2 niveaux](#seance-9-exercice-5)
    - [Exercice 3 — MAX-3-LIN](#seance-9-exercice-6)
- [Séance 10 — Introduction à la complexité, classes P/NP et réductions](#seance-10)
    - [1. Couvertures, cliques et stables dans un graphe](#seance-10-exercice-1)
    - [2. Montrer que \text{CLIQUE} \leq_P \text{INDEPENDENT-SET}](#seance-10-exercice-2)
    - [3. Montrer que \text{INDEPENDENT-SET} \leq_P \text{VERTEX-COVER}](#seance-10-exercice-3)
    - [4. Si l’un des trois problèmes n’a pas d’algorithme polynomial, alors aucun des trois n’en a](#seance-10-exercice-4)
    - [5. Problèmes de calcul de cardinal optimal et problème de décision CLIQUE](#seance-10-exercice-5)
    - [6. Problèmes d’optimisation : trouver une solution optimale](#seance-10-exercice-6)
    - [7. Autre représentation du graphe](#seance-10-exercice-7)
    - [2. Programmation linéaire en nombres entiers et ordonnancement](#seance-10-exercice-8)
    - [1. Taille de l’entrée](#seance-10-exercice-9)
    - [2. Montrer que \text{ORDONNANCEMENT} \leq_P \text{ILP}](#seance-10-exercice-10)
- [Séance 11 — Complexité partie 2 : SAT, inapproximabilité et P-complétude](#seance-11)
    - [Exercice 1 — Taille de la sortie d’un algorithme en espace logarithmique](#seance-11-exercice-1)
    - [Exercice 2 — Montrer que \{a^n b^n : n\geq 0\}\in L](#seance-11-exercice-2)
    - [Exercice 3 — Montrer que CHEMIN appartient à NL](#seance-11-exercice-3)
    - [Exercice 4 — Montrer que X\leq_L Y et Y\in L implique X\in L](#seance-11-exercice-4)
    - [Exercice 5 — Montrer que CHEMIN est NL-complet et en déduire NL\subseteq P](#seance-11-exercice-5)
    - [Exercice 1 — Montrer que HORN-SAT appartient à P](#seance-11-exercice-6)
    - [Exercice 2 — Montrer que HORN-SAT est P-complet](#seance-11-exercice-7)
- [Séance 12 — Complexité 3 : arbre des réductions et inapproximabilité](#seance-12)
    - [1.1. Si Partition est NP-complet, prouver que Ordonnancement est NP-complet](#seance-12-exercice-1)
    - [1.2. Si Somme est NP-complet, prouver que Partition et Ordonnancement sont NP-complets](#seance-12-exercice-2)
    - [1.3. Réduction de Somme vers Sac à dos](#seance-12-exercice-3)
    - [1.4. Sac à dos approximable en O(n^{k+1}) avec ratio 1+\frac{1}{k}. Qu’en déduire ?](#seance-12-exercice-4)
    - [2.1. Écrire VC-dec, le problème de décision correspondant](#seance-12-exercice-5)
    - [2.2. Réduction du Cycle hamiltonien vers VC-dec](#seance-12-exercice-6)
    - [2.3. Montrer que VC est inapproximable sauf si P=NP](#seance-12-exercice-7)

## Préambule source

C'est tout à fait normal de s'y perdre quand les notes au tableau fusent dans tous les sens ! L'algorithmique avancée (
et particulièrement la théorie de la complexité et de l'approximation) demande beaucoup de rigueur dans les définitions.
Je vous ai rédigé un cours structuré, mis au propre et détaillé, basé sur vos notes et les documents fournis. Cela vous
fera une excellente fiche de révision pour votre examen où tous les documents sont autorisés.

<a id="seance-1"></a>

## Séance 1 — Introduction aux algorithmes d'approximation et parallélisme

> Plage source conservée : lignes `4` à `297` de `course.txt`.

### Partie Théorique

#### Séance 1 : Introduction aux Algorithmes d'Approximation et Parallélisme

L'objectif principal du cours : Face à des problèmes d'optimisation dits "difficiles" (souvent NP-complets, où trouver
la solution exacte prendrait un temps exponentiel dans le pire des cas), on renonce à trouver la solution parfaite.
L'idée est de concevoir un algorithme polynomial qui trouve une solution approchée, mais avec une garantie mathématique
sur sa qualité par rapport à l'optimum.

1. Concepts Fondamentaux et Ratios de Performance
   Un problème d'optimisation cherche à minimiser ou maximiser une valeur. Pour évaluer la qualité d'un algorithme d'
   approximation $A$, on compare la valeur de sa solution $val(A(e))$ à la valeur de la solution optimale $val(opt(e))$
   pour une entrée $e$.
   Le rapport de performance (ou ratio d'approximation), souvent noté $\rho$, mesure l'écart maximal entre le coût de la
   solution produite par l'algorithme et le coût de l'optimum.


* Pour un problème de MINIMISATION : L'algorithme $A$ est une $\rho$-approximation si, pour toute entrée $e$:
  $$\frac{val(A(e))}{val(opt(e))} \le \rho$$

(Le ratio est toujours $\ge 1$. Plus il est proche de 1, meilleur est l'algorithme).

* Pour un problème de MAXIMISATION : L'algorithme $A$ est une $\rho$-approximation si, pour toute entrée $e$ :
  $$\frac{val(opt(e))}{val(A(e))} \le \rho$$

(Ici aussi, le ratio défini ainsi est $\ge 1$).

2. Les Schémas d'Approximation (Familles d'algorithmes)
   Un schéma d'approximation est un algorithme qui prend en paramètre l'instance du problème ET une
   valeur $\epsilon > 0$ qui fixe la précision souhaitée. Plus on veut être précis (petit $\epsilon$), plus le temps de
   calcul augmente. On les classe selon leur complexité temporelle par rapport à la taille de l'entrée $n$ et
   à $\epsilon$ :

| Acronyme | Nom complet                          | Complexité temporelle (exemples)  | Propriétés                                                                                                                           |
|----------|--------------------------------------|-----------------------------------|--------------------------------------------------------------------------------------------------------------------------------------|
| PTAS     | Polynomial Time Approximation Scheme | $O(n^{f(1/\epsilon)})$            | Le temps est polynomial par rapport à $n$ pour un $\epsilon$ fixé. Exemple : Algorithme $AB_k$ pour le sac à dos.                    |
| EPTAS    | Efficient PTAS                       | $O(f(1/\epsilon) \cdot n^{O(1)})$ | Amélioration du PTAS. La dépendance en $\epsilon$ est séparée de l'exposant de $n$, ce qui le rend beaucoup plus rapide en pratique. |
| FPTAS    | Fully PTAS                           | $O((n/\epsilon)^{O(1)})$          | Variante très performante où la complexité est polynomiale à la fois en $n$ et en $1/\epsilon$.                                      |

3. Exemple Détaillé 1 : La Couverture de Sommets (Vertex Cover)
   C'est un problème classique de minimisation.

*

Entrée : Un graphe non orienté $G = (V, E)$ avec $V$ l'ensemble des sommets et $E$ l'ensemble des arêtes.

*

Sortie : Un sous-ensemble de sommets $C \subseteq V$ tel que pour chaque arête $(u, v) \in E$, au moins $u$ ou $v$
appartient à $C$.

*

Objectif : Trouver une couverture $C$ de taille minimale.

L'Algorithme Glouton (Couverture-sommet approché)
Cet algorithme simple fournit une 2-approximation.

1. On initialise $C = \emptyset$.


2. Tant qu'il reste des arêtes non couvertes dans $E$:

    * Choisir une arête arbitraire $(u, v)$.


    * Ajouter $u$ et $v$ à $C$.
    * Supprimer du graphe toutes les arêtes incidentes à $u$ et à $v$ (puisqu'elles sont maintenant couvertes).

3. Retourner $C$.

Preuve du ratio d'approximation $\rho \le 2$
C'est ici que réside le cœur de l'algorithmique avancée : prouver que notre heuristique n'est pas "trop mauvaise".
Puisqu'on ne connaît pas la valeur de la solution optimale $|C^*|$, on doit trouver un minorant de l'optimal.

* Soit $X$ l'ensemble des arêtes sélectionnées par notre algorithme à l'étape 2.
* Par construction, aucune des arêtes de $X$ ne partage de sommet (puisqu'on supprime les arêtes incidentes à chaque
  étape).
* Pour couvrir ces arêtes indépendantes $X$, la solution optimale $C^*$ est obligée de prendre au moins un sommet pour
  chaque arête de $X$. Donc $|C^*| \ge |X|$.
* Notre algorithme, lui, a pris exactement 2 sommets pour chaque arête de $X$. Donc la taille de notre solution
  est $|C| = 2|X|$.
* En combinant les deux :
  $$\frac{|C|}{|C^*|} \le \frac{2|X|}{|X|} \le 2$$


4. Exemple Détaillé 2 : Parallélisme et Ordonnancement
   Problème de minimisation du temps de complétion (makespan).

* Modèle : On a un ensemble de tâches de durée 1, des dépendances entre elles (certaines doivent être finies avant de
  commencer d'autres), et $m$ processeurs identiques.
* Algorithme (Ordonnancement de liste) : Dès qu'un processeur est inactif, on lui affecte la première tâche disponible
  dont les dépendances sont résolues.
  Preuve du ratio d'approximation
  On cherche à borner le temps de complétion de l'algorithme ($C_{max}$) par rapport à l'optimal ($C_{max}^*$).

1. Borner l'optimal : Soit $W$ le travail total (nombre de tâches) et $D$ la profondeur (le chemin critique, la plus
   longue chaîne de dépendances).
    * Même avec une infinité de processeurs, le temps minimal est dicté par la chaîne de
      dépendances : $C_{max}^* \ge D$.
    * Même s'il n'y a aucune dépendance, on a $W$ tâches à répartir sur $m$ processeurs : $C_{max}^* \ge W/m$.
2. Analyser l'algorithme : Notre algorithme de liste ne laissera un processeur inactif que s'il attend une dépendance (
   ce qui contribue à $D$). Dans le pire des cas, le temps total est borné par la somme du temps de traitement
   parfaitement réparti et du temps d'attente dû aux dépendances : $C_{max} \le W/m + D$.
3. Calcul du ratio :
   $$\frac{C_{max}}{C_{max}^*} \le \frac{W/m + D}{C_{max}^*} = \frac{W/m}{C_{max}^*} + \frac{D}{C_{max}^*} \le 1 + 1 = 2$$

L'ordonnancement de liste est donc une 2-approximation.

5. Lien avec votre TD
   Votre TD met en pratique ces notions sur deux problèmes classiques :

*

<a id="seance-1-exercice-1"></a>

##### Exercice 1 : Sac à dos binaire (Knapsack)

    *

Problème : Maximiser le gain d'un sac de volume $V$ avec des objets de volume $v_i$ et de gain $g_i$.

    * L'algorithme glouton classique ("Ali Baba") trie les objets par densité de gain ($g_i/v_i$). Le TD démontre que cet algorithme est arbitrairement mauvais (il n'a pas de ratio fini).


    * Cependant, le TD construit une famille d'algorithmes $AB_k$ qui testent toutes les combinaisons de $k$ objets et complètent avec l'algorithme glouton. Le TD démontre que le ratio tend vers 1 (ratio de $1 + 1/k$), ce qui en fait un PTAS parfait !

*

<a id="seance-1-exercice-2"></a>

##### Exercice 2 : Bin-Packing (Rangement dans des boîtes)

    *

Problème : Minimiser le nombre de sacs de taille 1 pour ranger $n$ objets de taille $s_i$.

    * L'algorithme First-Fit (mettre l'objet dans le premier sac où il rentre) est prouvé comme étant une 2-approximation.


    * Une variante abordée est le First-Fit Decreasing (FFD) qui trie d'abord les objets du plus grand au plus petit, améliorant drastiquement le ratio d'approximation autour de 1.22.

Voulez-vous que l'on s'attaque à la résolution détaillée et rédigée de l'exercice 1 du TD (le Sac à dos et la
démonstration du PTAS) pour vous entraîner aux preuves de ratio ?

### Partie Pratique (TD)

#### TD — Algorithmes d'Approximation · Correction Pédagogique Complète

🗺️ Vue d'ensemble de la feuille
Thèmes abordés :

* Algorithmique d'approximation : notion de ratio d'approximation
* Problème du sac à dos binaire (NP-difficile) et construction d'un PTAS
* Problème du bin-packing et analyse de l'heuristique First-Fit
  Compétences clés requises :
* Comprendre pourquoi certains problèmes sont NP-difficiles (pas de solution polynomiale exacte connue)
* Analyser un algorithme glouton et ses limites
* Maîtriser la notion de ratio d'approximation $\rho$ : un algorithme est $\rho$-approché si pour toute
  instance, $\text{solution retournée} \geq \frac{1}{\rho} \cdot \text{solution optimale}$ (pour un problème de
  maximisation)
* Raisonner par inégalités pour borner la qualité d'une solution

<a id="seance-1-exercice-3"></a>

##### Exercice 1 — Sac à dos binaire et PTAS

Reformulation du problème
On a un sac de capacité $V$ et $n$ objets, chacun avec un volume $v_i$ et un gain $g_i$. On veut maximiser le gain total
des objets choisis sans dépasser la capacité $V$. Les objets sont triés par gain volumique
décroissant : $\frac{g_1}{v_1} \geq \frac{g_2}{v_2} \geq \cdots \geq \frac{g_n}{v_n}$.
L'algorithme glouton Ali Baba ajoute les objets dans cet ordre si ils rentrent dans le sac.

###### Question 1 — Ali Baba n'admet pas de ratio fini

Ce qui est demandé : Trouver une instance où Ali Baba est arbitrairement mauvais.
Stratégie : Construire un contre-exemple où l'optimal est très grand mais Ali Baba renvoie quelque chose de très petit.
Résolution :
Prenons $n = 2$, $(g_1, v_1) = (1, 2)$ et $(g_2, v_2) = (V, V)$ avec $V > 2$.
D'abord, vérifions l'ordre de tri par gain
volumique : $$\frac{g_1}{v_1} = \frac{1}{2}, \quad \frac{g_2}{v_2} = \frac{V}{V} = 1$$
⚠️ Ici $\frac{g_2}{v_2} > \frac{g_1}{v_1}$, donc l'ordre correct serait objet 2 en premier. Mais le sujet impose cet
exemple, il faut interpréter $V = 2$ ou prendre $(g_1, v_1) = (V, V)$ vs $(g_2, v_2) = (1, 2)$... Reprenons plus
soigneusement.
Bonne instance : Prenons $(g_1, v_1) = (1, 1)$ et $(g_2, v_2) = (V, V)$ avec sac de capacité $V$.

* Gain volumique : $\frac{g_1}{v_1} = 1$ et $\frac{g_2}{v_2} = 1$. Ou simplement posons $(g_1, v_1) = (1, 2)$
  et $(g_2, v_2) = (V, V)$ avec $V$ pair et $V \geq 4$.
  Utilisons exactement les données du sujet : $n=2$, $(g_1,v_1)=(1,2)$, $(g_2,v_2)=(V,V)$.
* Ordre de tri : $\frac{g_1}{v_1} = \frac{1}{2}$, $\frac{g_2}{v_2} = 1$. Donc l'objet 2 devrait être en premier si on
  trie... Le sujet suppose que l'indexation est déjà triée, donc il faut accepter cet exemple tel quel (Ali Baba
  parcourt dans l'ordre 1, 2).
  Exécution d'Ali Baba :
* $L = V$, $i = 1$ : $v_1 = 2 \leq V$ → on ajoute l'objet 1 : $L = V - 2$, $\phi = 1$
* $i = 2$ : $v_2 = V > V - 2$ → on ne peut pas ajouter l'objet 2
  Ali Baba retourne un gain de $\phi = 1$.
  Solution optimale : On peut mettre l'objet 2 seul (il rentre car $v_2 = V$), avec un gain de $\bar\Phi = V$.
  Ratio : $$\frac{\bar\Phi}{\phi} = \frac{V}{1} = V \xrightarrow{V \to \infty} +\infty$$
  💡 Intuition : Ali Baba est "aveuglé" par l'objet 1 (meilleur ratio volumique local) et bloque l'entrée de l'objet 2
  très lucratif. C'est la limite classique des algorithmes gloutons.

###### Question 2 — L'algorithme AB0 est 2-approché

Ce qui est demandé : Montrer $\bar\Phi < \sum_{i=1}^{s-1} g_i + g_s$, puis en déduire le ratio 2.
Définitions :

* $s$ = premier objet que Ali Baba ne met pas dans le sac
* Les objets $1, \ldots, s-1$ sont dans le sac d'Ali Baba
* L'objet $s$ ne rentre pas : $\sum_{i=1}^{s} v_i > V$
  AB0 retourne $\gamma_0 = \max\left{\sum_{i=1}^{s-1} g_i,\ g_s\right}$.
  Étape 1 : Montrer $\bar\Phi < \sum_{i=1}^{s-1} g_i + g_s$
  Notons $S_{opt}$ une solution optimale de valeur $\bar\Phi$. Considérons la solution fractionnaire (sac à dos
  continu) : on peut prendre tous les objets $1, \ldots, s-1$ (ils rentrent dans le sac d'Ali Baba,
  donc $\sum_{i=1}^{s-1} v_i \leq V$) et une fraction de l'objet $s$.
  Raisonnement clé : Puisque les objets sont triés par ratio décroissant $\frac{g_i}{v_i}$, le sac à dos fractionnel
  optimal prend les $s-1$ premiers objets entièrement plus une fraction de
  l'objet $s$ : $$\bar\Phi^{frac} = \sum_{i=1}^{s-1} g_i + \frac{V - \sum_{i=1}^{s-1} v_i}{v_s} \cdot g_s$$
  Comme $\bar\Phi \leq \bar\Phi^{frac}$ (le fractionnel est plus puissant que le binaire) et la fraction de $s$
  est $< 1$ (sinon $s$ rentrerait dans le sac d'Ali Baba), on
  a : $$\bar\Phi \leq \bar\Phi^{frac} < \sum_{i=1}^{s-1} g_i + g_s$$
  Étape 2 : Déduire le ratio 2
  On sait que $\bar\Phi < \sum_{i=1}^{s-1} g_i + g_s$.
  Or : $\sum_{i=1}^{s-1} g_i + g_s \leq 2 \cdot \max\left{\sum_{i=1}^{s-1} g_i,\ g_s\right} = 2\gamma_0$
  (car $a + b \leq 2\max(a,b)$ pour tous réels positifs $a, b$).
  Donc : $$\bar\Phi < 2\gamma_0 \implies \frac{\bar\Phi}{\gamma_0} < 2 \implies \gamma_0 > \frac{\bar\Phi}{2}$$
  AB0 est donc bien une 2-approximation.
  💡 Astuce clé : L'inégalité $a + b \leq 2\max(a,b)$ est très classique dans les preuves d'approximation. Retenez-la !

###### Question 3 — AB1 est 2-approché et meilleur qu'Ali Baba

Ce qui est demandé : Justifier que AB1 (qui teste chaque objet $i$ en tête, puis complète avec Ali Baba) est 2-approché
et $\geq$ Ali Baba.
AB1 est meilleur qu'Ali Baba :
Parmi les $n$ solutions testées par AB1, l'une d'elles est la solution d'Ali Baba seul (en choisissant un $i$ qui serait
le premier objet d'Ali Baba). Plus précisément, AB1 teste aussi la combinaison avec le premier objet que Ali Baba
prendrait, puis complète avec les autres. Donc $\gamma_1 \geq \phi(E, V)$.
AB1 est 2-approché :
On reprend la même analyse qu'AB0. AB1 teste en particulier la combinaison $C = {s}$ (l'objet $s$ seul) et complète par
Ali Baba sur $E - {s}$ avec capacité $V - v_s$.
Mais surtout, AB1 inclut AB0 dans ses solutions testées :

* Si $C = {s}$ : gain = $g_s + \phi(E - {s}, V - v_s) \geq g_s$
* Ali Baba prend les objets $1, \ldots, s-1$, donc l'une des solutions testées contient ces $s-1$ objets + objet $i$
  quelconque = au moins $\sum_{i=1}^{s-1} g_i$
  Donc $\gamma_1 \geq \gamma_0 > \frac{\bar\Phi}{2}$ et AB1 est 2-approché.
  💡 Idée pédagogique : AB1 est un "super-AB0" : il tente plus de combinaisons, donc son résultat est au moins aussi bon.

###### Question 4 — Si $S_{opt}$ a $\leq k$ objets, $\gamma_k = \bar\Phi$

Ce qui est demandé : Que vaut $\gamma_k$ si la solution optimale $S_{opt}$ contient au plus $k$ objets ?
Réponse :
ABk teste toutes les combinaisons de 1 à $k$ objets rentrant dans le sac. Si $S_{opt}$ a au plus $k$ objets, c'est une
combinaison testée par ABk. Il complète alors avec Ali Baba sur les objets restants, mais comme $S_{opt}$ est déjà la
solution optimale, Ali Baba ne peut qu'ajouter 0 ou du gain supplémentaire (il ne retire pas d'objets).
Donc ABk trouve (au moins) $S_{opt}$, et comme il maximise sur toutes les combinaisons : $$\gamma_k \geq \bar\Phi$$
Mais $\gamma_k \leq \bar\Phi$ par définition de l'optimum. Donc :
$$\boxed{\gamma_k = \bar\Phi}$$
💡 Intuition : Si la solution optimale est "petite" (peu d'objets), ABk la trouve exactement ! Le problème n'apparaît que
quand $S_{opt}$ est grande.

###### Question 5 — Analyse du ratio quand $S_{opt}$ a $\geq k+1$ objets

C'est la question centrale et la plus délicate. Lisons attentivement les notations :

* $X$ = les $k$ objets de $S_{opt}$ avec les gains les plus élevés
* ABk teste la combinaison $X$ (car $|X| = k$ et $X \subseteq S_{opt}$ rentre dans le sac)
* Ali Baba complète $X$ avec les objets restants (par ratio volumique décroissant)
* $s$ = premier objet de $S_{opt} \setminus X$ que Ali Baba n'arrive pas à mettre après $X$
* $G$ = objets pris par Ali Baba pour compléter $X$ (jusqu'à bloquer sur $s$)

###### Question 5.1 — Montrer la double inégalité

$$\sum_{i \in X \cup G} g_i \leq \gamma_k \leq \bar\Phi < g_s + \sum_{i \in X \cup G} g_i$$
Partie gauche : $\sum_{i \in X \cup G} g_i \leq \gamma_k$
ABk teste la combinaison $C = X$ et la complète par Ali Baba, qui prend les objets de $G$. Donc la valeur de cette
combinaison est $\sum_{i \in X} g_i + \phi(E - X, V - \sum_{i \in X} v_i) \geq \sum_{i \in X \cup G} g_i$. Comme ABk
prend le maximum sur toutes les combinaisons : $$\gamma_k \geq \sum_{i \in X \cup G} g_i$$
Partie milieu : $\gamma_k \leq \bar\Phi$
Trivial : ABk ne peut pas faire mieux que l'optimal.
Partie droite : $\bar\Phi < g_s + \sum_{i \in X \cup G} g_i$
Même raisonnement qu'à la question 2 ! Après avoir placé $X \cup G$, le volume restant
est $V' = V - \sum_{i \in X \cup G} v_i$. L'objet $s \in S_{opt} \setminus X$ ne rentre pas dans ce volume restant (par
définition de $s$). Le gain maximal réalisable avec les objets de $S_{opt} \setminus X$ est borné par le
fractionnel : $$\sum_{i \in S_{opt} \setminus X} g_i \leq \sum_{i \in G} g_i + g_s$$
(les objets de $G$ ont un meilleur ratio que $s$ et remplissent le sac avant $s$, par l'argument du sac à dos
fractionnel).
Donc : $$\bar\Phi = \sum_{i \in X} g_i + \sum_{i \in S_{opt} \setminus X} g_i < \sum_{i \in X} g_i + \sum_{i \in G} g_i + g_s = \sum_{i \in X \cup G} g_i + g_s$$

###### Question 5.2 — Montrer $\sum_{i \in X} g_i \geq k \cdot g_s$ et en déduire le ratio

Montrons $\sum_{i \in X} g_i \geq k \cdot g_s$ :
Rappel : $X$ contient les $k$ objets de $S_{opt}$ avec les gains maximaux. Or $s \in S_{opt} \setminus X$, donc $s$ est
un objet de $S_{opt}$ non retenu dans $X$, ce qui signifie que tous les objets de $X$ ont un gain $\geq g_s$.
Formellement : $\forall i \in X$, $g_i \geq g_s$ (car $X$ contient les $k$ plus grands gains de $S_{opt}$
et $s \notin X$). Donc : $$\sum_{i \in X} g_i \geq k \cdot g_s \implies g_s \leq \frac{1}{k} \sum_{i \in X} g_i$$
Déduire le ratio :
De la question 5.1 : $\bar\Phi < g_s + \sum_{i \in X \cup G} g_i$
On remplace $g_s \leq \frac{1}{k} \sum_{i \in X} g_i \leq \frac{1}{k} \sum_{i \in X \cup G} g_i$ :
$$\bar\Phi < \frac{1}{k} \sum_{i \in X \cup G} g_i + \sum_{i \in X \cup G} g_i = \left(1 + \frac{1}{k}\right) \sum_{i \in X \cup G} g_i$$
Et puisque $\gamma_k \geq \sum_{i \in X \cup G} g_i$ :
$$\bar\Phi < \left(1 + \frac{1}{k}\right) \gamma_k \implies \frac{\bar\Phi}{\gamma_k} < 1 + \frac{1}{k}$$
$$\boxed{\gamma_k > \frac{\bar\Phi}{1 + \frac{1}{k}} = \frac{k}{k+1}\bar\Phi}$$
💡 Astuce clé : Choisir les $k$ meilleurs objets de $S_{opt}$ dans $X$ permet de borner $g_s$ par $\frac{1}{k}$ de leur
somme. Plus $k$ est grand, plus cette borne est serrée et meilleur est le ratio !

###### Question 6 — Conclusion sur le PTAS

ABk est polynomial :
Pour chaque combinaison de taille $\leq k$, il y a $O(n^k)$ combinaisons possibles. Chaque Ali Baba coûte $O(n)$. Donc
le coût total est $O(n^{k+1})$ — polynomial en $n$ pour $k$ fixé.
Le ratio tend vers 1 :
$$\text{ratio}(AB_k) = 1 + \frac{1}{k} \xrightarrow{k \to \infty} 1$$
Conclusion : $(AB_k)_{k \in \mathbb{N}}$ est un PTAS (Polynomial Time Approximation Scheme) :

* Pour tout $\varepsilon > 0$, prendre $k = \lceil 1/\varepsilon \rceil$ donne un algorithme polynomial de
  ratio $1 + \varepsilon$
* On peut approcher l'optimal aussi près que voulu, au prix d'une complexité $O(n^{1/\varepsilon + 1})$
  💡 Conclusion philosophique : Bien que le sac à dos soit NP-difficile (pas de solution exacte polynomiale sauf
  si $P=NP$), l'existence d'un PTAS montre qu'on peut l'approcher polynomialement avec un ratio arbitrairement proche de
  1. C'est une des distinctions subtiles de la théorie de la complexité !

<a id="seance-1-exercice-4"></a>

##### Exercice 2 — Bin-Packing et First-Fit

Reformulation du problème
On a $n$ objets de taille $s_i \in (0, 1)$ à ranger dans des sacs de taille 1 (capacité unitaire). On veut minimiser le
nombre de sacs. $C^*$ = optimal, $C$ = résultat de First-Fit.
First-Fit : Pour chaque objet, on le place dans le premier sac qui a encore assez de place.

###### Question 1 — Minorant de $C^*$

Ce qui est demandé : Montrer $C^* \geq \lceil \sum_{i=1}^n s_i \rceil$.
Stratégie : Argument de volume total.
Résolution :
Chaque sac a une capacité de 1. Avec $C^$ sacs, le volume total disponible est $C^$. Or on doit loger tous les objets de
volume total $\sum s_i$.
Donc : $C^* \geq \sum_{i=1}^n s_i$.
Comme $C^$ est un entier : $C^ \geq \lceil \sum_{i=1}^n s_i \rceil$.
⚠️ Erreur classique : Oublier le plafond $\lceil \cdot \rceil$ ! $C^*$ est un entier, donc l'inégalité s'arrondit vers
le haut.

###### Question 2 — First-Fit laisse au plus un sac à moitié vide

Ce qui est demandé : Montrer qu'au plus 1 sac est rempli à moins de moitié, et en
déduire $C \leq \lceil 2 \sum s_i \rceil$.
Raisonnement clé (par l'absurde) :
Supposons qu'il y ait deux sacs $A$ et $B$ avec chacun un remplissage $\leq \frac{1}{2}$.
Cela signifie que le dernier objet ajouté dans $B$ n'a pas été mis dans $A$ (sinon $A$ aurait un
remplissage $> \frac{1}{2}$). Or First-Fit aurait essayé $A$ avant $B$ (ou $A$ était plein au moment d'ajouter
dans $B$).
Mais si $A$ est rempli à $\leq \frac{1}{2}$ et le dernier objet de $B$ a une taille $\leq$ capacité restante de $A$ (qui
est $\geq \frac{1}{2}$)... First-Fit l'aurait mis dans $A$ !
Formellement : Si deux sacs $A$ et $B$ ont chacun un contenu $< \frac{1}{2}$, les objets de $B$ auraient pu entrer
dans $A$ (puisque place $> \frac{1}{2}$ dans $A$ et objets $< \frac{1}{2}$ dans $B$). First-Fit aurait placé les objets
de $B$ dans $A$ en premier → contradiction.
Donc au plus 1 sac est rempli à moins de $\frac{1}{2}$.
Déduire $C \leq \lceil 2 \sum s_i \rceil$ :
Volume total des objets : $\sum s_i$.

* Les $C - 1$ sacs "bien remplis" contiennent chacun $> \frac{1}{2}$, donc : $(C-1) \cdot \frac{1}{2} < \sum s_i$
* Ce qui donne : $C < 2 \sum s_i + 1$, donc $C \leq \lfloor 2\sum s_i \rfloor \leq \lceil 2 \sum s_i \rceil$

###### Question 3 — First-Fit est une 2-approximation

De Q1 et Q2 :
$$C^* \geq \left\lceil \sum s_i \right\rceil \geq \frac{\sum s_i + 1}{2} \cdot \frac{2}{1}$$
Plus directement :
$$C \leq \left\lceil 2 \sum s_i \right\rceil \leq 2 \left\lceil \sum s_i \right\rceil \leq 2 C^*$$
Donc : $\frac{C}{C^*} \leq 2$
First-Fit est bien une 2-approximation.

###### Question 4 — Exemple où First-Fit est optimal

Exemple simple : Tous les objets ont une taille $\frac{1}{2}$.

* $n = 2k$ objets de taille $\frac{1}{2}$
* First-Fit remplit les sacs 2 par 2 → $k$ sacs
* Optimal = $k$ sacs
* First-Fit = optimal ✓
  Autre exemple : objets de tailles décroissantes qui s'emboîtent parfaitement.

###### Question 5 — Exemple où First-Fit atteint le ratio 2 (asymptotiquement)

Construction : Prenons $2n$ objets : $n$ objets de taille $\frac{1}{2} + \varepsilon$ (légèrement plus d'un demi).

* Optimal : On ne peut mettre qu'un seul objet par sac → $C^* = 2n$ ... Non, attendons.
  Meilleur exemple classique pour ratio $\to 2$ :
* $n$ objets de taille $\frac{1}{2} + \varepsilon$
* $n$ objets de taille $\frac{1}{2} - \varepsilon$ (légèrement moins d'un demi), présentés dans l'ordre : tous les "
  grands" d'abord, puis tous les "petits"
  Avec First-Fit (ordre : grands d'abord, puis petits) :
* Les $n$ grands objets ($\frac{1}{2}+\varepsilon$) : 1 par sac → $n$ sacs, chaque sac avec espace
  libre $\frac{1}{2}-\varepsilon$
* Les $n$ petits objets ($\frac{1}{2}-\varepsilon$) : chaque petit objet $\frac{1}{2}-\varepsilon$ cherche le premier
  sac où il rentre. La place restante dans chaque sac est $\frac{1}{2}-\varepsilon$. Donc chaque petit rentre ! → $n$
  petits dans les $n$ sacs existants.
* Total : $n$ sacs. Optimal aussi $n$ sacs (1 grand + 1 petit par sac). Ratio = 1 ici !
  Exemple qui force le ratio 2 : Prenons $n$ objets de taille $\frac{1}{2}+\varepsilon$, suivis de $n$ objets de
  taille $\frac{1}{n}$ (très petits).
  En fait, l'exemple classique est :
* $6n$ objets : $2n$ de taille $\frac{1}{3}+\varepsilon$, $2n$ de taille $\frac{1}{3}+\varepsilon$, $2n$ de
  taille $\frac{1}{3}+\varepsilon$ — tous semblables...
  L'exemple le plus simple pour illustrer le ratio $\to 2$ :
* $n$ objets de taille juste au-dessus de $\frac{1}{2}$ (disons $\frac{1}{2}+\varepsilon$) présentés un par un
* First-Fit : chaque objet remplit un nouveau sac (car 2 ne rentrent pas ensemble) → $C = n$ sacs, chacun à moitié vide
* Optimal : idem, on ne peut pas faire mieux → $C^* = n$, ratio = 1
  Pour vraiment approcher le ratio 2, il faut une instance où First-Fit crée beaucoup de sacs sous-remplis. Le ratio
  exact est 1.7 (voir Question 6), pas 2.

###### Question 6 — FFD et son analyse

FFD (First Fit Decreasing) : On trie d'abord les objets par taille décroissante, puis on applique First-Fit.
Est-ce plus compliqué à implémenter ?
Très légèrement : il faut ajouter un tri au début. Cela prend $O(n \log n)$ avec un tri classique.
Coût total de FFD :

* Tri : $O(n \log n)$
* First-Fit sur $n$ objets avec $C$ sacs : $O(n \cdot C)$ dans le pire cas (pour chaque objet, on parcourt tous les
  sacs) → $O(n^2)$ dans le pire cas
  Donc : coût de FFD = $O(n^2)$ (dominé par First-Fit, le tri étant négligeable).
  Bilan comparatif :
  | Algorithme | Ratio absolu | Ratio asymptotique | Coût |
  | --- | --- | --- | --- |
  | First-Fit | 1.7 | 1.7 | $O(n^2)$ |
  | FFD | $\frac{4}{3}$ | $\frac{11}{9} \approx 1.22$ | $O(n^2)$ |
  💡 Conclusion : Pour un coût quasi-identique, FFD offre une bien meilleure garantie d'approximation. Le tri est un
  investissement minime pour un gain de ratio significatif !

📋 Résumé Final
Méthodes / techniques clés utilisées

1. Argument de contre-exemple : pour montrer qu'un algo n'a pas de ratio fini
2. Relaxation fractionnaire : le sac à dos fractionnel borne l'optimal binaire
3. Inégalité $a + b \leq 2\max(a,b)$ : pour passer de la somme au max
4. Choix des $k$ meilleurs éléments : pour borner le "petit objet" $s$ par $\frac{1}{k}$ de leur somme
5. Argument de volume : minorant de $C^*$ dans le bin-packing
6. Raisonnement par l'absurde : au plus un sac à moitié vide
   Formules et résultats clés
   $$\text{AB}k \text{ : ratio } = 1 + \frac{1}{k}, \quad \text{coût } O(n^{k+1})$$ $$\bar\Phi < \left(1 + \frac{1}{k}\right)\gamma_k$$ $$C^* \geq \left\lceil \sum s_i \right\rceil, \quad C{FF} \leq \lceil 2\sum s_i \rceil$$ $$\text{FFD : } C \leq \frac{11}{9}C^* + \frac{2}{3}$$
   Pièges fréquents ⚠️
1. Oublier le $\lceil \cdot \rceil$ dans les minorants d'entiers
2. Confondre ratio de maximisation et minimisation : pour la maximisation, $\rho$-approché
   signifie $\text{sol} \geq \frac{\bar\Phi}{\rho}$ ; pour la minimisation, $\text{sol} \leq \rho \cdot C^*$
3. Oublier que $s \notin X$ dans la preuve de $\sum_{i \in X} g_i \geq k \cdot g_s$
4. Croire que trier suffit à améliorer le ratio : FFD est meilleur que FF, mais pas optimal
5. Complexité de ABk : bien noter que le coût est $O(n^{k+1})$, pas $O(k \cdot n)$

🎯 Questions d'entraînement
Q1. Pour le sac à dos avec $k = 3$, quel est le ratio d'approximation de $AB_3$ ? Quelle est sa complexité ?
Réponse : Ratio $= 1 + \frac{1}{3} = \frac{4}{3}$, complexité $O(n^4)$.
Q2. Dans le bin-packing, si $\sum s_i = 7.3$, donnez un minorant de $C^*$.
Réponse : $C^* \geq \lceil 7.3 \rceil = 8$.
Q3. Pourquoi l'existence d'un PTAS pour le sac à dos ne contredit-elle pas le fait que le problème est NP-difficile ?
Réponse : Un PTAS donne des algorithmes polynomiaux pour chaque $\varepsilon > 0$ fixé, mais la
complexité $O(n^{1/\varepsilon})$ explose quand $\varepsilon \to 0$. Ce n'est pas un algorithme exact polynomial.
Q4. Montrez que si tous les objets ont une taille $> \frac{1}{2}$ dans le bin-packing, alors First-Fit est optimal.
Réponse : Chaque sac ne peut contenir qu'un objet (deux objets dépasseraient la capacité 1). First-Fit met un objet par
sac, ce qui est optimal.
Q5. Dans ABk, pourquoi est-il essentiel que $X$ contienne les $k$ objets de gain maximal de $S_{opt}$ (et pas, par
exemple, les $k$ objets de plus petit volume) ?
Réponse : Pour pouvoir borner $g_s \leq \frac{1}{k}\sum_{i \in X} g_i$. Si $X$ contenait les $k$ plus petits
objets, $g_s$ pourrait être bien plus grand que les $g_i$ de $X$, et la borne s'effondrerait.

C'est reparti pour la séance 2 ! L'algorithmique parallèle demande une gymnastique d'esprit un peu différente de
l'algorithmique classique, car il faut penser "en même temps" plutôt que "l'un après l'autre". Vos notes sont denses,
mais elles contiennent tous les piliers de la conception d'algorithmes parallèles.
Voici le cours détaillé et mis au propre pour cette deuxième séance.


---

<a id="seance-2"></a>

## Séance 2 — Algorithmes parallèles : modèles, fork-join, travail et profondeur

> Plage source conservée : lignes `298` à `732` de `course.txt`.

### Partie Théorique

#### Séance 2 : Algorithmes Parallèles (Modèles, Fork-Join, Travail et Profondeur)

Objectif principal : Apprendre à écrire du code hautement parallèle. On s'autorise un nombre polynomial de cœurs pour
atteindre un temps d'exécution (la profondeur) logarithmique ou poly-logarithmique, tout en essayant de garder un coût
total des opérations (le travail) proche de celui de l'algorithme séquentiel de base.

1. Intergiciels et Primitives de Parallélisme
   Pour éviter de gérer manuellement les threads du système d'exploitation, on utilise un intergiciel (une bibliothèque)
   qui gère l'exécution et la synchronisation pour nous.

On s'appuie principalement sur deux primitives :

* join(f1, f2) : Exécute deux fonctions (f1 et f2) en parallèle. Le programme parent attend que les deux soient
  terminées pour récupérer les résultats et continuer.


* for// : Lance toutes les itérations d'une boucle en parallèle. Attention : il est impossible d'utiliser une
  instruction break dans un for//, car toutes les branches s'exécutent simultanément.
  Le graphe Fork-Join : L'exécution de ces programmes se modélise sous la forme d'un graphe orienté acyclique (DAG).


*

Fork : C'est le point où une tâche se divise en plusieurs sous-tâches exécutables en parallèle.

*

Join : C'est le point de synchronisation où les tâches parallèles doivent se rejoindre avant que le programme ne puisse
continuer.

2. Métriques d'Évaluation : Travail ($W$) et Profondeur ($D$)
   Pour jauger l'efficacité théorique d'un algorithme multithread, on n'utilise pas la notation $\mathcal{O}(n)$
   classique, mais deux métriques:


*

Le Travail ($W$) : C'est le temps total pris par l'ensemble des calculs, ce qui correspond au temps qu'il faudrait pour
tout exécuter sur un seul processeur.

    * Règle pour join(A, B) : $W = W_A + W_B$.

*

La Profondeur ($D$) : C'est le temps maximal pris par le plus long chemin (le chemin critique) dans le graphe
d'exécution. Elle représente le temps d'exécution si l'on disposait d'une infinité de processeurs.

    * Règle pour join(A, B) : $D = \max(D_A, D_B)$.


    * Règle pour for// : $D = \max(D_i)$ (la profondeur de la plus longue itération).

Performance sur $p$ processeurs : En supposant que les accès mémoire se font en $\mathcal{O}(1)$ et que le système
utilise un ordonnanceur optimal (par "vol de travail"), le temps d'exécution $T_p$ sur $p$ processeurs est donné par la
loi de Brent :

$$T_p = \frac{W}{p} + \mathcal{O}(D)$$

3. Modèles d'Accès Mémoire
   Quand plusieurs threads accèdent à un même tableau (comme illustré dans votre exemple de recherche d'une valeur v),
   il faut définir comment la machine gère les conflits. Il existe trois grands modèles théoriques :

* EREW (Exclusive Read, Exclusive Write) : Un seul thread à la fois peut lire ou écrire dans une case mémoire. C'est le
  modèle le plus restrictif.
* CREW (Concurrent Read, Exclusive Write) : Plusieurs threads peuvent lire en même temps la même case, mais un seul peut
  y écrire.
* CRCW (Concurrent Read, Concurrent Write) : Plusieurs threads peuvent lire et écrire simultanément (nécessite des
  règles pour définir quelle écriture "gagne").

4. Algorithmes Diviser pour Régner et Amortissement
   L'approche "Diviser pour Régner" est la reine du parallélisme.
   Exemple : Produit itéré d'un tableau
   Au lieu de multiplier les éléments un par un ($W=n$, $D=n$), on coupe le tableau en deux, on lance le produit à
   gauche et à droite en parallèle via un join, puis on multiplie les deux résultats.

* Analyse par le Master Theorem :
    *

$W(n) = 2W(n/2) + \mathcal{O}(1) \implies W(n) = \mathcal{O}(n)$. Le travail reste optimal.

    * $D(n) = D(n/2) + \mathcal{O}(1) \implies D(n) = \mathcal{O}(\log n)$. La profondeur devient excellente !

Le problème des surcoûts (Amortissement) :
En pratique, créer une tâche (un Fork) prend du temps. Si on divise le tableau jusqu'à des sous-tableaux de taille 1, le
coût de création des tâches va détruire les performances.

* Solution (Algorithmes en cascade) : On garde l'approche parallèle pour descendre dans l'arbre, mais dès que la taille
  du sous-tableau devient petite (par exemple inférieure à $\log n$), on bascule sur l'algorithme séquentiel classique.
  Cela réduit drastiquement les surcoûts tout en gardant une profondeur globale en $\mathcal{O}(\log n)$.

5. Lien avec votre TD : Application du Diviser pour Régner
   Votre TD vise à mettre en pratique ces notions sur des algorithmes concrets.


*

<a id="seance-2-exercice-1"></a>

##### Exercice 1 (Le for parallèle) : Vous allez devoir recréer vous-même l'opérateur for// en utilisant un algorithme diviser pour régner. Le but est d'appliquer une fonction sur une plage d'entiers en parallèle et de calculer les métriques $W$ et $D$.

*

<a id="seance-2-exercice-2"></a>

##### Exercice 2 (Mélange de tableau) : On part d'un algorithme séquentiel de mélange qui contient des dépendances de données. L'objectif est de trouver une astuce pour paralléliser le calcul en pré-tirant les nombres aléatoires dans un tableau annexe $B$.

*

<a id="seance-2-exercice-3"></a>

##### Exercice 3 (Bin-packing et First-Fit) : Vous chercherez à paralléliser l'algorithme de rangement de boîtes (vu à la séance 1) avec une approche diviser pour régner et des fusions parallèles.

Voulez-vous que l'on rédige ensemble la solution de l'Exercice 1 du TD pour voir comment coder proprement un for//avec
des join et calculer rigoureusement son $W$ et son $D$ ?

C'est une excellente idée. L'algorithmique parallèle est avant tout visuelle : il faut imaginer l'exécution du programme
comme un arbre ou un réseau qui se déploie dans le temps, et non plus comme une simple ligne droite.
Voici des schémas, des graphes explicatifs et des exemples de pseudo-code pour rendre tout cela beaucoup plus concret.

1. Le Graphe Fork-Join (Schéma d'exécution)
   Lorsqu'on exécute un programme parallèle avec des join, l'exécution se divise (Fork) puis se resynchronise (Join). On
   représente cela par un Graphe Orienté Acyclique (DAG).

Voici à quoi ressemble un graphe d'exécution basique :

```text

Temps
  |          [Tâche A]
  |         /         \   <-- FORK : La tâche A lance B et C en parallèle
  |        /           \
  |   [Tâche B]     [Tâche C]
  |       |             |
  |   [Tâche D]         |
  |       |             |
  |        \           /  <-- JOIN : On attend que le côté gauche ET droit
  |         \         /              soient finis pour continuer.
  V          [Tâche E]
```

Comment lire W et D sur ce graphe ? En supposant que chaque nœud prend un temps unitaire $\mathcal{O}(1)$:

*

Le Travail ($W$) : C'est la somme de tous les nœuds du graphe (le volume total de calcul). Ici, $W = 5$ (A, B, C, D, E).

*

La Profondeur ($D$) : C'est le chemin le plus long du début à la fin (le chemin critique). Le chemin A $\rightarrow$
B $\rightarrow$ D $\rightarrow$ E compte 4 nœuds. Le chemin A $\rightarrow$ C $\rightarrow$ E compte 3 nœuds.
Donc, $D = 4$.

2. Pseudo-code : Séquentiel vs Parallèle (for// et join)
   A. La boucle for parallèle (for//)
   Contrairement à une boucle classique qui exécute l'itération $i=1$ puis $i=2$, le for// lance toutes les itérations
   en même temps sur différents cœurs.

```text

// Séquentiel classique : W = O(n), D = O(n)
pour i allant de 0 à n-1 faire
    T[i] = T[i] * 2
fin pour

// Parallèle : W = O(n), D = O(1)
for// i allant de 0 à n-1 faire
    T[i] = T[i] * 2
fin for//
```

Note : Si on a $n$ processeurs, la boucle parallèle prendra un temps $\mathcal{O}(1)$ !
B. La primitive join
Elle permet de lancer deux fonctions complètement différentes en même temps.

```text

// Les deux appels s'exécutent simultanément
Pg, Pd = join( Calculer_Gauche(T), Calculer_Droite(T) )

// Cette ligne ne s'exécutera que lorsque Pg ET Pd seront calculés
Resultat = Pg + Pd

```

3. L'Algorithme "Diviser pour Régner" (Exemple : Produit d'un tableau)
   C'est la méthode reine pour obtenir une profondeur logarithmique $D = \mathcal{O}(\log n)$.
   Version 1 : Diviser pour régner pur (Théorique)
   On coupe le tableau en deux à chaque étape.

```text

Fonction Produit_Parallele(T) :
    Si taille(T) == 1 alors
        retourner T[0]
    Sinon
        // Découpe le tableau en deux moitiés égales en temps O(1)
        Tg, Td = decoupe(T)

        // Appels récursifs en parallèle
        Pg, Pd = join( Produit_Parallele(Tg), Produit_Parallele(Td) )

        retourner Pg * Pd
    Fin Si
```

Analyse de complexité :

*

Travail ($W$) : $W(n) = 2W(n/2) + \mathcal{O}(1) \implies W(n) = \mathcal{O}(n)$.

*

Profondeur ($D$) : $D(n) = D(n/2) + \mathcal{O}(1) \implies D(n) = \mathcal{O}(\log n)$.

Version 2 : Algorithme en Cascade (Pratique / Amorti)
En pratique, l'opération join coûte très cher (création de threads). On ne veut pas créer un thread juste pour
multiplier deux nombres. On fixe donc un seuil (souvent $\log n$) en dessous duquel on repasse en séquentiel pur.

```text

Fonction Produit_Cascade(T, n_initial) :
    // Seuil d'amortissement : si le tableau est petit, on ne parallélise plus
    Si taille(T) < log(n_initial) alors
        retourner Produit_Sequentiel_Classique(T)
    Sinon
        Tg, Td = decoupe(T)
        Pg, Pd = join( Produit_Cascade(Tg, n_initial), Produit_Cascade(Td, n_initial) )
        retourner Pg * Pd
    Fin Si

```

4. Les conflits mémoire (EREW, CREW, CRCW)
   Prenons l'exemple de votre cours : on cherche si une valeur v existe dans un tableau T.

```text

contient = Faux
for// i allant de 0 à n-1 faire
    Si T[i] == v alors
        contient = Vrai
    Fin Si
fin for//
Que se passe-t-il si $T[2]$ et $T[5]$ valent tous les deux v ? Les deux itérations (qui s'exécutent en même temps) vont vouloir écrire Vrai dans la variable contient au même moment exact.
```

* Si votre machine est EREW (Exclusive Read, Exclusive Write) : Le programme plante. L'écriture simultanée est
  interdite. Il faudrait utiliser un arbre de réduction (diviser pour régner) pour remonter le résultat proprement.
* Si votre machine est CRCW (Concurrent Read, Concurrent Write) : La machine gère le conflit (par exemple, elle accepte
  une des écritures au hasard ou fait un OU logique). L'algorithme ci-dessus fonctionnera avec une
  profondeur $D = \mathcal{O}(1)$ !

Voulez-vous que l'on applique le principe de l'algorithme "Diviser pour Régner" (vu en partie 3) pour résoudre le
premier exercice de votre TD, c'est-à-dire coder votre propre primitive for// à partir de join ?

### Partie Pratique (TD)

#### TD — Diviser pour Régner & Algorithmique Parallèle · Correction Complète

🗺️ Vue d'ensemble de la feuille
Thèmes abordés :

* Paradigme diviser pour régner appliqué à la parallélisation
* Calcul du travail W (work, = coût séquentiel équivalent) et de la profondeur D (depth/span = coût sur machine
  infiniment parallèle)
* Primitives parallèles : join, for//, reduction
* Parallélisation d'un tri aléatoire et de bin-packing
  Compétences clés requises :
* Écrire un algorithme récursif diviser-pour-régner
* Résoudre des récurrences : $W(n) = 2W(n/2) + f(n)$ → Théorème Maître
* Identifier les dépendances de données qui empêchent la parallélisation
* Maintenir un invariant lors d'une fusion récursive
  📐 Rappel des définitions :
* W(n) = nombre total d'opérations (comme si on exécutait tout en séquentiel)
* D(n) = longueur du chemin critique (les opérations qu'on ne peut pas paralléliser)
* Sur $p$ processeurs : $T_p \approx \frac{W}{p} + D$

<a id="seance-2-exercice-4"></a>

##### Exercice 1 — For Parallèle

Reformulation
On veut implémenter for_par(range [a,b), c) qui appelle c(i) pour tout $i \in [a,b)$ en parallèle, en utilisant diviser
pour régner.

###### Question 1 — Algorithme diviser pour régner

Stratégie : Couper la range en deux, traiter chaque moitié en parallèle avec join, récursion jusqu'au cas de base (range
de taille 1).
for_par([a, b), c):
si b - a == 1:
c(a)                          ← cas de base : appel direct
sinon:
mid ← (a + b) / 2
join(
λ : for_par([a, mid), c), ← moitié gauche en parallèle
λ : for_par([mid, b), c)    ← moitié droite en parallèle
)
💡 Intuition : On construit un arbre binaire d'appels. Les feuilles font les vrais appels c(i). Tout le travail est dans
les feuilles, le join ne fait qu'orchestrer.

###### Question 2 — Calcul de W et D

Soit $n = b - a$ la taille de la range.
Récurrence pour W(
n) : $$W(n) = 2 \cdot W(n/2) + $O(1)$$$ (deux sous-problèmes de taille $n/2$, plus $O(1)$ pour le join)
Par le Théorème Maître : $a=2$, $b=2$, $f(n) = $O(1)$ = O(n^0)$, $\log_2 2 = 1 > 0$ → cas 1 :
$$\boxed{W(n) = $O(n)$}$$
Récurrence pour D(n) :
Les deux appels récursifs sont en parallèle → on prend le max des deux profondeurs : $$D(n) = D(
n/2) + $O(1)$$$ (les deux branches s'exécutent en même temps, on ne compte que la plus longue)
Théorème Maître : $a=1$, $b=2$, $f(n) = $O(1)$$ → cas 1 (en fait $\log_2 1 = 0 = $ exposant de $f$, cas 2) :
$$\boxed{D(n) = O(\log n)}$$
⚠️ Erreur classique : Écrire $D(n) = 2D(
n/2) + $O(1)$$ comme pour W. Non ! Pour D, les branches parallèles ne s'accumulent pas, on prend le max → $D(n) =
\mathbf{1} \cdot D(n/2) + $O(1)$$.

###### Question 3 — Remplir un tableau de 0

remplir_zeros(T, n):
for_par([0, n), λ i : T[i] ← 0)

* Chaque c(i) est l'affectation T[i] ← 0 en $O(1)$
* W = $O(n)$, D = $O(\log n)$
* Pas de dépendance entre les indices → parallélisation parfaitement valide ✓

<a id="seance-2-exercice-5"></a>

##### Exercice 2 — Mélange aléatoire d'un tableau

Reformulation
L'algorithme séquentiel de Fisher-Yates parcourt de $i=0$ à $n-2$, choisit $j > i$ aléatoirement, et échange $T[i]$
avec $T[j]$.

###### Question 1 — Pourquoi ne peut-on pas paralléliser la boucle ?

Il y a des dépendances de données entre les itérations.
À l'itération $i$, on échange $T[i]$ et $T[j_i]$. À l'itération $i' > i$, on peut à nouveau accéder à $T[j_i]$
si $j_{i'} = j_i$ ou $j_{i'} = i$. Ces conflits d'accès en écriture rendent les itérations dépendantes :

* L'échange à l'itération $i$ modifie $T[j_i]$, qui pourrait être lu/écrit à l'itération suivante.
* Exécuter deux échanges simultanément sur des indices qui se chevauchent produirait un résultat non déterministe(race
  condition).
  💡 Exemple : Si $j_0 = 3$ et $j_1 = 3$, les itérations 0 et 1 accèdent toutes deux à $T[3]$. Si elles s'exécutent en
  parallèle, l'une des deux mises à jour sera perdue.

###### Question 2 — Pré-calculer tous les indices j en parallèle

On sépare le tirage aléatoire des échanges. Les tirages sont indépendants !
calculer_B(B, n):
for// i de 0 à n-2:
B[i] ← randint(i+1, n-1)    ← tirage uniforme dans ]i, n-1]
Chaque tirage est indépendant : $B[i]$ ne dépend que de $i$, pas des autres $B[i']$. Pas de race condition sur les
écritures (chaque thread écrit dans sa propre case $B[i]$).
W et D :
Chaque randint est $O(1)$, il y en a $n-1$ : $$W = $O(n)$, \quad D = O(1)$$
(toutes les opérations en parallèle, profondeur = 1 niveau)

###### Question 3 — Analyse de l'Algorithme 2

Rappel de l'Algorithme 2 :
calculer B en parallèle;
join(
λ : déplacements(T, B, faux, faux),
λ : déplacements(T, B, vrai, vrai)
);
déplacements(T, B, faux, vrai);
L'algorithme déplacements contient une boucle for k de 0 à n/2-1 → $n/2$ itérations séquentielles.
Si on ne regarde que les appels randint :
C'est uniquement la phase calculer B : $$W_{rand} = $O(n)$, \quad D_{rand} = $O(1)$$$
Si on regarde toutes les opérations :

* calculer B : $W = $O(n)$$, $D = $O(1)$$
* join(déplacements, déplacements) : deux appels en parallèle, chacun avec $n/2$ itérations → $W = $O(n)$$, $D = O(n/2)$
* déplacements(...) séquentiel : $W = D = O(n/2)$
  Total : $$W = $O(n)$, \quad D = O(n/2) = $O(n)$$$
  La profondeur reste linéaire à cause des boucles for séquentielles dans déplacements. L'algorithme n'est pas vraiment
  parallèle.

###### Question 4 — Est-ce que ça va marcher en pratique ?

Non, il y a des race conditions !
Les deux appels dans le join modifient le même tableau T en parallèle. Un échange T[i] ↔ T[B[i]] dans la première
branche peut interférer avec un échange de la deuxième branche si les indices se chevauchent.
Exemple concret : Si la branche 1 échange $T[2]$ et $T[5]$, et en même temps la branche 2 échange $T[5]$ et $T[7]$, les
deux threads lisent et écrivent $T[5]$ simultanément → comportement indéfini.
💡 Leçon : Séparer les tirages des échanges ne suffit pas. Pour paralléliser les échanges eux-mêmes, il faudrait garantir
que les zones modifiées sont disjointes (partitionnement des indices), ce qui est plus complexe.

<a id="seance-2-exercice-6"></a>

##### Exercice 3 — Bin-packing First-Fit en diviser pour régner

Reformulation
On reprend l'algorithme First-Fit (FFSeq) et on cherche à le réécrire en diviser pour régner pour le paralléliser, tout
en maintenant l'invariant : au plus une boîte à moitié vide.

###### Question 1 — Algorithme diviser pour régner

Rappel de l'invariant : Au plus une boîte dans le résultat a un remplissage $< \frac{1}{2}$.
Stratégie : Couper $S$ en deux moitiés, résoudre chacune récursivement, puis fusionner les deux résultats $A_{left}$
et $A_{right}$.
Clé : Comment fusionner en préservant l'invariant ?

* $A_{left}$ a au plus une boîte partielle $b_L$ (remplissage $r_L < \frac{1}{2}$)
* $A_{right}$ a au plus une boîte partielle $b_R$ (remplissage $r_R < \frac{1}{2}$)
  Observation cruciale : $r_L < \frac{1}{2}$ et $r_R < \frac{1}{2}$ donc $r_L + r_R < 1$ → on peut toujours
  fusionner $b_L$ et $b_R$ en une seule boîte !
  FF_div_conq(S[a..b)):
  si b - a == 1:
  retourner [S[a]]              ← une boîte contenant cet objet seul
  mid ← (a + b) / 2
  A_left ← FF_div_conq(S[a..mid))
  A_right ← FF_div_conq(S[mid..b))
  retourner fusion(A_left, A_right)

fusion(A_left, A_right):
b_L ← boîte partielle de A_left  (si elle existe)
b_R ← boîte partielle de A_right (si elle existe)

si b_L et b_R existent toutes les deux:
// r_L + r_R < 1, donc on peut les fusionner
b_merged ← boîte avec remplissage r_L + r_R
retourner (boîtes pleines de A_left)
+ [b_merged]
+ (boîtes pleines de A_right)

sinon si seul b_L existe:
retourner A_left + (boîtes pleines de A_right)

sinon si seul b_R existe:
retourner (boîtes pleines de A_left) + A_right

sinon:
retourner A_left + A_right
Preuve de l'invariant :
Après fusion, les "boîtes pleines" de $A_{left}$ et $A_{right}$ ont remplissage $\geq \frac{1}{2}$. La boîte
fusionnée $b_{merged}$ a remplissage $r_L + r_R$, ce qui peut être $< \frac{1}{2}$, mais c'est la seule boîte
potentiellement partielle → invariant maintenu ✓
💡 Astuce : La fusion est $O(1)$ si on représente $A$ comme une structure avec des pointeurs (liste chaînée ou vecteur
avec métadonnées), grâce à l'hypothèse "découpage en O(1)".

###### Question 2 — Accélération intuitive attendue

FFSeq a un coût $O(n^2)$ dans le pire cas (cf. Q4 ci-dessous).
Notre algorithme D&C avec fusion $O(1)$ :

* $W(n) = 2W(n/2) + $O(1)$ \Rightarrow W(n) = $O(n)$$
  Accélération en travail : $\frac{W_{FFSeq}}{W_{D&C}} = \frac{O(n^2)}{$O(n)$} = $O(n)$$ → accélération d'un facteur $n$
  même en séquentiel !
  De plus, sur une machine parallèle avec profondeur $D = O(\log n)$, on peut traiter $n$ éléments en temps $O(\log n)$
  au lieu de $O(n^2)$.

###### Question 3 — Calcul de W et D

Récurrence pour W (fusion $O(1)$) : $$W(n) = 2W(n/2) + $O(1)$$$ $$\Rightarrow \boxed{W(n) = $O(n)$}$$
Récurrence pour D (les deux appels récursifs sont en parallèle via join implicite) : $$D(n) = D(
n/2) + $O(1)$$$ $$\Rightarrow \boxed{D(n) = O(\log n)}$$
⚠️ Attention : les deux appels récursifs à FF_div_conq ne sont pas dans un join explicitement dans la question 1 (on ne parallélise pas). Dans ce cas, D = $
O(n)$ également. Mais le but est de les paralléliser, donc on suppose join.

###### Question 4 — Coût au pire cas de FFSeq

Analyse de FFSeq :
Pour chaque objet $s$ (boucle externe : $n$ itérations), on parcourt toutes les boîtes déjà ouvertes (boucle interne).
Dans le pire cas, chaque objet ouvre une nouvelle boîte (par exemple si tous les objets ont taille $> \frac{1}{2}$ :
deux objets ne peuvent jamais partager une boîte). Après $i$ objets, il y a $i$ boîtes. L'objet $i$ scanne $i$ boîtes
avant d'en ouvrir une nouvelle.
Coût total : $$\sum_{i=1}^{n} i = \frac{n(n+1)}{2} = O(n^2)$$
$$\boxed{W_{FFSeq} = O(n^2)}$$

###### Question 5 — Accélération attendue par rapport à FFSeq

Avec $p$ processeurs et l'algorithme D&C (W = $O(n)$, D = $O(\log n)$) :
$$T_p \approx \frac{W}{p} + D = \frac{$O(n)$}{p} + O(\log n)$$
Accélération par rapport à FFSeq séquentiel ($T_1^{FFSeq} = O(n^2)$) :
$$\text{Speedup} = \frac{O(n^2)}{O(n/p + \log n)}$$

* Avec $p = n$ processeurs : $T_n = $O(1)$ + O(\log n) = O(\log n)$, speedup $= O(n^2 / \log n)$
* Avec $p = n / \log n$ : speedup $= $O(n)$$ (speedup linéaire en $n$, optimal)

###### Question 6 — Algorithme parallèle pour les deux minimums

Pourquoi en a-t-on besoin ? Pour identifier les deux boîtes partielles dans la fusion.
Stratégie : Réduction parallèle qui propage non pas 1, mais 2 minimums à chaque niveau.
deux_min(T, a, b):    // retourne (min1, idx1, min2, idx2)
si b - a == 1:
retourner (T[a], a, +∞, -1)
si b - a == 2:
si T[a] ≤ T[a+1]: retourner (T[a], a, T[a+1], a+1)
sinon:            retourner (T[a+1], a+1, T[a], a)
mid ← (a + b) / 2
(l1, li1, l2, li2), (r1, ri1, r2, ri2) ← join(
λ : deux_min(T, a, mid),
λ : deux_min(T, mid, b)
)
// Fusionner deux paires de minimums : $O(1)$
retourner fusion_mins(l1, li1, l2, li2, r1, ri1, r2, ri2)

fusion_mins(l1, li1, l2, li2, r1, ri1, r2, ri2):
// Trier les 4 valeurs {l1, l2, r1, r2} et garder les 2 plus petites
// $O(1)$ car 4 valeurs fixées → séquence de comparaisons
W et D : $$W(n) = 2W(n/2) + $O(1)$ \Rightarrow W(n) = $O(n)$$$ $$D(n) = D(n/2) + $O(1)$ \Rightarrow D(n) = O(\log n)$$
💡 Généralisation : Cette technique (réduction avec accumulation de $k$ minimums) fonctionne pour tout $k$ fixé avec le même $W = $O(n)$$
et $D = O(\log n)$.

###### Question 7 — Fusion parallèle : concaténation + profondeur finale

Algorithme de concaténation parallèle de deux tableaux A (taille p) et B (taille q) :
concat_par(A, B):
n_A ← |A|, n_B ← |B|
C ← nouveau tableau de taille n_A + n_B
for// i de 0 à n_A - 1 : C[i]       ← A[i]   ← copie A en parallèle
for// i de 0 à n_B - 1 : C[n_A + i] ← B[i]   ← copie B en parallèle
retourner C

* W $= O(n_A + n_B)$
* D $= $O(1)$$ (les deux for// sont en parallèle, et chaque copie est $O(1)$ de profondeur)
  Fusion parallèle complète :
  fusion_parallèle(A_left, A_right):
  (b_L, idx_L) ← min de A_left // boîte avec remplissage minimum → $O(\log n)$ via deux_min
  (b_R, idx_R) ← min de A_right // idem

  si b_L < 1/2 ET b_R < 1/2:
  b_merged ← b_L + b_R
  A_left_sans_bL ← concat_par(A_left[0..idx_L), A_left[idx_L+1..))
  A_right_sans_bR ← concat_par(A_right[0..idx_R), A_right[idx_R+1..))
  retourner concat_par(A_left_sans_bL, [b_merged] + A_right_sans_bR)
  ...
  Profondeur de la fusion parallèle :
* Trouver les boîtes partielles (deux_min) : $O(\log n)$
* Concaténation : $O(1)$
  Donc : $D_{fusion} = O(\log n)$
  Profondeur totale de l'algorithme D&C avec fusion parallèle :
  La nouvelle récurrence pour D : $$D(n) = D(n/2) + D_{fusion}(n) = D(n/2) + O(\log n)$$
  En déroulant : $D(n) = O(\log n) + O(\log n/2) + \ldots = O(\log^2 n)$
  $$\boxed{D_{total}(n) = O(\log^2 n)}$$
  W total (avec concat_par de coût $O(n)$) : $$W(n) = 2W(n/2) + $O(n)$ \Rightarrow W(n) = O(n \log n)$$
  Bilan comparatif final :
  | Version | W | D |
  | --- | --- | --- |
  | FFSeq | $O(n^2)$ | $O(n^2)$ |
  | D&C fusion séquentielle O(1) | $O(n)$ | $O(\log n)$ |
  | D&C fusion parallèle | $O(n \log n)$ | $O(\log^2 n)$ |
  💡 La fusion parallèle coûte plus de travail ($O(n \log n)$ vs $O(n)$) mais offre une meilleure
  profondeur($O(\log^2 n)$ vs $O(\log n)$... en fait la version séquentielle avait aussi $O(\log n)$). Le vrai gain est
  que la fusion parallèle est correctement parallélisable, sans dépendre d'une représentation en liste chaînée.

📋 Résumé Final

#### Méthodes / techniques clés

1. Diviser pour régner pour la parallélisation : couper en deux, join sur les deux moitiés, fusionner
2. Calcul W/D via Théorème Maître : $W$ accumule les deux branches, $D$ prend seulement la plus longue
3. Invariant de fusion : deux boîtes "partielles" (fill $< \frac{1}{2}$) ont toujours une somme $< 1$, donc se
   fusionnent en une seule
4. Réduction parallèle à k-minimums : étend la réduction standard au suivi de plusieurs valeurs
   Formules clés
   $$W(n) = 2W(n/2) + $O(1)$ \Rightarrow $O(n)$$$ $$D(n) = D(n/2) + $O(1)$ \Rightarrow O(\log n)$$ $$W(n) = 2W(
   n/2) + $O(n)$ \Rightarrow O(n \log n)$$ $$D(n) = D(n/2) + O(\log n) \Rightarrow O(\log^2 n)$$ $$T_p \approx
   \frac{W}{p} + D \quad \text{(loi de Brent)}$$
   Pièges fréquents ⚠️
1. D ≠ W/2 : La profondeur n'est pas la moitié du travail. Elle suit la branche la plus longue du chemin critique, pas
   la somme.
2. Oublier les race conditions : Des boucles for// sur un tableau partagé en écriture ne sont valides que si les indices
   d'écriture sont disjoints.
3. Fusion qui casse l'invariant : Ne pas vérifier que $r_L + r_R < 1$ avant de fusionner (toujours vrai ici, mais à
   justifier).
4. Confondre W et D dans le Théorème Maître : Pour D, le facteur multiplicatif du sous-problème est toujours 1 (on prend
   le max, pas la somme).
5. Coût de la concaténation : Si les tableaux sont en mémoire contiguë, concat coûte $O(n)$ en travail, pas $O(1)$ —
   sauf si on utilise des structures avec pointeurs.

🎯 Questions d'entraînement
Q1. Calculez W et D pour un algorithme D&C de somme d'un tableau de $n$ entiers.
Réponse : $W(n) = 2W(n/2) + $O(1)$ = $O(n)$$, $D(n) = D(n/2) + $O(1)$ = O(\log n)$.
Q2. Un algorithme a $W = O(n \log n)$ et $D = O(\log^2 n)$. Quel est le temps sur $p = \sqrt{n}$ processeurs ?
Réponse : $T_p = O(n \log n / \sqrt{n}) + O(\log^2 n) = O(\sqrt{n} \log n)$.
Q3. Peut-on paralléliser un tri par insertion ? Pourquoi ?
Réponse : Non directement : l'insertion à la position $i$ dépend du résultat de l'insertion à $i-1$. Dépendance de données séquentielle. On préférera le tri fusion parallèle.
Q4. Dans le bin-packing D&C, que se passe-t-il si les deux moitiés ont chacune une boîte avec remplissage exactement $\frac{1}{2}$ ? Peut-on fusionner ?
Réponse : $r_L = r_R = \frac{1}{2}$, donc $r_L + r_R = 1 \leq 1$. On peut fusionner en une boîte pleine. Résultat : aucune boîte partielle, invariant largement satisfait ✓
Q5. Quelle est la profondeur d'une réduction parallèle (ex: max d'un tableau) par D&C ? Comparez avec une réduction séquentielle.
Réponse : D&C : $D = O(\log n)$ (arbre binaire). Séquentiel : $D = W = $O(n)$$. Sur machine infiniment parallèle, gain
d'un facteur $O(n / \log n)$.

C'est une excellente suite ! La séance 3 rentre dans le vif du sujet avec deux des algorithmes parallèles les plus
fondamentaux : le Tri Fusion et surtout le Préfixe (qui est la clé de voûte de votre TD).
Vos notes montrent une petite confusion classique sur l'étape de correction du préfixe (le fameux P[i] += P[m-i] ), que
nous allons corriger en douceur. C'est tout à fait normal de s'y emmêler, le "Diviser pour Régner" parallèle demande
beaucoup de rigueur.

Voici votre cours détaillé et structuré pour cette troisième séance.


---

<a id="seance-3"></a>

## Séance 3 — Tri fusion parallèle et calcul de préfixe

> Plage source conservée : lignes `733` à `1033` de `course.txt`.

### Partie Théorique

#### Séance 3 : Tri Fusion Parallèle et Calcul de Préfixe

Objectif de la séance : Étudier comment paralléliser des algorithmes classiques en gérant intelligemment les dépendances
de données, et introduire l'opération de "Préfixe" qui deviendra une brique de base (une primitive) pour résoudre des
problèmes complexes en parallèle.

1. Le Tri Fusion Parallèle (Merge Sort)
   Le tri fusion est naturellement adapté au parallélisme grâce à sa structure "Diviser pour Régner".
   L'algorithme
   L'idée est de couper le tableau en deux, de trier les deux moitiés en même temps (en parallèle), puis de fusionner
   les deux moitiés triées. Pour éviter que la création de threads ne coûte plus cher que le tri lui-même sur de petits
   tableaux, on utilise un seuil d'arrêt (algorithme en cascade).

```text

Fonction Tri_Fusion_Parallele(T) :
    // 1. Amortissement du surcoût
    Si taille(T) < SEUIL alors
        retourner Tri_Sequentiel(T)
    Sinon
        // 2. Division
        G, D = diviser_en_deux_moities(T)

        // 3. Appels récursifs en parallèle
        G_trie, D_trie = join( Tri_Fusion_Parallele(G), Tri_Fusion_Parallele(D) )

        // 4. Fusion
        retourner Fusion(G_trie, D_trie)
    Fin Si
```

Analyse de complexité (Master Theorem)

* Travail ($W$) : Le volume de calcul total reste le même que l'algorithme séquentiel classique. À chaque étape, on
  divise par 2, et la fusion coûte $\mathcal{O}(n)$.

$$W(n) = 2W\left(\frac{n}{2}\right) + \mathcal{O}(n) \implies W(n) = \mathcal{O}(n \log n)$$

* Profondeur ($D$) : La profondeur dépend fortement de la fonction Fusion.
    * Si la fusion est séquentielle (classique), alors $D(n) = D(n/2) + \mathcal{O}(n) \implies D(n) = \mathcal{O}(n)$.
      C'est décevant, car on n'atteint pas une profondeur logarithmique.
    * Note avancée : Pour avoir un tri fusion hautement parallèle, il faudrait aussi paralléliser l'étape de fusion (ce
      qui est possible mais plus complexe, abaissant $D$ à $\mathcal{O}(\log^2 n)$).

2. Le Problème du Préfixe (Prefix Sum)
   C'est LE concept central de cette séance.
   Le problème : Étant donné un tableau $T$ (ex: [1, 4, 0, 3, 2]), on veut calculer un tableau $P$ où chaque case $i$
   contient la somme de tous les éléments de $T$ de l'indice $0$ à $i$.

* Entrée $T$ : [1, 4, 0, 3, 2]
* Sortie $P$ : [1, 5, 5, 8, 10]
  Le piège de la dépendance
  En séquentiel, on fait simplement une boucle : $P[i] = P[i-1] + T[i]$. Mais en parallèle, un for// est impossible.
  Pourquoi ? Parce que pour calculer $P[4]$, le processeur a besoin de $P[3]$, qui est en train d'être calculé par un
  autre processeur au même moment. Il y a une dépendance stricte.

La solution : Diviser pour Régner
Quand on manque d'inspiration en algorithmique parallèle, la règle d'or est : Diviser pour Régner !.

1.

Diviser : On coupe le tableau en deux (gauche et droite).

2.

Régner en parallèle : On calcule le préfixe de la moitié gauche et le préfixe de la moitié droite simultanément avec un
join.

3. Corriger : C'est ici qu'il faut gently corriger vos notes. Le résultat de la moitié droite est faux, car il lui
   manque la somme totale de la moitié gauche ! On utilise un for// pour ajouter la dernière valeur du préfixe gauche à
   tous les éléments du préfixe droit.

```text

Fonction Prefixe_Rec(T, P, debut, fin) :
    Si fin - debut == 1 alors
        P[debut] = T[debut]
    Sinon
        milieu = (debut + fin) / 2

        // Calcul indépendant des deux moitiés
        join( Prefixe_Rec(T, P, debut, milieu),
              Prefixe_Rec(T, P, milieu, fin) )

        // Étape de correction : on ajoute la somme de la partie gauche à la partie droite
        Somme_Gauche = P[milieu - 1]
        for// i allant de milieu à fin - 1 faire
            P[i] = P[i] + Somme_Gauche  // Correction de vos notes (P[m-i] était une erreur)
        fin for//
    Fin Si
```

Complexité du Préfixe

* Travail ($W$) : $W(n) = 2W(n/2) + \mathcal{O}(n)$ (à cause de la boucle de
  correction) $\implies W(n) = \mathcal{O}(n \log n)$.

(Il existe des versions optimisées en deux passes qui font $\mathcal{O}(n)$, mais l'approche naïve ci-dessus est
en $n \log n$).

*

Profondeur ($D$) : $D(n) = D(n/2) + \mathcal{O}(1)$ (car le for// prend un temps
constant) $\implies D(n) = \mathcal{O}(\log n)$. Une excellente profondeur !

### Partie Pratique (TD)

3. Lien avec votre TD (La Magie du Préfixe)
   Maintenant que l'on sait calculer un préfixe en $\mathcal{O}(\log n)$, on s'autorise à l'utiliser comme une fonction
   de base, au même titre qu'une addition ou un join. Le TD vous montre la puissance de cet outil.

<a id="seance-3-exercice-1"></a>

##### Exercice 1 : Le marché boursier

Vous avez les prix futurs $A$ et devez acheter au jour $i$ et vendre au jour $j$ ($j \ge i$) pour
maximiser $A[j] - A[i]$.

* L'astuce parallèle : Au lieu de comparer toutes les paires avec deux boucles imbriquées, on fait un Préfixe-Minimum
  sur le tableau $A$. Cela nous donne un tableau $Min$ où $Min[j]$ contient le prix le plus bas rencontré jusqu'au
  jour $j$.
* Ensuite, un simple for// calcule $A[j] - Min[j]$ pour chaque jour, et une réduction (max) nous donne le profit
  maximum !
  <a id="seance-3-exercice-2"></a>

##### Exercice 2 : Parenthésage

Vous avez une chaîne de parenthèses (ex: ((()))) et vous devez construire le tableau $C$ des parenthèses ouvertes non
fermées.

* L'astuce parallèle : On remplace chaque ( par $1$ et chaque ) par $-1$.
* Que se passe-t-il si on applique notre fameux algorithme de Préfixe sur ce tableau de $1$ et $-1$ ? On obtient
  exactement le tableau $C$ demandé dans la question 1! En $\mathcal{O}(\log n)$ de profondeur.

Le préfixe est un outil redoutable. Souhaitez-vous que l'on rédige intégralement la solution de l'Exercice 2 du TD (le
Parenthésage), notamment les questions 2 et 3 qui demandent de vérifier en parallèle si la chaîne est correcte?

#### TD — Préfixe & Algorithmique Parallèle · Correction Complète

🗺️ Vue d'ensemble de la feuille
Thèmes abordés :

* Scan/Préfixe parallèle : l'outil central de toute la feuille
* Problème du meilleur achat/vente (max subarray variant)
* Vérification de parenthésage et traitement de chaînes en parallèle
  Compétences clés requises :
* Savoir utiliser préfixe (prefix scan) comme brique algorithmique
* Calculer W et D via le Théorème Maître
* Réduire un problème à un scan ou une réduction parallèle
* Manipuler des opérateurs associatifs pour composer des résultats partiels
  📐 Rappel fondamental — l'opérateur préfixe : Étant donné un tableau $[a_0, a_1, \ldots, a_{n-1}]$ et un opérateur
  associatif $\oplus$, préfixe
  calcule : $$[a_0,\ a_0 \oplus a_1,\ a_0 \oplus a_1 \oplus a_2,\ \ldots,\ a_0 \oplus \cdots \oplus a_{n-1}]$$
  Complexité : $W = $O(n)$$, $D = O(\log n)$

<a id="seance-3-exercice-3"></a>

##### Exercice 1 — Le Marché

Reformulation
On dispose du tableau $A[0..n-1]$ des cours futurs d'une action. On veut trouver les jours $i \leq j$ qui maximisent le
profit $A[j] - A[i]$ (acheter au jour $i$, vendre au jour $j$). La contrainte de budget est implicite (on cherche juste
l'optimum).

###### Question 1 — Algorithme séquentiel

Stratégie : Parcourir le tableau en maintenant le minimum courant vu jusqu'ici. À chaque jour $j$, le meilleur profit
réalisable en vendant ce jour-là est $A[j] - \min_{i \leq j} A[i]$.
marche_seq(A, n):
min_prix ← A[0]
best_i ← 0
best_j ← 0
best_profit ← 0

pour j de 1 à n-1 :
si A[j] - min_prix > best_profit :
best_profit ← A[j] - min_prix
best_j ← j
best_i ← indice du minimum actuel
si A[j] < min_prix :
min_prix ← A[j]
best_i_courant ← j // mémoriser où est le min

retourner (best_i, best_j, best_profit)
Coût : $W = $O(n)$$, $D = $O(n)$$ (tout séquentiel)
Exemple : $A = [3, 1, 4, 1, 5, 9, 2, 6]$

* Jour 1 : min=1, profit potentiel si on vend j=5 : $9-1=8$ ✓
* Meilleur : acheter $i=3$ (prix 1), vendre $j=5$ (prix 9), profit = 8

###### Question 2 — Algorithme parallèle

Idée clé : On va exprimer le problème en termes de préfixe.
Étape 1 : Calculer le préfixe minimum de $A$ : $$M[j] = \min(A[0], A[1], \ldots, A[j])$$ → préfixe avec
opérateur $\min$, en $W = $O(n)$$, $D = O(\log n)$.
Étape 2 : Calculer le tableau des profits potentiels : $$P[j] = A[j] - M[j-1] \quad \text{pour } j \geq
1$$ → for// en $W = $O(n)$$, $D = $O(1)$$.
Étape 3 : Trouver le maximum de $P$ : $$\text{best_profit} = \max_j
P[j]$$ → réduction avec $\max$, en $W = $O(n)$$, $D = O(\log n)$.
marche_par(A, n):
M ← préfixe(A, min)                  // M[j] = min(A[0..j])
for// j de 1 à n-1 :
P[j] ← A[j] - M[j-1]              // profit si on vend en j
(best_profit, best_j) ← réduction(P, max, avec_indice)
best_i ← indice où M[best_j - 1] est atteint // retrouver i
retourner (best_i, best_j, best_profit)
Complexité totale : $$W = $O(n)$ + $O(n)$ + $O(n)$ = $O(n)$$$ $$D = O(\log n) + $O(1)$ + O(\log n) = O(\log n)$$
💡 Astuce fondamentale : Dès qu'un problème séquentiel se résout en "maintenir une valeur courante tout en parcourant",
on peut souvent le paralléliser via un préfixe sur cette valeur courante.
⚠️ Erreur classique : Vouloir calculer $\max_{i \leq j}(A[j] - A[i])$ directement en parallèle sur toutes les
paires $(i,j)$ coûterait $O(n^2)$ en travail. Le passage par le préfixe-min réduit à $O(n)$.

<a id="seance-3-exercice-4"></a>

##### Exercice 2 — Parenthésage

Reformulation
On a une chaîne $S$ de parenthèses. On définit $C[j]$ = nombre de ( minus nombre de ) dans $S[0..j]$.
Exemple : (()(())))→ $C = [1, 2, 1, 2, 3, 2, 1, 0, -1, -2]$.

###### Question 1 — Calcul parallèle de C

Observation : $C[j]$ est une somme préfixe ! Si on
définit : $$\delta[i] = \begin{cases} +1 & \text{si } S[i] = \text{'('} \ -1 & \text{si } S[i] = \text{')'} \end{cases}$$
Alors $C[j] = \sum_{i=0}^{j} \delta[i]$ = préfixe somme de $\delta$.
calcul_C(S, n):
for// i de 0 à n-1 :
delta[i] ← si S[i]=='(' alors +1 sinon -1 // $O(1)$, W=$O(n)$, D=$O(1)$
C ← préfixe(delta, +)                           // W=$O(n)$, D=$O(\log n)$
retourner C
$$\boxed{W = $O(n)$, \quad D = O(\log n)}$$
Illustration : $S = $ (() → $\delta = [+1, +1, -1]$ → préfixe-somme → $C = [1, 2, 1]$ ✓

###### Question 2 — Condition de parenthésage correct

En regardant $C$, le parenthésage est correct si et seulement si :

1. $C[n-1] = 0$ : autant de ( que de ) au total
2. $\forall j \in [0, n-1]$, $C[j] \geq 0$ : jamais plus de ) que de ( à un moment donné
   Intuition : La condition 1 assure l'équilibre global. La condition 2 assure qu'on ne ferme pas avant d'avoir ouvert.
   Exemple : )( → $C = [-1, 0]$. $C[1]=0$ mais $C[0]=-1 < 0$ → invalide. Et `))(($ → $C=[-1,-2,-1,0]$ → invalide.

###### Question 3 — Algorithme parallèle de vérification

Stratégie : Vérifier les deux conditions de Q2 en parallèle.
verifier_parenthesage(S, n):
C ← calcul_C(S, n)                          // W=$O(n)$, D=$O(\log n)$

// Condition 1 : C[n-1] == 0
condition1 ← (C[n-1] == 0)                  // $O(1)$

// Condition 2 : min de C >= 0
min_C ← réduction(C, min)                   // W=$O(n)$, D=$O(\log n)$
condition2 ← (min_C >= 0)

retourner condition1 ET condition2
$$W = $O(n)$, \quad D = O(\log n)$$
💡 Pourquoi réduction(min) suffit ? Si le minimum de $C$ est $\geq 0$, alors tous les éléments sont $\geq 0$. On évite un
for// de comparaisons individuelles suivi d'un ET en arbre.

###### Question 4 — Trouver la parenthèse ouvrante correspondante

Problème : Pour une parenthèse fermante à la position $j$, trouver $i < j$ tel que S[i] est la parenthèse ouvrante qui
la "ferme".
Idée clé : La parenthèse ouvrante correspondante à la fermante en $j$ est la dernière position $i < j$ telle
que $C[i] = C[j] + 1$ (le niveau redescend de 1 entre $i$ et $j+1$, donc $C[i-1] = C[j]$ et $S[i]$ = ().
Plus précisément : $C[j] = C[j-1] - 1$ puisque $S[j] = $ ). La parenthèse ouvrante correspondante est à l'indice $i$ tel
que :

* $S[i] = $ (
* $C[i] = C[j] + 1$ (c'est-à-dire $C[i-1] + 1 = C[j] + 1$, soit $C[i-1] = C[j]$)
* $i$ est le plus grand tel indice inférieur à $j$
  Stratégie avec préfixe :
  On cherche $i = \max{k < j \mid C[k-1] = C[j] \text{ et } S[k] = \text{'('}}$.
  Autrement dit, $i$ est la position du dernier ( au niveau $C[j]+1$ avant $j$.
  Algorithme :
  trouver_ouvrante(S, C, j):
  // On cherche le plus grand i < j tel que C[i] == C[j] + 1
  // i.e. la dernière fois que le niveau était C[j]+1 avant j

  niveau_cible ← C[j] + 1 // niveau juste avant la fermeture

  // Construire un tableau R où R[k] = k si C[k]==niveau_cible et k<j, sinon -∞
  for// k de 0 à j-1 :
  R[k] ← si C[k] == niveau_cible alors k sinon -∞

  // Le maximum de R[0..j-1] donne la dernière occurrence
  i ← réduction(R[0..j-1], max)
  retourner i
  Complexité : $$W = $O(n)$, \quad D = O(\log n)$$
  Illustration : $S = $ (()()), $C = [1,2,1,2,1,0]$, $j = 5$ (dernière ))
* $C[5] = 0$, niveau cible $= 1$
* $R = [0, -\infty, 2, -\infty, 4, -\infty]$ (positions où $C[k]=1$)
* $\max(R[0..4]) = 4$ → la parenthèse ouvrante est en $i=4$ ✓ ((()) puis ())
  💡 Alternative directe : Si on veut trouver le partenaire de toutes les parenthèses en parallèle, on peut faire un
  préfixe plus élaboré, mais pour un $j$ donné, la méthode ci-dessus suffit.

###### Question 5 — Fonction analyse : compter les parenthèses non équilibrées

Problème : Retourner :

* $f$ = nombre de ) non ouvertes (excès de fermantes)
* $o$ = nombre de ( non fermées (excès d'ouvrantes)
  Exemples :
* (() → $f = 0$, $o = 1$
* ))(( → $f = 2$, $o = 2$
* (()) → $f = 0$, $o = 0$ (bien parenthésé)
  Stratégie : Diviser pour régner avec opérateur de composition
  L'idée centrale est de représenter le résultat d'une sous-chaîne par une paire $(f, o)$ et de définir un opérateur de
  fusion associatif $\oplus$.
  Définition de $\oplus$ : Pour deux sous-chaînes consécutives de résultats $(f_1, o_1)$ et $(f_2, o_2)$ :
  Quand on concatène, les $o_1$ ouvrantes non fermées de la partie gauche "absorbent" les $f_2$ fermantes non ouvertes
  de la partie droite :
* Les deux parties s'annulent mutuellement à hauteur de $\min(o_1, f_2)$
* Ce qui reste non annulé de la gauche : $o_1 - \min(o_1, f_2)$ ouvrantes
* Ce qui reste non annulé de la droite : $f_2 - \min(o_1, f_2)$ fermantes
  $$\boxed{(f_1, o_1) \oplus (f_2, o_2) = \left(f_1 + \max(0, f_2 - o_1),\ o_2 + \max(0, o_1 - f_2)\right)}$$
  Preuve de la formule :
* $f_{result} = f_1 + (f_2 - \min(o_1, f_2)) = f_1 + \max(0, f_2 - o_1)$ ✓
* $o_{result} = (o_1 - \min(o_1, f_2)) + o_2 = \max(0, o_1 - f_2) + o_2$ ✓
  Associativité : L'opérateur $\oplus$ est associatif (on peut le vérifier en déroulant sur 3 termes). C'est essentiel
  pour pouvoir utiliser réduction ou préfixe.
  Algorithme parallèle :
  analyse(S, n):
  // Cas de base : transformer chaque caractère
  for// i de 0 à n-1 :
  T[i] ← si S[i]=='(' alors (0, 1) sinon (1, 0)

  // Réduction avec l'opérateur ⊕
  (f, o) ← réduction(T, ⊕)
  retourner (f, o)
  $$W = $O(n)$, \quad D = O(\log n)$$
  Vérification sur ))(( :
* $T = [(1,0), (1,0), (0,1), (0,1)]$
* $(1,0) \oplus (1,0) = (1+\max(0,1-0),\ 0+\max(0,0-1)) = (2, 0)$
* $(0,1) \oplus (0,1) = (0+\max(0,0-1),\ 1+\max(0,1-0)) = (0, 2)$
* $(2,0) \oplus (0,2) = (2+\max(0,0-0),\ 2+\max(0,0-0)) = (2, 2)$ ✓
  Vérification sur (()) :
* $T = [(0,1),(0,1),(1,0),(1,0)]$
* $(0,1)\oplus(0,1) = (0,2)$
* $(1,0)\oplus(1,0) = (2,0)$
* $(0,2)\oplus(2,0) = (0+\max(0,2-2), 0+\max(0,2-2)) = (0,0)$ ✓
  💡 Astuce clé : La représentation $(f, o)$ est un exemple de monoïde — une structure avec un opérateur associatif et un
  élément neutre ($(0,0)$). Dès qu'on peut représenter un résultat partiel comme un monoïde, on peut paralléliser via
  réduction ou préfixe. C'est un pattern fondamental en algorithmique parallèle.
  ⚠️ Erreur classique : Vouloir utiliser directement $C$ de la question 1 pour calculer $f$ et $o$. Ce n'est pas
  suffisant : )( et () ont le même $C$ final (0) mais des $(f, o)$ différents.

📋 Résumé Final

#### Méthodes / techniques clés

1. Préfixe-min/max/somme : transformer un parcours séquentiel "maintenir un running optimum" en calcul
   parallèle $O(\log n)$
2. Réduction avec indice : trouver le maximum/minimum et sa position
3. Monoïde pour diviser pour régner : représenter un résultat partiel par une structure $(f, o)$ avec opérateur
   associatif → réduction parallèle applicable
4. Conditions sur le préfixe : vérifier une propriété globale via le minimum ou maximum du tableau de préfixe
   Formules et résultats clés
   $$C[j] = \text{préfixe-somme}(\delta)[j], \quad \delta[i] = \begin{cases}+1 & S[i]=\text{'('} \ -1 & S[i]=\text{')'}\end{cases}$$
   $$\text{Parenthésage correct} \iff C[n-1]=0 \text{ et } \min_j C[j] \geq 0$$
   $$(f_1,o_1) \oplus (f_2,o_2) = \bigl(f_1 + \max(0, f_2-o_1),; o_2 + \max(0, o_1-f_2)\bigr)$$
   $$\text{Préfixe / Réduction : } W=$O(n)$,\ D=O(\log n)$$
   Pièges fréquents ⚠️
1. Oublier la condition $\min C \geq 0$ : $C[n-1]=0$ seul ne garantit pas la validité ()( par exemple)
2. Confondre $C[j]$ et $\delta[j]$ : $C[j]$ est la somme préfixe, pas le caractère converti
3. Opérateur $\oplus$ non associatif : toujours vérifier l'associativité avant d'utiliser réduction
4. Chercher $i$ dans $[0,n]$ au lieu de $[0,j-1]$ dans Q4 : bien restreindre la recherche avant $j$
5. Mauvais élément neutre : l'élément neutre de $\oplus$ pour analyse est $(0,0)$, pas $(0,1)$

🎯 Questions d'entraînement
Q1. Donnez le tableau $C$ pour S = ")(()". Le parenthésage est-il correct ?
Réponse : $\delta = [-1,+1,+1,-1]$, $C = [-1, 0, 1, 0]$. $C[3]=0$ ✓ mais $C[0]=-1 < 0$ ✗ → invalide.
Q2. Calculez analyse(")(()") avec l'opérateur $\oplus$.
Réponse : $T = [(1,0),(0,1),(0,1),(1,0)]$. $(1,0)\oplus(0,1)=(1,1)$. $(0,1)\oplus(1,0)=(0+\max(0,1-1), 0+\max(0,1-1))=(0,0)$.
Puis $(1,1)\oplus(0,0)=(1,1)$. Donc $f=1$, $o=1$.
Q3. Pour le problème du marché, $A = [5, 3, 6, 1, 8, 2]$. Calculez le préfixe-min $M$ et le tableau de profits $P$. Quel
est le meilleur achat/vente ?
Réponse : $M = [5,3,3,1,1,1]$. $P = [-, 0, 3, 0, 7, 1]$. Best : acheter jour 3 (prix 1), vendre jour 4 (prix 8),
profit = 7.
Q4. Montrez que $\oplus$ admet $(0,0)$ comme élément neutre.
Réponse : $(f,o)\oplus(0,0) = (f+\max(0,0-o), 0+\max(0,o-0)) = (f, o)$.
Et $(0,0)\oplus(f,o) = (0+\max(0,f-0), o+\max(0,0-f)) = (f,o)$ ✓.
Q5. Comment adapter l'algorithme du marché si on veut autoriser plusieurs achats et ventes (sans détenir plus d'une
action à la fois) ?
Réponse : Le profit maximum = somme de tous les $\max(0, A[j] - A[j-1])$ (on profite de chaque hausse). On
calcule $P[j] = \max(0, A[j]-A[j-1])$ en for// puis réduction(P, +). $W=$O(n)$$, $D=O(\log n)$.

C'est parti pour la séance 4 ! Cette séance aborde des concepts fondamentaux pour la performance réelle des algorithmes
parallèles : comment le système répartit le travail entre les processeurs (le vol de travail) et comment on peut
optimiser l'exécution quand on cherche un élément précis (les interruptions ou early termination).
Voici votre cours détaillé et structuré pour cette quatrième séance.


---

<a id="seance-4"></a>

## Séance 4 — Ordonnancement par vol de travail et interruptions parallèles

> Plage source conservée : lignes `1034` à `1384` de `course.txt`.

### Partie Théorique

#### Séance 4 : Ordonnancement par Vol de Travail et Interruptions Parallèles

Objectif de la séance : Comprendre comment l'intergiciel (la bibliothèque de threads) distribue efficacement les tâches
aux processeurs pour éviter qu'ils ne restent inactifs, et apprendre à concevoir des algorithmes parallèles capables de
s'arrêter tôt ("early termination") lorsqu'une solution est trouvée.

1. Le "Work Stealing" (Vol de Travail)
   Dans les séances précédentes, nous avons supposé que le travail ($W$) était parfaitement réparti sur les $p$
   processeurs (rappel de la loi de Brent : $T_p = \frac{W}{p} + \mathcal{O}(D)$). Mais comment le système réalise-t-il
   cette magie en pratique ? Il utilise un algorithme d'ordonnancement appelé Work Stealing (vol de travail).

Le Principe de Base

*

Gestion Locale : Chaque thread (ou processeur virtuel) possède sa propre file d'attente de tâches locale. Cette file est
généralement structurée comme une "Deque" (Double-Ended Queue, une file à double entrée).

*

Exécution Normale : Un thread travaille toujours en priorité sur sa propre file. Lorsqu'il crée de nouvelles tâches (par
exemple lors d'un Fork ou d'un appel récursif), il les empile dans sa Deque, et il les dépile pour les exécuter (
comportement LIFO - Last In, First Out).

* Le Vol (Le Cœur du Système) : Que se passe-t-il si un thread termine toutes ses tâches et que sa file est vide ? Au
  lieu de rester inactif, il devient un "voleur". Il choisit aléatoirement un autre thread (la victime) et va "voler"
  une tâche dans la file de ce dernier.


*

Intégration : Une fois la tâche volée, le voleur l'exécute comme si c'était la sienne, remplissant potentiellement sa
propre file avec de nouvelles sous-tâches.

L'Amélioration : Le "Thief Splitting"
Voler une seule petite tâche à la fois est inefficace (beaucoup de surcoûts de communication). À l'inverse, voler toute
la file de la victime n'est pas solidaire.

* Le concept de Thief Splitting (ou fractionnement du voleur) consiste, pour le voleur, à ne pas prendre une seule
  tâche, mais une fraction (souvent la moitié) des tâches disponibles dans la file de la victime.


*

Avantages : Cela permet d'éviter de voler trop ou trop peu de travail, de partager équitablement la charge entre le
thread d'origine et le voleur, et d'améliorer la granularité de la parallélisation.

2. Le Concept d'"Early Termination" (Interruption Précoce)
   C'est l'objet principal de l'Exercice 1 de votre TD.
   Le Problème : Imaginez que vous cherchez la première occurrence d'une valeur dans un immense tableau.

* En séquentiel : Vous parcourez le tableau de gauche à droite. Dès que vous trouvez la valeur (disons, à l'indice $k$),
  vous faites un return (ou un break). Le travail est proportionnel à $k$ ($\mathcal{O}(k)$). C'est très efficace si l'
  élément est au début !


* En parallèle naïf (ex: for//) : Vous lancez la recherche sur tous les indices en même temps. Même si l'élément est à
  l'indice 0, vous aurez inspecté tout le tableau ($W = \mathcal{O}(n)$). C'est un énorme gâchis de ressources.
  L'objectif de l'"early termination" est de concevoir un algorithme parallèle capable de s'arrêter sans faire le
  travail complet si ce n'est pas nécessaire.
  L'approche par "Blocs Doublants" (Exercice 1 du TD)
  Pour éviter de faire trop d'évaluations inutiles, on inspecte le tableau par blocs de taille croissante, en doublant
  la taille du bloc à chaque itération (1, 2, 4, 8, 16...). On inspecte chaque bloc en parallèle.


1. Phase 1 (taille 1) : On vérifie l'indice 0. Si c'est bon, on s'arrête.
2. Phase 2 (taille 2) : On vérifie les indices 1 et 2 en parallèle. Si on trouve, on prend le plus petit indice et on
   s'arrête.
3.

Phase 3 (taille 4) : On vérifie les indices 3 à 6 en parallèle... et ainsi de suite.

Analyse de cette méthode :

* Si la réponse est à l'indice $k$, on aura vérifié des blocs de taille $1, 2, 4, \dots, 2^m$ tels que la somme soit
  juste supérieure à $k$.
* Le travail total ($W$) ne dépassera jamais $2k$. On a donc un travail proportionnel à la solution
  séquentielle ($\mathcal{O}(k)$) !


* Cependant, la profondeur ($D$) est contrainte par les lancements successifs de blocs.

3. Étude de Cas : L'Addition Binaire Parallèle (Exercice 2 du TD)
   Cet exercice est un classique absolu de l'algorithmique parallèle. Il illustre comment briser une dépendance forte (
   la retenue) pour transformer un algorithme intrinsèquement séquentiel en un algorithme hautement
   parallèle $\mathcal{O}(\log n)$.

Le problème séquentiel : L'addition de deux nombres bit à bit propage une retenue de la droite vers la gauche. On ne
peut pas calculer le bit de poids fort tant qu'on n'a pas la retenue provenant du bit précédent. La boucle pour i de 0 à
n-1est donc strictement séquentielle ($D = \mathcal{O}(n)$).

L'Approche "Diviser pour Régner" Spéculative (Question 2)
Puisqu'on ne connaît pas la retenue qui arrivera à la moitié gauche ($Ag$, $Bg$) au moment où on la lance, on calcule
les deux cas possibles en parallèle !

```text

Fonction Add_Parallele(A, B, r_entree) :
    // ... cas de base ...
    Ag, Bg, Ad, Bd = Couper_en_deux(A, B)

    // On lance 3 additions en parallèle :
    // 1. La moitié droite (qui reçoit r_entree)
    // 2. La moitié gauche en SUPPOSANT que la retenue sortante de droite sera 0
    // 3. La moitié gauche en SUPPOSANT que la retenue sortante de droite sera 1
    Res_Droite, Res_Gauche_0, Res_Gauche_1 = join(
        Add_Parallele(Ad, Bd, r_entree),
        Add_Parallele(Ag, Bg, 0),
        Add_Parallele(Ag, Bg, 1)
    )

    // Une fois terminés, on regarde la vraie retenue sortante de la droite (s_droite)
    // et on choisit le bon résultat gauche.
    Si s_droite == 0 alors
        retourner Concatener(Res_Gauche_0, Res_Droite)
    Sinon
        retourner Concatener(Res_Gauche_1, Res_Droite)
    Fin Si
Note : Cette méthode a une excellente profondeur $\mathcal{O}(\log n)$ mais son travail "explose" ($W = \mathcal{O}(n^{\log_2 3})$) car on fait trop de calculs inutiles.
```

L'Approche par Préfixe (Question 7 - L'état de l'art)
C'est la méthode ultime (utilisée dans les vrais processeurs, le Carry-Lookahead Adder). On modélise la retenue comme un
calcul de Préfixe !

Pour chaque paire de bits $A_k$ et $B_k$, il y a trois états possibles pour la retenue sortante :

1.

Génération ($g_k$) : Si $A_k = 1$ et $B_k = 1$, ça va forcément générer une retenue de $1$, peu importe ce qui arrive de
la droite.

2. Propagation ($p_k$) : Si $A_k \neq B_k$ (un 1 et un 0), la retenue sortante sera égale à la retenue entrante. Elle "
   propage".


3. Annulation : Si $A_k = 0$ et $B_k = 0$, la retenue sortante sera forcément $0$.
   L'astuce consiste à définir une loi de composition entre ces états, et à utiliser notre fameux algorithme de
   Préfixe $\mathcal{O}(\log n)$ (vu à la séance 3) sur le tableau des états $(g_k, p_k)$. En un seul passage
   logarithmique, on calcule toutes les retenues de tous les bits simultanément ! Ensuite, une simple boucle parallèle
   calcule l'addition finale ($C_k = A_k \oplus B_k \oplus r_{k-1}$). On obtient un travail optimal $W = \mathcal{O}(n)$
   et une profondeur $D = \mathcal{O}(\log n)$.

Voulez-vous que l'on détaille la Question 4 du TD, c'est-à-dire proposer un algorithme parallèle efficace pour "
incrémenter un tableau C de 1" (ce qui servira à optimiser l'addition) ?

### Partie Pratique (TD)

#### TD Algorithmique Avancée – Correction Complète et Pédagogique

📋 Vue d'ensemble de la feuille
Thèmes abordés :

* Parallélisme par réduction et scan/préfixe parallèle
* Diviser pour régner en contexte parallèle
* Early termination (arrêt anticipé) : comment ne pas surtravailler en parallèle
* Analyse de complexité : Travail W(n) et Profondeur D(n)
  Compétences clés requises :
* Maîtrise des primitives parallèles : reduce, map, scan (préfixe)
* Loi de Brent : temps ≈ D + W/P
* Analyse de récurrences (Théorème maître)
* Manipulation algébrique de fonctions booléennes

<a id="seance-4-exercice-1"></a>

##### Exercice 1 — Le Premier Élément

🔍 Reformulation du problème
On cherche le premier indice k ∈ [d, f) tel que pred(k) soit vrai (ou f si aucun n'existe). Le séquentiel fait k−d+1
évaluations, ce qui est optimal. On veut des algorithmes parallèles qui :

* soient rapides (faible profondeur), et
* ne fassent pas beaucoup plus d'évaluations que le séquentiel

###### Question 1 — Algorithme par réduction : $O(\log n)$ profondeur, $O(n)$ travail

Stratégie
La clé est de se ramener à une réduction par minimum. On "encode" le résultat de pred(i) comme un indice valide ou une
valeur sentinelle f.
Résolution
Idée : Pour chaque indice i ∈ [d, f), on calcule en parallèle :
val(i) = i si pred(i) est vrai
val(i) = f sinon
Puis on prend le minimum de tous ces val(i).
Algorithme :
recherche1(pred, d, f) :
// Étape 1 : map parallèle — $O(1)$ profondeur, $O(n)$ travail
pour tout i ∈ [d, f) en parallèle :
T[i] ← (pred(i) ? i : f)

// Étape 2 : réduction par min — $O(\log n)$ profondeur, $O(n)$ travail
retourner reduce(min, T, f)
Analyse
| Mesure | Valeur | Justification |
| --- | --- | --- |
| Travail W(n) | O(n) | n évaluations du prédicat + n-1 comparaisons dans le reduce |
| Profondeur D(n) | O(log n) | L'arbre de réduction a log n niveaux |
⚠️ Piège classique : Cet algorithme évalue toujours les n prédicats, même si k = d (réponse immédiate). Il est donc
optimal en profondeur mais pas en travail vis-à-vis du séquentiel.

###### Question 2 — Algorithme par blocs doublants : analyse et profondeur

Stratégie
L'algorithme procède par blocs dont la taille double à chaque tour, en s'arrêtant dès qu'on trouve un résultat. Cela
évite de trop surtravailler.
Structure des blocs
Voici ce que fait l'algorithme (supposons que pred(d) est faux) :
| Étape | Indice de départ | Taille du bloc | Total évalué |
| --- | --- | --- | --- |
| Init | d | 1 | 1 |
| Bloc 1 | d+1 | 1 | 2 |
| Bloc 2 | d+2 | 2 | 4 |
| Bloc 3 | d+4 | 4 | 8 |
| Bloc j | d+2^(j-1) | 2^(j-1) | 2^j |
Preuve : nombre d'évaluations entre k et 2k−2
Hypothèse : le séquentiel fait exactement k > 1 évaluations, donc pred(d+k-1) est le premier vrai.
L'indice cible est d+k-1, qui appartient au bloc j défini par : $$2^{j-1} \leq k-1 < 2^j$$
Le total d'évaluations à la fin du bloc j
est : $$1 + \underbrace{1 + 2 + 4 + \cdots + 2^{j-1}}_{\text{blocs 1 à } j} = 1 + (2^j - 1) = 2^j$$
Borne inférieure : on doit évaluer au moins jusqu'à l'indice cible → au moins k évaluations ✓
Borne supérieure : puisque k-1 < 2^j, on a 2^j < 2(k-1), donc : $$\text{Total} = 2^j \leq 2(k-1) = 2k - 2$$
🎯 Résultat : L'algorithme effectue entre k et 2k−2 évaluations → moins de 2× le travail séquentiel !
Profondeur
Il y a O(log k) blocs (car les tailles doublent et atteignent k). Le bloc j a taille 2^(j-1) et est traité par
recherche1 qui a profondeur O(log(2^{j-1})) = O(j).
Les blocs sont séquentiels (on ne commence le bloc j+1 qu'après le bloc j), donc :
$$D(n) = \sum_{j=1}^{\log k} O(j) = O\left(\frac{(\log k)^2}{2}\right) = \boxed{O(\log^2 n)}$$
💡 Intuition : On sacrifie un facteur log n en profondeur pour gagner en travail. C'est le compromis classique entre
parallélisme et économie d'évaluations.

###### Question 3 — Algorithme polylogarithmique et proche du séquentiel

Stratégie : Recherche exponentielle + recherche parallèle dans le bloc
Idée : L'algorithme de la Q2 a déjà profondeur O(log²n) (polylogarithmique) et travail ≤ 2k. On peut cependant optimiser
en faisant des sondes exponentielles parallèles puis en affinant.
Algorithme optimisé (recherche exponentielle parallèle) :
recherche_poly(pred, d, f) :
// Phase 1 : sondes exponentielles pour trouver le bon bloc
// Tester pred(d + 2^0), pred(d + 2^1), pred(d + 2^2), ...
// en parallèle pour trouver le premier j tel que pred(d + 2^j) = vrai

// Phase 2 : recherche parallèle dans le bloc [d + 2^(j-1), d + 2^j)
// par recherche1 (réduction)
Analyse de la version Q2 (déjà polylogarithmique) :
En fait, l'algorithme de la Q2 est déjà la réponse naturelle :

* Profondeur : O(log²n) — polylogarithmique ✓
* Travail : entre k et 2k−2 — proche du séquentiel ✓
  Pour atteindre $O(\log n)$ de profondeur tout en gardant un travail proche de k : on peut affiner avec une recherche
  parallèle dans des blocs qui grandissent plus vite (e.g. blocs de taille n^(1/log n)) mais au prix de constantes plus
  grandes.
  🔑 Idée clé retenir : Il y a un triangle de tension entre :
* Profondeur faible ($O(\log n)$) → évalue tout (Q1)
* Travail proche de k → blocs séquentiels (Q2, O(log²n))
* Optimum : O(log²n) profondeur, ≤ 2k travail (Q2 est la réponse standard attendue)

<a id="seance-4-exercice-2"></a>

##### Exercice 2 — Addition Parallèle Binaire

🔍 Reformulation
On additionne deux nombres binaires A et B de n bits avec une retenue initiale r. Le problème : la retenue se propage
séquentiellement, ce qui empêche une parallélisation naïve.

###### Question 1 — Pourquoi la boucle ne se parallélise pas

Analyse des dépendances
Itération i :  lit r[i-1]  → calcule C[i] et r[i]  → écrit r[i]
Itération i+1: lit r[i]  ← dépend de l'itération i !
La retenue r[i] dépend de r[i-1] → chaîne de dépendances de longueur n → profondeur $O(n)$ impossible à réduire par
parallélisme simple.
💡 Intuition : C'est exactement le problème du carry propagation ou ripple carry : la retenue peut se propager sur tous
les n bits dans le pire cas (ex: 0111...1 + 0000...1).

###### Question 2 — Diviser pour régner avec 3 appels récursifs

Stratégie
On découpe A et B en deux moitiés gauche (poids faibles) et droite (poids forts). On ne connaît pas la retenue
intermédiaire rg, donc on calcule la moitié droite deux fois : une avec retenue 0 et une avec retenue 1.
Algorithme complet
add(A, B, r, n) :
si n == 1 :
u ← A[0] + B[0] + r // u ∈ {0,1,2,3}
retourner ([u mod 2], u div 2)

m ← n/2
Ag, Bg ← A[0..m-1], B[0..m-1]  // moitié gauche (poids faibles)
Ad, Bd ← A[m..n-1], B[m..n-1]  // moitié droite (poids forts)

// Trois appels EN PARALLÈLE
(Cg, rg)  ← add(Ag, Bg, r, m)  // gauche avec la vraie retenue
(Cd0, rd0) ← add(Ad, Bd, 0, m)  // droite si retenue entrante = 0
(Cd1, rd1) ← add(Ad, Bd, 1, m)  // droite si retenue entrante = 1

// Sélection selon la retenue produite par la gauche
si rg == 0 :
retourner (Cg ++ Cd0, rd0)
sinon :
retourner (Cg ++ Cd1, rd1)
💡 Idée clé : On précalcule les deux cas possibles pour la moitié droite, puis on choisit le bon en $O(1)$ une fois rg
connu. C'est l'astuce "spéculation sur la retenue".

###### Question 3 — Analyse W(n), D(n), et profondeur arithmétique Da(n)

Récurrences
Travail : $$W(n) = 3W(n/2) + $O(n)$$$
Application du Théorème maître : a=3, b=2, f(n)=$O(n)$, n^{log_b a} = n^{log_2 3} ≈ n^{1.585}
Comme 1.585 > 1 → Cas 1 du théorème maître : $$\boxed{W(n) = O(n^{\log_2 3}) \approx O(n^{1.585})}$$
⚠️ Piège : Ce n'est pas O(n log n) ! C'est le Cas 1 du théorème maître car a=3 > b=2.
Profondeur : $$D(n) = D(
n/2) + $O(1)$$$ Les 3 appels sont en parallèle → on ne compte qu'une fois D(n/2). La sélection finale est $O(
1)$. $$\boxed{D(n) = O(\log n)}$$
Profondeur arithmétique Da(n) (opérations bit sur les entrées A, B) :
Les opérations A[i]+B[i] sont $O(1)$ au niveau des bits. La sélection ne relit pas A, B. Donc : $$D_a(n) = D_a(n/2) + $
O(1)$ \Rightarrow \boxed{D_a(n) = O(\log n)}$$

###### Question 4 — Algorithme d'incrément parallèle

Stratégie : Scan parallèle par AND
Pour incrémenter C, la retenue se propage à travers tous les bits à 1 consécutifs depuis le LSB.
increment(C, n) :
// Calcul parallèle : carry_i = 1 ssi C[0..i-1] sont tous à 1
// (la retenue arrive jusqu'à la position i)

// Étape 1 : préfixe ET en parallèle — $O(\log n)$ profondeur, $O(n)$ travail
carry[0] ← 1
pour tout i de 1 à n-1 en parallèle :
carry[i] ← AND(C[0], C[1], ..., C[i-1])  // via scan

// Étape 2 : calcul des nouvelles valeurs — $O(1)$ profondeur, $O(n)$ travail
pour tout i de 0 à n-1 en parallèle :
C'[i] ← C[i] XOR carry[i]

retenue_sortie ← AND(C[0], ..., C[n-1])
retourner C', retenue_sortie
Analyse : W = $O(n)$, D = $O(\log n)$ ✓

###### Question 5 — Addition avec 2 appels récursifs via l'incrément

Stratégie
Au lieu de calculer la moitié droite deux fois, on la calcule une seule fois avec retenue 0, puis on incrémente si la
retenue gauche vaut 1.
add2(A, B, r, n) :
si n == 1 :
u ← A[0] + B[0] + r
retourner ([u mod 2], u div 2)

m ← n/2

// Deux appels EN PARALLÈLE (au lieu de trois)
(Cg, rg) ← add2(Ag, Bg, r, m)
(Cd, rd) ← add2(Ad, Bd, 0, m)

// Correction si nécessaire
si rg == 1 :
(Cd, rd) ← increment(Cd, m)   // O(log m) profondeur, O(m) travail

retourner (Cg ++ Cd, rd)
💡 Idée clé : L'incrément remplace le troisième appel récursif. C'est moins coûteux en travail que de recalculer toute la
moitié droite.

###### Question 6 — Analyse de add2

Récurrences
Travail : $$W(n) = 2W(n/2) + W_{\text{inc}}(n/2) + $O(n)$ = 2W(n/2) + $O(n)$$$ a=2, b=2, f(n)=$O(n)$, n^{log_2 2} = n^1 = n → Cas 2 (borderline) : $$
\boxed{W(n) = O(n \log n)}$$
Mieux que les O(n^{1.585}) de la version à 3 appels ! ✓
Profondeur : Les 2 appels récursifs sont en parallèle → profondeur D(n/2). Ensuite l'incrément séquentiel avec profondeur $O(\log n)$ :
$$D(n) = D(n/2) + O(\log n)$$
En développant (télescopage) : $$D(n) = \sum_{i=0}^{\log n - 1} O(\log(n/2^i)) = \sum_{i=0}^{\log n - 1} O(\log n - i) =
O\left(\frac{(\log n)^2}{2}\right) = \boxed{O(\log^2 n)}$$
⚠️ Comparaison : La version à 3 appels est plus rapide ($O(\log n)$) mais fait plus de travail (O(n^1.585)). La version
à 2 appels fait moins de travail (O(n log n)) mais a plus de profondeur (O(log²n)). Trade-off classique !

###### Question 7 — Algorithme $O(\log n)$ profondeur et $O(n)$ travail par scan de préfixe

Stratégie : Composition de fonctions affines booléennes via scan parallèle
C'est l'approche la plus élégante et la plus efficace.
Rappel du cadre algébrique
Chaque retenue vérifie : rk = gk ∨ (pk ∧ rk-1) où :

* gk = 1 si Ak + Bk ≥ β (génération de retenue)
* pk = 1 si Ak + Bk = β−1 (propagation de retenue)
  On définit la fonction affine booléenne : Tk(x) = gk ∨ (pk ∧ x)
  Loi de composition
  Calculons (Tb ∘ Ta)(x) = Tb(Ta(
  x)) : $$T_b(T_a(x)) = g_b \vee (p_b \wedge (g_a \vee (p_a \wedge x)))$$ $$= g_b \vee (p_b \wedge g_a) \vee (p_b \wedge p_a \wedge x)$$ $$= \underbrace{(g_b \vee (p_b \wedge g_a))}{u{b,a}} \vee \left(\underbrace{(p_b \wedge p_a)}{v{b,a}} \wedge x\right)$$
  Donc la composition de deux fonctions affines est stable : (u, v) ∘ (u', v') = (u ∨ (v ∧ u'), v ∧ v') ✓
  Algorithme complet
  addition_scan(A, B, r, n) :
  // Étape 1 : Calcul des prédicats locaux — $O(1)$ profondeur, $O(n)$ travail
  pour tout k de 0 à n-1 en parallèle :
  gk ← (Ak + Bk ≥ β)    // booléen
  pk ← (Ak + Bk = β-1)  // booléen
  // Tk représentée par (gk, pk)

  // Étape 2 : Scan de préfixe avec l'opérateur ∘ — $O(\log n)$ profondeur, $O(n)$ travail
  // Calcule Uk = Tk ∘ Tk-1 ∘ ... ∘ T0, représentée par (uk, vk)
  (u, v) ← prefix_scan(⊗, [(g0,p0), (g1,p1), ..., (gn-1,pn-1)])
  // où (ub, vb) ⊗ (ua, va) = (ub ∨ (vb ∧ ua), vb ∧ va)

  // Étape 3 : Calcul des retenues — $O(1)$ profondeur, $O(n)$ travail
  r[-1] ← r
  pour tout k de 0 à n-1 en parallèle :
  rk ← uk ∨ (vk ∧ r)   // car rk = Uk(r)

  // Étape 4 : Calcul des chiffres de sortie — $O(1)$ profondeur, $O(n)$ travail
  pour tout k de 0 à n-1 en parallèle :
  Ck ← (Ak + Bk + r[k-1]) mod β

  s ← rn-1 // retenue finale
  retourner C, s
  Analyse finale
  | Étape | Profondeur | Travail |
  | --- | --- | --- |
  | Calcul g, p | O(1) | O(n) |
  | Scan préfixe ⊗ | O(log n) | O(n) |
  | Calcul retenues | O(1) | O(n) |
  | Calcul C | O(1) | O(n) |
  | Total | O(log n) | O(n) |
  ✅ Optimal ! $O(\log n)$ profondeur, $O(n)$ travail.
  🔑 Idée clé fondamentale : En reconnaissant que les Tk forment un monoïde sous la composition(opération associative,
  élément neutre (0, 1)), on peut appliquer un scan parallèle pour calculer tous les préfixes en $O(\log n)$ profondeur.
  C'est l'application paradigmatique du scan parallèle à un problème a priori séquentiel.

📚 Résumé de la feuille

#### Méthodes et techniques clés

1. Réduction parallèle : transformer un problème de recherche en réduction par min/max
2. Technique des blocs doublants : compromis profondeur/travail pour l'early termination
3. Diviser pour régner avec spéculation : calculer les deux cas possibles en parallèle
4. Incrément via scan-AND : application du préfixe parallèle
5. Scan sur monoïde : la technique la plus puissante — si l'opération est associative, le scan parallèle
   donne $O(\log n)$ profondeur

#### Formules importantes

$$W(n) = 3W(n/2) + $O(n)$ \Rightarrow O(n^{\log_2 3})$$ $$W(n) = 2W(n/2) + $O(n)$ \Rightarrow O(n \log n)$$ $$D_{\text{scan}}(n) = O(\log n), \quad W_{\text{scan}}(n) = $O(n)$$$
Composition des fonctions affines booléennes : $$(u_b, v_b) \circ (u_a, v_a) = (u_b \vee (v_b \wedge u_a),\ v_b \wedge
v_a)$$
Erreurs et pièges fréquents
| Piège | Comment l'éviter |
| --- | --- |
| Confondre Cas 1 et Cas 2 du Théorème Maître | Comparer log_b(a) avec le degré de f(n) |
| Oublier que les blocs de Q2 sont séquentiels → D = O(log²n) et non O(log n) | Toujours tracer le graphe de
dépendances |
| Croire que "composition associative" = "commutatif" | La composition de fonctions n'est pas commutative en général ! |
| Dans add2, oublier que rd change aussi lors de l'incrément | L'incrément retourne à la fois le nouveau tableau et la
retenue sortante |
| Dire que la parallélisation est impossible parce qu'il y a des dépendances | Les dépendances ralentissent, elles
n'empêchent pas — le scan les résout |
🏋️ Questions d'entraînement
Q1. Donnez un algorithme parallèle pour calculer le maximum d'un tableau de n éléments. Quelle est sa profondeur et son
travail ?
Réponse : Réduction par max → D = $O(\log n)$, W = $O(n)$.
Q2. Adaptez l'algorithme de Q7 pour additionner des entiers en base 10 (β=10). Quels sont gk et pk ?
Réponse : gk = 1[Ak+Bk≥10], pk = 1[Ak+Bk=9]. L'algorithme est identique.
Q3. Dans l'algorithme add à 3 appels (Q2-Q3), que se passe-t-il si n n'est pas une puissance de 2 ? Peut-on quand même
appliquer le Théorème Maître ?
Réponse : On prend m = ⌊n/2⌋. Le théorème maître s'applique avec la même conclusion.
Q4. Montrez que l'identité pour la composition (⊗) est (0, 1) (c.-à-d. la fonction identité T(x) = x).
Réponse : T(x) = 0 ∨ (1 ∧ x) = x ✓. Et (u,v) ⊗ (0,1) = (u ∨ (v∧0), v∧1) = (u, v) ✓.
Q5. Quelle est la profondeur de add2 si l'incrément a profondeur $O(1)$ (hypothèse) ?
Réponse : D(n) = D(n/2) + $O(1)$ → D(n) = $O(\log n)$. L'incrément est le goulot d'étranglement.

C'est noté pour la séance 5 ! Nous passons ici de la théorie des algorithmes parallèles à des modèles de programmation
de plus haut niveau, très utilisés dans l'industrie pour le traitement de données massives (Big Data) : OpenMP,
MapReduce, et l'opération de Filtrage (Filter).
Voici votre cours détaillé et structuré pour cette cinquième séance.


---

<a id="seance-5"></a>

## Séance 5 — OpenMP, MapReduce et modèles de filtrage

> Plage source conservée : lignes `1385` à `1776` de `course.txt`.

### Partie Théorique

#### Séance 5 : OpenMP, MapReduce et Modèles de Filtrage

Objectif de la séance : Découvrir comment structurer des traitements parallèles à grande échelle sur des données
distribuées ou en mémoire partagée, en utilisant des modèles fonctionnels (Map, Reduce, Filter) et des pragmas (OpenMP).

1. Introduction à OpenMP (Pratique)
   Bien que l'essentiel de notre cours soit théorique, il est crucial de savoir comment ces concepts se traduisent dans
   la vraie vie. OpenMP est une interface de programmation (API) standard pour la mémoire partagée (C, C++, Fortran).
   Au lieu de gérer manuellement des fork et join, OpenMP utilise des directives de compilation (pragmas) pour indiquer
   au compilateur quelles parties du code doivent être parallélisées.
   Exemple de traduction de notre for// théorique :
   C

// Code C avec OpenMP
#pragma omp parallel for
for (int i = 0; i < n; i++) {
A[i] = B[i] + C[i];
}
Sous le capot, le compilateur OpenMP va générer le graphe de dépendance, créer le pool de threads, et gérer
l'ordonnancement (statique, dynamique, ou guidé) automatiquement.

2. Le Modèle MapReduce
   MapReduce est un modèle de programmation rendu célèbre par Google , conçu spécifiquement pour traiter d'énormes
   volumes de données de manière distribuée sur des clusters de machines.

Il repose sur deux fonctions fonctionnelles primitives, exécutées séquentiellement (l'une après l'autre, mais chacune
est hautement parallélisée):

1.

Phase MAP : On prend l'ensemble des données d'entrée, et on applique une fonction Map sur chaque élément de manière
totalement indépendante. La sortie de cette fonction est une liste de paires (clé, valeur).

    * Exemple (Comptage de mots) : Pour la phrase "le chat mange le chat", le Map émet ("le", 1), ("chat", 1), ("mange", 1), ("le", 1), ("chat", 1).

2.

Phase REDUCE : Le système regroupe toutes les valeurs associées à la même clé. Ensuite, on applique la fonction Reduce
sur chaque groupe pour produire un résultat agrégé final.

    * Exemple (suite) : Le système regroupe la clé "le" : ("le", [1, 1]). Le Reduce somme les valeurs et sort : ("le", 2).

Pourquoi c'est puissant ? Parce que le Map est "embarrassingly parallel" (les tâches ne communiquent pas entre elles).
La seule complexité réside dans le tri et le regroupement des clés entre la phase Map et la phase Reduce (souvent appelé
le Shuffle). Ce modèle est très efficace pour les données qui se prêtent à une traduction rapide en clé/valeur.

3. L'Opération de Filtrage (Filter) et les Pipelines
   Un "filtre" en multithreading n'est pas juste un "if". C'est une étape fonctionnelle indépendante dans une chaîne de
   traitement de données (un pipeline). Chaque filtre fait généralement une petite tâche spécifique puis passe le relais
   au filtre suivant.

Le problème classique du Filtre Parallèle (Compactage)

Application pratique : Vous avez un tableau d'entiers et vous voulez créer un nouveau tableau ne contenant que les
nombres pairs.

* Séquentiel : Boucle for, test if pair, ajout à la fin du nouveau
  tableau. ($W = \mathcal{O}(n)$, $D = \mathcal{O}(n)$).
* Parallèle naïf ? Impossible avec un simple for// ! Si deux processeurs trouvent un nombre pair en même temps, ils vont
  essayer d'écrire dans la même case du nouveau tableau (conflit d'écriture / modèle mémoire).
  La solution magique : Le Préfixe (encore lui !)
  Pour savoir où écrire dans le tableau de destination, chaque élément a besoin de savoir combien d'éléments valides ont
  été trouvés avant lui. C'est exactement la définition d'une somme préfixe!


1. Map : Créer un tableau B de même taille. Mettre $1$ si l'élément est pair, $0$ sinon. (Parfaitement
   parallèle, $D=\mathcal{O}(1)$).
2. Scan (Préfixe) : Calculer le préfixe sur B. Cela donne l'indice de destination exact de chaque nombre pair. (Vu
   séance 3 : $D=\mathcal{O}(\log n)$).
3. Scatter (Écriture) : Faire un for// : si B[i] était 1, écrire la valeur d'origine à la position donnée par le
   préfixe. (Parfaitement parallèle, $D=\mathcal{O}(1)$).
   Bilan du Filtre Parallèle : $W = \mathcal{O}(n)$, $D = \mathcal{O}(\log n)$.

4. Circuit Optimal pour l'Opération de Préfixe (Schéma du Cours)
   Vos notes présentent un schéma fondamental sur l'optimisation du calcul de la somme préfixe. L'algorithme vu à la
   Séance 3 (Préfixe récursif) fait trop de travail ($W = \mathcal{O}(n \log n)$).
   Pour obtenir un algorithme optimal en travail ($W = \mathcal{O}(n)$ et $D = \mathcal{O}(\log n)$), on utilise un
   circuit en deux passes, illustré par votre schéma :

```text

    t0    t1    t2    t3    t4    t5    t6    t7
     \   /       \   /       \   /       \   /
      (+)         (+)         (+)         (+)   <-- 1ère passe (Aller) : Réduction par paire
       |           |           |           |        (Construit un arbre de somme)
   [ t0+t1 ]   [ t2+t3 ]   [ t4+t5 ]   [ t6+t7 ]
       \___________|___________|___________/
                   |
     [ APPEL RÉCURSIF (PREC 2) sur n/2 éléments ]  <-- (Le circuit est "2 fois plus petit")
                   |
       /___________|___________|___________\
       |           |           |           |
    [t0+t1]   [t0..t3]    [t0..t5]    [t0..t7]
     /   \       /   \       /   \       /
    t0  t0..t1  ...       ...         ...       <-- 2ème passe (Retour) : Distribution
```

Analyse de ce circuit :

* Le travail total est défini par la récurrence : $W(n) = n + W(n/2)$.


* Cette somme géométrique converge : $W(n) = \sum \frac{n}{2^i} < 2n$. Donc $W = \mathcal{O}(n)$ ! Le travail est
  proportionnel à la taille de l'entrée.


* La profondeur est $D(n) = D(n/2) + \mathcal{O}(1) \implies D = \mathcal{O}(\log n)$.


5. Lien avec votre TD (MapReduce)
   Votre TD met en pratique MapReduce sur des problèmes d'agrégation et de listes.
   <a id="seance-5-exercice-1"></a>

#####  * Exercice 1 : Count and Say

    * Vous devez transformer [1,1,3,4,4] en "deux 1, un 3, deux 4".
    * L'idée (Q2) est de découper le tableau. Le Map lit de petits intervalles en séquentiel et produit des listes partielles (ex: le premier Map voit [1,1,3] et émet [(2,1), (1,3)]).
    * Le Reduce prend ces listes et les fusionne. Si la fin d'une liste est le même chiffre que le début de la liste suivante, on additionne les occurrences.

<a id="seance-5-exercice-2"></a>

#####  * Exercice 2 : Le cache LRU

    * C'est un problème complexe car le cache "glisse" avec le temps (forte dépendance temporelle).
    * Pour le paralléliser, l'astuce (Q2) est de traiter des sous-séquences d'accès, et d'utiliser une opération de "composition" (qui servira de Reduce) pour combiner l'état du cache de deux sous-séquences adjacentes. L'algorithme final sera un arbre de réduction.

Souhaitez-vous que l'on détaille la résolution d'un de ces deux exercices de MapReduce (le "Count and Say" ou le "LRU")
pour voir comment on écrit formellement une opération de Map et une opération de Reduce ?

### Partie Pratique (TD)

#### TD Algorithmique Avancée – MapReduce : Correction Complète et Pédagogique

📋 Vue d'ensemble de la feuille
Thèmes abordés :

* La primitive map_reduce et son utilisation pour paralléliser des problèmes séquentiels
* Conception d'opérateurs de réduction associatifs sur des structures de données
* Le thief-splitting et ses impacts sur le travail
* Optimisation du travail parallèle pour se rapprocher du séquentiel
  Compétences clés requises :
* Savoir identifier l'opérateur de réduction adapté à un problème
* Maîtriser l'analyse W/D via les récurrences ou la structure du map_reduce
* Comprendre la notion de fusion de résultats partiels (merge)
* Identifier quand et pourquoi le parallélisme introduit du surcoût

🔧 Rappel : map_reduce en parallèle
map_reduce(f, ⊕, T, d, f) :

1. Map : applique f à chaque élément (ou bloc) → $O(1)$ profondeur
2. Reduce : combine avec ⊕ en arbre binaire → $O(\log n)$ profondeur, $O(n)$ travail si ⊕ est $O(1)$
   ⚠️ Si ⊕ coûte O(k), alors : D = O(k · log n) et W = O(k · n)

<a id="seance-5-exercice-3"></a>

##### Exercice 1 — Count and Say

🔍 Reformulation du problème
On dispose d'un tableau T de n entiers. On veut produire V, un vecteur de couples (count, valeur) représentant les runs(
séquences consécutives identiques) de T.
Exemple :
T = [1, 1, 3, 4, 4, 4, 2, 2, 1, 3, 3]
V = [(2,1), (1,3), (3,4), (2,2), (1,1), (2,3)]
Les concepts sous-jacents : Run-Length Encoding (RLE), fusion de résultats partiels, associativité de l'opérateur de
merge.

###### Question 1 — Algorithme séquentiel cseq en $O(n)$

Stratégie
On parcourt T une seule fois en maintenant un compteur du run courant.
cseq(T, d, f) :           // traite T[d..f-1]
V ← vecteur vide
si d ≥ f : retourner V

courant ← T[d]
compte ← 1

pour i de d+1 à f-1 faire :
si T[i] == courant :
compte ← compte + 1
sinon :
ajouter (compte, courant) à V
courant ← T[i]
compte ← 1

ajouter (compte, courant) à V // ne pas oublier le dernier run !
retourner V
Analyse : Une seule passe → $O(n)$ en temps, $O(n)$ en espace (au pire n runs de longueur 1). ✓
⚠️ Piège classique : Oublier d'ajouter le dernier run après la boucle.
Exemple de trace :
T = [1, 1, 3], d=0, f=3
i=1: T[1]=1 == courant=1 → compte=2
i=2: T[2]=3 != courant=1 → V=[(2,1)], courant=3, compte=1
fin: V=[(2,1),(1,3)]  ✓

###### Question 2 — Algorithme parallèle avec map_reduce

Stratégie
L'idée est de découper T en blocs, d'appliquer cseq à chaque bloc (map), puis de fusionner les vecteurs de couples (
reduce).
La difficulté clé : à la frontière entre deux blocs, le dernier run du bloc gauche et le premier run du bloc droit
peuvent concerner la même valeur → il faut les fusionner.
Définition de l'opérateur de fusion ⊕ :
merge(V1, V2) :
// V1 = [..., (c1, v1)]  (dernier élément de V1)
// V2 = [(c2, v2), ...]  (premier élément de V2)

si V1 est vide : retourner V2
si V2 est vide : retourner V1

si v1 == v2 :   // même valeur aux deux bouts → fusion du run
retourner V1[0..-2] ++ [(c1+c2, v1)] ++ V2[1..]
sinon :         // valeurs différentes → simple concaténation
retourner V1 ++ V2
Algorithme parallèle :
count_and_say_parallel(T, n) :
// Map : appliquer cseq à chaque bloc de taille b = $O(\log n)$
// Reduce : fusionner avec merge

retourner map_reduce(
f = λ(d,f) → cseq(T, d, f), // fonction map
⊕ = merge, // opérateur de réduction
T = [0, b, 2b, ..., n], // découpage en blocs
init = []                           // vecteur vide = neutre
)
Vérification de l'associativité de ⊕
C'est crucial pour que map_reduce soit correct !
Prenons V1 ++ V2 ++ V3 :

* (V1 ⊕ V2) ⊕ V3 : on fusionne V1-V2 d'abord, puis le résultat avec V3
* V1 ⊕ (V2 ⊕ V3) : on fusionne V2-V3 d'abord, puis V1 avec le résultat
  Dans les deux cas, on finit par examiner exactement les mêmes frontières (V1/V2 et V2/V3). Le résultat est le même ✓
  Élément neutre : le vecteur vide [] → [] ⊕ V = V ⊕ [] = V ✓
  Illustration sur l'exemple
  T = [1, 1, 3, | 4, 4, 4, | 2, 2, 1, | 3, 3]
  Bloc 0 Bloc 1 Bloc 2 Bloc 3

Map :
cseq(Bloc 0) = [(2,1),(1,3)]
cseq(Bloc 1) = [(3,4)]
cseq(Bloc 2) = [(2,2),(1,1)]
cseq(Bloc 3) = [(2,3)]

Reduce (arbre) :
[(2,1),(1,3)] ⊕ [(3,4)]  → derniers/premiers : (1,3) et (3,4) → 3≠4 → [(2,1),(1,3),(3,4)]
[(2,2),(1,1)] ⊕ [(2,3)]  → (1,1) et (2,3) → 1≠3 → [(2,2),(1,1),(2,3)]

[(2,1),(1,3),(3,4)] ⊕ [(2,2),(1,1),(2,3)] → (3,4) et (2,2) → 4≠2 → V final ✓

###### Question 3 — Analyse W et D

Paramètres

* n : taille du tableau
* b : taille d'un bloc (à choisir)
* Nombre de blocs : n/b
* Coût de merge : $O(1)$ (on ne regarde que les extrémités + concaténation en $O(1)$ si représentation par liste chaînée
  ou en O(taille) sinon)
  💡 Supposons merge en O(taille du résultat) dans le pire cas, mais $O(1)$ si on utilise des listes chaînées ou des
  vecteurs avec pointeurs.
  Avec merge en $O(1)$ (listes chaînées) :
  | Mesure | Calcul | Résultat |
  | --- | --- | --- |
  | Travail W | n évaluations de T par cseq + n-1 merges O(1) | O(n) |
  | Profondeur D | cseq sur bloc de taille b : O(b), arbre de réduction : O(log(n/b)) | O(b + log(n/b)) |
  En prenant b = log n : D = $O(\log n)$, W = $O(n)$ ✓
  En pratique (merge en O(taille du vecteur)) :
  | Mesure | Calcul | Résultat |
  | --- | --- | --- |
  | Travail W | O(n) (chaque élément traité une fois + merges en cascade) | O(n) amortis |
  | Profondeur D | O(b) pour map + O(log n) niveaux × O(taille max vecteur) | O(b + n) au pire |
  ⚠️ Piège : Si on ne fait pas attention à la représentation, le merge peut coûter $O(n)$ à la racine de l'arbre →
  profondeur $O(n)$, ce qui annule tout le bénéfice !
  Conclusion standard (attendue à l'examen) : $$\boxed{W = $O(n)$, \quad D = O(\log n)}$$ avec une implémentation
  adaptée du merge.

###### Question 4 — Comment améliorer ?

Problème identifié
Avec le découpage naïf en blocs de taille fixe, si les blocs sont trop petits :

* Beaucoup de merges → overhead
* Si merge est O(|V|), on peut avoir W = O(n log n) à cause de l'arbre
  Améliorations possibles
  Amélioration 1 : Pré-traitement par scan
  On peut d'abord identifier les positions de changement (frontières entre runs) avec un map, puis reconstruire V avec
  un scan :
  // Étape 1 : $O(1)$ profondeur, $O(n)$ travail
  pour tout i de 0 à n-2 en parallèle :
  boundary[i] ← (T[i] != T[i+1]) ? 1 : 0

// Étape 2 : scan préfixe pour numéroter les runs
run_id ← prefix_sum(boundary)   // $O(\log n)$ profondeur, $O(n)$ travail

// Étape 3 : réduction par run_id pour calculer les comptes
// (map_reduce groupé par run_id)
→ W = $O(n)$, D = $O(\log n)$ avec une implémentation propre
Amélioration 2 : Taille de blocs adaptative
Prendre des blocs plus grands (b = √n) pour réduire le nombre de merges au prix d'une profondeur légèrement plus grande.
🔑 Idée clé : L'approche par scan est plus propre et évite entièrement la complexité du merge de vecteurs.

<a id="seance-5-exercice-4"></a>

##### Exercice 2 — Le cache LRU

🔍 Reformulation du problème
On simule un cache LRU (Least Recently Used) de capacité Z pages. Étant donné une séquence d'accès S[0..n-1], on veut
l'état final du cache.
Propriété clé de l'algorithme seqC : il parcourt S de droite à gauche, en ajoutant les pages dans l'ordre de leur
dernière occurrence. Les Z premières pages distinctes rencontrées en allant de droite à gauche sont exactement les Z
pages en cache à la fin.
Exemple :
Z=3, S = [3, 2, 8, 2, 7, 5, 3]
Parcours droite→gauche : 3, 5, 7, 2, 8, 2(déjà vu), 3(déjà vu)
Premières 3 distinctes : 3, 5, 7 → Cache = [3, 5, 7] ✓

###### Question 1 — Complexité de seqC

Analyse
L'algorithme parcourt S une fois de droite à gauche (n itérations). Pour chaque élément :

* Recherche dans la table de hachage T : $O(1)$ amorti
* Ajout éventuel dans C et T : $O(1)$ amorti
  L'arrêt anticipé se produit dès que C atteint la taille Z.
  Dans le pire cas (les Z pages en cache sont les Z premières dans S en partant de la fin) : on parcourt tout S.
  $$\boxed{W_{\text{seq}} = $O(n)$}$$
  Remarque : En pratique, on peut s'arrêter dès qu'on a trouvé Z pages distinctes. Dans le meilleur cas : O(Z).

###### Question 2 — Version parallèle avec map_reduce

Stratégie
Observation clé : L'algorithme seqC est en fait un calcul de "Z premières valeurs distinctes vues de la droite".
Si on découpe S en blocs et qu'on applique seqC à chaque bloc, on obtient une liste ordonnée des pages vues dans ce
bloc (de la plus récente à la moins récente). Il faut ensuite fusionner ces listes en respectant la priorité (les blocs
les plus à droite ont priorité).
Opérateur de fusion ⊕ pour LRU
merge_lru(C_gauche, C_droite) :
// C_droite a priorité (bloc plus récent)
// On veut garder les Z premières pages distinctes
// en donnant priorité à C_droite

résultat ← C_droite // pages du bloc droit en premier

pour chaque page p dans C_gauche faire :
si p n'est pas dans résultat :
ajouter p à résultat
si |résultat| == Z :
retourner résultat

retourner résultat
Algorithme parallèle :
lru_parallel(Z, S, n) :
retourner map_reduce(
f = λ(d,f) → seqC_local(Z, S, d, f),
// seqC sur le bloc [d,f), retourne liste ordonnée
⊕ = merge_lru,
S = [0, b, 2b, ..., n],
init = []
)
Vérification de l'associativité de ⊕
merge_lru est associatif ? Voyons :
Intuitivement : (A ⊕ B) ⊕ C = donner priorité à C, puis B, puis A et A ⊕ (B ⊕ C) = donner priorité à (B⊕C) sur A =
priorité à C, puis B, puis A ✓
Plus formellement : dans tous les cas, on garde les Z premières pages distinctes dans l'ordre de priorité droite >
gauche, ce qui est associatif. ✓
Analyse W et D
Coût de merge_lru(C1, C2) : On parcourt C_gauche (taille ≤ Z) et on teste l'appartenance à résultat (taille ≤ Z). Avec
une table de hachage : O(Z) par merge.
Nombre de merges dans l'arbre : O(n/b) feuilles → O(n/b) merges → mais en arbre, O(log(n/b)) niveaux, donc :
| Mesure | Calcul | Résultat |
| --- | --- | --- |
| Travail W | n/b feuilles × O(b) + (n/b - 1) merges × O(Z) | O(n + Z·n/b) |
| Profondeur D | O(b) map + O(log(n/b)) niveaux × O(Z) merge | O(b + Z·log(n/b)) |
En prenant b = Z :
$$\boxed{W(n) = O(Z \cdot n/Z + Z \cdot n/Z) = O(n + Z \cdot n/Z) = O(n + n) = $O(n)$}$$
Hmm, réanalysons. Le sujet dit W = O(Z×n). Prenons b = 1 (un élément par feuille) :

* Map : $O(1)$ par feuille, $O(n)$ total
* Reduce : n-1 merges, chacun O(Z) → O(Z·n) total
  $$\boxed{W(n) = O(Z \cdot n), \quad D(n) = O(Z \cdot \log n)}$$
  💡 Intuition du coût : Chaque merge coûte O(Z) car on doit vérifier l'appartenance à une liste de Z éléments. Il y
  a $O(n)$ merges au total → O(Z·n) travail.

###### Question 3 — Impact du thief-splitting sur le travail

Qu'est-ce que le thief-splitting ?
Le thief-splitting (ou work-stealing avec découpage) est une technique de parallélisme dynamique où un processeur
inactif "vole" du travail à un autre en coupant une tâche en cours. Quand une tâche est volée, elle est découpée en deux
sous-tâches de taille égale.
Impact sur map_reduce LRU
Sans thief-splitting, on peut choisir les blocs de taille b optimale. Avec thief-splitting :
Le problème : Le travail de reduction n'est pas linéaire ici — il est en O(Z) par merge. Quand le système découpe des
tâches dynamiquement, il peut créer beaucoup plus de blocs que prévu.
Analyse : Si une tâche portant sur un bloc de taille k est découpée en deux :

* On crée deux sous-blocs de taille k/2
* On ajoute un merge O(Z) supplémentaire qui n'existait pas avant
* En pratique, le découpage peut se faire $O(\log n)$ fois sur chaque chemin → O(Z·log n) merges supplémentaires par
  chemin
  Conséquence : Le thief-splitting peut augmenter le travail total par un facteur supplémentaire, passant de O(Z·n) à
  potentiellement O(Z·n·log n) dans le pire cas.
  🔑 Idée clé : Le thief-splitting est problématique quand l'opérateur de réduction est coûteux (ici O(Z)). Il est bénin
  quand ⊕ est $O(1)$ (ex: sum, max).
  Concrètement : Avec thief-splitting non
  contrôlé : $$W_{\text{thief}} = O(Z \cdot n \cdot \log n) \quad \text{(pire cas)}$$

###### Question 4 — Amélioration pour se rapprocher du travail séquentiel

Objectif : W = $O(n)$ ou O(n + Z·log n)
Idée 1 : Réduire le coût du merge à $O(1)$
Si on représente les listes LRU comme des ensembles ordonnés avec une structure de données persistante (ex: arbres de
fusion), le merge peut être fait en O(log Z) au lieu de O(Z).
$$W_{\text{amélioré}} = O(n \cdot \log Z)$$
Idée 2 : Algorithme basé sur les rangs (meilleure approche)
Observation : La page S[i] se retrouve dans le cache final si et seulement si, parmi toutes les occurrences de S[i] dans
S, la plus récente (= la plus à droite) se trouve parmi les Z premières positions de dernières occurrences.
lru_optimal(Z, S, n) :
// Étape 1 : Pour chaque position i, calculer si c'est la DERNIÈRE occurrence de S[i]
// Un scan par valeur distincte est trop coûteux, on fait autrement

// Étape 1 : map parallèle — $O(1)$ prof, $O(n)$ travail
// Pour chaque i, marquer si S[i] n'apparaît plus dans S[i+1..n-1]
// (= c'est la dernière occurrence de cette valeur)

// Étape 2 : Identifier les Z dernières occurrences les plus à droite
// via un tri ou un scan de sélection

// Étape 3 : Retourner les Z valeurs correspondantes, triées par position
Approche concrète et efficace :
lru_scan(Z, S, n) :
// Étape 1 : calcul des "dernières occurrences" — $O(\log n)$ prof, $O(n)$ travail
// Pour chaque valeur v, trouver max(i | S[i] = v)
// Via une réduction groupée par valeur

last_occ ← map_reduce(
f = λi → (S[i], i), // (valeur, indice)
⊕ = λ(v1,i1),(v2,i2) → // garde la paire avec l'indice max
si v1 == v2 : (v1, max(i1,i2))
sinon : les deux paires séparément,
T = S
)  // retourne un ensemble {(v, last_index(v))}

// Étape 2 : trier par last_index décroissant, garder les Z premiers
sorted ← sort(last_occ, clé = -last_index)   // O(n log n) ou $O(n)$ si radix
cache ← [v pour (v, _) dans sorted[0..Z-1]]

retourner cache
Analyse : $$W = O(n \log n), \quad D = O(\log^2 n) \quad \text{ou} \quad W = $O(n)$, D = O(\log n) \text{ avec radix sort}$$
💡 Intuition de l'amélioration : Au lieu de simuler le cache étape par étape (coûteux à paralléliser), on identifie
directement quelles pages seront en cache à la fin, sans simulation.
Résumé des compromis
| Algorithme | Travail W | Profondeur D |
| --- | --- | --- |
| Séquentiel seqC | O(n) | O(n) |
| map_reduce naïf (b=1) | O(Z·n) | O(Z·log n) |
| map_reduce (b=Z) | O(n) | O(Z·log(n/Z)) |
| Scan + sort | O(n log n) | O(log² n) |
| Scan + radix sort | O(n) | O(log n) ✓ |

📚 Résumé de la feuille

#### Méthodes et techniques clés

1. map_reduce sur blocs : découper en blocs → appliquer algo séquentiel → merger
2. Conception de l'opérateur ⊕ : doit être associatif avec élément neutre
3. Coût de ⊕ détermine W et D : si ⊕ coûte O(k), alors W=O(k·n), D=O(k·log n)
4. Reformulation directe : parfois, au lieu de simuler, on identifie directement le résultat (ex: LRU → problème de
   sélection sur les dernières occurrences)

#### Formules importantes

$$W = O\left(\text{coût map} + \frac{n}{b} \cdot \text{coût}(\oplus)\right), \quad D = O(b + \log\left(\frac{n}{b}\right) \cdot \text{coût}(\oplus))$$
Choix optimal de b : b = coût(⊕) pour équilibrer W et D.
Erreurs et pièges fréquents
| Piège | Comment l'éviter |
| --- | --- |
| Oublier de vérifier l'associativité de ⊕ | Toujours prouver (A ⊕ B) ⊕ C = A ⊕ (B ⊕ C) explicitement |
| Dans Count&Say, oublier la fusion aux frontières | Tester avec deux blocs dont la frontière coupe un run |
| Croire que thief-splitting est toujours neutre | Il multiplie le nombre de merges → coûteux si ⊕ ≠ O(1) |
| Analyser W comme si tous les merges étaient à la racine | L'arbre de réduction répartit les merges, compter les
niveaux |
| Pour LRU, confondre "page accédée" et "page en cache" | Bien retracer la sémantique de seqC (parcours droite→gauche) |
🏋️ Questions d'entraînement
Q1. Donnez un algorithme parallèle map_reduce pour calculer la plus longue suite croissante dans un tableau T. Quel est
l'opérateur de réduction ?
Réponse : ⊕(séq1, séq2) doit gérer la frontière entre les deux séquences. Plus complexe — la LIS n'est pas "locale" → ce
n'est pas directement map_reduce-able en $O(n)$ ; nécessite dp + scan.
Q2. Appliquez map_reduce pour compter le nombre de mots dans un texte (liste de caractères). Quelle est la difficulté
aux frontières ?
Réponse : Aux frontières, un mot peut être coupé → merger en vérifiant si le dernier char du bloc gauche et le premier
du bloc droit sont tous deux non-espace → fusionner les mots partiels. W=$O(n)$, D=$O(\log n)$.
Q3. Pour un cache LRU de capacité Z=1, que vaut le cache final ? Comment l'obtenir directement en $O(\log n)$
profondeur ?
Réponse : C'est simplement la dernière valeur distincte de S = S[n-1] si S est non vide. Ou directement
S[n-1] — $O(1)$ !
Q4. L'opérateur max est-il associatif et commutatif ? Est-ce nécessaire pour map_reduce ?
Réponse : Oui, max est associatif et commutatif. map_reduce requiert seulement l'associativité (pour l'arbre de
réduction). La commutativité est un bonus mais pas requis.
Q5. Expliquez pourquoi, pour Count&Say, remplacer les listes par des listes chaînées avec pointeur de fin permet de
faire le merge en $O(1)$.
Réponse : On accède directement au dernier élément (pointeur de fin) pour comparer, et on relie les deux listes
en $O(1)$ (concaténation par mise à jour de pointeur). La fusion du run frontière demande seulement de modifier les deux
éléments adjacents à la jonction.



---

<a id="seance-6"></a>

## Séance 6 — Algorithmes en cascade et optimisation extrême

> Plage source conservée : lignes `1777` à `2452` de `course.txt`.

### Partie Théorique

C'est la séance 6, et on entre dans la "haute voltige" de l'algorithmique parallèle ! On quitte les simples divisions
par deux pour s'attaquer aux Algorithmes en cascade (Cascading Divide & Conquer).
L'idée centrale de cette séance est brillante : quand un algorithme parallèle a une excellente profondeur ($D$) mais
fait trop de travail ($W$), ou inversement, on va le combiner avec un autre algorithme ou changer la taille de découpe (
par exemple, couper en $\sqrt{n}$ morceaux au lieu de $2$) pour obtenir le meilleur des deux mondes.
Voici votre cours détaillé et structuré pour cette sixième séance.

#### Séance 6 : Algorithmes en Cascade et Optimisation Extrême

Objectif de la séance : Apprendre à briser la barrière du $\mathcal{O}(\log n)$ en profondeur pour certains problèmes (
comme le calcul du maximum), et découvrir comment équilibrer parfaitement le Travail et la Profondeur en découpant les
données en blocs de taille $\sqrt{n}$ ou en $\log n$.

1. Le Maximum "Ultra Rapide" (Modèle CRCW)
   Jusqu'à présent, pour trouver le maximum d'un tableau, on utilisait une réduction (un arbre binaire inversé), ce qui
   donnait une profondeur $D = \mathcal{O}(\log n)$. Peut-on faire plus rapide ? Oui, en temps
   constant $\mathcal{O}(1)$ ! Mais cela nécessite un modèle mémoire qui autorise les écritures concurrentes (CRCW).
   L'approche naïve en $\mathcal{O}(1)$
   On compare tous les éléments avec tous les autres en même temps.

```text

Fonction est_max_ultra_rapide(T, i) :
    est_max = Vrai
    // On lance n comparaisons en parallèle pour l'élément i
    for// j allant de 0 à n-1 (avec j != i) faire
        Si T[j] > T[i] alors
            est_max = Faux  // Écriture concurrente (CRCW) !
        Fin Si
    fin for//
    retourner est_max
```

Pour trouver le maximum de tout le tableau : on lance est_max_ultra_rapide pour chaque indice $i$ en parallèle.

* Profondeur ($D$) : $\mathcal{O}(1)$. C'est instantané !
* Travail ($W$) : $\mathcal{O}(n^2)$ car on fait $n \times n$ comparaisons. C'est beaucoup trop lourd.
  L'approche en cascade (Blocs de $\sqrt{n}$)
  Pour ramener le travail vers $\mathcal{O}(n)$, on utilise une stratégie en cascade.

1. On découpe le tableau de taille $n$ en $\sqrt{n}$ blocs de taille $\sqrt{n}$.
2. On trouve le maximum de chaque bloc récursivement.
3. On trouve le maximum des $\sqrt{n}$ maximums avec l'algorithme "Ultra Rapide".
   Complexité de cette cascade :

* Le travail devient $W(n) = \sqrt{n}W(\sqrt{n}) + \mathcal{O}(n)$, ce qui donne $W(n) = \mathcal{O}(n \log(\log n))$.
* La profondeur devient $D(n) = D(\sqrt{n}) + \mathcal{O}(1)$, ce qui donne $D(n) = \mathcal{O}(\log(\log n))$.
  On a réussi à faire mieux que $\mathcal{O}(\log n)$ !

2. Le Tri Fusion Hautement Parallèle
   Lors de la séance 3, nous avons vu que le tri fusion parallèle classique avait un défaut : l'étape de fusion était
   séquentielle, ce qui bloquait la profondeur totale à $D = \mathcal{O}(n)$.
   Pour régler ce problème, il faut paralléliser la fusion elle-même.
   L'algorithme de Fusion Parallèle
   Soient deux tableaux triés $A$ et $B$ à fusionner dans un tableau $S$.
1. Trouver le pivot : On prend l'élément du milieu de $A$ (disons $A[m]$).
2. Dichotomie : On cherche par recherche dichotomique où $A[m]$ devrait s'insérer dans $B$. Cela coupe $B$ en deux
   parties : $B_1$ (éléments $< A[m]$) et $B_2$ (éléments $> A[m]$).
3. Placement : On sait exactement où placer $A[m]$ dans le tableau de sortie $S$.
4. Appels récursifs : On lance en parallèle la fusion de la moitié gauche de $A$ avec $B_1$, et la moitié droite de $A$
   avec $B_2$.

```text

// Schéma de la fusion parallèle
join( Fusion_Parallele(A_gauche, B1, S_gauche),
      Fusion_Parallele(A_droite, B2, S_droite) )
Nouvelle Analyse de Complexité :
* Fusion : La recherche dichotomique coûte $\mathcal{O}(\log n)$. La profondeur de la fusion seule est $D_{fusion}(n) = \mathcal{O}(\log n) + D_{fusion}(n/2) \implies \mathcal{O}(\log^2 n)$.
* Tri complet : En remplaçant la fusion séquentielle par cette fusion parallèle, la profondeur globale du tri devient $D_{tri}(n) = D_{tri}(n/2) + \mathcal{O}(\log^2 n) \implies D = \mathcal{O}(\log^3 n)$ (ou $\mathcal{O}(\log^2 n)$ avec une analyse plus fine). Le travail reste optimal à $W = \mathcal{O}(n \log n)$.

```

3. Lien avec votre TD : La magie des blocs $\sqrt{n}$
   Votre TD illustre parfaitement ce principe de "Cascade" pour optimiser des algorithmes de base (comme le calcul de
   puissances ou de préfixes) en réduisant le nombre total d'opérations tout en gardant une
   profondeur $\mathcal{O}(\log n)$.
   <a id="seance-6-exercice-1"></a>

##### Exercice 1 : Toutes les puissances

Vous voulez calculer $x^0, x^1, x^2, \dots, x^n$.

* Un algorithme de préfixe classique donne bien une profondeur de $\mathcal{O}(\log n)$, mais il effectue $2n$
  multiplications , soit le double de l'algorithme séquentiel initial.


*

La solution en cascade (puissanceRapide) : Au lieu de faire un préfixe géant, l'algorithme utilise des blocs de
taille $\sqrt{n}$.

    1. Il calcule les puissances jusqu'à $x^{\sqrt{n}}$.


    2. Il fait un appel récursif pour sauter de bloc en bloc ($x^{\sqrt{n}}, x^{2\sqrt{n}}, \dots$).


    3. Il utilise une double boucle parallèle parallelFor pour combler les "trous" à l'intérieur de chaque bloc en multipliant les résultats.

*

Résultat : La profondeur reste $\mathcal{O}(\log n)$, mais le nombre de multiplications chute
à $n + \mathcal{O}(\sqrt{n})$, ce qui est asymptotiquement optimal!

<a id="seance-6-exercice-2"></a>

##### Exercice 2 : Préfixe de Ladner-Fisher

L'algorithme de Ladner-Fisher est une implémentation directe du préfixe récursif.

* Le TD montre que sa profondeur réelle est en $\mathcal{O}(\log^2 n)$ à cause de la gestion des tableaux.


* Là encore, l'astuce de la cascade est proposée : on découpe le tableau $A$ en blocs de taille $\sqrt{n}$ , on fait des
  réductions locales , un calcul intermédiaire sur $\sqrt{n}$ éléments , puis $\sqrt{n}$ calculs récursifs en parallèle.

Voulez-vous que l'on rédige en détail la question 4 de l'exercice 1, c'est-à-dire la démonstration qui prouve que la
double boucle parallelFor a bien une profondeur $\mathcal{O}(\log n)$ et ne fait que $n - o(n)$ opérations ? C'est un
grand classique des partiels !

Cette photo de tableau est géniale ! Elle résume exactement la philosophie de cette 6ème séance. Comme l'a écrit votre
professeur : "Principe des algos en cascade $\rightarrow$ créer un hybride avec les propriétés voulues".
L'idée de base est qu'on a un algorithme "ULTRA" très rapide (profondeur $\mathcal{O}(1)$) mais beaucoup trop gourmand
en ressources (travail $\mathcal{O}(n^2)$). Comme indiqué sur la photo : pour respecter la contrainte d'un travail
total $W = \mathcal{O}(n)$, on ne peut utiliser cet algorithme ULTRA que sur des tableaux d'une taille maximale
de $\sqrt{n}$ (car $(\sqrt{n})^2 = n$).
Voici la traduction au propre du schéma de votre tableau, accompagnée de son pseudo-code et de l'explication de ses
coûts.

1. Le Schéma de la Cascade (Hybride 1)
   Ce schéma reproduit le dessin de votre professeur. Il montre comment on découpe le problème pour limiter la taille de
   l'entrée donnée à l'algorithme ULTRA.

```text

 Axe du Temps (Profondeur D)
 |
 |       Tableau initial T de taille n : [ t_0, t_1, t_2, ..., t_{n-1} ]
 |
 |       1. Découpage en √n blocs de taille √n :
 |          [ t_0 ... t_{√n-1} ]     ...     [ ... t_{n-1} ]
 |                  |                               |
 |                  v                               v
 |          +---------------+               +---------------+
 | D(√n)    | Appel Récursif|      ...      | Appel Récursif|  <-- Chaque bloc calcule son max en parallèle
 |          +---------------+               +---------------+
 |                  |                               |
 |                max_0                           max_k        <-- On obtient un tableau de √n maximums locaux
 |                  \                               /
 |                   \                             /
 |                    \                           /
 |                     +-------------------------+
 | O(1)                |    Algorithme ULTRA     |             <-- On applique l'algo ultra-rapide sur les √n éléments
 |                     +-------------------------+
 |                                  |
 v                              MAX GLOBAL
Explication visuelle : La flèche verticale à gauche sur votre photo montre bien l'addition des profondeurs. Le temps total $D(n)$ est égal au temps pris par les appels récursifs $D(\sqrt{n})$ PLUS le temps pris par l'algo ULTRA $\mathcal{O}(1)$. Ce qui donne l'équation écrite à droite sur le tableau : $D(n) = D(\sqrt{n}) + \mathcal{O}(1)$.

```

2. Le Pseudo-Code de l'Hybride (Calcul du Max)
   Voici comment on programme concrètement ce que décrit le schéma.

```text

Fonction Max_Hybride_Cascade(T, n) :
    // Condition d'arrêt (quand le tableau est tout petit, on fait un max classique)
    Si n <= 2 alors
        retourner Max_Sequentiel(T)
    Fin Si

    taille_bloc = racine_carree(n)
    Soit M un nouveau tableau de taille taille_bloc  // Pour stocker les max locaux

    // Étape 1 : Diviser et Régner (La ligne des "Appels Récursifs" du schéma)
    // On lance la recherche sur les √n blocs EN PARALLÈLE
    for// i allant de 0 à taille_bloc - 1 faire
        Sous_Tableau = T[ i*taille_bloc ... (i+1)*taille_bloc - 1 ]
        M[i] = Max_Hybride_Cascade(Sous_Tableau, taille_bloc)
    fin for//

    // Étape 2 : Combiner avec l'algorithme coûteux mais ultra rapide
    // M contient exactement √n éléments.
    // L'algo ULTRA va faire (√n)² = n opérations. La contrainte W = O(n) est respectée !
    retourner Algorithme_ULTRA_CRCW(M)

```

3. L'Analyse de Complexité (L'équilibre parfait)
   La puissance des algorithmes en cascade réside dans la résolution de ces équations de récurrence.

* Pour la Profondeur (Temps d'exécution) :
  Comme écrit sur le tableau :
  $$D(n) = D(\sqrt{n}) + \mathcal{O}(1)$$

Si on déroule cette équation (combien de fois faut-il appliquer la racine carrée pour arriver à 2 ?), la solution
mathématique est :
$$D(n) = \mathcal{O}(\log(\log n))$$

C'est incroyablement rapide. Pour un milliard d'éléments, $\log(\log(10^9))$ vaut environ 5 étapes !

* Pour le Travail (Volume de calcul total) :
  On a $\sqrt{n}$ appels récursifs sur des blocs de taille $\sqrt{n}$, plus l'algorithme ULTRA qui fait un travail
  de $(\sqrt{n})^2 = n$.
  $$W(n) = \sqrt{n} \cdot W(\sqrt{n}) + n$$

La solution mathématique de cette équation donne :
$$W(n) = \mathcal{O}(n \log(\log n))$$

Bilan de l'hybride : On a sacrifié un tout petit peu le travail (qui passe de $n$ à $n \log(\log n)$) pour obtenir une
profondeur spectaculaire de $\log(\log n)$. C'est tout le principe de la cascade !

Voulez-vous que l'on applique exactement ce même principe mathématique pour résoudre la question 4 de l'exercice 1 du
TD ("Toutes les puissances"), où l'on vous demande de prouver qu'une double boucle parallelFor avec des blocs de
taille $\sqrt{n}$ permet d'obtenir un travail quasi optimal de $n - o(n)$ et une profondeur de $\mathcal{O}(\log n)$ ?

Ces nouvelles photos sont de véritables pépites ! Elles montrent exactement comment votre professeur pousse le concept
de la cascade encore plus loin.
Sur la première photo, on découvre une astuce brillante : utiliser le hasard (l'algorithme probabiliste) pour trouver le
maximum en un temps record de $\mathcal{O}(1)$. Sur la seconde, on s'attaque au fameux problème de la fusion
ultra-parallèle.
Voici le cours détaillé et mis au propre pour ces deux concepts avancés.

1. Le Maximum Probabiliste (Photo 1)
   Dans la partie précédente, nous avions réussi à trouver le maximum avec une
   profondeur $D = \mathcal{O}(\log(\log n))$grâce à une cascade déterministe.
   Le tableau montre qu'on peut faire encore mieux (une profondeur $D = \mathcal{O}(1)$ en espérance !) en introduisant
   de l'aléatoire, tout en respectant la contrainte stricte de travail $W = \mathcal{O}(n)$.
   A. Le Schéma d'Exécution
   Voici la retranscription visuelle du schéma présent sur le tableau de gauche :

```text

       Tableau d'entrée 'e' (taille n)
                  |
                  v
 +----------------------------------------+
 | Sélectionner √n éléments aléatoirement |
 +----------------------------------------+
                  |
            Tableau 'T' (taille √n)
                  |
                  v
           +-------------+
           | Algo ULTRA  |   <-- Travail : (√n)² = n  | Profondeur : O(1)
           +-------------+
                  |
                  v
         Maximum partiel 'm'
                  |
                  v
 +----------------------------------------+
 | Filtrer 'e' : garder les éléments >= m |
 +----------------------------------------+
                  |
          Tableau 'reste'
  (Taille attendue très petite, ≤ √n)
                  |
                  v
           +-------------+
           | Algo ULTRA  |   <-- Travail : (√n)² = n  | Profondeur : O(1)
           +-------------+
                  |
                  v
             MAX GLOBAL
```

B. Le Pseudo-Code (Retranscription du tableau de droite)

```text

Fonction algo_max_probabiliste(e) :
    n <- taille(e)
    Soit T un tableau de taille √n

    // 1. Tirage aléatoire de √n éléments
    for// i de 0 à √n - 1 faire
        T[i] <- e[ random(0, n-1) ]
    fin for//

    // 2. Calcul du max partiel avec l'algo ultra-rapide O(1)
    m <- max_ultra_par(T)

    // 3. Filtrage : on ne garde que les "champions"
    reste <- garder_elements_superieurs(e, m)

    // 4. Calcul du max final sur les survivants
    renvoyer max_ultra_par(reste)
```

C. Pourquoi c'est génial ? (Analyse)

* Phase 1 : On tire $\sqrt{n}$ éléments. Calculer leur maximum m avec l'algo "ULTRA" prend $(\sqrt{n})^2 = n$opérations.
  Le travail est donc $W = \mathcal{O}(n)$.
* Phase 2 : Ce maximum partiel m est statistiquement déjà très grand ! Quand on filtre le tableau d'origine pour ne
  garder que les éléments plus grands que m, il restera en moyenne moins de $\sqrt{n}$ éléments.
* Phase 3 : On réapplique l'algo ULTRA sur le reste. Puisque sa taille est $\le \sqrt{n}$, le travail est à
  nouveau $\le n$.
* Bilan : Le travail total est $\mathcal{O}(n)$ et la profondeur est $\mathcal{O}(1)$ (avec une très forte probabilité).

2. La Fusion Ultra-Parallèle et l'Hybride (Photo 2)
   Ici, le professeur s'attaque au Tri Fusion. Pour rappel, le nerf de la guerre du Tri Fusion parallèle, c'est l'étape
   de fusion de deux sous-tableaux triés $A$ et $B$.
   A. La Fusion "ULTRA" (Naïve)
   Le professeur écrit sur la gauche une approche ultra-parallèle mais très coûteuse.
   Pour fusionner $A$ et $B$ dans un tableau résultat $R$ :

```text

// Pour placer les éléments de A
for// i de 0 à n-1 faire
    // On compte combien d'éléments dans B sont plus petits que A[i]
    k <- calcul_place(A[i], B)
    R[i + k] <- A[i]
fin for//

// + code similaire pour placer les éléments de B
```

* Profondeur ($D$) : $\mathcal{O}(1)$ (tout le monde cherche sa place en même temps).
* Travail ($W$) : $\mathcal{O}(n^2)$ (car chaque élément de $A$ doit être comparé à tous les éléments de $B$). C'est
  beaucoup trop grand !
  B. L'Hybride (Le schéma de droite)
  Pour ramener le travail à quelque chose d'acceptable, le professeur dessine le principe d'une fusion hybride (en
  cascade).
  Plutôt que d'utiliser la fusion ULTRA sur des tableaux complets, on va contraindre sa taille !

1. Découpage : On découpe les grands tableaux $A$ et $B$ en blocs de taille $\sqrt{n}$ (les petits carrés dessinés sur
   la droite du tableau).
2. Repères (Pivots) : On prend un élément sur $\sqrt{n}$ (ce qu'il appelle $b_1, b_2, \dots$ sur le tableau) pour servir
   de repère.
3. Routage : On trouve la position de ces $\sqrt{n}$ repères dans l'autre tableau avec l'algorithme ULTRA. Puisqu'il n'y
   a que $\sqrt{n}$ repères, le coût est raisonnable.
4. Fusion locale : Une fois les repères placés, le gros problème est cassé en plein de petits problèmes indépendants de
   taille $\le \sqrt{n}$. On peut alors les fusionner très rapidement.
   L'objectif : Obtenir une profondeur de fusion de $\mathcal{O}(\log(\log n))$ au lieu de $\mathcal{O}(\log n)$, et
   ainsi améliorer la profondeur globale du Tri Fusion.

Voulez-vous que l'on applique ces principes de complexité sur les exercices de votre TD, ou préférez-vous que l'on
détaille mathématiquement pourquoi le tableau reste (dans le max probabiliste) a une taille moyenne inférieure
à $\sqrt{n}$ ?

Voici le cours complet, réorganisé et fusionné pour regrouper toutes les notions de cette 6ème séance de manière
parfaitement logique et progressive.
C'est en effet de la "haute voltige" algorithmique ! L'objectif ici n'est plus seulement de paralléliser, mais de
repousser les limites mathématiques de la complexité en combinant intelligemment plusieurs algorithmes.

#### Séance 6 : Algorithmes en Cascade et Optimisation Extrême

Objectif de la séance : Apprendre à briser la barrière temporelle du $\mathcal{O}(\log n)$ en profondeur pour certains
problèmes (comme le calcul du maximum ou la fusion). La philosophie de la séance se résume par la phrase de votre
professeur : "Principe des algos en cascade $\rightarrow$ créer un hybride avec les propriétés voulues".
Il s'agit d'équilibrer parfaitement le Travail ($W$) et la Profondeur ($D$) en découpant les données en blocs de
taille $\sqrt{n}$ (ou $\log n$) pour tirer le meilleur parti d'algorithmes extrêmement rapides mais trop coûteux.

1. Le problème du Maximum : Évolution des approches
   Jusqu'à présent, pour trouver le maximum d'un tableau, on utilisait une réduction (un arbre binaire inversé), ce qui
   donnait une profondeur $D = \mathcal{O}(\log n)$. Peut-on faire plus rapide ? Oui, en temps
   constant $\mathcal{O}(1)$ ! Mais cela nécessite d'évoluer vers un modèle mémoire qui autorise les écritures
   concurrentes (CRCW).
   1.1. L'approche naïve "Ultra Rapide" (CRCW)
   L'idée est de comparer tous les éléments avec tous les autres en même temps.

```text

Fonction est_max_ultra_rapide(T, i) :
    est_max = Vrai
    // On lance n comparaisons en parallèle pour l'élément i
    for// j allant de 0 à n-1 (avec j != i) faire
        Si T[j] > T[i] alors
            est_max = Faux  // Écriture concurrente (CRCW) !
        Fin Si
    fin for//
    retourner est_max
```

Pour trouver le maximum de tout le tableau, on lance est_max_ultra_rapide pour chaque indice $i$ en parallèle.

* Profondeur ($D$) : $\mathcal{O}(1)$. C'est instantané !
* Travail ($W$) : $\mathcal{O}(n^2)$ car on fait $n \times n$ comparaisons. C'est beaucoup trop lourd. L'objectif est
  donc de ramener le travail vers $\mathcal{O}(n)$.
  1.2. L'Hybride 1 : La Cascade Déterministe (Blocs de $\sqrt{n}$)
  Pour respecter la contrainte d'un travail total $W = \mathcal{O}(n)$, on ne peut utiliser l'algorithme "ULTRA" que sur
  des tableaux d'une taille maximale de $\sqrt{n}$ (car $(\sqrt{n})^2 = n$). On va donc créer un hybride :
  Le Schéma d'exécution :

```text

 Axe du Temps (Profondeur D)
 |
 |       Tableau initial T de taille n : [ t_0, t_1, t_2, ..., t_{n-1} ]
 |
 |       1. Découpage en √n blocs de taille √n :
 |          [ t_0 ... t_{√n-1} ]     ...     [ ... t_{n-1} ]
 |                  |                               |
 |                  v                               v
 |          +---------------+               +---------------+
 | D(√n)    | Appel Récursif|      ...      | Appel Récursif|  <-- Chaque bloc calcule son max
 |          +---------------+               +---------------+
 |                  |                               |
 |                max_0                           max_k        <-- On obtient √n maximums locaux
 |                  \                               /
 |                     +-------------------------+
 | O(1)                |    Algorithme ULTRA     |             <-- Sur les √n éléments
 |                     +-------------------------+
 |                                  |
 v                              MAX GLOBAL
```

Le Pseudo-Code de l'Hybride :

```text

Fonction Max_Hybride_Cascade(T, n) :
    Si n <= 2 alors retourner Max_Sequentiel(T)

    taille_bloc = racine_carree(n)
    Soit M un nouveau tableau de taille taille_bloc

    // Étape 1 : Diviser et Régner (Appels récursifs)
    for// i allant de 0 à taille_bloc - 1 faire
        Sous_Tableau = T[ i*taille_bloc ... (i+1)*taille_bloc - 1 ]
        M[i] = Max_Hybride_Cascade(Sous_Tableau, taille_bloc)
    fin for//

    // Étape 2 : Algorithme ULTRA sur les √n éléments de M
    retourner Algorithme_ULTRA_CRCW(M)
```

Analyse de Complexité (L'équilibre parfait) :

* Profondeur : On a la récurrence $D(n) = D(\sqrt{n}) + \mathcal{O}(1)$. La solution mathématique
  donne $D(n) = \mathcal{O}(\log(\log n))$.
* Travail : On a $\sqrt{n}$ appels récursifs sur des blocs de taille $\sqrt{n}$, plus l'algorithme ULTRA qui fait un
  travail de $(\sqrt{n})^2 = n$. Soit $W(n) = \sqrt{n} \cdot W(\sqrt{n}) + n$. La solution
  donne $W(n) = \mathcal{O}(n \log(\log n))$.
* Bilan : On a sacrifié un tout petit peu le travail pour obtenir une profondeur spectaculaire de $\log(\log n)$ !
  1.3. L'Hybride 2 : Le Maximum Probabiliste
  On peut faire encore mieux en introduisant de l'aléatoire pour obtenir une profondeur $D = \mathcal{O}(1)$ en
  espérance, tout en gardant un travail $W = \mathcal{O}(n)$.
  Principe et Pseudo-Code :

```text

Fonction algo_max_probabiliste(e) :
    n <- taille(e)
    Soit T un tableau de taille √n

    // 1. Tirage aléatoire de √n éléments
    for// i de 0 à √n - 1 faire
        T[i] <- e[ random(0, n-1) ]
    fin for//

    // 2. Calcul du max partiel avec l'algo ULTRA O(1)
    // Travail : (√n)² = n
    m <- max_ultra_par(T)

    // 3. Filtrage : on ne garde que les "champions"
    reste <- garder_elements_superieurs(e, m)

    // 4. Calcul du max final sur les survivants
    renvoyer max_ultra_par(reste)
Pourquoi ça marche ?
Ce maximum partiel m tiré au hasard est statistiquement déjà très grand ! Quand on filtre le tableau d'origine, il restera en moyenne moins de $\sqrt{n}$ éléments. Réappliquer l'algo ULTRA sur ce reste coûtera donc à nouveau $\le n$ en travail. On a donc un travail total $\mathcal{O}(n)$ et une profondeur instantanée $\mathcal{O}(1)$ (avec une très forte probabilité).

```

2. Le Tri Fusion Hautement Parallèle
   Le problème du Tri Fusion parallèle classique (vu en séance 3), c'est que l'étape de fusion est séquentielle,
   bloquant la profondeur totale à $D = \mathcal{O}(n)$. Il faut donc paralléliser la fusion de deux sous-tableaux
   triés $A$ et $B$ dans un tableau $R$.
   2.1. La Fusion "ULTRA" (Naïve)
   Pour placer les éléments de $A$, on compte combien d'éléments dans $B$ sont plus petits que $A[i]$ en temps réel.

* Profondeur : $\mathcal{O}(1)$ (tout le monde cherche sa place en même temps).
* Travail : $\mathcal{O}(n^2)$ (chaque élément de $A$ doit être comparé à tous les éléments de $B$). C'est trop grand.
  2.2. La Fusion Parallèle Dichotomique
  Pour baisser le travail, on utilise une dichotomie.

1. On prend l'élément du milieu de $A$ (disons $A[m]$).
2. On cherche par recherche dichotomique ($\mathcal{O}(\log n)$) où $A[m]$ s'insère dans $B$. Cela coupe $B$ en $B_1$
   et $B_2$.
3. On sait où placer $A[m]$ dans la sortie $S$.
4. On lance en parallèle Fusion_Parallele(A_gauche, B1) et Fusion_Parallele(A_droite, B2).

* Profondeur de la fusion : $D_{fusion}(n) = \mathcal{O}(\log n) + D_{fusion}(n/2) \implies \mathcal{O}(\log^2 n)$. Le
  tri complet passe alors en $\mathcal{O}(\log^3 n)$.
  2.3. L'Hybride : La Fusion en Cascade
  Pour atteindre une profondeur de fusion de $\mathcal{O}(\log(\log n))$, on couple les deux idées précédentes :

1. Découpage : On découpe $A$ et $B$ en blocs de taille $\sqrt{n}$.
2. Pivots (Repères) : On prend $\sqrt{n}$ repères (un par bloc).
3. Routage ULTRA : On trouve la position de ces $\sqrt{n}$ repères dans l'autre tableau avec l'algorithme ULTRA. Le coût
   est gérable car on n'a que $\sqrt{n}$ éléments.
4. Fusion locale : Le gros problème est maintenant cassé en petits problèmes indépendants de taille $\le \sqrt{n}$,
   fusionnables très rapidement.

3. Lien avec votre TD : La magie des blocs $\sqrt{n}$
   Votre TD illustre parfaitement ce principe pour optimiser des algorithmes de base, en réduisant le nombre total
   d'opérations tout en gardant une excellente profondeur.
   <a id="seance-6-exercice-3"></a>

#####  * Exercice 1 : Toutes les puissances ($x^0, x^1, x^2, \dots, x^n$)

    * Problème : Un préfixe classique effectue $2n$ multiplications, soit le double de l'algorithme séquentiel initial.
    * La Cascade (puissanceRapide) : L'algorithme utilise des blocs de taille $\sqrt{n}$. Il calcule les puissances du premier bloc, fait un appel récursif pour sauter de bloc en bloc ($x^{\sqrt{n}}, x^{2\sqrt{n}} \dots$), puis utilise une double boucle parallelFor pour combler les "trous" à l'intérieur de chaque bloc.
    * Résultat : Le nombre de multiplications chute à $n + \mathcal{O}(\sqrt{n})$, ce qui est asymptotiquement optimal pour un travail $\mathcal{O}(n)$ et une profondeur $\mathcal{O}(\log n)$.

<a id="seance-6-exercice-4"></a>

#####  * Exercice 2 : Préfixe de Ladner-Fisher

    * Problème : Sa profondeur réelle est de $\mathcal{O}(\log^2 n)$ à cause de la gestion de la mémoire.
    * La Cascade : On découpe le tableau en blocs de $\sqrt{n}$, on fait des réductions locales, un calcul intermédiaire sur $\sqrt{n}$ éléments, puis $\sqrt{n}$ calculs récursifs en parallèle.

Souhaitez-vous que l'on détaille pas à pas la preuve mathématique de la question 4 de l'exercice 1 du TD ("Toutes les
puissances") pour démontrer que la double boucle parallelFor atteint bien $n - o(n)$ opérations ? C'est un grand
classique à maîtriser pour l'examen !

### Partie Pratique (TD)

#### TD Algorithmique Avancée – Algorithmes en Cascade : Correction Complète et Pédagogique

📋 Vue d'ensemble de la feuille
Thèmes abordés :

* La technique des algorithmes en cascade (cascading D&C) : combiner diviser-pour-régner à deux échelles différentes
  pour atteindre simultanément profondeur $O(\log n)$ et travail $O(n)$
* Le calcul de toutes les puissances dans un monoïde
* Le préfixe parallèle (Ladner-Fisher) et ses optimisations
* L'équilibrage séquentiel/parallèle pour minimiser le nombre d'opérations
  Compétences clés requises :
* Résolution de récurrences non-standard : D(n) = D(√n) + log n et W(n) = W(√n) + n
* Maîtrise du préfixe parallèle comme primitive fondamentale
* Analyse fine du nombre d'opérations (distinct du travail)
* Technique de "changement de variable" n = 2^m pour résoudre des récurrences en √n

🔑 Rappel : les deux récurrences fondamentales du TD
Ces deux récurrences reviennent partout dans la feuille — mémorisez-les :
$$D(n) = D(\sqrt{n}) + \log n \implies D(n) = \Theta(\log n)$$ $$W(n) = W(\sqrt{n}) + n \implies W(n) = \Theta(n)$$
💡 Preuve intuitive de la première : En posant n = 2^m, on obtient D(2^m) = D(2^{m/2}) + m. Soit f(m) = D(2^m), alors f(
m) = f(m/2) + m. Par téléscopage : f(m) = m + m/2 + m/4 + ... = 2m = Θ(m) = Θ(log n) ✓

<a id="seance-6-exercice-5"></a>

##### Exercice 1 — Toutes les Puissances

🔍 Reformulation
On veut calculer toutes les puissances x⁰, x¹, ..., xⁿ dans un monoïde (E, ×, e). L'objectif est un algorithme de
profondeur $O(\log n)$ faisant n + O(√n) multiplications — presque optimal !

###### Question 1 — Algorithme séquentiel et borne inférieure

Algorithme séquentiel
toutes_puissances_seq(x, n) :
P[0] ← e // x⁰ = neutre
pour i de 1 à n faire
P[i] ← P[i-1] × x // x^i = x^(i-1) × x
retourner P
Coût : n-1 multiplications (les pas i=1 à i=n, soit n itérations, mais P[1] = e × x = x est en fait 1 multiplication,
donc n multiplications au total).
Wait — corrigeons : on fait P[i] = P[i-1] × x pour i de 1 à n, soit n multiplications. Mais on peut aussi dire que
P[1] = x est donné et qu'on ne fait que n-1 multiplications pour calculer P[2] à P[n]. Le sujet dit n-1 : on suppose que
x¹ = x est "gratuit" (c'est l'entrée).
Borne inférieure : pourquoi n-1 est optimal ?
Argument de comptage : On part de l'ensemble {e, x} (les deux valeurs initiales disponibles). Chaque multiplication
produit au plus une nouvelle valeur. On a besoin de calculer n-1 nouvelles valeurs : x², x³, ..., xⁿ. Donc il faut au
moins n-1 multiplications. ✓
💡 Intuition : C'est comme construire une chaîne — chaque maillon dépend du précédent.

###### Question 2 — Réduction au préfixe parallèle et borne inférieure

Réduction au préfixe
Considérons le tableau T = [e, x, x, x, ..., x] de taille n+1. Le préfixe par × donne :
$$\Pi[k] = T[0] \times T[1] \times \cdots \times T[k] = e \times \underbrace{x \times \cdots \times x}_{k \text{ fois}} = x^k$$
Donc : TOUTES-LES-PUISSANCES = préfixe de [e, x, x, ..., x] ✓
Borne inférieure log₂(n) sur la profondeur
Argument : La plus grande puissance à calculer est xⁿ. À chaque étape parallèle (profondeur 1), la plus grande puissance
calculable double au plus (on peut calculer x^{2k} à partir de x^k). Donc après d étapes, la plus grande puissance
atteignable est x^{2^d}. Pour atteindre xⁿ, il faut 2^d ≥ n, soit :
$$d \geq \log_2 n$$
⚠️ Remarque importante du sujet : Tout algorithme de préfixe de profondeur D effectue au moins 2n - D multiplications.
Donc un préfixe de profondeur $O(\log n)$ fait ≥ 2n - $O(\log n)$ ≈ 2n multiplications → deux fois plus que le
séquentiel ! C'est le problème que puissanceRapide va résoudre.

###### Question 3 — Justification de puissanceRapide

Structure de l'algorithme
puissanceRapide(x, n) :
T ← [e, x, x, ..., x]              // taille 1 + √n
P[0..√n] ← Préfixe(×, T)           // P[i] = xⁱ pour i ≤ √n
Z ← puissanceRapide(P[√n], √n)     // Z[j] = (x^√n)^j = x^(j·√n)

parallelFor j de 1 à √n-1 faire
parallelFor i de 1 à √n-1 faire
P[i + j·√n] ← P[i] × Z[j]
P[(j+1)·√n] ← Z[j+1]

retourner P
Vérification de la correction
Claim : P[k] = x^k pour tout 0 ≤ k ≤ n.
Tout entier k ∈ [0, n] s'écrit de façon unique dans la "base
√n" : $$k = i + j \cdot \sqrt{n}, \quad 0 \leq i < \sqrt{n}, \quad 0 \leq j \leq \sqrt{n}$$
Cas 1 : k ≤ √n (i.e., j=0). Le préfixe initial calcule P[i] = xⁱ ✓
Cas 2 : k = i + j·√n avec 1 ≤ j ≤ √n-1 et 1 ≤ i ≤ √n-1.
L'appel récursif donne Z[j] = (x^{√n})^j = x^{j·√n}.
Alors : $$P[i + j\sqrt{n}] = P[i] \times Z[j] = x^i \times x^{j\sqrt{n}} = x^{i+j\sqrt{n}} \checkmark$$
Cas 3 : k = (j+1)·√n (multiples de √n). $$P[(j+1)\sqrt{n}] = Z[j+1] = x^{(j+1)\sqrt{n}} \checkmark$$
Illustration avec n=9, x=2 (multiplicatif dans ℤ)
√n = 3, T = [e, 2, 2, 2]
Préfixe → P[0..3] = [1, 2, 4, 8]  (= 2⁰, 2¹, 2², 2³)
Appel récursif : Z = puissanceRapide(8, 3) = [1, 8, 64, 512] (= (2³)⁰, (2³)¹, (2³)², (2³)³)

Double boucle (j=1,2 ; i=1,2) :
j=1, i=1: P[1+3] = P[4] = P[1]×Z[1] = 2×8 = 16 = 2⁴ ✓
j=1, i=2: P[2+3] = P[5] = P[2]×Z[1] = 4×8 = 32 = 2⁵ ✓
j=1, i=3→: P[3+3] = P[6] = Z[2] = 64 = 2⁶ ✓
j=2, i=1: P[1+6] = P[7] = P[1]×Z[2] = 2×64 = 128 = 2⁷ ✓
j=2, i=2: P[2+6] = P[8] = P[2]×Z[2] = 4×64 = 256 = 2⁸ ✓
j=2, i=3→: P[9] = Z[3] = 512 = 2⁹ ✓

###### Question 4 — Analyse de la double boucle parallèle

Profondeur
La double boucle est un parallelFor imbriqué : toutes les itérations (j, i) sont indépendantes et s'exécutent en
parallèle. Chaque itération effectue une seule multiplication $O(1)$. La profondeur d'un parallelFor de taille k est O(
log k).
$$D_{\text{boucle}} = O(\log \sqrt{n}) = O\left(\frac{\log n}{2}\right) = O(\log n) \checkmark$$
Nombre de multiplications
| Partie | Nombre de × |
| --- | --- |
| P[i] × Z[j] pour j∈[1,√n-1], i∈[1,√n-1] | $(\sqrt{n}-1)^2$ |
| P[(j+1)√n] = Z[j+1] | 0 (copie, pas de ×) |
| Total | $(\sqrt{n}-1)^2 = n - 2\sqrt{n} + 1$ |
$$(\sqrt{n}-1)^2 = n - 2\sqrt{n} + 1 = n - o(n) \checkmark$$

###### Question 5 — Analyse complète de puissanceRapide

Récurrence sur le nombre de multiplications W(n)
Les 4 étapes contribuent :
| Étape | Multiplications |
| --- | --- |
| Préfixe de taille √n+1 | $2\sqrt{n} - o(\sqrt{n})$ |
| Appel récursif sur √n | $W(\sqrt{n})$ |
| Double boucle | $n - 2\sqrt{n} + 1$ |
| Total | $W(\sqrt{n}) + n + 1 - o(\sqrt{n})$ |
$$W(n) = W(\sqrt{n}) + n + O(\sqrt{n})$$
Résolution par
téléscopage : $$W(n) = n + O(\sqrt{n}) + W(\sqrt{n})$$ $$= n + O(\sqrt{n}) + \sqrt{n} + O(n^{1/4}) + W(n^{1/4})$$ $$= n + O(\sqrt{n}) + O(n^{1/4}) + O(n^{1/8}) + \cdots$$
La série
géométrique : $\sqrt{n} + n^{1/4} + n^{1/8} + \cdots \leq \sqrt{n} \cdot \frac{1}{1 - 1/\sqrt{2}} = O(\sqrt{n})$
$$\boxed{W(n) = n + O(\sqrt{n})}$$
Ceci est presque optimal (seulement O(√n) de plus que la borne inférieure n-1) !
Récurrence sur la profondeur D(n)
$$D(n) = \underbrace{O(\log\sqrt{n})}{\text{préfixe}} + \underbrace{D(\sqrt{n})}{\text{récursif}} + \underbrace{O(\log n)}_{\text{boucle}}$$ $$= D(\sqrt{n}) + O(\log n)$$
Par la récurrence donnée : $D(n) = \Theta(\log n)$ ✓
Récurrence sur le travail W_total(n)
Le travail inclut la surcharge des
parallelFor : $$W_{\text{total}}(n) = $O(n)$ \text{ (map sur n éléments)} + W_{\text{total}}(\sqrt{n}) + $O(n)$ = \Theta(n)$$
Tableau récapitulatif
| Algorithme | Profondeur | Multiplications | Travail |
| --- | --- | --- | --- |
| Séquentiel | O(n) | n-1 ✓ optimal | O(n) |
| Préfixe naïf | O(log n) | ≥ 2n − O(log n) ❌ | O(n) |
| puissanceRapide | O(log n) ✓ | n + O(√n) ✓ | O(n) ✓ |
🔑 Idée clé : La technique en cascade à deux niveaux (√n blocs de taille √n) permet de séparer le travail en deux
parties : les grandes puissances (multiples de √n) calculées récursivement, et les petites puissances (≤ √n) calculées
par préfixe — puis on combine en $O(1)$ profondeur par multiplication.

<a id="seance-6-exercice-6"></a>

##### Exercice 2 — Préfixe parallèle en profondeur log n

🔍 Reformulation
On calcule les préfixes $\Pi_k = v \star A_0 \star \cdots \star A_k$ pour tout k < n. L'objectif final est un algorithme
qui atteint simultanément :

* Profondeur : $O(\log n)$
* Travail : $O(n)$
* Opérations ★ : au plus 2n + o(n)
  Ces trois objectifs simultanés sont non-triviaux — c'est le cœur de l'exercice.

###### Question 1 — Analyse de Ladner-Fisher direct

Rappel de l'algorithme
PrefixeDC(A[0..n-1], v, λ) :
si n == 1 : retourner [λ(v, A[0])]

// Étape 1 : pairwise
ParallelFor i de 0 à n/2-1 : B[i] ← A[2i] ★ A[2i+1]

// Étape 2 : appel récursif
β ← PrefixeDC(B, v, λ)

// Étape 3 : reconstruction
doPar en parallèle :
Π[0] ← v ★ A[0]
ParallelFor i de 0 à n/2-1 : Π[2i+1] ← β[i]        // copie
ParallelFor i de 1 à n/2-1 : Π[2i] ← β[i-1] ★ A[2i]  // 1 ★
Vérification de la correction
Pourquoi β[i] = v ★ A[0] ★ ... ★ A[2i+1] ?
Le tableau B[i] = A[2i] ★ A[2i+1] regroupe les paires. L'appel récursif
calcule : $$\beta[i] = v \star B[0] \star \cdots \star B[i] = v \star A[0] \star A[1] \star \cdots \star A[2i+1] = \Pi[2i+1] \checkmark$$
Donc Π[2i+1] = β[i] directement ✓
Et Π[2i] = v ★ A[0] ★ ... ★ A[2i] = β[i-1] ★ A[2i] ✓ (car β[i-1] = Π[2i-1])
1a. Profondeur en opérations ★ et nombre d'opérations
Profondeur en ★ :

* Étape 1 : 1 opération ★ de profondeur
* Récursif : D★(n/2)
* Étape 3 : 1 opération ★ de profondeur (β[i-1] ★ A[2i])
  $$D_\star(n) = D_\star(n/2) + 2, \quad D_\star(1) = 1$$
  Par téléscopage : $$\boxed{D_\star(n) = 1 + 2\log_2 n}$$
  Nombre total d'opérations ★ :
* Étape 1 : n/2 opérations
* Récursif : N★(n/2)
* Étape 3 : 1 (pour Π[0]) + 0 (copies) + (n/2 - 1) (pour les Π[2i])
  $$N_\star(n) = N_\star(n/2) + \frac{n}{2} + 1 + \frac{n}{2} - 1 = N_\star(n/2) + n$$
  $$\boxed{N_\star(n) = 2n - $O(1)$}$$
  ✓ conforme au sujet
  1b. Profondeur totale et travail
  Profondeur totale (incluant la surcharge des parallelFor de taille n/2) : $$D(n) = D(n/2) + O(\log n)$$
  Par
  téléscopage : $D(n) = O(\log n) + O(\log n/2) + \cdots = O\left(\sum_{k=0}^{\log n} k\right) = O\left(\frac{(\log n)^2}{2}\right)$
  $$\boxed{D(n) = \Theta(\log^2 n)}$$
  Travail : Chaque niveau de récursion effectue $O(n)$ opérations, avec $O(\log n)$ niveaux : $$\boxed{W(n) = $O(n)$}$$
  ⚠️ Le problème : La profondeur est O(log² n) et non $O(\log n)$, à cause de la surcharge des parallelFor. C'est ce que
  la Q2 va corriger.

###### Question 2 — Algorithme cascade de profondeur $O(\log n)$

Principe : 3 étapes en cascade
Structure : on découpe A en √n blocs de taille √n chacun.
PrefixeCascade(A[0..n-1], v, λ) :
s ← √n // taille d'un bloc

// Étape 1 : réduction de chaque bloc en parallèle
ParallelFor k de 0 à s-1 :
B[k] ← réduction(A[k·s .. (k+1)·s - 1])   // = A[ks] ★ ... ★ A[(k+1)s-1]

// Étape 2 : calcul des préfixes des blocs
// β[k] = v ★ B[0] ★ ... ★ B[k], chacun calculé indépendamment
ParallelFor k de 0 à s-1 :
β[k] ← v ★ B[0] ★ ... ★ B[k]   // réduction de k+2 éléments

// Étape 3 : √n appels récursifs sur les blocs
ParallelFor k de 0 à s-1 :
Π[k·s .. (k+1)·s - 1] ← PrefixeCascade(A[k·s..(k+1)s-1], β[k-1], λ)
// avec β[-1] = v par convention

retourner Π
Vérification de la correction
Pour tout i dans le bloc k (i.e., i = k·√n + r avec 0 ≤ r < √n) :
$$\Pi[i] = v \star A[0] \star \cdots \star A[i]$$ $$= \underbrace{v \star A[0] \star \cdots \star A[k\sqrt{n}-1]}{\beta{k-1}} \star \underbrace{A[k\sqrt{n}] \star \cdots \star A[i]}_{\text{préfixe local du bloc }k}$$
L'appel récursif calcule exactement le préfixe local du bloc k à partir de β[k-1], donc le résultat est Π[i] ✓
Analyse de profondeur D(n)
| Étape | Profondeur |
| --- | --- |
| Étape 1 (réduction de √n éléments) | O(log √n) = O(½ log n) |
| Étape 2 (réductions indépendantes, max taille √n) | O(log √n) = O(½ log n) |
| Étape 3 (appels récursifs de taille √n, en parallèle) | D(√n) |
$$D(n) = D(\sqrt{n}) + O(\log n)$$
Par la récurrence donnée : $\boxed{D(n) = \Theta(\log n)}$ ✓
Analyse du travail W(n)
| Étape | Travail |
| --- | --- |
| Étape 1 : √n réductions de taille √n | √n × O(√n) = O(n) |
| Étape 2 : β[k] coûte k+1 ops, somme = Σk = O(n) | O(n) |
| Étape 3 : √n appels récursifs de taille √n | √n × W(√n) |
$$W(n) = \sqrt{n} \cdot W(\sqrt{n}) + $O(n)$$$
Résolution : Posons n = 2^m, f(m) = W(2^m) : $$f(m) = 2^{m/2} \cdot f(m/2) + O(2^m)$$
Divisons par 2^m : si g(m) = f(m)/2^m, alors : $$g(m) = g(m/2) + $O(1)$ \implies g(m) = O(\log m) = O(\log \log n)$$
Donc : $f(m) = 2^m \cdot g(m)$, soit : $$\boxed{W(n) = O(n \log \log n)}$$
⚠️ Pourquoi pas $O(n)$ ? Les √n appels récursifs en parallèle ne réduisent pas le travail — le travail est la somme !
C'est le surcoût de cet algorithme.

###### Question 3 — Algorithme optimal : profondeur $O(\log n)$, travail $O(n)$, opérations ≤ 2n + o(n)

Idée clé : équilibrage séquentiel/parallèle
Observation : L'algorithme de Q2 a W = O(n log log n). Pour ramener à $O(n)$, on réduit la taille du problème sur lequel
on applique Q2 en traitant de petits blocs séquentiellement d'abord.
Choix de la taille des blocs : b = log n (taille de bloc traitée séquentiellement)
Algorithme
PrefixeOptimal(A[0..n-1], v, λ) :
b ← log n
m ← n/b = n/log n // nombre de blocs

// Étape 1 : traitement séquentiel de chaque bloc (en parallèle entre blocs)
ParallelFor k de 0 à m-1 :
// Calcule les préfixes LOCAUX du bloc k (sans v)
LocalPref[k][0] ← A[k·b]
pour i de 1 à b-1 faire
LocalPref[k][i] ← LocalPref[k][i-1] ★ A[k·b + i]
// Le "résumé" du bloc k = son dernier élément local
B[k] ← LocalPref[k][b-1]   // = A[k·b] ★ ... ★ A[(k+1)b - 1]

// Étape 2 : préfixe des résumés (algorithme Q2 sur m = n/log n éléments)
β ← PrefixeCascade(B[0..m-1], v, λ)
// β[k] = v ★ B[0] ★ ... ★ B[k] = v ★ A[0] ★ ... ★ A[(k+1)b - 1]

// Étape 3 : combinaison finale (parfor)
ParallelFor k de 0 à m-1 :
ParallelFor i de 0 à b-1 :
Π[k·b + i] ← β[k-1] ★ LocalPref[k][i]
// avec β[-1] = v

retourner Π
Vérification de la correction
Pour i = k·b + r (r-ième élément du bloc
k) : $$\Pi[i] = \underbrace{v \star A[0] \star \cdots \star A[kb-1]}{\beta[k-1]} \star \underbrace{A[kb] \star \cdots \star A[kb+r]}{\text{LocalPref}[k][r]} \checkmark$$
Analyse de profondeur D(n)
| Étape | Profondeur |
| --- | --- |
| Étape 1 (séquentiel sur blocs de taille b = log n, en parallèle) | O(log n) |
| Étape 2 (PrefixeCascade sur n/log n éléments) | D(n/log n) = O(log(n/log n)) = O(log n) |
| Étape 3 (double parfor, corps O(1)) | O(log(n/log n) × log(log n)) = O(log n) |
$$\boxed{D(n) = O(\log n)} \checkmark$$
Analyse du travail W(n)
| Étape | Travail |
| --- | --- |
| Étape 1 : m blocs × b ops = n | O(n) |
| Étape 2 : PrefixeCascade sur n/log
n | $O\left(\frac{n}{\log n} \cdot \log\log\frac{n}{\log n}\right) = O\left(\frac{n \cdot \log\log n}{\log n}\right) = o(n)$ |
| Étape 3 : parfor sur n éléments | O(n) |
$$\boxed{W(n) = $O(n)$} \checkmark$$
Décompte précis des opérations ★
C'est la partie la plus délicate. Comptons exactement :
Étape 1 : Chaque bloc de taille b = log n fait b-1 opérations ★ (préfixe séquentiel). Avec m = n/log n
blocs : $$\text{ops étape 1} = m \times (b-1) = \frac{n}{\log n} \times (\log n - 1) = n - \frac{n}{\log n}$$
Étape 2 : PrefixeCascade sur m = n/log n éléments. D'après la Q2, le nombre d'opérations est O(m log log m) = O\left(
\frac{n \log\log n}{\log n}\right) = o(n).
Étape 3 : Pour chaque i = k·b + r, on fait 1 opération ★ (β[k-1] ★ LocalPref[k][r]). Cela fait n opérations ★ (une par
élément de A).
Total : $$\text{ops totales} = \left(n - \frac{n}{\log n}\right) + o(n) + n = 2n - \frac{n}{\log n} + o(n)$$
$$\boxed{\text{ops} = 2n + o(n)} \checkmark$$
Tableau récapitulatif des trois algorithmes
| Algorithme | Profondeur | Travail | Opérations ★ |
| --- | --- | --- | --- |
| Ladner-Fisher direct (Q1) | O(log²n) | O(n) | 2n - O(1) |
| PrefixeCascade (Q2) | O(log n) ✓ | O(n log log n) | O(n log log n) |
| PrefixeOptimal (Q3) | O(log n) ✓ | O(n) ✓ | 2n + o(n) ✓ |
🔑 Idée clé de Q3 : Le traitement séquentiel des petits blocs sert à "compresser" le problème par un facteur log n, de
sorte que le coût de PrefixeCascade (qui a un surcoût de log log n par élément) ne représente que o(n) opérations
totales.

📚 Résumé de la feuille

#### Méthodes et techniques clés

1. Décomposition en √n blocs de √n : La structure "carrée" qui apparaît dans les deux exercices, permettant d'atteindre
   D = $O(\log n)$ avec des récurrences en √n
2. Équilibrage séquentiel/parallèle : Traiter les petits blocs séquentiellement pour réduire la taille du problème
   soumis à l'algorithme parallèle coûteux
3. Distinction travail / nombre d'opérations : Le travail compte la surcharge des primitives parallèles ; le nombre
   d'opérations ★ ne compte que les appels à λ
4. Résolution de récurrences en √n : Via le changement de variable n = 2^m

#### Formules importantes

$$D(n) = D(\sqrt{n}) + O(\log n) \implies D(n) = \Theta(\log n)$$ $$W(n) = \sqrt{n} \cdot W(\sqrt{n}) + $O(n)$ \implies W(n) = O(n \log\log n)$$
Borne sur les algorithmes de préfixe : profondeur D → au moins 2n - D opérations ★
Erreurs et pièges fréquents
| Piège | Comment l'éviter |
| --- | --- |
| Confondre profondeur en ★ et profondeur totale | La profondeur totale inclut log n par parfor ; la profondeur en ★ ne
compte que les appels à λ |
| Oublier que √n appels parallèles ne réduisent pas le travail | Le travail est la somme (pas le max) des travaux des
sous-problèmes |
| Résoudre W(n)=√n·W(√n)+O(n) comme O(n) | Faire le changement de variable pour obtenir O(n log log n) |
| Dans puissanceRapide, oublier les indices multiples de √n | L'affectation P[(j+1)√n] = Z[j+1] est une copie, pas un
calcul |
| Compter une double boucle parallèle comme ayant profondeur O(1) | La profondeur d'un parfor de taille k est O(log k),
pas O(1) |
🏋️ Questions d'entraînement
Q1. Résolvez la récurrence D(n) = D(√n) + $O(1)$ (sans le log n).
Réponse : Par changement de variable n=2^m : f(m) = f(m/2) + $O(1)$ → f(m) = O(log m) = O(log log n). Donc D(n) = O(log
log n).
Q2. Pourquoi l'algorithme PrefixeCascade (Q2) fait-il $O(n)$ opérations à l'étape 2 alors qu'on calcule √n préfixes
indépendants ?
Réponse : Le k-ème préfixe coûte k+1 opérations. La somme Σ(k+1) pour k=0..√n-1 = √n(√n+1)/2 ≈ n/2 = $O(n)$.
Q3. Si on utilise des blocs de taille b = √log n au lieu de b = log n dans l'algorithme de Q3, que devient le nombre
d'opérations ?
Réponse : Étape 1 : (b-1)·n/b = n - n/√(log n) ops. Étape 3 : n ops. Étape 2 : PrefixeCascade sur n/√(log n) éléments →
o(n) ops. Total : 2n - n/√(log n) + o(n) = 2n + o(n) ✓ mais le gain par rapport à b=log n est minimal.
Q4. Dans l'algorithme puissanceRapide, que se passe-t-il si n n'est pas un carré parfait ?
Réponse : On prend s = ⌈√n⌉ comme taille de bloc. L'analyse reste valable avec O(√n) de correction. Le nombre
d'opérations reste n + O(√n).
Q5. Montrez que le nombre d'opérations de tout algorithme de préfixe de profondeur D vérifie N ≥ 2n - D.
Réponse : Chaque des n éléments de sortie Π[k] "dépend" de A[k]. Dans le DAG de calcul, A[k] contribue à Π[k] via un
chemin. Chaque nœud à profondeur ≤ D peut "hériter" de au plus 2^D entrées. Un argument de comptage sur le DAG montre
que les nœuds à la profondeur D ont été "créés" par N opérations dont au moins N-(D opérations sur la branche de
profondeur max) = N-D contribuent à deux sorties distinctes → N ≥ 2n - D.

C'est une excellente transition ! La séance 7 marque un véritable tournant dans votre apprentissage : l'introduction de
**l'aléatoire** comme outil pour concevoir des algorithmes plus simples et souvent beaucoup plus rapides que leurs
équivalents déterministes.

C'est un changement de paradigme fascinant. On accepte qu'un algorithme puisse se tromper (avec une probabilité infime)
ou prendre un temps variable, en échange d'un gain de performance massif.

Voici votre cours structuré et détaillé pour cette septième séance.

---


---

<a id="seance-7"></a>

## Séance 7 — Algorithmes probabilistes : Las Vegas, Monte-Carlo, Atlantic City

> Plage source conservée : lignes `2453` à `3031` de `course.txt`.

### Partie Théorique

#### Séance 7 : Algorithmes Probabilistes (Las Vegas, Monte-Carlo, Atlantic City)

**Objectif de la séance :** Comprendre comment l'injection de "bits aléatoires" permet de contourner les pires cas des
algorithmes déterministes. Classifier ces algorithmes selon leur gestion de l'erreur et apprendre à analyser
mathématiquement leur probabilité de succès.

##### 1. Concepts Fondamentaux : Déterministe vs Probabiliste

* **Algorithme Déterministe :** Pour une entrée donnée, l'exécution est toujours identique et la sortie est garantie
  correcte. L'objectif est d'être rapide dans le pire des cas.
* **Algorithme Probabiliste :** En plus de l'entrée, il utilise une source de bits aléatoires pour faire des choix en
  cours d'exécution. Pour une même entrée, le chemin d'exécution et même la sortie peuvent varier. L'objectif est de
  fournir une réponse *probablement* correcte.

> **⚠️ Piège classique :** Il ne faut pas confondre un algorithme probabiliste avec l'analyse probabiliste (en moyenne)
> d'un algorithme déterministe (comme le Quicksort avec pivot fixe sur des données mélangées). Dans un algorithme
> probabiliste, l'aléatoire vient de *l'algorithme lui-même*, pas de la distribution des données en entrée.

---

##### 2. La Classification : Le "Zoo" Probabiliste

Les algorithmes probabilistes se divisent en trois grandes villes (classes), selon la façon dont ils gèrent l'erreur et
le temps d'exécution.

| Type              | Temps d'exécution         | Tolérance à l'erreur                                                                                                          | Exemples                          | Classe de Complexité       |
|:------------------|:--------------------------|:------------------------------------------------------------------------------------------------------------------------------|:----------------------------------|:---------------------------|
| **Las Vegas**     | Variable (Moyenne bornée) | **Aucune erreur.** S'il termine, la réponse est 100% correcte. Peut renvoyer `ECHEC` (probabilité $\le 0.5$).                 | Évaluation d'arbre ET-OU          | **ZPP** (Zero-sided error) |
| **Monte-Carlo**   | Déterministe (Borné)      | Erreur possible mais **unilatérale** (One-sided error). Ex: S'il dit "NON", c'est sûr. S'il dit "OUI", il y a un petit doute. | Test de primalité de Miller-Rabin | **RP** (Random Polynomial) |
| **Atlantic City** | Déterministe (Borné)      | Erreur possible **bilatérale** (Both-sided error). S'il dit "OUI" ou "NON", la proba d'être correct est $\ge c > 0.5$.        | Vérification de produit matriciel | **BPP** (Bounded-error)    |

---

##### 3. Exemples Classiques du Cours

Votre professeur a utilisé des exemples très élégants pour illustrer la puissance de l'aléatoire.

###### A. Le Tableau de Booléens (La Simplicité)

* **Problème :** Trouver un VRAI dans un tableau de taille $n$ contenant au moins 75% de VRAI.
* **Déterministe :** Boucle `for` classique. Dans le pire cas (les 25% de FAUX sont au début), on fait $0.25n + 1$
  lectures. Temps $\mathcal{O}(n)$.
* **Probabiliste :** On tire $K$ indices au hasard. La probabilité de ne tomber *que* sur des FAUX (l'échec) est
  de $p^K$ avec $p < 0.25$. Pour $K=200$, la probabilité d'erreur est $< 10^{-120}$ (une certitude absolue en
  pratique !). Temps $\mathcal{O}(1)$.

###### B. La Table de Multiplication Erronée (L'Amplification)

* **Problème :** On a une table de multiplication $T$ de taille $n \times n$ qui contient 10% d'erreurs réparties
  arbitrairement. On veut calculer $a \times b$ de façon fiable.
* **L'astuce algébrique :** On utilise l'identité remarquable :
  $$ab \equiv (a+u)(b+v) - (a+u)v - u(b+v) + uv$$
* **L'algorithme :** On tire $u$ et $v$ au hasard. On lit les 4 termes dans la table $T$. Si la table donne les 4 bonnes
  valeurs, le calcul est juste. La probabilité d'erreur est $\le 0.4$.
* **Amplification par vote majoritaire :** Comment passer d'une fiabilité de 60% à 99.99% ? On répète l'algorithme $k$
  fois et on prend le résultat majoritaire. Les lois de Hoeffding et Bienaymé-Tchebychev prouvent que la probabilité
  d'erreur chute de façon exponentielle ($< 10^{-86}$ pour $k=10^4$).

###### C. L'Évaluation d'Arbre ET-OU (Las Vegas)

* **Problème :** Évaluer la racine d'un arbre binaire strict alternant des nœuds MIN (ET) et MAX (OU) de hauteur $h$.
* **Déterministe :** Un adversaire peut toujours construire un arbre qui force l'algorithme à lire toutes les feuilles :
  coût $\mathcal{O}(n)$.
* **Probabiliste (Las Vegas) :** Pour évaluer un nœud, on choisit un de ses deux fils *au hasard*. S'il donne la
  réponse (ex: un 1 pour un nœud OU), on n'a pas besoin de lire l'autre ! Le coût moyen chute
  à $\mathcal{O}(n^{0.793})$.

---

##### 4. Outils Théoriques Avancés

###### A. Le Principe Minimax de Yao (Borne Inférieure)

Comment prouver qu'il n'existe *aucun* algorithme probabiliste plus rapide qu'une certaine limite ? On utilise le
principe de Yao, issu de la théorie des jeux :
> Le coût en pire cas du *meilleur algorithme probabiliste* est toujours supérieur ou égal au coût en moyenne du
*meilleur algorithme déterministe* sur une distribution d'entrée spécifique (choisie par un adversaire).

Pour l'arbre ET-OU, en choisissant une distribution d'entrée très vicieuse, on prouve (via Yao) que la borne inférieure
est $\Omega(n^{0.792})$. Votre algorithme en $\mathcal{O}(n^{0.793})$ est donc quasi-optimal !

###### B. Le Lemme de Schwartz-Zippel (Magie Algébrique)

C'est un outil surpuissant pour l'algorithmique Atlantic City / Monte Carlo.

* **Théorème :** Un polynôme non nul de degré $d$ évalué sur des valeurs tirées au hasard dans un ensemble fini $I$ a
  une probabilité d'être égal à zéro très faible : $Pr(P = 0) \le \frac{d}{|I|}$.
* **Application (Vérification $AB = C$) :** Au lieu de multiplier les matrices en $\mathcal{O}(n^3)$, on tire un
  vecteur $u$ au hasard et on vérifie si $A(Bu) = Cu$. Le coût n'est que de $\mathcal{O}(n^2)$ ! Si $AB \ne C$,
  Schwartz-Zippel garantit qu'on le détectera avec une haute probabilité.

---

##### 5. Lien avec votre TD

Votre TD est exceptionnellement riche et met en pratique ces concepts sur trois problèmes majeurs :

1. **Recherche de chaîne (Algorithme de Karp-Rabin) :** Au lieu de comparer les chaînes caractère par caractère, on les
   hache en un entier modulo $K$ (un peu comme Schwartz-Zippel). C'est un algorithme Monte Carlo ultra rapide en
   temps $\mathcal{O}(n)$.
2. **Hachage Parfait :** Comment stocker $n$ clés sans aucune collision ? On utilise des tirages probabilistes pour
   trouver une fonction de hachage $h_k$. Les mathématiques (via le calcul des espérances des collisions) prouvent
   qu'une telle fonction existe et qu'on la trouvera très vite en tirant au hasard.
3. **MAX-3-LIN et la "Dérandomisation" :** C'est la perle de ce TD. On vous demande de concevoir un algorithme
   probabiliste qui satisfait en moyenne la moitié des équations (ratio 2). Ensuite, en utilisant la méthode des *
   *espérances conditionnelles**, on transforme cet algorithme aléatoire en un algorithme **100% déterministe** qui
   garantit ce même ratio de 2.

---

Souhaitez-vous que l'on détaille la méthode de **Dérandomisation du MAX-3-LIN (Exercice 3 du TD)** ? C'est une technique
redoutable (souvent demandée aux examens) qui montre comment supprimer l'aléatoire d'un algorithme probabiliste pour en
faire un algorithme déterministe avec de fortes garanties mathématiques.

### Cours : Algorithmes Probabilistes — Las Vegas, Monte-Carlo, Atlantic City

---

#### 1. Vue d'ensemble du cours

##### Principaux thèmes

Ce cours introduit une classe d'algorithmes qui utilisent de l'**aléatoire** comme outil algorithmique à part entière.
On y étudie trois grandes familles (Las Vegas, Monte-Carlo, Atlantic City), deux exemples concrets (table de
multiplication erronée, arbre min-max), et des outils mathématiques pour analyser ces algorithmes.

##### Objectifs

- Comprendre **pourquoi** l'aléatoire peut être un avantage algorithmique (simplicité, performance).
- Savoir **classifier** un algorithme probabiliste selon son type d'erreur.
- Maîtriser les **outils d'analyse** : inégalités de concentration, lemme de Schwartz-Zippel, principe Minimax de Yao.
- Être capable de **prouver des bornes** sur la probabilité d'erreur et la complexité.

---

#### 2. Cours complet, diapositive par diapositive

---

##### 🔷 Rappel : Algorithmes déterministes

Un algorithme **déterministe**, c'est ce que tu connais bien : tu donnes une entrée, tu obtiens **toujours la même
sortie**, et cette sortie est **toujours correcte**.

> **Objectif formel :** Pour toute entrée, l'algorithme produit une sortie correcte, en temps polynomial en la taille de
> l'entrée.

C'est le modèle standard, mais il a des limites : pour certains problèmes, les algorithmes déterministes sont coûteux en
pire cas. L'idée du cours est de **relâcher l'exigence de correction à 100 %**, en échange de gains en vitesse ou en
simplicité.

---

##### 🔷 Algorithmes probabilistes : définition

Un algorithme probabiliste, c'est un algorithme qui, **en plus de son entrée**, reçoit une **source de bits aléatoires
**. Ces bits peuvent influencer les décisions prises pendant l'exécution.

Conséquence directe : si tu relances l'algorithme sur la **même entrée**, tu peux obtenir une **sortie différente** (
selon les bits aléatoires tirés).

> **Objectif fondamental :** Pour toute entrée, l'algorithme doit produire une sortie **probablement correcte**. La
> probabilité d'erreur dépend uniquement des tirages aléatoires, **pas de l'entrée**.

C'est crucial : on ne dit pas "ça marche en moyenne sur les entrées typiques". On dit : "pour **n'importe quelle entrée
**, ça marche avec haute probabilité sur les tirages aléatoires". C'est une garantie bien plus forte.

---

##### ⚠️ Distinction importante : ne pas confondre !

Il y a deux choses très différentes :

|                    | Algorithme probabiliste                             | Analyse en moyenne                             |
|--------------------|-----------------------------------------------------|------------------------------------------------|
| Source d'aléatoire | **L'algorithme** tire des bits aléatoires           | **L'entrée** est supposée aléatoire            |
| Garantie           | Pour toute entrée, sortie correcte avec haute proba | Correct pour la plupart des entrées "typiques" |
| Pire cas           | Maîtrisé probabilistiquement                        | Peut être catastrophique                       |

**Exemple illustratif :** QuickSort a une complexité moyenne O(n log n) si les entrées sont aléatoires — mais si
l'adversaire choisit une entrée ordonnée, c'est O(n²). En revanche, QuickSort **randomisé** (pivot choisi aléatoirement)
donne O(n log n) en espérance **pour toute entrée**, car l'aléatoire est dans l'algorithme.

---

##### 🔷 Avantage des algorithmes probabilistes (1) : l'exemple du tableau booléen

**Problème concret :**

- Entrée : un tableau A de n booléens, dont **au moins 75 % valent VRAI**.
- Sortie : un indice i tel que A[i] = VRAI.

**Solution déterministe :**

```text
for (i=0; i<n; ++i) { if A[i] return i ; }
```

- Meilleur cas : 1 accès (A[0] = VRAI).
- Pire cas : l'adversaire place tous les FAUX en début de tableau. Si p < 25 % sont FAUX, le pire cas est **p·n + 1
  accès**. Par exemple, si n = 1 000 000 et p = 24 %, c'est 240 001 accès avant de trouver un VRAI. C'est mauvais.

---

##### 🔷 Avantage des algorithmes probabilistes (2) : solution probabiliste

**Algorithme probabiliste (version bornée, K essais) :**

```text
for t=1..K do {
    i = int_rand(n);    // tire un indice au hasard dans {0,...,n-1}
    if A[i] return i;
}
return ECHEC;
```

**Analyse :**

- La probabilité qu'un tirage aléatoire tombe sur un FAUX est p < 1/4.
- La probabilité d'échec après K essais indépendants : Pr(échec) = p^K < (1/4)^K.

Pourquoi ? Parce que pour échouer K fois de suite, il faut tomber K fois sur un FAUX, et ces tirages sont indépendants.
Donc la probabilité est p^K.

| K   | Pr(échec) |
|-----|-----------|
| 5   | < 10⁻³    |
| 200 | < 10⁻¹²⁰  |

Avec seulement **K = 200 accès constants** (indépendants de n !), la probabilité d'erreur est astronomiquement petite.
C'est la puissance de l'aléatoire.

---

**Algorithme probabiliste (version non bornée) :**

```text
do { i = int_rand(n); } while (!A[i]);
return i;
```

Cet algorithme **ne s'arrête que quand il a trouvé un VRAI**, donc il ne fait jamais d'erreur. Mais son temps
d'exécution est une variable aléatoire.

**Calcul de l'espérance du nombre de tours de boucle :**

Soit L le nombre de tours. On utilise l'identité :
$$\mathbb{E}[L] = \sum_{k=1}^{\infty} \Pr(L \geq k) = 1 + p + p^2 + \ldots = \frac{1}{1-p}$$

Intuition de cette formule : Pr(L ≥ k) = p^(k-1) (il faut avoir échoué k-1 fois de suite). La somme d'une série
géométrique donne 1/(1-p).

Comme p < 1/4, on a E[L] < 4/3. En moyenne, **moins de 2 tirages suffisent**, quelle que soit la taille n du tableau !

---

##### 🔷 Exercice intermédiaire : MAX-3-SAT

Juste mentionné ici comme exercice à la maison. L'idée clé à retenir : une affectation **uniformément aléatoire** des
variables satisfait une clause à 3 littéraux avec probabilité 7/8 (car la seule façon de ne pas satisfaire une clause
est que les 3 littéraux soient tous faux simultanément, probabilité = (1/2)³ = 1/8). Cela donne un algorithme
d'approximation probabiliste avec ratio espéré ≤ 8/7.

---

##### 🔷 Exemple 2 : Table de multiplication erronée

**Problème :** On dispose d'une table T de multiplication n×n avec **au plus 10 % d'erreurs** (i.e., au plus 10 % des
cases T[a,b] ont une valeur incorrecte). On sait additionner correctement. Comment calculer a×b de manière fiable ?

**Idée naïve :** Lire T[a,b] directement → risque d'erreur de 10 %.

**Idée probabiliste :** Utiliser l'identité algébrique :
$$ab = (a+u)(b+v) - (a+u)v - u(b+v) + uv$$

où u et v sont choisis **aléatoirement**. Cette identité est vraie pour tous entiers.

**Algorithme :**

1. Choisir u ∈ {0,...,n-1} et v ∈ {0,...,n-1} aléatoirement.
2. Lire dans la table (avec accès modulo n) :
    - m₁ = T[(a+u) mod n, (b+v) mod n]
    - m₂ = T[u, v]
    - m₃ = T[(a+u) mod n, v]
    - m₄ = T[u, (b+v) mod n]
3. Retourner r = m₁ + m₂ - m₃ - m₄ + corrections de bord (σu, σv)

**Pourquoi ça marche ?** Si les 4 valeurs lues sont correctes, alors r = ab (par l'identité algébrique). Le bénéfice de
la randomisation : au lieu de lire T[a,b] directement (case peut-être erronée), on accède à 4 cases **aléatoires** de la
table.

---

**Analyse de la probabilité d'erreur :**

On veut majorer Pr(r ≠ a×b).

**Étape 1 :** On sait que si les 4 valeurs mi sont correctes → r est correct. Donc :
$$\Pr(r \text{ correct}) \geq \Pr(m_1 \text{ et } m_2 \text{ et } m_3 \text{ et } m_4 \text{ corrects})$$

Mais pourquoi **≥** et pas **=** ? Parce qu'il peut arriver que des erreurs dans les mi se **compensent** et donnent
quand même le bon résultat par coïncidence. Donc la probabilité de correction est au moins celle où tout est correct,
mais potentiellement plus grande.

**Étape 2 (astuce clé) :** Les variables m₁, m₂, m₃, m₄ ne sont **pas indépendantes** (elles partagent les mêmes u, v).
Quand les variables aléatoires sont dépendantes, on ne peut pas facilement factoriser les probabilités de conjonction (
ET).

**L'astuce** : passer à la **contraposée** et travailler avec la **disjonction (OU)** plutôt que la conjonction (ET) :

> Si r est erroné, alors au moins un des mi est erroné.

Donc :
$$\Pr(r \neq ab) \leq \Pr(m_1 \text{ ou } m_2 \text{ ou } m_3 \text{ ou } m_4 \text{ erronés})$$

Puis on utilise l'**inégalité de l'union** (union bound) :
$$\Pr(A_1 \cup A_2 \cup \ldots \cup A_k) \leq \sum_{i=1}^k \Pr(A_i)$$

Ce qui donne :
$$\Pr(\text{erreur}) \leq \sum_{i=1}^4 \Pr(m_i \text{ erroné}) \leq 4 \times 0.1 = 0.4$$

Donc Pr(résultat correct) ≥ 0.6 > 1/2. ✓

---

**Amplification par répétition (Loi des grands nombres) :**

Si on fait k exécutions indépendantes et qu'on retourne la **valeur majoritaire** :

| k     | Pr(erreur) |
|-------|------------|
| 10    | < 3×10⁻²   |
| 100   | < 3×10⁻³   |
| 1000  | < 5×10⁻⁹   |
| 10000 | < 3×10⁻⁸⁷  |

C'est le **principe général d'amplification** : un algorithme Monte-Carlo avec probabilité d'erreur < 1/2 peut être
rendu aussi fiable qu'on veut par répétition.

---

##### 🔷 Résultat majoritaire et inégalités de concentration

**Question générale :** Si on fait n exécutions indépendantes d'un algorithme d'erreur p < 0.5, quelle est la
probabilité que la valeur majoritaire soit fausse ?

La probabilité d'erreur ε est la probabilité d'avoir **plus de n/2 erreurs** parmi n exécutions. Cela correspond à une *
*déviation vers le haut** de la somme de variables de Bernoulli indépendantes.

**Outil 1 : Inégalité de Markov** (borne naïve)
> Pour toute variable aléatoire positive X : Pr(X ≥ t) ≤ E[X]/t

Application : E[#faux] = p·n. Donc Pr(#faux ≥ n/2) ≤ p·n / (n/2) = **2p**. C'est une borne très grossière.

**Outil 2 : Inégalité de Hoeffding** (borne exponentielle)

Pour une somme Sₙ de variables de Bernoulli i.i.d. de paramètre p :
$$\Pr\left(|S_n - \mathbb{E}[S_n]| \geq x\sqrt{n}\right) \leq 2e^{-2x^2}$$

En posant x = ½(1-2p)√n, on obtient :
$$\Pr(\text{erreur}) \leq 2e^{-\frac{1}{2}(1-2p)^2 n}$$

C'est une **décroissance exponentielle en n** — c'est beaucoup mieux que 2p !

**Outil 3 : Inégalité de Bienaymé-Tchebychev** (borne polynomiale)
$$\Pr(\text{erreur}) \leq \frac{2p(1-p)}{1-2p} \cdot n^{-1}$$

**Application pour p = 0.4 (table de multiplication erronée) :**
$$\Pr(\text{erreur}) \leq \min\left(2e^{-0.02n},\; 0.24 \cdot n^{-1}\right)$$

La borne de Hoeffding est meilleure pour les grands n, celle de Bienaymé-Tchebychev pour les petits n.

---

##### 🔷 Classification : Las Vegas, Monte-Carlo, Atlantic City

C'est le **cœur conceptuel du cours**. On classe les algorithmes probabilistes selon leur **type d'erreur** pour les
problèmes de décision (sortie OUI/NON).

---

###### Atlantic City (classe BPP — Both-sided error)

L'algorithme peut se tromper **dans les deux sens** (dire OUI quand c'est NON, et dire NON quand c'est OUI), mais
toujours avec une probabilité bornée :

|            | Sortie NON | Sortie OUI |
|------------|------------|------------|
| f(x) = NON | ≥ c₁ > 0.5 | ≤ 1-c₁     |
| f(x) = OUI | ≤ 1-c₂     | ≥ c₂ > 0.5 |

**BPP** = *Bounded-error Probabilistic Polynomial time* : la classe des problèmes résolubles en temps polynomial avec
une erreur bilatérale bornée. C'est la classe la plus générale.

---

###### Monte-Carlo (classe RP — Random Polynomial)

L'erreur est **unilatérale** : l'algorithme ne peut se tromper que d'un seul côté. Ici, s'il dit NON alors que c'est
OUI, il peut se tromper, mais s'il dit NON alors que c'est effectivement NON, il est toujours correct.

|            | Sortie NON | Sortie OUI |
|------------|------------|------------|
| f(x) = NON | prob = 1   | impossible |
| f(x) = OUI | ≤ c < 1    | ≥ 1-c      |

**RP** = *Random Polynomial* : classe des problèmes où on peut reconnaître les OUI avec probabilité > 1/2, sans jamais
dire OUI à tort (pas de faux positifs).

**Intuition :** Si l'algorithme dit OUI, c'est **forcément correct**. Si l'algorithme dit NON, c'est peut-être une
erreur. En répétant : si on obtient une fois OUI, c'est vrai. Si on obtient k fois NON, l'erreur est ≤ cᵏ.

---

###### Las Vegas (classe ZPP — Zero-sided error)

L'algorithme **ne se trompe jamais** — mais il peut renvoyer ÉCHEC, signifiant "je ne sais pas". La source d'aléatoire
affecte uniquement le **temps d'exécution**, pas la correction.

|            | Sortie NON | Sortie OUI | Sortie ÉCHEC |
|------------|------------|------------|--------------|
| f(x) = NON | ≥ 1-c₁     | impossible | ≤ c₁         |
| f(x) = OUI | impossible | ≥ 1-c₂     | ≤ c₂         |

**ZPP** = *Zero-error Probabilistic Polynomial time*.

**Relation entre les classes :** ZPP ⊆ RP ⊆ BPP (et on pense que ZPP = RP = BPP = P, mais c'est une question ouverte
majeure en complexité).

---

###### Algorithme Las Vegas sans échec

Si on a un algorithme Las Vegas de probabilité d'échec p et de coût T(x), on peut **éliminer l'ÉCHEC** en boucleant :

```text
do {res := LasVegas(x);} while (LasVegas(x) == ECHEC)
```

**Coût moyen :** E[nombre d'itérations] = 1/(1-p). Donc coût moyen = T(x)/(1-p).

Pourquoi 1/(1-p) ? C'est la même série géométrique que tout à l'heure : l'espérance d'une loi géométrique de paramètre (
1-p).

**Réciproquement :** Si un algorithme probabiliste sans ÉCHEC a coût moyen T(x), on peut le transformer en Las Vegas de
coût 2T(x) et probabilité d'ÉCHEC ≤ 1/2, par l'inégalité de Markov : si on coupe l'exécution après 2T(x) étapes, la
probabilité de ne pas avoir terminé est ≤ 1/2 (car E[temps] = T(x)).

---

##### 🔷 Exemple de Monte-Carlo : algorithme de Miller-Rabin

**Problème :** tester si n est premier.

**Comportement de Miller-Rabin :**

- Si n est premier → renvoie toujours "PREMIER" (pas de faux négatifs).
- Si n est composé → renvoie "COMPOSÉ" avec probabilité ≥ 3/4 (au pire 1/4 de chance de se tromper).

C'est un algorithme **Monte-Carlo de non-primalité** (RP) : jamais de faux positifs ("PREMIER" alors que composé), mais
des faux négatifs possibles.

En répétant k fois : Pr(erreur) ≤ (1/4)^k → négligeable rapidement.

---

##### 🔷 Exemple : Évaluation d'un arbre min-max (ET-OU)

**Problème :** On a un arbre binaire complet de hauteur h, avec n = 2^h feuilles. Les nœuds alternent MIN (ET) et MAX (
OU). Les feuilles ont des valeurs booléennes. On veut calculer la valeur de la racine.

**Borne inférieure déterministe :** Tout algorithme déterministe doit, en pire cas, lire **toutes les n feuilles**. Donc
coût pire cas ≥ n pour tout algorithme déterministe.

**Algorithme probabiliste (Las Vegas, P(ÉCHEC) = 0) :**

```text
evaluer(noeud n) :
    fils1 = choisir_un_fils_au_hasard(n)
    eval1 = evaluer(fils1)
    si val(n) n'est pas déterminée par eval1 :
        eval2 = evaluer(l'autre fils)
```

**Intuition :** Pour un nœud OU, si le premier fils évalué vaut 1, on sait que le OU vaut 1 → on n'évalue pas le second
fils ! Pour un nœud ET, si le premier fils vaut 0, le ET vaut 0 → idem. La randomisation fait qu'en moyenne, on "
court-circuite" souvent.

---

**Analyse du coût :**

Notons h = 2k (hauteur de l'arbre, alternance ET/OU).

**Lemme clé :** Pour un nœud ET de hauteur 2i (resp. OU de hauteur 2i+1), le coût moyen d'évaluation est ≤ 3^i.

**Preuve par récurrence :**

*Base :* i=0, nœud feuille, coût = 1 = 3⁰. ✓

*Hérédité :* On suppose vrai pour les nœuds ET de hauteur 2i (coût ≤ 3^i).

**Pour un nœud OU de hauteur 2i+1 :**

- Ses deux fils sont des nœuds ET de hauteur 2i.
- On tire l'un au hasard.

    - *Cas valeur OU = 0 :* Les deux fils valent 0. On doit évaluer les deux. Coût moyen ≤ 2·3^i.
    - *Cas valeur OU = 1 :* Au moins un fils vaut 1. Le premier tiré :
        - Avec proba 1/2, il vaut 1 → on s'arrête. Coût : 3^i.
        - Avec proba 1/2, il vaut 0 → on évalue le second. Coût : 2·3^i.
        - Coût moyen : ½·3^i + ½·2·3^i = 3/2·3^i.

Dans les deux cas, coût ≤ 2·3^i.

**Pour un nœud ET de hauteur 2(i+1) :**

- Ses deux fils sont des nœuds OU de hauteur 2i+1.

    - *Cas valeur ET = 1 :* Les deux fils valent 1. On doit évaluer les deux. Coût ≤ 2·(3/2·3^i) = 3^(i+1). ✓
    - *Cas valeur ET = 0 :* Au moins un fils vaut 0.
        - Avec proba 1/2, le premier tiré vaut 0 → coût : 2·3^i (coût d'un OU = 0).
        - Avec proba 1/2, le premier vaut 1, puis le second vaut 0 → coût : 3/2·3^i + 2·3^i = 7/2·3^i.
        - Coût moyen : ½·2·3^i + ½·7/2·3^i = 11/4·3^i ≤ 3^(i+1) (car 11/4 < 3). ✓

**Théorème :** Le coût moyen est O(n^0.793).

Preuve : La racine est un ET de hauteur h = 2k, donc coût ≤ 3^k = 3^(h/2) = (√3)^(log₂ n) = n^(log₂ √3) = n^0.793.

C'est **spectaculairement meilleur** que n ! Et on verra que c'est **optimal**.

---

##### 🔷 Borne inférieure et Principe Minimax de Yao

Comment prouver qu'aucun algorithme probabiliste ne peut faire mieux que O(n^0.793) ? C'est là qu'intervient le *
*principe Minimax de Yao**.

**Modélisation :** Un algorithme probabiliste peut être vu comme une **distribution de probabilité sur des algorithmes
déterministes**. À chaque exécution, on "tire au sort" quel algorithme déterministe on va utiliser.

Formellement : un algorithme probabiliste A est une variable aléatoire X_A à valeurs dans A_Det (l'ensemble des
algorithmes déterministes).

Le coût de A sur l'instance i est :
$$\text{Coût}(A, I) = \max_{i \in I} E_{X_A}[\text{Coût}(X_A, i)]$$

---

**Principe Minimax [Yao, 1977] :**

Soient X et Y deux variables aléatoires indépendantes, f une fonction réelle. Alors :
$$\min_{a} E[f(a, Y)] \leq \max_{b} E[f(X, b)]$$

**Preuve courte :**
$$\min_a E[f(a, Y)] \leq E_X[E_Y[f(X, Y)]] \stackrel{\text{Fubini}}{=} E_Y[E_X[f(X, Y)]] \leq \max_b E[f(X, b)]$$

(On utilise simplement que la moyenne est entre le min et le max.)

**Application au calcul de borne inférieure :**

Pour tout algorithme probabiliste A et toute distribution d'entrée Y_I :
$$\text{Coût}(A, I) = \max_{i \in I} E_{X_A}[\text{Coût}(X_A, i)] \geq \min_{B \in A_{\text{Det}}} E_{Y_I}[\text{Coût}(B, Y_I)]$$

**Traduction :** Pour obtenir une borne inférieure sur tout algorithme **probabiliste**, il suffit de trouver une borne
inférieure sur tout algorithme **déterministe** en **moyenne sur une distribution d'entrées bien choisie**.

C'est beaucoup plus facile à prouver ! On choisit nous-mêmes la distribution d'entrées.

---

**Application à l'arbre ET-OU :**

**Réduction :** L'arbre ET-OU est équivalent à un arbre NOR (toutes les opérations remplacées par NOR) : (a OR b) AND (c
OR d) ≡ (a NOR b) NOR (c NOR d).

**Distribution choisie :** Chaque feuille prend la valeur 1 indépendamment avec probabilité p. On choisit p tel que la
valeur de chaque nœud NOR de même hauteur ait la même probabilité d'être 1 :
$$p = \Pr[\text{NOR}(a,b) = 1] = \Pr[a=0] \cdot \Pr[b=0] = (1-p)^2$$

Résoudre (1-p)² = p : 1 - 2p + p² = p → p² - 3p + 1 = 0 → **p = (3 - √5)/2 ≈ 0.382**.

**Borne inférieure déterministe :** Pour tout algorithme déterministe a, le coût moyen W_a(h) d'évaluation d'un nœud de
hauteur h vérifie :
$$W_a(h) \geq (2-p) \cdot W_a(h-1)$$

Pourquoi ? Avant d'inspecter une feuille du second sous-arbre, il faut avoir fini le premier (coût W_a(h-1)), puis avec
probabilité (1-p) il faut continuer sur le second.

Donc : W_a(h) ≥ (2-p)^h = ((1+√5)/2)^h = n^(log₂((1+√5)/2)) = Ω(n^0.694).

**Pour obtenir la borne exacte n^0.792 :** On raffine la distribution pour exclure le cas où les deux fils d'un NOR
valent 1 (cas où un bon algorithme n'évalue pas les deux fils). La distribution optimale donne,
selon [Saks & Wigderson, 1986], la borne n^(log₂(3/2)) = n^0.792, qui correspond exactement au coût de l'algorithme
probabiliste proposé.

**Conclusion :** L'algorithme probabiliste d'évaluation aléatoire est **optimal** parmi tous les algorithmes
probabilistes.

---

##### 🔷 Lemme de Schwartz-Zippel

C'est un outil fondamental pour les algorithmes probabilistes en algèbre.

**Énoncé :**
Soit P ∈ K[X₁,...,Xₙ] un polynôme **non nul** de degré d sur un corps K. Soit I ⊆ K fini, et (u₁,...,uₙ) tiré *
*uniformément** dans Iⁿ. Alors :
$$\Pr(P(u_1, \ldots, u_n) = 0) \leq \frac{d}{|I|}$$

**Intuition :** Un polynôme non nul de degré d a au plus d racines (en une variable). En n variables, il a "peu" de
racines relatives à la taille de l'espace. Si on tire au hasard, on a peu de chances de tomber sur une racine.

**Applications majeures :**

**1. Vérification du produit de matrices (Freivalds, 1977) :**

Problème : Étant donné A, B, C ∈ Mₙₓₙ(K), vérifier si C = A×B sans calculer A×B directement (qui coûte O(n²·⁸⁷) avec
Strassen).

Algorithme :

```text
1. Choisir u ∈ {0,1}ⁿ uniformément
2. Calculer v = B·u, w = A·v, z = C·u  (en O(n²))
3. Si z == w : retourner OUI, sinon retourner NON
```

Analyse : Si AB ≠ C, soit la i-ème ligne (AB)ᵢ ≠ Cᵢ. Le polynôme Pᵢ(X₁,...,Xₙ) = Σⱼ(ABᵢⱼ - Cᵢⱼ)Xⱼ est non nul et de
degré 1. Par Schwartz-Zippel avec I = {0,1}, Pr(erreur) ≤ 1/|I| = 1/2. En prenant I plus grand, l'erreur diminue.

**Coût :** O(n²) au lieu de O(n^2.87) pour la multiplication directe. Et la vérification est probabiliste.

**2. Test de primalité :**
n est premier ssi (1+X)ⁿ = 1+Xⁿ (mod n). On vérifie cela en tirant un polynôme Q de petit degré et en calculant (1+X)ⁿ
mod Q.

**3. Couplage parfait :**
Un graphe a un couplage parfait ssi le déterminant de sa matrice de Tutte est non nul. On peut le tester
probabilistiquement par Schwartz-Zippel.

---

#### 3. Résumé concis du cours

Les algorithmes probabilistes exploitent l'**aléatoire comme ressource algorithmique** (et non comme propriété de
l'entrée). Ils sont classés selon leur type d'erreur : **Monte-Carlo** (erreur unilatérale, toujours terminé), **Las
Vegas** (jamais d'erreur, mais peut signaler ÉCHEC), **Atlantic City** (erreur bilatérale bornée). L'aléatoire apporte
gains en vitesse (O(n^0.793) vs $O(n)$ pour l'arbre ET-OU) et en simplicité. Les outils d'analyse principaux sont les
inégalités de concentration (Markov, Hoeffding, Bienaymé-Tchebychev), le lemme de Schwartz-Zippel pour les identités
algébriques, et le principe Minimax de Yao pour prouver des bornes inférieures.

---

#### 4. Formules et algorithmes clés

| Outil                 | Formule                                             |
|-----------------------|-----------------------------------------------------|
| Espérance géométrique | E[L] = 1/(1-p) pour une boucle avec proba p d'échec |
| Union bound           | Pr(A₁ ∪ ... ∪ Aₖ) ≤ Σ Pr(Aᵢ)                        |
| Markov                | Pr(X ≥ t) ≤ E[X]/t                                  |
| Hoeffding             | Pr(erreur) ≤ 2 exp(−½(1-2p)²n)                      |
| Bienaymé-Tchebychev   | Pr(erreur) ≤ 2p(1-p)/((1-2p)·n)                     |
| Schwartz-Zippel       | Pr(P(u₁,...,uₙ) = 0) ≤ d/                           |I| |
| Minimax de Yao        | min_a E[f(a,Y)] ≤ max_b E[f(X,b)]                   |
| Coût arbre ET-OU      | O(n^(log₂ √3)) = O(n^0.793)                         |

---

#### 5. Les 10 concepts les plus importants

1. **Algorithme probabiliste vs analyse en moyenne :** l'aléatoire est dans l'algorithme, pas dans l'entrée.
2. **Classification Monte-Carlo / Las Vegas / Atlantic City** et les classes de complexité RP, ZPP, BPP associées.
3. **Amplification par répétition :** un algorithme d'erreur p < 1/2 peut être rendu aussi fiable qu'on veut.
4. **Union bound :** Pr(∪ Aᵢ) ≤ Σ Pr(Aᵢ), outil universel pour borner les erreurs.
5. **Inégalité de Hoeffding :** décroissance exponentielle de l'erreur avec le nombre de répétitions.
6. **Lemme de Schwartz-Zippel :** vérification probabiliste d'identités polynomiales.
7. **Algorithme d'évaluation aléatoire d'arbre ET-OU :** coût O(n^0.793) vs $O(n)$ déterministe.
8. **Principe Minimax de Yao :** pour borner inférieurement la complexité probabiliste, il suffit de borner la
   complexité déterministe en moyenne sur une distribution bien choisie.
9. **Modélisation d'un algo probabiliste comme distribution sur algos déterministes.**
10. **Transformation Las Vegas ↔ algo sans ÉCHEC** via la boucle et l'inégalité de Markov.

---

#### 6. Questions conceptuelles pour tester ta compréhension

**Question 1 :** Soit un algorithme probabiliste Monte-Carlo qui, quand f(x) = 1, retourne 1 avec probabilité 2/3. Si on
le répète 100 fois indépendamment et qu'on prend la valeur majoritaire, quelle est (approximativement) la probabilité
d'erreur ?

**Question 2 :** Pourquoi utilise-t-on l'inégalité de l'union (union bound) pour analyser la probabilité d'erreur de l'
algorithme de table de multiplication erronée, plutôt que simplement multiplier les probabilités individuelles ?

**Question 3 :** Dans l'algorithme d'évaluation d'arbre ET-OU, pourquoi l'algorithme est-il classifié Las Vegas avec Pr(
ÉCHEC) = 0 ? N'est-ce pas contradictoire avec la définition de Las Vegas ?

**Question 4 :** Explique intuitvement pourquoi le principe Minimax de Yao permet de déduire une borne inférieure sur
les algorithmes **probabilistes** à partir d'une borne inférieure sur les algorithmes **déterministes** en moyenne.

**Question 5 :** Dans la vérification probabiliste de C = A×B par Schwartz-Zippel, pourquoi choisit-on u dans {0,1}ⁿ
plutôt que dans un ensemble plus grand ? Quel est l'avantage d'un ensemble plus grand ?

### Partie Pratique (TD)

_Aucun bloc TD distinct n'est séparé dans la source pour cette séance ; les exercices et questions présents dans les
notes ci-dessus ont été conservés dans leur emplacement source._

---

<a id="seance-8"></a>

## Séance 8 — Techniques d'analyse probabiliste, chaînes de Markov et vol de travail

> Plage source conservée : lignes `3032` à `3631` de `course.txt`.

### Partie Théorique

C'est une excellente suite ! La séance 8 rentre véritablement dans le "moteur" des algorithmes probabilistes. Maintenant
que vous avez vu *pourquoi* l'aléatoire est utile (Séance 7), cette séance vous montre *comment prouver
mathématiquement* que ces algorithmes sont efficaces et fiables, avant de l'appliquer à des structures distribuées (le
fameux *Work-Stealing*).

Accrochez-vous, il y a un peu de formalisme, mais c'est ce qui donne toute sa puissance à l'informatique théorique
moderne.

Voici votre cours détaillé et structuré pour cette huitième séance.

---

#### Séance 8 : Techniques d'Analyse Probabiliste, Chaînes de Markov et Vol de Travail

**Objectif de la séance :** Maîtriser les outils mathématiques (inégalités et bornes) permettant de borner l'erreur d'un
algorithme probabiliste. Appliquer ces concepts aux graphes (Marches aléatoires, PageRank), à la recherche de la
médiane, et comprendre l'ordonnancement distribué par vol de travail.

##### 1. Le Vocabulaire des Probabilités en Algorithmique

Quand on analyse un algorithme probabiliste, on ne dit pas juste "ça marche souvent". On utilise un vocabulaire précis
pour qualifier la probabilité de succès d'un événement $E$ par rapport à la taille du problème $n$ :

* **Surely (Sûrement) :** L'événement est toujours vrai, il n'y a aucun cas contraire.
* **Almost surely (a.s.) :** La probabilité de $E$ est exactement $1$.
* **With high probability (w.h.p.) :** La probabilité de succès tend très vite vers 1.
  Formellement : $\exists c > 0, Pr(E) \ge 1 - n^{-c}$.
* **With overwhelming probability (w.o.p.) :** La probabilité d'échec est écrasée exponentiellement. Par
  exemple : $Pr(E) \ge 1 - e^{-cn}$.

---

##### 2. La Boîte à Outils Mathématique (Les 3 Inégalités d'Or)

Pour prouver qu'un algorithme a une "haute probabilité" de réussir, on utilise des théorèmes de concentration. Plus on
descend dans cette liste, plus on a besoin de conditions sur nos variables, mais plus la borne est "serrée" (précise).

###### A. Inégalité de Markov (La plus basique)

Elle s'applique à toute variable aléatoire $X$ positive. Elle dit qu'il est rare qu'une variable dépasse largement son
espérance.
Pour tout $\lambda > 0$ :
$$Pr[X \ge \lambda] \le \frac{E[X]}{\lambda}$$
*Application :* Si un algorithme sans échec prend un temps moyen $T(x)$, la probabilité qu'il prenne plus de $2T(x)$
est $\le 1/2$.

###### B. Inégalité de Bienaymé-Tchebychev (L'écart-type)

Elle utilise la variance ($\sigma^2$) pour borner l'écart à la moyenne ($\mu$).
$$Pr(|X - \mu| \ge \lambda) \le \frac{\sigma^2}{\lambda^2}$$

###### C. Les Bornes de Chernoff (L'arme absolue)

C'est l'outil le plus puissant pour les algorithmes probabilistes. Il s'applique aux sommes de variables de Bernoulli
indépendantes (des tirages "pile ou face" avec une probabilité de succès $p$).
Chernoff prouve que la probabilité de s'écarter de l'espérance décroît de manière **exponentielle** :

* Pour la borne inférieure : $Pr\{X \le (1-\epsilon)pn\} \le e^{-\epsilon^2 np / 2}$.
* Pour la borne supérieure : $Pr\{X \ge (1+\epsilon)pn\} \le e^{-\epsilon^2 np / 3}$.

---

##### 3. Les Marches Aléatoires et Chaînes de Markov

Une chaîne de Markov modélise un système qui passe d'un état à un autre avec certaines probabilités.

###### A. Résolution de 2-SAT par Marche Aléatoire

* **Le problème :** Trouver une affectation qui satisfait une formule logique où chaque clause a 2 variables.
* **L'algorithme :** On prend une affectation au hasard. Tant que ce n'est pas bon, on prend une clause fausse et on "
  flappe" (inverse) l'une de ses 2 variables au hasard.
* **L'analyse :** Cela forme une marche aléatoire (un pas en avant vers la solution, ou un pas en arrière). Le temps
  moyen pour atteindre la solution (s'il y en a une) est borné par $n^2$. Par l'inégalité de Markov, après $2n^2$
  étapes, si on n'a rien trouvé, on peut répondre "NON" avec une certitude $\ge 50\%$.

###### B. PageRank (L'algorithme originel de Google)

Le PageRank est une marche aléatoire sur le graphe du web !

* Google calcule l'importance d'une page en simulant un internaute qui clique au hasard sur les liens.
* Pour éviter d'être bloqué dans des "puits" (pages sans liens sortants) , on ajoute un facteur de saut ou
  téléportation : avec une probabilité $\alpha \simeq 0.85$, on suit un lien, et avec $(1-\alpha)$, on saute sur une
  page complètement au hasard.
* Le système converge vers une "distribution stationnaire", qui correspond au score PageRank.

---

##### 4. Médiane et Algorithmes "Diviser pour Régner" Probabilistes

Trouver le $k$-ième plus petit élément (ex: la médiane) d'un tableau non trié.

* **L'algorithme (Random Median) :** 1. On choisit un pivot $p$ au hasard.
    2. On partitionne le tableau autour de $p$.
    3. Si le pivot tombe à la position $k$, c'est fini! Sinon, on relance récursivement sur la bonne moitié.
* **Analyse :** En moyenne, le pivot réduit la taille du problème d'un facteur $3/4$ (avec une proba $1/2$). L'espérance
  du coût total est une série géométrique qui converge vers un temps linéaire $\le 8n$. L'aléatoire permet d'obtenir
  du $\mathcal{O}(n)$ de manière élégante et ultra simple à coder.

---

##### 5. Algorithmique Distribuée : Le Vol de Travail (Work-Stealing)

C'est la méthode utilisée par tous les ordonnanceurs modernes (comme OpenMP, Cilk, etc.) pour équilibrer la charge entre
plusieurs processeurs sans créer de goulot d'étranglement centralisé.

###### Le Principe de la Deque (Double-Ended Queue)

Chaque processeur possède sa propre file de tâches locale.

1. **Le Comportement Local (LIFO) :** Quand un processeur crée des tâches (ex: appels récursifs), il les empile en haut
   de sa propre file. Il les dépile également par le haut. Il agit comme une pile (Last In, First Out). Cela optimise le
   cache mémoire !
2. **Le Vol (FIFO) :** Quand un processeur n'a plus rien à faire (sa file est vide), il devient un *voleur*.
    * Il choisit une victime au hasard.
    * Il va voler la tâche **la plus ancienne** (en bas de la file de la victime), agissant comme une file d'attente (
      First In, First Out).

**Schéma du concept :**

```text
Processeur Victime (P1)                       Processeur Voleur (P2)
=======================                       ======================
[ Tâche Récente ] <--- P1 travaille ici        [       VIDE      ] <-- P2 n'a plus rien
[ Tâche Moyenne ]
[ Tâche Ancienne] <--- P2 Vole ICI ! (FIFO)
```

**Pourquoi voler en bas de la file (FIFO) ?**
Parce que dans un algorithme "Diviser pour Régner", les tâches les plus anciennes sont celles situées le plus haut dans
l'arbre d'exécution : elles représentent de *gros* blocs de calcul. Le voleur récupère ainsi un gros morceau de travail,
ce qui lui évitera d'avoir à voler à nouveau 2 millisecondes plus tard !

---
*Voulez-vous que nous passions à la séance suivante, ou souhaitez-vous explorer un exercice d'application sur les bornes
de Chernoff pour voir comment on les utilise concrètement dans un calcul ?*

### Cours 2/3 : Algorithmes Probabilistes — Techniques d'Analyse, Tri, Médiane, Work-Stealing

---

#### 1. Vue d'ensemble du cours

##### Principaux thèmes

Ce cours approfondit les **outils mathématiques** pour analyser les algorithmes probabilistes, puis les applique à des
exemples concrets : approximation de MAX-SAT/3-SAT, marches aléatoires (2-SAT, PageRank), tri et médiane probabilistes,
et ordonnancement distribué par vol de travail.

##### Objectifs

- Maîtriser la **hiérarchie des probabilités** (a.s., w.h.p., w.o.p.)
- Comprendre et appliquer les **inégalités de concentration** : Markov, Tchebychev, Hoeffding, **Chernoff**
- Analyser des algorithmes probabilistes via des **chaînes de Markov** et des **marches aléatoires**
- Comprendre QuickSort et la médiane probabilistes avec leurs analyses fines

---

#### 2. Cours complet

---

##### 🔷 Dénominations communes : hiérarchie des probabilités

Avant d'analyser des algorithmes, il faut un vocabulaire précis pour parler de probabilités "proches de 1".

**Définitions (du plus faible au plus fort) :**

| Terme                                      | Définition formelle                 | Intuition                                                                           |
|--------------------------------------------|-------------------------------------|-------------------------------------------------------------------------------------|
| **surely** (vrai)                          | Le complémentaire est vide          | Toujours vrai, sans exception                                                       |
| **almost surely** (a.s.)                   | Pr(E) = 1                           | Vrai avec probabilité 1 (peut exclure des événements de mesure nulle)               |
| **a.a.s.** (asymptotically almost surely)  | lim Pr(E) = 1 quand n → ∞           | Vrai avec probabilité tendant vers 1                                                |
| **w.h.p.** (with high probability)         | ∃c > 0 : Pr(E) ≥ 1 − n⁻ᶜ            | Probabilité d'erreur polynomialement petite en n                                    |
| **w.o.p.** (with overwhelming probability) | ∀A > 0, ∃cₐ > 0 : Pr(E) ≥ 1 − cₐ/nᴬ | Probabilité d'erreur super-polynomialement petite — par exemple Pr(E) ≥ 1 − e^(−cn) |

**Pourquoi ces distinctions sont-elles importantes ?**

Quand on analyse un algorithme probabiliste, on veut savoir "à quel point il est fiable". Dire "ça marche avec
probabilité ≥ 1 − 1/n²" est une garantie bien plus forte que "ça marche avec probabilité ≥ 3/4". Dans la pratique
algorithmique :

- **w.h.p.** est souvent suffisant : une erreur de probabilité 1/n^c devient négligeable pour n grand.
- **w.o.p.** (décroissance exponentielle) est encore mieux : même pour n = 1000, 1/e^(1000) est astronomiquement petit.

> **Exemple concret :** Dans l'analyse de QuickSort, on montrera que le tri est correct w.h.p. — c'est-à-dire que la
> probabilité qu'un élément soit mal placé est inférieure à 1/√n.

---

##### 🔷 Inégalité de Markov — rappel et applications

**Énoncé :** Pour toute variable aléatoire X ≥ 0 et tout λ > 0 :
$$\Pr[X \geq \lambda] \leq \frac{\mathbb{E}[X]}{\lambda}$$

**Intuition :** Si X est positif et a petite espérance, elle ne peut pas prendre de grandes valeurs trop souvent. C'est
la borne la plus grossière mais la plus universelle — elle ne nécessite que l'espérance.

**Application immédiate :** Pr[X ≤ 2·E[X]] ≥ 1/2.

*Preuve :* Pr[X > 2E[X]] ≤ E[X]/(2E[X]) = 1/2. Donc la probabilité complémentaire est ≥ 1/2.

**Application clé — transformation en Las Vegas :**

Si un algorithme sans ÉCHEC a coût moyen T(x), on peut le transformer en Las Vegas :

- On lance l'algorithme et on le coupe après **2T(x)** opérations.
- Par Markov : Pr[temps > 2T(x)] ≤ T(x)/(2T(x)) = 1/2.
- Donc avec probabilité ≥ 1/2, l'algorithme a terminé → probabilité d'ÉCHEC ≤ 1/2. ✓

---

##### 🔷 Inégalité de Tchebychev

**Énoncé :** Pour X de moyenne μ et variance σ² :
$$\Pr(|X - \mu| \geq \lambda) \leq \frac{\sigma^2}{\lambda^2}$$

**Progrès par rapport à Markov :** Markov dit "X ne s'éloigne pas trop de 0 en espérance". Tchebychev dit "X ne
s'éloigne pas trop de sa **moyenne**". C'est une borne symétrique des deux côtés, qui utilise la **variance**.

**Limitation :** La borne décroît seulement en 1/λ², ce qui est polynomial. Les bornes de **Chernoff** font bien mieux (
décroissance exponentielle).

---

##### 🔷 Formules utiles à connaître par cœur

Ces approximations sont utilisées constamment dans les analyses :

**Stirling :** $n! \simeq \sqrt{2\pi n} \left(\frac{n}{e}\right)^n$

Utile pour majorer des coefficients binomiaux.

**Coefficients binomiaux :** $\left(\frac{n}{k}\right)^k \leq \binom{n}{k} \leq \left(\frac{ne}{k}\right)^k$

La borne supérieure $\binom{n}{k} \leq (ne/k)^k$ est la plus utilisée pour les majorations.

**Approximation de Poisson :** $\left(1 - \frac{a}{n}\right)^n \simeq e^{-a}$

Indispensable : si on fait n tirages avec probabilité de succès a/n chacun, la probabilité de ne jamais réussir est ≈
e^{-a}.

---

##### 🔷 Bornes de Chernoff — l'outil central de ce cours

C'est l'inégalité **la plus puissante et la plus utilisée** pour les algorithmes probabilistes.

**Cadre :** X₁,...,Xₙ variables de Bernoulli i.i.d., Pr(Xₖ = 1) = p, X = ΣXᵢ ~ Binomiale(n,p).

**Bornes de Chernoff :** Pour tout 0 < ε < 1 :
$$\Pr\{X \leq (1-\epsilon)pn\} \leq e^{-\epsilon^2 np/2} \quad \text{(borne inférieure)}$$
$$\Pr\{X \geq (1+\epsilon)pn\} \leq e^{-\epsilon^2 np/3} \quad \text{(borne supérieure)}$$

**Décryptage :**

- $pn$ = E[X] = espérance de X.
- $(1-\epsilon)pn$ = fraction (1-ε) de l'espérance. La borne dit : la probabilité d'être **bien en dessous** de la
  moyenne décroît **exponentiellement** en n.
- L'argument de l'exponentielle est $\epsilon^2 \cdot np$ — plus n est grand, plus la borne est serrée.

**Intuition derrière Chernoff :** Chernoff exploite la **fonction génératrice des moments** $\mathbb{E}[e^{tX}]$, qui
encode toute l'information sur la distribution de X. En optimisant sur t, on obtient des bornes exponentielles bien
meilleures que Markov ou Tchebychev.

**Autre formulation (pour variables centrées) :** Si E[Xᵢ] = 0, |Xᵢ| ≤ 1, σ² = Var(X = ΣXᵢ), alors pour 0 ≤ λ ≤ 2σ :
$$\Pr[|X| \geq \lambda\sigma] \leq 2e^{-\lambda^2/4}$$

**Illustration — estimation de la moyenne :** Dans une population de N éléments, proportion p inconnue a une propriété.
Après n tirages :
$$\Pr\left\{\frac{X}{n} = p(1 \pm \epsilon)\right\} \geq 1 - 2e^{-\epsilon^2 np/2}$$

Exemple : pour estimer p à 1% près avec probabilité > 99%, il suffit de n = O(1/p) tirages — indépendant de N !

---

##### 🔷 Application de Chernoff : MAX-3-SAT

**Problème MAX-3-SAT :** m clauses à 3 variables, maximiser les clauses satisfaites.

**Algorithme probabiliste :** Affecter chaque variable uniformément dans {0,1}.

- Pr(clause Cᵢ non satisfaite) = (1/2)³ = 1/8 (les 3 variables doivent toutes être "mauvaises").
- Pr(Cᵢ satisfaite) = 7/8.
- E[Xᵢ] = 7/8 (Xᵢ = 1 si clause i satisfaite).
- E[nombre de clauses satisfaites] = 7m/8.

**Ratio d'approximation = 8/7.** C'est l'un des meilleurs ratios connus pour MAX-3-SAT (sous P ≠ NP, on ne peut pas
faire mieux que 8/7, résultat de Håstad).

**Corollaire (résultat d'existence) :** Toute instance de MAX-3-SAT admet une affectation qui satisfait au moins 7m/8
clauses. Ce n'est pas un résultat de complexité — c'est une garantie existentielle prouvée par l'argument probabiliste !

**Exercice (Chernoff) :** On tire des affectations jusqu'à en obtenir une avec ≥ 7m/8 clauses satisfaites. Quel est le
temps moyen ?

Posons Pᵣ = Pr(une affectation aléatoire satisfait ≥ 7m/8 clauses). Le nombre de tirages suit une loi géométrique de
paramètre Pᵣ. Pour estimer Pᵣ, on utilise Chernoff : la somme X = ΣXᵢ (nombre de clauses satisfaites) est une somme de
Bernoulli i.i.d. de paramètre p = 7/8. Avec E[X] = 7m/8 et ε tel que (1-ε)·7m/8 = 7m/8 → ε → 0, Chernoff donne que X ≥
7m/8 avec probabilité Ω(1). Le temps moyen est donc $O(1)$ tirages, chacun en O(m) → **coût moyen O(m)**.

---

##### 🔷 Briser la symétrie aléatoirement — éléments indépendants dans un cycle

**Problème :** Une liste circulaire L₀,...,Lₙ₋₁. En parallèle (en $O(1)$), trouver un grand ensemble X d'éléments
indépendants (aucun adjacent dans le cycle).

**Pourquoi difficile en parallèle ?** En séquentiel, trivial : parcourir et prendre un élément sur deux. En parallèle,
tous les processeurs doivent décider simultanément.

**Algorithme $O(1)$ :**

```text
en parallèle : attribuer à chaque Li une couleur aléatoire col(Li) ∈ {0,1}
si col(Li) = 1 ET col(Succ(Li)) = 0 : mettre Li dans X
```

**Analyse :**

- Pr(Lᵢ ∈ X) = Pr(col(Lᵢ)=1) · Pr(col(Lᵢ₊₁)=0) = 1/2 · 1/2 = 1/4.

**Problème :** Les Lᵢ adjacents ne sont pas indépendants (Lᵢ et Lᵢ₊₁ partagent col(Lᵢ₊₁)).

**Astuce de décorrélation :** On se restreint aux éléments d'indices **pairs** x₂ᵢ. Les événements "x₂ᵢ sélectionné"
et "x₂ⱼ sélectionné" pour i ≠ j sont **indépendants** (ils n'ont pas de voisin en commun).

Soit Y = Σ X₂ᵢ (sur n/2 termes i.i.d. de paramètre p = 1/4), et C ≥ Y le nombre total sélectionné.

Chernoff (borne inférieure) : E[Y] = n/8, avec (1-ε) = α·8 :
$$\Pr(Y < (1-\epsilon)\frac{n}{8}) < \exp\left(-\frac{\epsilon^2 n}{16}\right)$$

En posant α = (1-ε)/8, soit ε = 1-8α : pour α ∈ ]0, 1/8[ :
$$\Pr(C < \alpha n) \leq \Pr(Y < \alpha n) < \exp(-\beta n) \quad \text{avec } \beta = \frac{(1-8\alpha)^2}{16}$$

**Exemple concret :** α = 1/16 → Pr(C < n/16) < e^{-64n} < (2×10⁻²⁸)ⁿ.

**Conclusion :** C > n/16 **w.o.p.** — avec probabilité écrasante, on sélectionne au moins n/16 éléments en temps
parallèle $O(1)$ !

---

##### 🔷 MAX-SAT — généralisation

**Différence avec MAX-3-SAT :** Les clauses peuvent avoir **k variables quelconque** (k ≥ 1).

**Analyse :** La probabilité qu'une clause à k variables soit satisfaite est 1 - 2^{-k} ≥ 1/2 (au moins autant que le
cas k=1 où c'est 1/2).

Donc E[v(X)] ≥ m/2 → il existe toujours une affectation satisfaisant ≥ m/2 clauses.

**Ratio d'approximation :** L'algorithme randomisé a ratio ≥ 1/2. Si toutes les clauses ont ≥ k variables, le ratio
est ≥ 1 − 1/2^k (qui tend vers 1 quand k augmente).

---

##### 🔷 Marche aléatoire — 2-SAT

**Problème 2-SAT :** Formule CNF avec au plus 2 littéraux par clause. Décider si satisfaisable.

**Algorithme probabiliste (Papadimitriou, 1991) :**

```text
Choisir une affectation arbitraire
Pour i = 1..2n² :
    Trouver une clause non satisfaite (si aucune : retourner OUI)
    Choisir au hasard l'un de ses 2 littéraux et l'inverser
Retourner NON
```

**Type :** Monte-Carlo. Si F est insatisfaisable → toujours NON. Si F est satisfaisable → NON possible (erreur).

**Modélisation par chaîne de Markov :**

Soit A une affectation satisfaisante. On pose Nᵢ = nombre de variables de l'affectation courante qui **coïncident** avec
A à l'étape i.

L'algorithme prend une clause non satisfaite (au moins un des 2 littéraux diffère de A) et inverse un littéral au
hasard :

- Avec probabilité ≥ 1/2 : on inverse un littéral qui diffère de A → Nᵢ₊₁ = Nᵢ + 1
- Avec probabilité ≤ 1/2 : on inverse un littéral correct → Nᵢ₊₁ = Nᵢ − 1

C'est une **marche aléatoire sur une chaîne** avec états {0,...,n} !

**Calcul du temps d'atteinte :** Notons hⱼ = E[temps pour atteindre n depuis j]. On a l'équation de récurrence :

$$h_j = 1 + \frac{1}{2}h_{j-1} + \frac{1}{2}h_{j+1}$$

avec conditions hₙ = 0, h₀ = h₁ + 1 (bord absorbant à 0 avec rebond).

En posant dⱼ = hⱼ - hⱼ₊₁, l'équation donne dⱼ = dⱼ₋₁ + 2 → dⱼ = 2j + 1.

Donc : $h_0 = h_1 + 1 = \sum_{j=1}^n (2j-1) = n^2$

**Application :** E[temps depuis 0 vers n] = n².

**Inégalité de Markov :** Pr[X₀ > 2n²] ≤ E[X₀]/(2n²) = n²/(2n²) = 1/2.

→ Après 2n² étapes, la probabilité de ne pas avoir trouvé une solution est ≤ 1/2. En répétant k fois : probabilité
d'erreur ≤ (1/2)^k. Pour k = 30 : erreur < 10⁻⁹. ✓

---

##### 🔷 Marches aléatoires dans les graphes — Parcours de graphe

**Problème :** Tester si deux sommets s et t sont connectés dans un graphe non orienté G = (V,E), n sommets, m arcs.

BFS/DFS : O(n+m) temps, $O(n)$ espace mémoire. **Peut-on faire mieux en espace ?**

**Algorithme probabiliste (marche aléatoire) :**

```text
r = s;
tant que (r ≠ t) : r = voisin_aléatoire(r);
```

**Lien avec chaîne de Markov :** Cette marche correspond à une chaîne de Markov de matrice de
transition $P_{i,j} = 1/d(i)$ si $(i,j) \in E$, 0 sinon.

**Propriétés de convergence :**

- La chaîne est **irréductible** (G connexe → on peut atteindre tout état).
- La chaîne est **apériodique** si G n'est pas bipartite.
- → Elle admet une **unique distribution stationnaire** Π.

---

##### 🔷 Analyse de la chaîne de Markov — Distribution stationnaire

**Théorème fondamental :** Pour une marche aléatoire sur un graphe G non orienté :
$$\Pi_i = \frac{\deg(i)}{2m}$$

**Preuve :** Il suffit de vérifier Π·P = Π et Σᵢ Πᵢ = 1.

*Vérification de Π·P = Π :* Pour tout sommet j :
$$(Π P)_j = \sum_i \Pi_i P_{i,j} = \sum_{i:(i,j)\in E} \frac{\deg(i)}{2m} \cdot \frac{1}{\deg(i)} = \sum_{i:(i,j)\in E} \frac{1}{2m} = \frac{\deg(j)}{2m} = \Pi_j \checkmark$$

**Interprétation :** Les sommets de haut degré sont plus fréquemment visités — logique, car plus de chemins y mènent.

**Temps de retour :** hᵢ,ᵢ = 1/Πᵢ = 2m/deg(i).

**Temps d'atteinte :** Si (i,j) ∈ E, alors hⱼ,ᵢ < 2m.

*Preuve :* hᵢ,ᵢ = 2m/deg(i) et hᵢ,ᵢ = Σⱼ voisin 1/deg(i) · (1 + hⱼ,ᵢ). Donc :
$$\sum_{j \text{ voisin}} (1 + h_{j,i}) = 2m$$

et en particulier chaque terme vérifie $1 + h_{j,i} \leq 2m$, soit $h_{j,i} \leq 2m-1 < 2m$. ✓

**Temps de couverture :** Cᵢ = temps moyen pour visiter **tous** les sommets < 4nm.

*Preuve :* Il existe un arbre couvrant de G. Le parcours de cet arbre avec retour à la racine traverse 2n arcs. Chaque
arc est parcouru en temps moyen < 2m. Donc Cᵢ ≤ 2n·2m = 4nm. ✓

**Application :** En faisant K = 8nm = O(n³) pas depuis s, la probabilité de ne pas atteindre t est (Markov) < 4nm/(
8nm) = 1/2. ✓

> **Gain en espace :** La marche aléatoire utilise $O(\log n)$ espace (juste le sommet courant), contre $O(n)$ pour
> BFS/DFS. C'est la base de l'algorithme de Reingold (2008) qui résout la connectivité en espace $O(\log n)$
> deterministement.

---

##### 🔷 Application : PageRank

**Idée de Google :** L'importance R(B) d'une page web est proportionnelle à la somme des importances des pages qui
pointent vers elle, pondérées par leur degré sortant :
$$R(B) = \sum_{A:A \to B} R(A)/d(A)$$

C'est exactement la **distribution stationnaire** d'une marche aléatoire sur le graphe du Web !

**Problème des puits :** Les pages sans liens sortants accumulent de l'importance sans en redistribuer. Cela crée des
solutions dégénérées.

**Solution (équation corrigée) :**
$$R(B) = \frac{1-\alpha}{N} + \alpha \sum_{A:A \to B} R(A)/d(A)$$

avec α ≈ 0.85. À chaque pas, avec probabilité (1-α) on téléporte vers une page aléatoire, avec probabilité α on suit un
lien.

**Algorithme :** Partir d'une distribution initiale arbitraire. Multiplier répétitivement par la matrice de transition.
La chaîne converge vers la distribution stationnaire. En pratique pour Google : 50-100 itérations suffisent.

---

##### 🔷 Médiane probabiliste — RandomMedian

**Problème :** Trouver l'élément de rang k dans un tableau de n éléments non triés.

**Algorithme RandomMedian(i, j, k) :**

```text
1. Si (j - i == 1) : retourner aᵢ  (cas de base)
2. Choisir p au hasard dans {i,...,j-1}
3. r := segmenter(i, j, p)   [O(j-i) comparaisons, place aₚ à sa bonne position r]
4. Si r == k : retourner aₚ
5. Si r > k : retourner RandomMedian(i, r, k)
6. Sinon : retourner RandomMedian(r+1, j, k-r-1)
```

C'est essentiellement QuickSelect randomisé. L'aléatoire vient du choix du pivot p.

**Analyse du coût :**

Soit Xⱼ = taille du sous-tableau à l'étape j.

**Lemme clé :** Pr(Xⱼ₊₁ ≤ 3Xⱼ/4) = 1/2.

*Pourquoi ?* Si le pivot tombe dans le quart central du sous-tableau (entre rang 25% et rang 75%), la partition est "
bonne" : les deux moitiés ont chacune ≤ 3/4 de la taille. La probabilité d'un tel pivot est 1/2.

**Calcul de l'espérance totale :**

Le nombre espéré d'appels pour diviser la taille par 4/3 est 2. Donc :
$$E[\text{coût total}] = \sum_j E[X_j] \leq \sum_j 2 \cdot \left(\frac{3}{4}\right)^j \cdot n = 2n \cdot \sum_{j=0}^\infty \left(\frac{3}{4}\right)^j = 2n \cdot \frac{1}{1-3/4} = 8n$$

**Résultat : coût espéré $O(n)$.** C'est optimal car il faut au moins n comparaisons pour trouver la médiane.

---

##### 🔷 Algorithme optimal de la médiane (Floyd-Rivest probabiliste)

Pour trouver la **médiane exacte** d'un ensemble de 2n-1 éléments, on peut faire encore mieux :

**Algorithme :**

1. Choisir aléatoirement Y ⊆ X de taille 2n^{2/3}
2. Trier Y en O(n^{2/3} log n) comparaisons
3. Prendre a = Y_{n^{2/3} - n^{1/3} log n} et b = Y_{n^{2/3} + n^{1/3} log n} (un intervalle autour de la position
   médiane de Y)
4. Calculer Z = X ∩ [a,b] en balayant X, compter nₐ = #{éléments < a}
5. **Avec haute probabilité** (Chernoff) : la vraie médiane xₙ ∈ Z et |Z| < 2n^{2/3} log n
6. Trier Z et retourner xₙ = z_{n-nₐ}

**Intuition de l'étape 5 :** L'échantillon Y de taille n^{2/3} est assez grand pour que ses statistiques d'ordre
reflètent fidèlement celles de X. Par Chernoff, la médiane de X tombe dans l'intervalle [a,b] de Y avec grande
probabilité, et cet intervalle est petit (O(n^{2/3} log n)).

**Coût :**

- Tri de Y : O(n^{2/3} log n) = o(n)
- Balayage pour Z : $O(n)$
- Tri de Z : O(n^{2/3} log n · log(n^{2/3} log n)) = o(n)
- **Total : 3n/2 + o(n) comparaisons** — approchant la borne inférieure de n-1 comparaisons !

---

##### 🔷 Quicksort probabiliste — Analyse fine avec Chernoff

On analyse QuickSort randomisé : pivot choisi uniformément à chaque étape.

**Objectif :** Borner la probabilité qu'un élément e soit mal placé après t partitions.

**Définition :** Une partition est **réussie** si le sous-tableau contenant e est réduit au moins à 3/4 de sa taille :
$$\Pr\left(n_{j+1} \leq \frac{3n_j}{4}\right) \geq \frac{1}{2}$$

Après $\log_{4/3} n$ partitions réussies, e est correctement placé (le sous-tableau ne contient plus qu'un seul
élément).

**Application de Chernoff :**

Soit Xₜ = nombre de partitions réussies parmi t. On a p = 1/2, E[Xₜ] = pt = t/2.

On veut majorer Pr(Xₜ ≤ log_{4/3} n) = Pr(Xₜ ≤ (1-ε)·pt) avec (1-ε)pt = log_{4/3} n → ε = 1 - (2/t)log_{4/3} n.

Pour t > 2 log_{4/3} n : ε ∈ ]0,1[ et on peut appliquer Chernoff :
$$\Pr_\text{échec}^{(e)}(t) = \Pr(X_t \leq \log_{4/3} n) < \exp\left(-\frac{\epsilon^2 t}{4}\right)$$

En prenant t = 5 log_{4/3} n :
$$\text{Prob}_\text{échec}^{(e)}(5\log_{4/3} n) < n^{-9/5 \times 0.86} \approx n^{-1.54}$$

**Par union bound sur tous les n éléments :**
$$\text{Prob}_\text{échec} \leq n \cdot n^{-1.54} = n^{-0.54} < \frac{1}{\sqrt{n}}$$

> **Résultat final :** Avec t = 5 log_{4/3} n partitions par élément, QuickSort trie correctement **w.h.p.** (
> probabilité d'erreur < 1/√n).

**En termes de nombre de comparaisons :** Le coût total est O(n log n) w.h.p. (voir Sedgewick pour l'analyse complète).

---

##### 🔷 Work-Stealing — Ordonnancement distribué probabiliste

**Contexte :** n processeurs P₁,...,Pₙ doivent exécuter un programme multithread. Les tâches se créent dynamiquement (
via fork/join). Comment répartir le travail efficacement sans communication globale ?

**Modélisation :**

L'exécution est modélisée par un **arbre d'activation** :

- Chaque **nœud** est une instruction.
- Une instruction a 0 successeur (fin de tâche), 1 successeur (continuation), ou 2 successeurs (activation/fork d'une
  nouvelle tâche).
- Les **tâches** sont des chaînes d'instructions liées par continuations.

**Deux mesures de complexité :**

- **Travail T₁ :** nombre total d'instructions (coût séquentiel optimal).
- **Profondeur T∞ :** longueur du chemin critique (borne inférieure sur le temps en parallèle).

**Algorithme Work-Stealing :**

Chaque processeur gère une **deque** (double-ended queue) de tâches prêtes.

```text
Exécution locale (LIFO) :
    Prendre et exécuter la tâche en bas de sa propre deque
    Si fork : empiler la nouvelle tâche en bas

Si inactif (deque locale vide) :
    Choisir une victime au hasard parmi les P processeurs
    Si deque de la victime vide : vol échoué (réessayer)
    Sinon : vol réussi → prendre la tâche en HAUT (FIFO) de la victime
```

**Intuition de LIFO local / FIFO vol :**

- **LIFO local :** Le processeur exécute la tâche la plus récente (DFS), ce qui minimise la taille des deques (localité
  de cache).
- **FIFO vol :** On vole la tâche la plus ancienne (racine de l'arbre de la victime). C'est la tâche la plus "grosse" —
  elle a le plus de descendants restants → maximise le travail transféré par vol.

**Propriété clé :** Le vol est **aléatoire** (victime choisie au hasard) → l'analyse est probabiliste.

**Théorème [Blumofe-Leiserson, 1999] :** Avec P processeurs, le temps d'exécution espéré est :
$$E[\text{temps}] = O\left(\frac{T_1}{P} + T_\infty \cdot \log P\right)$$

avec probabilité d'erreur exponentiellement petite.

**Simulation illustrée :**

1. Initialement : P1 a les tâches V₁ (en bas, exécution) + une file grandissante V₂,V₃,...
2. P2, P3, P4 sont vides → ils volent chez P1 (en FIFO : prennent V₁ la plus ancienne).
3. Les tâches volées génèrent de nouvelles tâches → les autres processeurs deviennent actifs.
4. La charge se répartit progressivement de manière équilibrée.

**Avantages du work-stealing :**

- Pas de scheduler centralisé → pas de bottleneck.
- Charge équilibrée automatiquement.
- Implémenté dans Java ForkJoin, Intel TBB, Cilk (MIT/Intel).

---

#### Résumé concis du cours

Ce cours présente les **outils d'analyse probabiliste** et leurs applications algorithmiques. Les outils progressent de
Markov (borne simple sur l'espérance) à Chernoff (décroissance exponentielle). Les applications majeures sont :
MAX-SAT (7/8 en espérance), marches aléatoires (2-SAT en O(n²) espérance, PageRank), médiane en $O(n)$ espérance et
3n/2 + o(n) optimal, QuickSort correct w.h.p., et work-stealing en O(T₁/P + T∞ log P).

---

#### Formules et algorithmes clés

| Outil                   | Formule                        |
|-------------------------|--------------------------------|
| Markov                  | Pr[X ≥ λ] ≤ E[X]/λ             |
| Tchebychev              | Pr[                            |X-μ| ≥ λ] ≤ σ²/λ² |
| Chernoff inf            | Pr{X ≤ (1-ε)pn} ≤ exp(-ε²np/2) |
| Chernoff sup            | Pr{X ≥ (1+ε)pn} ≤ exp(-ε²np/3) |
| Poisson approx          | (1-a/n)ⁿ ≈ e^{-a}              |
| Distrib stationnaire    | Πᵢ = deg(i)/(2m)               |
| Temps de couverture     | Cᵢ < 4nm                       |
| Temps d'atteinte voisin | hⱼ,ᵢ < 2m                      |
| 2-SAT temps moyen       | h₀ = n² depuis état 0          |
| RandomMedian coût       | E[comparaisons] = 8n           |
| Médiane optimale        | 3n/2 + o(n) comparaisons       |
| Work-Stealing           | E[temps] = O(T₁/P + T∞ log P)  |

---

#### Les 8 concepts les plus importants à retenir

1. **Hiérarchie w.h.p. / w.o.p. / a.a.s.** : vocabulaire indispensable pour qualifier la fiabilité des algorithmes
   probabilistes.
2. **Bornes de Chernoff** : l'outil central — décroissance exponentielle pour les déviations de sommes de Bernoulli
   indépendantes. À connaître dans les deux sens (surestimation et sous-estimation).
3. **Markov → Las Vegas** : arrêter un algo à 2·E[temps] donne Pr(ÉCHEC) ≤ 1/2.
4. **Distribution stationnaire de la marche aléatoire** : Πᵢ = deg(i)/(2m), temps de couverture < 4nm.
5. **MAX-3-SAT probabiliste** : ratio 7/8 par affectation aléatoire — corollaire existentiel fort.
6. **2-SAT par marche aléatoire** : chaîne de Markov sur la chaîne, E[temps] = n², répéter → proba erreur → 0.
7. **RandomMedian / QuickSort** : partition réussie avec probabilité 1/2, analyse par Chernoff → coût $O(n)$ espéré pour
   la médiane, O(n log n) w.h.p. pour le tri.
8. **Work-Stealing LIFO/FIFO** : vol aléatoire de la tâche la plus ancienne → équilibrage dynamique de charge avec
   E[temps] = O(T₁/P + T∞ log P).

---

#### Questions conceptuelles pour tester ta compréhension

**Q1.** Dans l'analyse de Chernoff pour les éléments indépendants dans un cycle, pourquoi se restreint-on aux éléments
d'indices pairs plutôt que de traiter tous les éléments directement ?

**Q2.** La marche aléatoire sur un graphe bipartite (par exemple un graphe complet K_{n,n}) converge-t-elle vers une
distribution stationnaire ? Pourquoi ? Comment y remédier ?

**Q3.** Dans l'algorithme 2-SAT, on a établi que le temps moyen de parcours depuis l'état 0 est n². Pourquoi l'inégalité
de Markov donne-t-elle Pr(X₀ > 2n²) ≤ 1/2 et non Pr(X₀ ≤ 2n²) ≤ 1/2 ? Est-ce que cela prouve bien ce que l'on veut ?

**Q4.** Dans l'algorithme optimal de la médiane, on tire un échantillon Y de taille 2n^{2/3}. Intuitivement, pourquoi
choisir cette taille et non n/2 ou √n ?

**Q5.** Dans le work-stealing, pourquoi est-il crucial de voler en FIFO (la tâche la plus ancienne) plutôt qu'en LIFO (
la plus récente) ? Que se passerait-il si on volait la tâche la plus récente ?

### Partie Pratique (TD)

_Aucun bloc TD distinct n'est séparé dans la source pour cette séance ; les exercices et questions présents dans les
notes ci-dessus ont été conservés dans leur emplacement source._

---

<a id="seance-9"></a>

## Séance 9 — Dérandomisation et complexité interactive

> Plage source conservée : lignes `3632` à `4724` de `course.txt`.

### Partie Théorique

C'est la dernière ligne droite ! Cette séance (que nous appellerons Séance 8 ou 9 selon le découpage) pose l'une des
questions les plus profondes de l'informatique théorique : **L'aléatoire est-il vraiment utile, ou n'est-ce qu'une
illusion pour nous simplifier la vie ?**

L'objectif de ce cours est de découvrir la **Dérandomisation** (comment transformer un algorithme probabiliste en
algorithme déterministe) et d'explorer les limites de la complexité avec les **Preuves Interactives (IP)** et le
théorème **PCP**.

Voici votre cours détaillé et structuré.

---

### Séance 8 : L'aléatoire est-il utile ? Dérandomisation et Complexité Interactive

**Objectif de la séance :** Comprendre les différentes méthodes pour éliminer l'aléatoire d'un algorithme (
dérandomisation) afin d'obtenir des garanties déterministes, et explorer comment l'aléatoire révolutionne la notion même
de "preuve" mathématique.

#### 1. Le bestiaire des classes probabilistes (Rappels)

Avant de dérandomiser, il faut situer nos algorithmes dans la hiérarchie de la complexité:

* **P** : Résoluble en temps polynomial déterministe.
* **ZPP (Zero-Error / Las Vegas)** : Temps polynomial en moyenne, aucune erreur.
* **RP (Random Polynomial / Monte Carlo)** : S'il dit OUI, c'est vrai. S'il dit NON, il peut se tromper (erreur
  unilatérale).
* **BPP (Bounded-error)** : Erreur bilatérale (Atlantic City), mais probabilité de succès $> 2/3$.
* **NP** : Vérifiable en temps polynomial déterministe.

**La hiérarchie :** $P \subseteq ZPP = RP \cap co\text{-}RP \subseteq RP \subseteq NP$.
*La grande question ouverte de l'informatique théorique est de savoir si $P = BPP$. La dérandomisation tente de prouver
que oui.*

---

#### 2. La Dérandomisation Non-Uniforme (Théorème d'Adleman)

Peut-on transformer un circuit probabiliste en un circuit totalement déterministe ? Oui, mais de manière "
non-uniforme" (c'est-à-dire qu'on crée un circuit spécifique pour chaque taille de problème $n$).

**Le Théorème d'Adleman :**
Si un problème est résolu par un circuit probabiliste de taille polynomiale, il existe un circuit **déterministe** de
taille polynomiale qui le résout.

* **L'idée de la preuve (La Matrice des probabilités) :**
  Imaginons une matrice où les lignes sont les instances d'entrées $x$ et les colonnes sont les chaînes de bits
  aléatoires $r$.
  Puisque l'algorithme probabiliste a une forte probabilité de succès (ex: $> 1/2$), la matrice contient une majorité
  de "bonnes réponses" (des 1).
  Mathématiquement, on peut prouver qu'il suffit de sélectionner un très petit nombre de colonnes (des chaînes
  aléatoires "fixes" $r_1, r_2, \dots, r_n$) de sorte que pour *n'importe quelle* entrée $x$, au moins l'une de ces
  chaînes fixes donne la bonne réponse.
* **Conséquence :** On construit un circuit déterministe qui fait un simple "OU" logique sur les résultats donnés par
  ces quelques chaînes fixes.

---

#### 3. La Dérandomisation Uniforme (Générateurs Pseudo-Aléatoires)

La méthode d'Adleman est théorique. En pratique, on utilise des **Générateurs Pseudo-Aléatoires (PRG)**.

* **Le principe :** Un algorithme probabiliste a besoin de $r(n)$ bits aléatoires (ce qui est trop long à simuler de
  manière exhaustive). On va utiliser une "graine" (seed) beaucoup plus petite $l(n)$ que l'on passe dans une fonction
  déterministe $f$ pour générer $r(n)$ bits "pseudo-aléatoires".
* **Indistingabilité :** Si aucun circuit polynomial ne peut faire la différence entre les vrais bits aléatoires et ceux
  générés par $f$, le générateur est parfait.
* **La puissance de la graine logarithmique :** Si la graine ne fait que $l(n) = \mathcal{O}(\log n)$ bits, on peut
  tester **toutes** les graines possibles en temps déterministe ! En
  effet, $2^{\mathcal{O}(\log n)} = n^{\mathcal{O}(1)}$ (temps polynomial).
* **Le Graal :** S'il existe un PRG suffisamment puissant, alors on a la preuve que **$BPP = P$** (tout algorithme
  probabiliste peut être rendu déterministe).

---

#### 4. Dérandomisation par Maximisation d'Espérance (La Pratique)

C'est la méthode la plus concrète de votre cours. Elle permet de transformer un algorithme glouton probabiliste en un
algorithme glouton déterministe.

##### L'exemple de MAX-CUT

* **Problème :** Séparer les sommets d'un graphe en deux ensembles $V_1$ et $V_2$ pour maximiser le nombre d'arêtes
  coupées (qui relient $V_1$ à $V_2$).
* **L'algo probabiliste naïf :** Pour chaque sommet, on tire à pile ou face. S'il fait "pile", on le met dans $V_1$,
  sinon dans $V_2$.
* **Espérance :** Chaque arête a 1 chance sur 2 d'être coupée (ses extrémités finissent dans des groupes différents).
  L'espérance de la coupe est donc $m/2$ (la moitié des arêtes totales).

**Comment dérandomiser cela (La méthode des espérances conditionnelles) ?**
Au lieu de tirer au sort pour le sommet $v_{i+1}$, on va calculer "l'avenir" :

1. Si je mets $v_{i+1}$ dans $V_1$, quelle est l'espérance mathématique de ma coupe finale ($E_1$) ?
2. Si je mets $v_{i+1}$ dans $V_2$, quelle est l'espérance de ma coupe finale ($E_2$) ?
3. **L'algorithme déterministe :** Je calcule $E_1$ et $E_2$. Si $E_1 > E_2$, je place *définitivement* $v_{i+1}$
   dans $V_1$. Sinon, je le place dans $V_2$.

**Le calcul magique :**
Si l'on pose :

* $m_1$ = arêtes reliant $v_{i+1}$ aux sommets *déjà placés* dans $V_1$.
* $m_2$ = arêtes reliant $v_{i+1}$ aux sommets *déjà placés* dans $V_2$.

Le théorème montre que la condition ($E_1 > E_2$) se résume simplement à vérifier si **$m_2 > m_1$**.
Nous avons donc transformé une loterie en un algorithme glouton déterministe brillant qui garantit une coupe d'au
moins $m/2$ (ratio d'approximation de 2).

---

#### 5. Preuves Interactives (IP) et Théorème PCP

L'aléatoire ne sert pas qu'à calculer plus vite, il redéfinit ce qu'est une "preuve".

* **Le concept IP (Interactive Proofs) :**
  Imaginons un **Prouveur** (avec une puissance de calcul infinie) qui veut convaincre un **Vérifieur** (qui n'a qu'un
  temps polynomial probabiliste) qu'une affirmation est vraie. Le Vérifieur peut poser des "questions pièges" aléatoires
  au Prouveur.
  *Théorème choc :* La classe des problèmes vérifiables ainsi est **IP = PSPACE** (des problèmes bien plus durs que NP,
  comme les jeux d'échecs ou le Non-Isomorphisme de Graphes).

* **Le Théorème PCP (Probabilistically Checkable Proofs) :**
  C'est l'un des théorèmes les plus importants de l'informatique moderne.
  Il définit $PCP[r(n), q(n)]$, la classe des langages vérifiables avec $r(n)$ bits aléatoires et en ne lisant
  que $q(n)$ bits de la preuve.
  **Le théorème : $NP = PCP[\mathcal{O}(\log n), \mathcal{O}(1)]$**.
  *Ce que ça signifie en clair :* N'importe quelle démonstration mathématique (NP) peut être réécrite sous une forme si
  robuste qu'un vérifieur n'a besoin de lire qu'un **nombre constant de bits** (ex: 3 bits tirés au hasard
  avec $\mathcal{O}(\log n)$ aléas) pour être convaincu à 99% que la preuve entière est correcte !

### Cours : Algorithmes Probabilistes (3/3) — *L'aléatoire est-il utile ?*

---

#### 🗺️ Vue d'ensemble du cours

Ce cours est la **troisième et dernière partie** d'une série sur les algorithmes probabilistes. Il répond à une question
fondamentale en théorie de la complexité : **peut-on toujours remplacer l'aléatoire par du déterminisme ?** Et si
l'aléatoire ne sert pas à calculer plus vite, sert-il au moins à *prouver* plus efficacement ?

Les deux grands thèmes sont :

**1. La dérandomisation** — Comment transformer un algorithme probabiliste en algorithme déterministe, et à quel coût ?

**2. Les preuves interactives probabilistes (classe IP)** — L'aléatoire permet-il de vérifier des choses impossibles à
vérifier classiquement ?

**Objectifs :**

- Maîtriser les classes de complexité probabiliste (BPP, RP, ZPP)
- Comprendre trois techniques de dérandomisation
- Appréhender la puissance surprenante de IP = PSPACE

---

#### 📐 Partie 1 — Dérandomisation

##### 1.1 Qu'est-ce que la dérandomisation ?

La **dérandomisation** consiste à éliminer les bits aléatoires d'un algorithme pour obtenir un algorithme **entièrement
déterministe**, qui donne toujours la même réponse pour la même entrée — sans aucun hasard.

Intuitivement : si un algorithme probabiliste fonctionne *en moyenne*, peut-on trouver un choix *fixe* des bits
aléatoires qui fonctionne *toujours* ?

---

##### 1.2 Les classes de complexité probabiliste

Avant de dérandomiser, il faut savoir *quoi* dérandomiser. Le cours présente trois classes :

###### 🔷 RP (Random Polynomial time — Monte Carlo)

Un langage $L \in \mathbf{RP}$ s'il existe un algorithme déterministe $A$ en temps polynomial et un polynôme $\rho$ tels
que :

$$x \in L \Rightarrow \Pr_{r \in \{0,1\}^{\rho(n)}}[A(x,r) \text{ accepte}] \geq \frac{1}{2}$$
$$x \notin L \Rightarrow \Pr_{r \in \{0,1\}^{\rho(n)}}[A(x,r) \text{ accepte}] = 0$$

**Interprétation :** Si $x \notin L$, l'algorithme ne se trompe jamais (pas de faux positifs). Si $x \in L$, il accepte
avec probabilité $\geq 1/2$ (il peut rater, mais jamais accuser à tort un non-membre). C'est le profil des algorithmes *
*Monte Carlo à erreur unilatérale**.

> **Exemple simple :** Tester si un nombre est premier. Si la réponse est "composite", c'est sûr. Si la réponse est "
> premier", c'est probablement vrai.

###### 🔷 co-RP

C'est le **complément** de RP : les faux négatifs sont impossibles, mais pas les faux positifs. Un algorithme co-RP
dit "non" avec certitude quand $x \notin L$.

###### 🔷 ZPP (Zero error Probabilistic Polynomial — Las Vegas)

$$\mathbf{ZPP} = \mathbf{RP} \cap \mathbf{co\text{-}RP}$$

Un algorithme ZPP **ne se trompe jamais**, mais peut ne pas terminer (ou signaler "je ne sais pas") avec une certaine
probabilité. En pratique, son temps d'exécution moyen est polynomial.

> **Exemple :** QuickSort avec pivot aléatoire : toujours correct, temps moyen $O(n \log n)$.

###### 🔷 BPP (Bounded error Probabilistic Polynomial)

$$x \in L \Rightarrow \Pr[A(x,r) \text{ accepte}] \geq \frac{2}{3}$$
$$x \notin L \Rightarrow \Pr[A(x,r) \text{ accepte}] \leq \frac{1}{3}$$

L'algorithme peut se tromper dans **les deux sens**, mais avec probabilité bornée. C'est la classe la plus large et la
plus "naturelle" des algorithmes probabilistes polynomiaux.

###### 🔷 La hiérarchie

$$\mathbf{P} \subset \mathbf{ZPP} = \mathbf{RP} \cap \mathbf{co\text{-}RP} \subset \mathbf{RP} \subset \mathbf{BPP}$$

**Idée clé à retenir :** On conjecture (sans preuve) que $\mathbf{BPP} = \mathbf{P}$, c'est-à-dire que l'aléatoire
n'apporte pas de puissance supplémentaire pour les décisions polynomiales.

---

##### 1.3 Deux idées philosophiques fondamentales

Le cours pose deux observations qui reviennent constamment :

> **Idée 1 :** Au moins une valeur d'une variable aléatoire est supérieure ou égale à sa moyenne.

C'est trivial mathématiquement ($\exists \omega : X(\omega) \geq \mathbb{E}[X]$), mais c'est le cœur du **raisonnement
probabiliste constructif** : si l'espérance d'une quantité est grande, il *existe* un résultat qui atteint cette valeur.

> **Idée 2 :** Si un objet choisi aléatoirement satisfait une propriété avec probabilité non nulle, alors il *existe* au
> moins un objet satisfaisant cette propriété.

Ces deux idées permettent de passer de "il existe en moyenne" à "il existe concrètement" — c'est-à-dire de **prouver
l'existence d'algorithmes déterministes performants**.

---

##### 1.4 Technique 1 — Dérandomisation brutale (et le théorème d'Adleman)

###### La dérandomisation naïve

Supposons qu'un algorithme $A$ utilise $\rho(n)$ bits aléatoires et tourne en temps $t(n)$. La dérandomisation la plus
simple : **tester toutes les séquences possibles** de bits aléatoires.

Il y a $2^{\rho(n)}$ séquences → temps total = $2^{\rho(n)} \cdot t(n)$. C'est **exponentiel**, donc inutilisable en
pratique, mais prouve que le problème est décidable déterministement.

###### Le théorème d'Adleman (dérandomisation non-uniforme)

> **Théorème :** Tout langage calculable par une famille de circuits **probabilistes** de taille polynomiale peut être
> calculé par une famille de circuits **déterministes** de taille polynomiale.

**Attention au mot "non-uniforme"** : une famille de circuits peut avoir un circuit différent pour chaque taille
d'entrée $n$. Cela n'implique *pas* qu'il existe un seul algorithme polynomial déterministe (uniforme) qui marche pour
tout $n$. Ce théorème **ne prouve pas** que $\mathbf{RP} = \mathbf{P}$.

###### Preuve du théorème d'Adleman (reconstructed)

C'est la partie la plus technique du cours — voici le raisonnement complet :

Soit $C_n(x, r)$ un circuit probabiliste de taille $t(n) = n^{$O(1)$}$, prenant en entrée $x \in \{0,1\}^n$ et $m$ bits
aléatoires $r$.

On sait que :

- Si $x \notin L$ : $\forall r$, $C_n(x,r) = 0$ (pas de fausse acceptation)
- Si $x \in L$ : $\Pr_r[C_n(x,r) = 1] \geq \frac{1}{2}$

**Construction d'une matrice :** Soit $M$ la matrice $|L| \times 2^m$ définie par $M(x, r) = C_n(x, r)$.

- Chaque ligne = un élément $x \in L$
- Chaque colonne = un aléa $r$ de $m$ bits

Puisque chaque $x \in L$ est accepté par au moins la moitié des colonnes, chaque ligne a au moins $2^m/2$ coefficients
égaux à 1.

**Calcul d'espérance :**
$$\mathbb{E}\left[\sum_{r} \sum_{x \in L} M(x,r)\right] \geq 2^{m-1} \cdot |L|$$

La **moyenne** des sommes de colonnes est $\geq |L|/2$.

Donc il existe **au moins une colonne** $r_1$ dont la somme est $\geq |L|/2$, c'est-à-dire que le circuit
déterministe $C_n^{DET}(\cdot) = C_n(\cdot, r_1)$ **accepte correctement au moins la moitié des $x \in L$**.

On supprime ces lignes → il reste $\leq |L|/2 \leq 2^{n-1}$ lignes.

**On réitère** pour trouver $r_2, r_3, \ldots, r_n$, en éliminant à chaque étape au moins la moitié des cas restants.

**Résultat final :** Le circuit $\text{OR}(C_n^{DET}(\cdot, r_1), \ldots, C_n^{DET}(\cdot, r_n))$ calcule $L$ en temps
déterministe $n \cdot t(n) = n^{$O(1)$}$.

> **Intuition :** On "hard-code" les bons bits aléatoires dans le circuit, un ensemble différent pour chaque taille
> d'entrée. C'est non-uniforme car ces bits dépendent de $n$.

---

##### 1.5 Technique 2 — Dérandomisation de Schwartz-Zippel (ZEROP)

###### Le problème ZEROP

**Entrée :** Un polynôme $P \in \mathbb{F}[X_1, \ldots, X_n]$ de degré $d$, représenté par un **circuit arithmétique**.

**Question :** Est-ce que $P \equiv 0$ (le polynôme nul) ?

Si $P$ est donné par ses monômes, c'est trivial. Mais si $P$ est donné par un circuit (une série d'additions et
multiplications), le nombre de monômes peut être exponentiel et on ne peut pas les énumérer.

**ZEROP ∈ co-RP** : on peut tester probabilistement si $P \neq 0$.

###### Le lemme de Schwartz-Zippel

> Si $P \not\equiv 0$, de degré $d$, et $r$ est choisi uniformément dans $I^n$ avec $I \subset \mathbb{F}$ :
> $$\Pr[P(r) = 0] \leq \frac{d}{|I|}$$

**Algorithme probabiliste :** Choisir $r$ aléatoirement, évaluer $P(r)$. Si $P(r) \neq 0$, on est certain
que $P \not\equiv 0$. Si $P(r) = 0$, on conclut $P \equiv 0$ avec une faible probabilité d'erreur.

###### Dérandomisation de Schwartz-Zippel

Si le circuit de taille $m$ évalue $P$, alors **il existe $m^2$ vecteurs** $r_1, \ldots, r_{m^2}$ tels que :
$$\text{si } P \neq 0 \Rightarrow \exists i : P(r_i) \neq 0$$

En construisant explicitement ces vecteurs, on obtient un algorithme **déterministe** pour ZEROP.

**Mais le problème ouvert :** On ne sait pas construire ces vecteurs efficacement dans le cas général ! (Le faire en
temps polynomial impliquerait des bornes inférieures non triviales de la
forme $\mathbf{NEXP} \not\subset \mathbf{P/Poly}$, ce qui est un résultat majeur non prouvé.)

> **Leçon :** La dérandomisation *existe* théoriquement, mais n'est pas toujours efficacement constructible.

---

##### 1.6 Technique 3 — Dérandomisation par générateur pseudo-aléatoire

###### L'idée centrale

Au lieu d'utiliser $r(n)$ bits vraiment aléatoires, on utilise une **semence (seed)** courte de $l(n)$ bits et une
fonction $f : \{0,1\}^{l(n)} \to \{0,1\}^{r(n)}$ qui **étire** la semence en une séquence pseudo-aléatoire :

$$\forall x : \Pr_{r \in \Sigma^{r(n)}}[A(x,r) \text{ accepte}] \approx_{\pm n^{-2}} \Pr_{s \in \Sigma^{l(n)}}[A(x, f(s)) \text{ accepte}]$$

**Traduction :** Le comportement de l'algorithme sur les pseudo-aléas $f(s)$ est quasi-identique à son comportement sur
les vrais aléas $r$.

###### Dérandomisation brutale avec seed courte

Avec cette substitution, on peut faire une dérandomisation brutale sur toutes les semences possibles :

- Il y a $2^{l(n)}$ semences
- Temps total : $O(2^{l(n)} \cdot t(n) \cdot t_f(n))$ où $t_f(n)$ est le temps de calcul de $f$

**Si $l(n) = O(\log n)$**, alors $2^{l(n)} = n^{$O(1)$}$ → la dérandomisation est **polynomiale** !

Le défi est de construire un tel $f$ efficace.

###### Définition formelle : pseudo-aléatoire

Une distribution $R$ sur $\{0,1\}^m$ est $(S, \epsilon)$-**pseudo-aléatoire** si aucun circuit de taille $S$ ne peut la
distinguer de la loi uniforme $U_m$ :

$$\forall C \text{ de taille } S : |\Pr[C(R) = 1] - \Pr[C(U_m) = 1]| < \epsilon$$

###### Le théorème clé

> **Théorème :** S'il existe $\epsilon > 0$ et un générateur $2^{l \times \epsilon}$-pseudo-aléatoire,
> alors $\mathbf{BPP} = \mathbf{P}$.

Ce résultat conditionnel est majeur : **l'existence d'un bon générateur pseudo-aléatoire suffit à prouver que
l'aléatoire est inutile** pour la décision polynomiale.

---

##### 1.7 Technique 4 — Dérandomisation par maximisation d'espérance (méthode conditionnelle)

###### Principe général

Pour un problème d'optimisation (maximiser $f$), un algorithme probabiliste glouton fait des choix aléatoires
successifs $r_1, \ldots, r_n$ pour produire une solution $\tilde{f}(r_1, \ldots, r_n)$.

**La méthode de la valeur espérée conditionnelle :** À chaque étape $i$, au lieu de choisir $r_i$ au hasard, on choisit
la valeur déterministe $a_i$ qui **maximise l'espérance conditionnelle** :

$$a_i = \arg\max_x \; \mathbb{E}_{r_{i+1},\ldots,r_n}\left[\tilde{f}(a_1, \ldots, a_{i-1}, x, r_{i+1}, \ldots, r_n)\right]$$

**Pourquoi ça marche ?** L'espérance est une moyenne. Si on choisit le meilleur des deux côtés à chaque étape,
l'espérance conditionnelle ne peut que croître ou rester stable. Donc la valeur finale est au moins aussi bonne que
l'espérance initiale.

---

##### 1.8 Application : MAX-CUT

###### Le problème

**Entrée :** Un graphe $G = (V, E)$ avec $n = |V|$ sommets et $m = |E|$ arêtes.

**Sortie :** Une partition $(V_1, V_2)$ de $V$ qui **maximise** le nombre d'arêtes "coupées" (une extrémité dans $V_1$,
l'autre dans $V_2$).

C'est un problème **NP-complet** (décision).

###### Algorithme probabiliste Monte Carlo

```text
V₁ = ∅ ; V₂ = ∅
for i = 1, ..., n:
    b = rand(1, 2)      // pile ou face
    Mettre vᵢ dans Vb
```

**Analyse :** Pour chaque arête $e = (u,v)$, la probabilité qu'elle soit coupée est $1/2$ (les deux extrémités sont
placées indépendamment). Par **linéarité de l'espérance** :

$$\mathbb{E}[\text{taille de la coupe}] = \sum_{e \in E} \mathbb{E}[\mathbf{1}_{e \in \text{coupe}}] = \sum_{e \in E} \frac{1}{2} = \frac{m}{2}$$

Donc en espérance, on coupe au moins la moitié des arêtes. C'est une **approximation de ratio 2** (le double de
l'optimal ne peut pas être mieux que $m$).

###### Dérandomisation par la méthode conditionnelle

**Idée :** Placer les sommets $v_1, \ldots, v_n$ un par un, en choisissant chaque fois la partition qui maximise
l'espérance conditionnelle.

Supposons que $v_1, \ldots, v_i$ sont déjà placés. À l'étape $i+1$, on calcule :

Soit à cet instant :

- $c$ = taille actuelle de la coupe
- $d$ = nombre d'arêtes internes (dans $V_1$ ou $V_2$)
- $m_1$ = arêtes entre $v_{i+1}$ et $V_1$
- $m_2$ = arêtes entre $v_{i+1}$ et $V_2$
- $r = m - c - d - m_1 - m_2$ = arêtes encore indéterminées

**Si on met $v_{i+1}$ dans $V_1$ :**
$$E_1 = c + m_2 + \frac{r}{2}$$
(les $m_2$ arêtes vers $V_2$ deviennent coupées, les $r$ arêtes futures contribuent $r/2$ en espérance)

**Si on met $v_{i+1}$ dans $V_2$ :**
$$E_2 = c + m_1 + \frac{r}{2}$$

**Décision :** Mettre $v_{i+1}$ dans $V_1$ si $m_2 > m_1$, sinon dans $V_2$.

C'est-à-dire : **placer chaque sommet du côté où il a le plus de voisins déjà placés de l'autre côté** — un algorithme
glouton simple !

**Garantie :** Par construction, l'espérance conditionnelle ne peut que croître :
$$\frac{m}{2} = \mathbb{E}[\text{coupe}] \leq \mathbb{E}[\text{coupe} | v_1 \text{ placé}] \leq \ldots \leq \text{résultat final}$$

→ L'algorithme déterministe garantit une coupe de taille $\geq m/2$.

---

#### 🔬 Partie 2 — Preuves probabilistes interactives : IP = PSPACE

##### 2.1 Motivation : le problème GNI

**GI (Graph Isomorphism) ∈ NP** : deux graphes $G_0, G_1$ sont isomorphes si on peut relabeller les sommets de l'un pour
obtenir l'autre. Si c'est le cas, la permutation est un certificat vérifiable en temps polynomial.

**GNI (Graph Non-Isomorphism) ∈ co-NP** : comment *prouver* que deux graphes ne sont *pas* isomorphes ? Il n'existe pas
de certificat court évident pour le NON.

C'est ici que les **preuves interactives probabilistes** deviennent indispensables.

---

##### 2.2 La classe IP (Interactive Proof)

Un **système de preuve interactive** met en jeu deux acteurs :

- **V** = vérifieur probabiliste en temps polynomial (le "juge")
- **P** = prouveur dynamique tout-puissant (le "witness")

Ils échangent des messages, puis V accepte ou rejette.

Un langage $L \in \mathbf{IP}$ si :

$$x \in L \Rightarrow \exists \text{prouveur honnête } P, \Pr[V(x,P) \text{ accepte}] = 1$$
$$x \notin L \Rightarrow \forall \text{prouveur } P', \Pr[V(x,P') \text{ accepte}] \leq \frac{1}{2}$$

**Complétude :** Un prouveur honnête convainct toujours le vérifieur.

**Solidité :** Aucun prouveur malhonnête ne peut tromper le vérifieur avec probabilité > 1/2.

###### Preuve interactive pour GNI

> Comment prouver que $G_0 \not\cong G_1$ ?

**Protocole :**

1. Le vérifieur V choisit $b \in \{0,1\}$ aléatoirement et une permutation $\pi$ aléatoire
2. V envoie $H = \pi(G_b)$ au prouveur
3. Le prouveur répond $b'$ (lequel des deux graphes est l'origine de $H$)
4. V accepte si $b' = b$

**Si $G_0 \not\cong G_1$ :** Le prouveur peut déterminer $b$ avec certitude (car $H$ ressemble à $G_b$ et pas
à $G_{1-b}$) → accepte toujours.

**Si $G_0 \cong G_1$ :** La distribution de $H$ est la même quel que soit $b$ → le prouveur ne peut pas faire mieux que
deviner → probabilité d'acceptation $= 1/2$.

---

##### 2.3 Le grand théorème : IP = PSPACE

> **Théorème (Shamir, 1992) :** $\mathbf{IP} = \mathbf{PSPACE}$

C'est un résultat **profond et surprenant**. Il dit que l'aléatoire interactif permet de vérifier exactement les
problèmes résolubles avec espace polynomial — une classe beaucoup plus grande que NP (a priori).

**Exemples dans IP :** GNI, #3-SAT (compter les solutions d'une formule 3-SAT) ∈ IP.

---

##### 2.4 La classe PCP (Probabilistically Checkable Proofs)

La classe $\mathbf{PCP}[r(n), q(n)]$ contient les langages vérifiables avec :

- $O(r(n))$ bits aléatoires
- $O(q(n))$ bits consultés dans la preuve

**Résultats directs :**

- $\mathbf{P} = \mathbf{PCP}[0, 0]$ (pas d'aléa, pas de preuve)
- $\mathbf{NP} = \mathbf{PCP}[0, n^{$O(1)$}]$ (preuve complète, pas d'aléa)
- $\mathbf{co\text{-}RP} = \mathbf{PCP}[n^{$O(1)$}, 0]$ (aléa, mais on ne lit rien de la preuve)

**Le théorème PCP (résultat profond) :**

$$\mathbf{NP} = \mathbf{PCP}[O(\log n), $O(1)$]$$

Cela signifie que **tout problème NP peut être vérifié en ne consultant que $O(1)$ bits de la preuve** (avec $O(\log n)$
bits d'aléa) ! Ce théorème a des conséquences majeures pour l'inapproximabilité.

---

#### 🗺️ Conclusion — Carte des classes de complexité

Le cours se conclut par une vue d'ensemble de la hiérarchie des classes :

$$\mathbf{NC}^1 \subset \ldots \subset \mathbf{NC} \subset \mathbf{P} \subset \mathbf{ZPP} \subset \mathbf{RP} \subset \mathbf{BPP} \subset \mathbf{NP} \subset \mathbf{PSPACE} = \mathbf{IP}$$

L'aléatoire occupe une place intermédiaire : plus puissant que P (en apparence), probablement égal à P (conjecture BPP =
P), et clairement moins puissant que PSPACE au niveau interactif.

---

#### 📝 Résumé concis

| Concept             | Résumé                                                              |
|---------------------|---------------------------------------------------------------------|
| **Dérandomisation** | Transformer probabiliste → déterministe                             |
| **Adleman**         | Circuits probabilistes → circuits déterministes (non-uniforme)      |
| **Schwartz-Zippel** | Test polynôme nul, dérandomisable théoriquement                     |
| **Seed PRG**        | Seed courte $O(\log n)$ → dérandomisation polynomiale               |
| **MAX-CUT**         | Glouton déterministe = 2-approximation via espérance conditionnelle |
| **IP**              | Preuves interactives probabilistes                                  |
| **IP = PSPACE**     | L'interactivité + aléa = espace polynomial                          |
| **PCP**             | NP = PCP[$O(\log n)$, $O(1)$]                                       |

---

#### 🔑 Formules et algorithmes clés

**Classe RP :**
$$x \in L \Rightarrow \Pr_r[A(x,r) = 1] \geq \tfrac{1}{2}, \quad x \notin L \Rightarrow \Pr_r[A(x,r) = 1] = 0$$

**Schwartz-Zippel :**
$$\Pr_{r \in_R I^n}[P(r) = 0 \mid P \not\equiv 0] \leq \frac{d}{|I|}$$

**MAX-CUT (espérance) :**
$$\mathbb{E}[\text{coupe}] = \frac{m}{2}$$

**Critère glouton dérandomisé :**
$$\text{Mettre } v_{i+1} \text{ dans } V_1 \iff m_2 > m_1$$

**Générateur pseudo-aléatoire :**
$$\text{Si } l(n) = O(\log n) \Rightarrow \text{dérandomisation polynomiale}$$

---

#### ⭐ Les 8 concepts les plus importants

1. **ZPP = RP ∩ co-RP** — hiérarchie des classes probabilistes
2. **Théorème d'Adleman** — dérandomisation non-uniforme en temps polynomial (mais attention : non-uniforme ≠ uniforme)
3. **Méthode de l'espérance conditionnelle** — cœur de la dérandomisation des algorithmes d'optimisation
4. **Lemme de Schwartz-Zippel** — test probabiliste de nullité polynomiale
5. **Générateur pseudo-aléatoire** — si seed $O(\log n)$ existe → BPP = P
6. **MAX-CUT ≥ m/2** — approx de ratio 2, déterministement garantie
7. **Classe IP** — preuves interactives probabilistes
8. **IP = PSPACE** — résultat fondamental sur la puissance de l'interactivité

---

#### ❓ Questions pour tester ta compréhension

**Q1.** Pourquoi le théorème d'Adleman ne prouve-t-il pas que RP = P ? Quelle est la différence entre une famille de
circuits et un algorithme uniforme ?

**Q2.** Dans l'algorithme dérandomisé pour MAX-CUT, on place $v_{i+1}$ dans $V_1$ si $m_2 > m_1$. Donne une intuition
géométrique ou graphique de pourquoi cette règle est la bonne.

**Q3.** Dans le protocole de preuve interactive pour GNI : que se passe-t-il exactement si les deux graphes sont
isomorphes ? Pourquoi le prouveur ne peut-il pas mieux faire que répondre au hasard ?

**Q4.** Explique en tes propres mots pourquoi le résultat IP = PSPACE est surprenant. Qu'est-ce que cela dit sur la
relation entre l'aléatoire, l'interaction et l'espace de calcul ?

**Q5.** Si on disposait d'un générateur pseudo-aléatoire calculable en temps polynomial avec une semence de
longueur $O(\log n)$, qu'est-ce que cela impliquerait pour la classe BPP ? Pourquoi n'a-t-on pas encore prouvé BPP = P ?

### Partie Pratique (TD)

### TD – Algorithmes Probabilistes : Correction Complète et Pédagogique

---

#### Vue d'ensemble de la feuille

##### Thèmes abordés

- **Exercice 1 :** Algorithme de Rabin-Karp (recherche de chaîne probabiliste par hachage)
- **Exercice 2 :** Construction probabiliste d'une fonction de hachage parfaite (2 niveaux)
- **Exercice 3 :** Approximation de MAX-3-LIN, dérandamisation par espérances conditionnelles

##### Compétences clés requises

- Calcul de préfixes parallèles, récurrences linéaires
- Inégalité de Markov, espérance linéaire
- Méthode des espérances conditionnelles (derandomization)
- Lemme de Schwartz-Zippel (implicite dans Exo 1)
- Hachage universel et hachage parfait à 2 niveaux

---

<a id="seance-9-exercice-1"></a>

### Exercice 1 – Recherche probabiliste de chaîne (Rabin-Karp)

#### Reformulation du problème

On cherche les occurrences d'un motif X (longueur m) dans un texte Y (longueur n). L'idée centrale est de remplacer les
comparaisons coûteuses de chaînes par des comparaisons d'**empreintes numériques** (fingerprints) calculées modulo un
entier K aléatoire.

---

##### Question 1 – Algorithme naïf octet par octet, coût O(n·m)

**Stratégie :** Pour chaque position i dans Y, comparer les m caractères de X avec Y[i..i+m-1].

**Algorithme :**

```text
pour i de 0 à n-m :
    match = vrai
    pour j de 0 à m-1 :
        si X[j] ≠ Y[i+j] :
            match = faux; break
    si match : signaler occurrence en i
```

**Analyse :**

- Nombre de positions : n − m + 1 = $O(n)$
- Pour chaque position : au pire m comparaisons
- **Coût total en pire cas = O(n · m)**

⚠️ **Pire cas concret :** X = `aaa...ab` (m-1 fois 'a' puis 'b'), Y = `aaa...a`. À chaque position, on lit m-1 'a' avant
de découvrir l'échec → exactement n·m comparaisons.

---

##### Question 2 – Calcul de toutes les empreintes en Θ(n) et profondeur O(log n + log m)

**Définitions clés :**

- $\Phi(A_0\ldots A_k) = \sum_{j=0}^{k} A_{k-j} \cdot 256^j$ (interprétation de la chaîne comme entier en base 256)
- $N_X = \Phi(X)$, $N_X' = N_X \bmod K$
- $N_i = \Phi(Y_i \ldots Y_{i+m-1})$, $N_i' = N_i \bmod K$

**Clé de l'exercice :** établir la récurrence donnée, puis l'identifier comme un calcul de préfixes.

**Démonstration de la récurrence :**

Développons $N_{i-1}$ et $N_i$ :
$$N_{i-1} = Y_{i-1} \cdot 256^{m-1} + Y_i \cdot 256^{m-2} + \ldots + Y_{i+m-2} \cdot 256^0$$
$$N_i = Y_i \cdot 256^{m-1} + Y_{i+1} \cdot 256^{m-2} + \ldots + Y_{i+m-1} \cdot 256^0$$

On observe : $N_i = 256 \cdot N_{i-1} - 256^m \cdot Y_{i-1} + Y_{i+m-1}$

(On multiplie par 256 pour décaler, on retire le premier octet, on ajoute le nouvel octet.)

Modulo K :
$$\boxed{N_i' = \left(256 \cdot \left(N_{i-1}' - 256^{m-1} \cdot Y_{i-1}\right) + Y_{i+m-1}\right) \bmod K}$$

**Calcul de toutes les $N_i'$ :**

Cette récurrence est de la forme $N_i' = a \cdot N_{i-1}' + b_i \pmod{K}$ avec $a = 256$ constant
et $b_i = -256^m \cdot Y_{i-1} + Y_{i+m-1} \pmod{K}$.

C'est une **récurrence linéaire** du premier ordre. On peut la reformuler comme un **calcul de préfixes** : si on
pose $f_i(x) = 256 \cdot x + b_i$, alors $N_i' = f_i \circ f_{i-1} \circ \ldots \circ f_0(N_0')$. La composition de
fonctions affines est associative et peut être calculée par l'algorithme de **scan parallèle**.

**Coûts :**

- Calcul des $b_i$ : $O(n)$ travail, $O(1)$ profondeur (opérations indépendantes)
- Calcul de $256^{m-1} \bmod K$ : O(log m) profondeur (exponentiation rapide)
- Scan parallèle des récurrences linéaires : $O(n)$ travail, $O(\log n)$ profondeur
- **Total : Θ(n) travail, O(log n + log m) profondeur** ✓

---

##### Question 3 – Algorithme Monte Carlo en $O(n)$ travail

**Algorithme Rabin-Karp (Monte Carlo) :**

```text
1. Choisir K premier aléatoirement (voir Q.6 pour le choix)
2. Calculer N'_X = Φ(X) mod K  [coût O(m)]
3. Calculer N'_0 = Φ(Y_0...Y_{m-1}) mod K  [coût O(m)]
4. Calculer tous les N'_i pour i=1..n-m via la récurrence  [coût O(n)]
5. Pour chaque i : si N'_i = N'_X, signaler une occurrence potentielle en i
```

**Correction partielle (Monte Carlo) :**

- Si X apparaît réellement en position i : $N_i = N_X$ donc $N_i' = N_X'$ → **pas de faux négatif**.
- Si X n'apparaît pas en i mais $N_i' = N_X'$ (collision modulo K) → **faux positif possible**.

C'est un algorithme **Monte Carlo** : toutes les vraies occurrences sont détectées, mais certaines non-occurrences
peuvent être signalées à tort.

**Coût total : Θ(n)**, profondeur O(log n + log m).

---

##### Question 4 – Condition de correction : K ne divise pas $N_{X,Y}$

**Définition :**
$$N_{X,Y} = \prod_{\substack{0 \leq i \leq n-m \\ Y_i\ldots Y_{i+m-1} \neq X}} (N_X - N_i)$$

C'est le produit des "différences d'empreintes entières" pour toutes les positions qui ne sont **pas** des occurrences
de X.

**Lemme préliminaire :** Si $Y_i\ldots Y_{i+m-1} \neq X$ (comme chaînes), alors $N_i \neq N_X$ (comme entiers).

*Preuve :* $\Phi$ est injective sur les chaînes de même longueur car c'est l'écriture en base 256, et chaque caractère
est dans $\{0,\ldots,255\}$ → représentation unique. Donc $N_X - N_i \neq 0$.

**Démonstration :**

L'algorithme produit une fausse occurrence en position $i$ (avec $Y_i\ldots Y_{i+m-1} \neq X$) si et seulement si :
$$N_X \equiv N_i \pmod{K} \iff K \mid (N_X - N_i)$$

Si $K \nmid N_{X,Y}$, alors $K$ ne divise aucun facteur $(N_X - N_i)$ du produit (car si $K$ divisait l'un des facteurs,
il diviserait le produit). Donc **aucune fausse occurrence n'est produite**. ✓

> **Astuce clé :** On passe du produit (conjonction) à chaque facteur (disjonction) par contraposée.

---

##### Question 5 – Borne sur $N_{X,Y}$ et nombre de facteurs premiers

**Borne sur chaque facteur :**

$N_X$ et $N_i$ sont chacun au plus $\sum_{j=0}^{m-1} 255 \cdot 256^j = 256^m - 1 < 256^m$.

Donc $|N_X - N_i| < 256^m$ pour chaque facteur.

**Nombre de facteurs :** il y a au plus $n - m$ positions où X n'apparaît pas, donc au plus $n - m < n$ facteurs dans le
produit.

**Borne sur $N_{X,Y}$ :**
$$N_{X,Y} = \prod |N_X - N_i| < (256^m)^n = 256^{nm}$$

**Nombre de facteurs premiers :**

Tout entier $N$ est majoré par $2^{\log_2 N}$, et s'il a $k$ facteurs premiers (avec multiplicité), alors $N \geq 2^k$,
donc $k \leq \log_2 N$.

$$\text{nombre de facteurs premiers de } N_{X,Y} \leq \log_2(256^{nm}) = nm \cdot \log_2(256) = 8nm$$

✓

---

##### Question 6 – Probabilité d'erreur $< 8nm / \pi(\alpha)$

**Raisonnement :**

Si K est choisi uniformément parmi les $\pi(\alpha)$ nombres premiers $\leq \alpha$, alors :
$$\Pr[\text{erreur}] = \Pr[K \mid N_{X,Y}]$$

Un nombre premier $p$ divise $N_{X,Y}$ ssi $p$ est l'un des facteurs premiers de $N_{X,Y}$. $N_{X,Y}$ a au plus $8nm$
facteurs premiers distincts. Donc :
$$\Pr[K \mid N_{X,Y}] \leq \frac{8nm}{\pi(\alpha)}$$

**Applications numériques :**

**a) Pratique : $\alpha = 2^{64}$, $n = 10^9$, $m = 25$**

$8nm = 8 \times 10^9 \times 25 = 2 \times 10^{11}$

$\pi(2^{64}) \geq \frac{2^{64}}{\ln(2^{64})} = \frac{2^{64}}{64 \ln 2} \approx \frac{1.84 \times 10^{19}}{44.4} \approx 4.15 \times 10^{17}$

$$\Pr[\text{erreur}] \leq \frac{2 \times 10^{11}}{4.15 \times 10^{17}} \approx 5 \times 10^{-7}$$

Probabilité d'erreur **négligeable** avec seulement 64 bits d'arithmétique !

**b) Théorique : $\alpha = 8n^2m$**

$\pi(8n^2m) \geq \frac{8n^2m}{\ln(8n^2m)}$

$$\Pr[\text{erreur}] \leq \frac{8nm}{\pi(\alpha)} \leq \frac{8nm \cdot \ln(8n^2m)}{8n^2m} = \frac{\ln(8n^2m)}{n} \xrightarrow[n \to \infty]{} 0$$

Résultat théorique : l'erreur tend vers 0 pour de grandes entrées.

---

##### Question 7 – De Monte Carlo à Las Vegas en O(n + m)

**Idée :** Lorsque le MC signale une occurrence potentielle en position $i$ (i.e., $N_i' = N_X'$), on **vérifie
directement** octet par octet en O(m).

**Algorithme Las Vegas :**

```text
1. Exécuter l'algorithme MC [O(n)]
2. Pour chaque position i signalée (N'_i = N'_X) :
   Vérifier Y[i..i+m-1] = X octet par octet [O(m)]
   Si oui : vraie occurrence; si non : faux positif, ignorer
```

**Analyse du coût :**

- Vraies occurrences : au plus $n/m$ occurrences, chacune vérifiée en O(m) → $O(n)$ total.
- Faux positifs : en espérance très peu (probabilité $< 8m/\pi(\alpha)$ par position), coût total négligeable.
- Coût total espéré : **O(n + m)** ✓

Cet algorithme ne produit **jamais** de fausse occurrence → algorithme **Las Vegas**.

---

##### Question 8 – Recherche de S chaînes de longueur m

**Algorithme :**

```text
1. Calculer N'_{X_s} pour s=1..S et les stocker dans une table de hachage H [O(mS)]
2. Calculer tous les N'_i [O(n)]
3. Pour chaque i : chercher N'_i dans H [O(1)]
   Si trouvé : vérifier quelle(s) chaîne(s) correspondent [O(m)]
```

- Construction de H : O(mS) (calculer les empreintes)
- Scan du fichier : $O(n)$
- **Coût total : O(n + mS)** ✓

---

<a id="seance-9-exercice-2"></a>

### Exercice 2 – Fonction de hachage parfaite

#### Reformulation du problème

On veut construire une **table de hachage sans collision** pour n clés, en espace $O(n)$. On utilise une construction
probabiliste à **deux niveaux**.

**Rappels des propriétés admises :**

- **(P1)** $h_k$ est injective $\iff \gamma(k) = 0$
- **(P2)** $\sum_{k=1}^{N-1} \gamma(k) = n(n-1)\lfloor\frac{N-1}{m}\rfloor$

---

##### Question 2.1 – $\mathbb{E}[\gamma] \leq \frac{n(n-1)}{m}$ et $\Pr\left[\gamma < \frac{2n(n-1)}{m}\right] \geq \frac{1}{2}$

**Calcul de l'espérance :**

$k$ est choisi uniformément dans $\{1,\ldots,N-1\}$, donc :
$$\mathbb{E}[\gamma] = \frac{1}{N-1} \sum_{k=1}^{N-1} \gamma(k) \stackrel{(P2)}{=} \frac{n(n-1)\lfloor\frac{N-1}{m}\rfloor}{N-1} \leq \frac{n(n-1)}{m}$$

(car $\lfloor\frac{N-1}{m}\rfloor \leq \frac{N-1}{m}$)

**Borne sur la probabilité — Inégalité de Markov :**

> **Inégalité de Markov :** Pour $Z \geq 0$ et $t > 0$ : $\Pr[Z \geq t] \leq \frac{\mathbb{E}[Z]}{t}$

Avec $t = \frac{2n(n-1)}{m}$ :

$$\Pr\left[\gamma \geq \frac{2n(n-1)}{m}\right] \leq \frac{\mathbb{E}[\gamma]}{\frac{2n(n-1)}{m}} \leq \frac{\frac{n(n-1)}{m}}{\frac{2n(n-1)}{m}} = \frac{1}{2}$$

Donc par complémentarité : $\Pr\left[\gamma < \frac{2n(n-1)}{m}\right] \geq \frac{1}{2}$ ✓

---

##### Question 2.2 – Si $m > 2n^2$, plus de la moitié des $h_k$ sont injectives

Avec $m > 2n^2 > 2n(n-1)$ :
$$\frac{2n(n-1)}{m} < \frac{2n(n-1)}{2n(n-1)} = 1$$

Donc $\frac{2n(n-1)}{m} < 1$, et comme $\gamma$ est un **entier positif** :
$$\Pr[\gamma < 1] = \Pr[\gamma = 0] \geq \frac{1}{2}$$

Par **(P1)**, $\gamma(k) = 0 \iff h_k$ injective. Donc **plus de la moitié des fonctions $h_k$ sont injectives**. ✓

> **Intuition :** Une table de taille quadratique ($m \approx 2n^2$) est si grande qu'une fonction de hachage aléatoire
> est injective avec bonne probabilité. Mais c'est trop d'espace ! L'enjeu est d'arriver à $O(n)$.

---

##### Question 2.3 – Construction avec espace linéaire

**Paramètre : $m = 2n$ (premier niveau)**

###### Sous-question 2.3.1 – Algorithme pour trouver k, nombre de tirages, coût

**Condition visée :** $\gamma(k) < n$

Avec $m = 2n$ : $\frac{2n(n-1)}{m} = \frac{2n(n-1)}{2n} = n-1 < n$

Donc d'après Q.2.1 : $\Pr[\gamma < n] \geq \Pr\left[\gamma < \frac{2n(n-1)}{m}\right] \geq \frac{1}{2}$

**Algorithme (Las Vegas) :**

```text
Répéter :
    Choisir k uniformément dans {1,...,N-1}
    Calculer h_k(x) pour tout x ∈ X  [O(n)]
    Calculer γ(k) en comptant les collisions  [O(n)]
Jusqu'à γ(k) < n
Retourner k
```

**Nombre espéré de tirages :** chaque tirage réussit avec probabilité $\geq 1/2$, donc le nombre espéré est $\leq 2$ (
loi géométrique : $\mathbb{E}[\text{essais}] \leq \frac{1}{1/2} = 2$).

**Coût moyen :** $2 \times $O(n)$ = $O(n)$$ ✓

###### Sous-question 2.3.2 – Vérifier que $\sum_{i=0}^{m-1} c_i^2 < 2n$

Par définition : $\gamma(k) = \sum_{i=0}^{m-1} c_i^2 - n$

Donc : $\sum_{i=0}^{m-1} c_i^2 = \gamma(k) + n < n + n = 2n$ ✓

###### Sous-question 2.3.3 – Calcul de tous les $k_i$ en $O(n)$

**Idée :** Pour chaque bucket $i$ avec $c_i \geq 2$, on applique **localement** la même construction (Q.2.2) avec
les $c_i$ éléments tombant dans ce bucket.

**Pour le bucket $i$ :** Choisir $m_i = 2c_i^2$ et un $k_i$ tel que $h_{k_i}$ est injective sur les $c_i$ éléments du
bucket. Par Q.2.2, une fraction $\geq 1/2$ des $k_i$ conviennent → espérance $\leq 2$ tirages.

**Coût pour le bucket $i$ :** O($c_i$) par tirage × 2 tirages espérés = O($c_i$) espéré.

**Coût total :** $\sum_i O(c_i) = O(\sum_i c_i) = $O(n)$$ ✓

(Car $\sum c_i = n$, chaque clé est dans exactement un bucket.)

**Initialisation des sous-tables :** Taille totale des
sous-tables $= \sum m_i = \sum 2c_i^2 \leq 2 \cdot \sum c_i^2 < 2 \cdot 2n = 4n = $O(n)$$. ✓

###### Sous-question 2.3.4 – Fonction de hachage parfaite $\phi(x)$

**Construction à deux niveaux :**

$$\phi(x) = \text{base}_{h_k(x)} + h_{k_{h_k(x)}}(x) \bmod m_{h_k(x)}$$

où $\text{base}_i = \sum_{j < i} m_j$ est l'offset du bucket $i$ dans la table globale.

**Calcul de $\phi(x)$ :**

1. $j \leftarrow h_k(x) = (k \cdot x \bmod N) \bmod m$ → bucket (premier niveau)
2. $\phi(x) \leftarrow \text{base}_j + h_{k_j}(x) \bmod m_j$ → position finale (second niveau)

**Deux opérations arithmétiques $O(1)$** → coût $O(1)$ par requête. ✓

**Espace mémoire :**

| Structure                                     | Taille        |
|-----------------------------------------------|---------------|
| $k$ (premier niveau)                          | $O(1)$        |
| $m = 2n$ cases premiers niveau                | $O(n)$        |
| Tableau des $k_i$, $m_i$, $\text{base}_i$     | O(m) = $O(n)$ |
| Tables second niveau (taille $\sum m_i < 4n$) | $O(n)$        |
| **Total**                                     | **$O(n)$**    |

**Réduire d'un facteur :** On peut optimiser en ne stockant que les $k_i$ des buckets non vides (au plus n buckets), et
en notant que $\sum m_i = \sum 2c_i^2 < 4n$ peut être réduit à $\sum c_i^2 + c_i \leq 3n$ avec une technique de hachage
légèrement différente (facteur 2 environ).

**Coûts de construction :** $O(n)$ comme montré ci-dessus.

**Avec arithmétique modulo N en $\tilde{O}(\log N)$ :**

- Chaque opération coûte $\tilde{O}(\log N)$ au lieu de $O(1)$.
- Construction : $O(n \log N)$
- Requête : $O(\log N)$
- Pour $N \approx 256^{16}$, $\log N = 128$ bits → coût modeste en pratique.

---

<a id="seance-9-exercice-3"></a>

### Exercice 3 – Approximation de MAX-3-LIN

#### Reformulation

On veut maximiser le nombre d'équations $x_a \oplus x_b \oplus x_c = s$ simultanément satisfaites. C'est un problème
NP-difficile (en général on ne peut pas tout satisfaire).

---

##### Question 3.1 – NP-difficulté

**Ce qu'il faudrait prouver :**

Il suffirait d'exhiber une **réduction polynomiale** d'un problème NP-complet connu (par exemple 3-SAT ou le problème de
satisfaisabilité MAX-3-LIN-exact) vers MAX-3-LIN. Plus précisément :

> Il faudrait montrer que : si un algorithme polynomial résout MAX-3-LIN, alors il résout aussi tout problème de NP en
> temps polynomial.

En pratique, on montrerait qu'il existe une réduction polynomiale depuis 3-SAT (ou 3-LIN-mod-2) : "décider si toutes les
équations sont simultanément satisfaisables est NP-complet", ce qui implique que la version optimisation est
NP-difficile.

---

##### Algorithme probabiliste R

###### Question R.1 – Probabilité 1/2 qu'une équation soit satisfaite

**Équation j :** $x_a \oplus x_b \oplus x_c = s$, avec $x_a, x_b, x_c$ tirées uniformément et indépendamment
dans $\{0,1\}$.

**Raisonnement :** Le XOR de 3 variables booléennes uniformes et indépendantes est une variable uniforme dans $\{0,1\}$.

*Preuve par dénombrement :* Sur les $2^3 = 8$ assignations :

- 4 donnent $x_a \oplus x_b \oplus x_c = 0$ : (0,0,0), (0,1,1), (1,0,1), (1,1,0)
- 4 donnent $x_a \oplus x_b \oplus x_c = 1$ : (0,0,1), (0,1,0), (1,0,0), (1,1,1)

Donc : $\Pr[x_a \oplus x_b \oplus x_c = s] = 1/2$ quel que soit $s \in \{0,1\}$. ✓

###### Question R.2 – Borne sur la valeur optimale

La valeur de toute affectation est au plus le nombre total d'équations :
$$\text{OPT}(I) \leq m$$

(trivial : on ne peut pas satisfaire plus d'équations qu'il n'en existe)

###### Question R.3 – Ratio d'approximation $\rho \leq 2$

**Calcul de l'espérance par linéarité :**

$$\mathbb{E}[\text{valeur}(R(I))] = \sum_{j=1}^m \Pr[\text{équation } j \text{ satisfaite}] = \sum_{j=1}^m \frac{1}{2} = \frac{m}{2}$$

**Ratio :**
$$\rho(I) = \frac{\text{OPT}(I)}{\mathbb{E}[\text{valeur}(R(I))]} \leq \frac{m}{m/2} = 2$$

Donc $\rho \leq 2$. ✓

> **Interprétation :** L'algorithme aléatoire satisfait en espérance **au moins la moitié** de la valeur optimale.

---

##### Algorithme déterministe (dérandamisation)

**Idée générale (méthode des espérances conditionnelles) :**

On maintient $E(v_1,\ldots,v_j)$ = nombre espéré d'équations satisfaites, **sachant** que $x_1=v_1,\ldots,x_j=v_j$ et
les variables $x_{j+1},\ldots,x_n$ restent uniformément aléatoires.

**Formule explicite :**
$$E(v_1,\ldots,v_j) = \underbrace{\#\{\text{équations totalement déterminées et satisfaites}\}}_{A_j} + \frac{1}{2}\underbrace{\#\{\text{équations avec au moins une variable libre}\}}_{B_j}$$

*Justification :* Si une équation a encore au moins une variable libre, sa valeur finale dépend de tirages uniformes →
contribution = 1/2 (indépendamment de combien de variables sont fixées, tant qu'une reste libre).

###### Question D.1 – Algorithme déterministe explicite

```text
// Initialisation
Pour chaque équation i :
    xor_fixé[i] ← 0         // XOR des valeurs des variables déjà fixées
    nb_libres[i] ← 3         // nombre de variables encore libres
    s[i] ← second membre de l'équation

// Derandomisation
Pour j = 1 à n :
    gain_0 ← 0; gain_1 ← 0
    Pour chaque équation i contenant x_j :
        Si nb_libres[i] = 1 :  // x_j est la DERNIÈRE variable libre
            // Avec x_j = 0 : équation devient (xor_fixé[i] ⊕ 0 = s[i]) ?
            si (xor_fixé[i] == s[i]) : gain_0 += 1/2  // satisfaite → gain +1/2
            sinon : gain_0 -= 1/2                        // non satisfaite → gain -1/2
            // Avec x_j = 1 : équation devient (xor_fixé[i] ⊕ 1 = s[i]) ?
            si (xor_fixé[i] ⊕ 1 == s[i]) : gain_1 += 1/2
            sinon : gain_1 -= 1/2
        // Si nb_libres[i] > 1 : contribution reste 1/2 dans les deux cas → pas de différence

    Si gain_0 >= gain_1 : v_j ← 0
    Sinon : v_j ← 1

    // Mise à jour des équations contenant x_j
    Pour chaque équation i contenant x_j :
        xor_fixé[i] ← xor_fixé[i] ⊕ v_j
        nb_libres[i] ← nb_libres[i] - 1

Retourner (v_1,...,v_n) et compter les équations satisfaites
```

**Complexité :** O(m) total — chaque équation est mise à jour exactement 3 fois (quand chacune de ses 3 variables est
fixée).

###### Question D.2 – $E(v_1,\ldots,v_j) \geq E(v_1,\ldots,v_{j-1})$

**Démonstration par espérance conditionnelle (loi des espérances totales) :**

Avant de fixer $x_j$, $x_j$ vaut 0 ou 1 avec probabilité 1/2 :
$$E(v_1,\ldots,v_{j-1}) = \frac{1}{2} E(v_1,\ldots,v_{j-1},0) + \frac{1}{2} E(v_1,\ldots,v_{j-1},1)$$

La **moyenne** de deux valeurs est toujours $\leq$ leur **maximum**, donc :
$$\max\{E(v_1,\ldots,v_{j-1},0),\; E(v_1,\ldots,v_{j-1},1)\} \geq \frac{E(v_1,\ldots,v_{j-1},0) + E(v_1,\ldots,v_{j-1},1)}{2} = E(v_1,\ldots,v_{j-1})$$

Or $e_j$ est précisément défini comme le maximiseur : $E(v_1,\ldots,v_{j-1},e_j) = \max\{E(\ldots,0),E(\ldots,1)\}$.

Donc : $E(v_1,\ldots,v_j) = E(v_1,\ldots,v_{j-1},e_j) \geq E(v_1,\ldots,v_{j-1})$ ✓

###### Question D.3 – Borne sur $E(v_1,\ldots,v_n)$ et ratio

**La suite est croissante :** par D.2, $E_0 \leq E(v_1) \leq E(v_1,v_2) \leq \ldots \leq E(v_1,\ldots,v_n)$.

**Valeur initiale :** $E_0 = \frac{m}{2}$ (espérance avant tout tirage, calculée en R.3).

**Au bout des n étapes :** $E(v_1,\ldots,v_n)$ est la valeur réelle de l'affectation déterministe (plus de variables
aléatoires), donc :
$$\text{valeur\_det}(v_1,\ldots,v_n) = E(v_1,\ldots,v_n) \geq E_0 = \frac{m}{2}$$

**Ratio de l'algorithme déterministe :**
$$\rho_{\text{det}} = \frac{\text{OPT}}{\text{valeur\_det}} \leq \frac{m}{m/2} = 2$$

L'algorithme déterministe **garantit aussi un ratio ≤ 2** ! 🎯

###### Question D.4 – Exemple avec OPT = m/2 et conclusion

**Exemple :** Prenons 4 équations contradictoires deux par deux :

| Équation 1 | $x_1 \oplus x_2 \oplus x_3 = 0$ |
|------------|---------------------------------|
| Équation 2 | $x_1 \oplus x_2 \oplus x_3 = 1$ |
| Équation 3 | $x_1 \oplus x_2 \oplus x_4 = 0$ |
| Équation 4 | $x_1 \oplus x_2 \oplus x_4 = 1$ |

Ici m = 4. Pour toute affectation :

- Les éq. 1 et 2 sont contradictoires (même LHS, seconds membres opposés) → exactement 1 satisfaite.
- Les éq. 3 et 4 aussi → exactement 1 satisfaite.

**Donc OPT = 2 = m/2**, et **toute** affectation satisfait exactement 2 équations.

**Conclusion :**

Ce exemple montre que OPT lui-même peut valoir m/2. Notre algorithme déterministe garantit $\geq m/2$ équations
satisfaites. Mais ici OPT = m/2, donc notre algorithme atteint l'optimal (ratio = 1 sur cet exemple).

Plus globalement : puisqu'il existe des instances où **OPT = m/2**, aucun algorithme ne peut garantir plus de m/2
équations satisfaites en général (ce serait dépasser OPT sur ces instances). **Le ratio de 2 est donc optimal** : on ne
peut pas l'améliorer par cette approche, car pour améliorer le ratio il faudrait soit dépasser m/2 (impossible parfois),
soit résoudre exactement le problème NP-difficile.

---

#### Résumé global de la feuille

<a id="seance-9-exercice-4"></a>

##### Exercice 1 — Rabin-Karp

- **Idée :** Remplacer les comparaisons de chaînes O(m) par des comparaisons d'empreintes $O(1)$ (hash modulaire).
- **Récurrence :** $N_i' = (256(N_{i-1}' - 256^{m-1}Y_{i-1}) + Y_{i+m-1}) \bmod K$ → calcul de préfixes.
- **Erreur :** Pr[faux positif] $\leq 8nm / \pi(\alpha)$.
- **Las Vegas :** vérifier chaque occurrence signalée en O(m).

<a id="seance-9-exercice-5"></a>

##### Exercice 2 — Hachage parfait à 2 niveaux

- **Niveau 1 :** $m = 2n$, chercher $k$ tel que $\gamma(k) < n$ (espérance 2 essais).
- **Niveau 2 :** Pour chaque bucket $i$, table de taille $2c_i^2$, injective.
- **Espace total :** $\sum 2c_i^2 < 4n = $O(n)$$.
- **Requête :** $O(1)$.

<a id="seance-9-exercice-6"></a>

##### Exercice 3 — MAX-3-LIN

- **Algorithme probabiliste :** affectation aléatoire → espérance m/2 → ratio 2.
- **Dérandamisation :** méthode des espérances conditionnelles, la suite est croissante.
- **Garantie :** toujours $\geq m/2$ équations satisfaites, ratio 2 optimal.

---

#### Méthodes / Techniques clés

| Technique                                              | Où utilisée    |
|--------------------------------------------------------|----------------|
| Calcul de préfixes parallèles                          | Exo 1 Q.2      |
| Lemme de facteurs premiers (Schwartz-Zippel implicite) | Exo 1 Q.4-6    |
| Inégalité de Markov                                    | Exo 2 Q.1, Q.2 |
| Loi des espérances totales                             | Exo 3 D.2      |
| Dérandamisation par espérances conditionnelles         | Exo 3 D.1-3    |

---

#### Formules et résultats importants

$$\text{(Rabin-Karp)} \quad N_i' = \big(256(N_{i-1}' - 256^{m-1}Y_{i-1}) + Y_{i+m-1}\big) \bmod K$$

$$\text{(Markov)} \quad \Pr[Z \geq t] \leq \frac{\mathbb{E}[Z]}{t}$$

$$\text{(Hachage parfait)} \quad \mathbb{E}[\gamma] \leq \frac{n(n-1)}{m}, \quad \sum c_i^2 < 2n \text{ si } m=2n, \gamma<n$$

$$\text{(MAX-3-LIN)} \quad \mathbb{E}[\text{satisfaites}] = \frac{m}{2}, \quad \text{ratio} \leq 2$$

---

#### Pièges fréquents à éviter

1. **Exo 1 :** Confondre "K divise le produit" avec "K divise chaque facteur" (ce n'est pas équivalent dans ce sens,
   mais l'implication inverse est correcte pour la contraposée).
2. **Exo 1 :** Oublier que $\Phi$ est injective (en base 256, chaque chaîne de longueur m fixée donne un entier unique).
3. **Exo 2 :** Ne pas remarquer que $\sum c_i^2 < 2n$ (pas $\leq n$) — c'est la clé pour borner la mémoire totale du
   second niveau.
4. **Exo 3 :** Dans la dérandamisation, les équations avec 2 ou 3 variables libres ne contribuent pas à la différence
   entre $E(\ldots,0)$ et $E(\ldots,1)$ — seules les équations dont $x_j$ est la **dernière** variable libre comptent.
5. **Général :** L'inégalité de Markov donne $\Pr[Z \geq t] \leq E[Z]/t$ — toujours prendre $t > E[Z]$ pour obtenir une
   probabilité $< 1$ non triviale.

---

#### Questions d'entraînement similaires

**Q1.** On dispose d'une table de multiplication $T$ de taille $n \times n$ avec au plus 5 % d'erreurs. On applique
l'algorithme vu en cours (4 accès aléatoires). Quelle est la probabilité maximale d'erreur ? Combien de répétitions pour
l'amener sous $10^{-6}$ ?

> *Réponse brève :* Pr(erreur) ≤ 4 × 0.05 = 0.2. Après k répétitions (valeur majoritaire), Pr(erreur) ≤ 2e^{-0.02k}.
> Pour $k = 700$, Pr < $10^{-6}$.

**Q2.** Dans l'exercice de hachage parfait, si on prend $m = 4n$ au premier niveau, quelle est la nouvelle borne
sur $\sum c_i^2$ ? La taille totale du second niveau est-elle toujours $O(n)$ ?

> *Réponse brève :* $\mathbb{E}[\gamma] \leq n(n-1)/(4n) < n/4$. Par Markov, on peut trouver $k$ avec $\gamma < n/2$,
> donc $\sum c_i^2 < n + n/2 = 3n/2$, et $\sum m_i = \sum 2c_i^2 < 3n = $O(n)$$. ✓

**Q3.** Pourquoi le ratio 2 pour MAX-3-LIN ne peut-il pas être amélioré à $3/2$ par la méthode des espérances
conditionnelles (sans information supplémentaire) ?

> *Réponse brève :* Parce qu'il existe des instances avec OPT = m/2, et la méthode garantit exactement m/2. On atteint
> déjà OPT sur ces instances → ratio = 1. Mais on ne peut pas faire mieux que m/2 en général (certaines instances sont
> saturées). La borne de 2 est donc tight.

**Q4.** On cherche un motif X de longueur m dans un texte Y de longueur n. On choisit K parmi les
premiers $\leq 2^{32}$. Pour $n = 10^6$, $m = 10$, quelle est la probabilité d'erreur ? Est-ce acceptable en pratique ?

> *Réponse brève :* $8nm = 8 \times 10^7$. $\pi(2^{32}) \approx 2^{32}/32 \approx 1.3 \times 10^8$. Pr(
> erreur) ≤ $8 \times 10^7 / 1.3 \times 10^8 \approx 0.62$. **Non acceptable** — prendre $\alpha = 2^{64}$ pour un
> meilleur résultat.

**Q5.** Montrez que l'algorithme déterministe de MAX-3-LIN s'exécute en temps O(nm) et proposez une optimisation à O(m).

> *Réponse brève :* Naïvement, pour chaque variable $x_j$, recalculer l'espérance sur toutes les m équations → O(nm).
> Optimisation : maintenir pour chaque équation un compteur `nb_libres[i]` et `xor_fixé[i]`. Chaque équation est mise à
> jour exactement 3 fois (une par variable). Total O(m). ✓


---

<a id="seance-10"></a>

## Séance 10 — Introduction à la complexité, classes P/NP et réductions

> Plage source conservée : lignes `4725` à `5772` de `course.txt`.

### Partie Théorique

Bienvenue dans la séance 10 ! Après avoir exploré comment contourner la difficulté des problèmes (via l'approximation,
le parallélisme ou l'aléatoire), nous entrons dans le cœur de l'informatique théorique : **la théorie de la complexité
**.

L'objectif de cette séance n'est plus de trouver *comment* résoudre un problème rapidement, mais de prouver
mathématiquement *pourquoi* certains problèmes sont intrinsèquement difficiles, et comment ils sont liés entre eux.

Voici votre cours détaillé, structuré et mis au propre.

---

### Séance 10 : Introduction à la Complexité, Classes P/NP et Réductions

**Objectif de la séance :** Comprendre les limites du calcul formel, classifier les problèmes selon leur difficulté
intrinsèque (les fameuses classes de complexité) et apprendre à utiliser les "réductions" pour prouver qu'un problème
est au moins aussi difficile qu'un autre.

#### 1. Concepts Fondamentaux

##### A. Problèmes d'Optimisation vs Problèmes de Décision

En théorie de la complexité, on ramène presque toujours les problèmes à des **problèmes de décision** (dont la réponse
est strictement OUI ou NON). Cela permet de simplifier l'analyse mathématique, car résoudre un problème revient à "
reconnaître si un mot appartient à un langage".

* *Exemple (Optimisation) :* "Quel est le plus court chemin entre A et B ?"
* *Exemple (Décision) :* "Existe-t-il un chemin entre A et B de longueur $\le k$ ?" (En faisant varier $k$, on peut
  trouver l'optimum).

##### B. Le Modèle : La Machine de Turing (TM)

C'est le modèle théorique fondamental de l'algorithmique.

* **Machine Déterministe (DTM) :** À chaque étape, pour un état donné, il n'y a qu'une seule action possible.
  L'exécution est une ligne droite. C'est l'équivalent de nos ordinateurs actuels.
* **Machine Non-Déterministe (NDTM) :** À chaque étape, la machine peut faire plusieurs choix simultanément. Elle
  explore "magiquement" tous les chemins en parallèle. Si un seul des chemins mène à la solution, elle répond OUI.

##### C. Notion de Décidabilité

* **Décidable :** Il existe un algorithme qui s'arrête toujours et donne la bonne réponse (OUI ou NON).
* **Semi-décidable :** L'algorithme s'arrête et dit OUI si la réponse est OUI. Mais si la réponse est NON, il peut
  boucler à l'infini.
* **Indécidable :** Il n'existe aucun algorithme capable de résoudre le problème dans tous les cas.

---

#### 2. Le "Zoo" des Classes de Complexité

Une classe de complexité regroupe tous les problèmes pouvant être résolus par une machine donnée sous une contrainte de
ressources donnée (temps ou mémoire).

Voici la hiérarchie classique (illustrée sur la photo de votre tableau) :

```text
       +-----------------------------------------------------------+
       | NP (Temps Polynomial Non-Déterministe)                    |
       |  +-----------------------------------------------------+  |
       |  | P (Temps Polynomial Déterministe)                   |  |
       |  |  +-----------------------------------------------+  |  |
       |  |  | NC (Nick's Class - Parallélisable)            |  |  |
       |  |  |  +-----------------------------------------+  |  |  |
       |  |  |  | NL (Espace Logarithmique Non-Déterm.)   |  |  |  |
       |  |  |  |  +-----------------------------------+  |  |  |  |
       |  |  |  |  | L (Espace Logarithmique)          |  |  |  |  |
       |  |  |  |  +-----------------------------------+  |  |  |  |
       |  |  |  +-----------------------------------------+  |  |  |
       |  |  +-----------------------------------------------+  |  |
       |  +-----------------------------------------------------+  |
       +-----------------------------------------------------------+
```

##### La Classe P (Ce que l'on sait faire)

C'est l'ensemble des problèmes de décision résolubles en **temps polynomial** $O(n^k)$ sur une machine déterministe.

* *Exemple :* Vérifier si un tableau est trié (boucle simple en $O(n)$).

##### La Classe NP (Ce que l'on sait vérifier)

Il existe deux définitions équivalentes pour la classe NP :

1. **Définition par NDTM :** Problèmes résolubles en temps polynomial sur une machine de Turing *non-déterministe*.
2. **Définition par Certificat (la plus intuitive) :** Un problème est dans NP s'il existe une machine
   déterministe $V$ (un vérifieur) capable de vérifier une solution en temps polynomial, à condition qu'on lui fournisse
   une "preuve" (le certificat $c_m$).
    * *Intuition :* Il est peut-être très difficile de trouver la solution (ex: un puzzle géant), mais si quelqu'un vous
      donne la solution terminée (le certificat), il est très facile et rapide de vérifier qu'elle est correcte.

##### La question à 1 million de dollars : P = NP ?

* P = "Ce qu'on peut trouver facilement"
* NP = "Ce qu'on peut vérifier facilement"
* **Conjecture :** $P \ne NP$. L'intuition de tous les chercheurs est qu'il y a des problèmes intrinsèquement difficiles
  à résoudre (comme casser un mot de passe) même s'ils sont faciles à vérifier.

---

#### 3. Les Réductions (Transformer pour vaincre)

Comment comparer la difficulté de deux problèmes qu'on ne sait pas résoudre ? On utilise le concept de **réduction**.

**Principe :** Le problème $A$ se réduit au problème $B$ (noté $A \le B$) si on peut utiliser un algorithme qui
résout $B$ (une "boîte noire" ou un Oracle) pour résoudre $A$.

##### La Réduction Polynomiale de Karp ($A \le_p B$)

C'est le type de réduction le plus utilisé en complexité. Pour prouver que $A \le_p B$, il faut trouver une fonction de
transformation $f$ telle que :

1. Une instance $x$ du problème $A$ est transformée en une instance $f(x)$ du problème $B$ en un **temps polynomial**.
2. La réponse pour $x$ dans $A$ est OUI $\iff$ la réponse pour $f(x)$ dans $B$ est OUI.

**Propriété fondamentale :**
Si $A \le_p B$ et que l'on trouve un algorithme polynomial pour $B$ (donc $B \in P$), alors on a automatiquement un
algorithme polynomial pour $A$ (donc $A \in P$). En clair, **$B$ est au moins aussi difficile que $A$**.

---

#### 4. Exemple Concret du Tableau : 2-Partitions $\le_p$ PLNE

Votre photo de tableau montre un exemple brillant de réduction pour prouver qu'un problème classique est difficile.

* **Le problème 1 (2-Partitions) :** On a un ensemble de $n$ objets avec des valeurs $v_i$. Peut-on les séparer en deux
  groupes équitables (de même somme) ?
* **Le problème 2 (PLNE - Programmation Linéaire en Nombres Entiers) :** Peut-on satisfaire un système
  d'inéquations $Ax \le B$ avec des variables strictement entières ?

**La Réduction (Comment transformer 2-Partitions en PLNE) :**
Soit la variable $x_i \in \{0, 1\}$. $x_i = 1$ signifie que l'objet $i$ va à la personne 1. $x_i = 0$ signifie qu'il va
à la personne 2.
Pour que les deux personnes aient la même part, la somme des objets de la personne 1 doit valoir exactement la moitié du
total.
On crée donc la contrainte mathématique suivante :
$$\sum_{i=1}^{n} x_i \cdot v_i = \frac{1}{2} \sum_{i=1}^{n} v_i$$
Ceci est très exactement une équation de Programmation Linéaire en Nombres Entiers ! On vient de prouver que *
*2-Partitions $\le_p$ PLNE**. Si un jour quelqu'un trouve un moyen rapide (polynomial) de résoudre PLNE, il saura
immédiatement résoudre 2-Partitions.

---

#### 5. NP-Difficulté et NP-Complétude

C'est ici que l'on identifie les "boss finaux" de l'informatique.

* **NP-Difficile (NP-Hard) :** Un problème $\Pi$ est NP-difficile si **tous** les problèmes de la classe NP peuvent se
  réduire à lui ($\forall A \in NP, A \le_p \Pi$). Ce sont les problèmes les plus durs qui existent (ils peuvent même
  être "pires" que NP et être indécidables).
* **NP-Complet (NP-Complete) :** Un problème $\Pi$ est NP-complet s'il est **à la fois** dans NP (on peut vérifier sa
  solution rapidement) ET qu'il est NP-difficile.

**Le Théorème de Cook :**
Comment prouver qu'un problème est le premier NP-complet (puisqu'on ne peut pas le réduire depuis un autre, il n'y en a
pas !) ? Stephen Cook a prouvé mathématiquement que le problème **SAT** (la satisfaisabilité d'une formule logique
booléenne) pouvait modéliser le fonctionnement interne de n'importe quelle machine de Turing non-déterministe. Ainsi, *
*SAT est NP-complet**.

Dès lors, pour prouver qu'un nouveau problème $X$ est NP-complet, il suffit de montrer que $X \in NP$, et
que $SAT \le_p X$.

---

Voulez-vous que l'on détaille pas-à-pas la réduction historique de 3-SAT vers la Coloration de Graphes évoquée dans vos
notes, ou préférez-vous passer directement aux exercices de votre TD ?

C'est tout à fait normal d'avoir lâché la prise de notes face aux nombreux dessins et flèches de cette démonstration !
Cette réduction est un classique absolu de la théorie de la complexité, mais elle demande de la rigueur pour ne pas se
perdre dans les arêtes.

Voici la démonstration détaillée et mise au propre de la réduction de Karp **3-SAT $\le_p$ 3-Coloriage**.

**L'objectif :** Étant donné une formule booléenne $\Phi$ en 3-SAT (composée de clauses de 3 littéraux), nous voulons
construire un graphe $G$ tel que $G$ est coloriable avec 3 couleurs **si et seulement si** la formule $\Phi$ est
satisfaisable.

---

##### Étape 1 : La Palette de Couleurs (Le Référentiel)

La première étape consiste à fixer nos 3 couleurs. Nous allons les appeler **Vrai ($V$)**, **Faux ($F$)** et *
*Neutre ($N$)**.
Pour imposer ces couleurs dans notre graphe, nous créons un simple triangle (une clique de 3 sommets) :

* Un sommet $V$
* Un sommet $F$
* Un sommet $N$

Puisque ces trois sommets sont tous reliés entre eux, une coloration valide exigera obligatoirement qu'ils aient tous
une couleur différente. Ces trois sommets vont servir de point d'ancrage absolu pour tout le reste du graphe.

---

##### Étape 2 : Le Gadget des Variables

Pour chaque variable booléenne $x_i$ de notre formule $\Phi$, nous devons simuler le fait qu'elle ne peut prendre que la
valeur Vrai ou Faux.

1. Nous créons deux sommets : un sommet $x_i$ et un sommet $\neg x_i$.
2. Nous les relions entre eux par une arête.
3. Nous relions ces deux sommets au sommet **Neutre ($N$)** de notre palette.

**Pourquoi ça marche ?**
Puisque $x_i$ et $\neg x_i$ sont reliés à $N$, aucun des deux ne peut prendre la couleur $N$. Ils sont donc obligés de
piocher dans les couleurs $\{V, F\}$. Comme ils sont reliés entre eux, l'un prendra obligatoirement la couleur $V$ et
l'autre la couleur $F$. C'est l'équivalent parfait d'une affectation booléenne !

---

##### Étape 3 : Le Gadget des Clauses (Le cœur de la preuve)

C'est ici qu'intervient le fameux schéma complexe. Pour chaque clause $C = (l_1 \vee l_2 \vee l_3)$ de la formule (où
les $l_i$ sont des littéraux, c'est-à-dire des variables ou leurs négations), nous ajoutons un "gadget" composé de 6
sommets internes organisés en deux triangles.

**Construction du gadget pour une clause :**

* **Triangle 1 :** Créons 3 sommets $A$, $B$ et $C$ reliés entre eux en triangle.
* **Triangle 2 :** Créons 3 autres sommets $D$, $E$ et $F_{out}$ reliés entre eux en triangle.
* **Connexions aux littéraux :**
    * Relions $A$ au sommet du littéral $l_1$.
    * Relions $B$ au sommet du littéral $l_2$.
    * Relions $E$ au sommet du littéral $l_3$.
* **Connexions internes et à la palette :**
    * Relions le sommet $C$ au sommet $D$.
    * Relions le sommet $F_{out}$ au sommet **Faux ($F$)** ET au sommet **Neutre ($N$)** de notre palette.

---

##### Étape 4 : La Preuve (Pourquoi ce gadget est-il magique ?)

L'objectif de ce gadget est d'être impossible à colorier avec 3 couleurs **si et seulement si** les trois
littéraux $l_1, l_2, l_3$ reçoivent la couleur Faux ($F$). Vérifions-le !

**1. Analysons la fin du gadget :**
Le sommet $F_{out}$ est relié aux sommets $F$ et $N$ de la palette. Il est donc **forcé** de prendre la
couleur $Vrai$ ($V$).
Dans le Triangle 2 ($D, E, F_{out}$), puisque $F_{out}$ est $V$, les sommets $D$ et $E$ doivent se répartir les
couleurs $\{F, N\}$.

**2. Que se passe-t-il si $l_1 = F$, $l_2 = F$ et $l_3 = F$ ? (Le cas interdit)**

* Le littéral $l_3$ est $F$. Le sommet $E$ (qui lui est relié) ne peut donc pas être $F$. D'après le point
  précédent, $E$ est forcé d'être $N$.
* Si $E$ est $N$, alors son voisin $D$ dans le triangle est forcé d'être $F$.
* Le sommet $C$ est relié à $D$ (qui est $F$). Donc $C$ ne peut pas être $F$. Il doit piocher dans $\{V, N\}$.
* Regardons le Triangle 1 ($A, B, C$) : $A$ est relié à $l_1$ ($F$) et $B$ est relié à $l_2$ ($F$). Donc ni $A$ ni $B$
  ne peuvent être $F$.
* $A$ et $B$ doivent tous les deux piocher dans $\{V, N\}$. Puisqu'ils sont en triangle (donc reliés), l'un sera $V$ et
  l'autre $N$.
* Par conséquent, la seule couleur restante pour $C$ dans ce triangle est $F$.
* **CONTRADICTION !** Nous venons de dire que $C$ est relié à $D$, or nous avons prouvé que $C$ devrait être $F$ et $D$
  est $F$. Deux sommets adjacents auraient la même couleur, ce qui rend le graphe non-coloriable. La
  clause $(F \vee F \vee F)$ fait "planter" le coloriage.

**3. Que se passe-t-il si au moins un littéral est Vrai ($V$) ?**
Si au moins un des littéraux est coloré en $V$, cela "libère" une couleur pour les sommets $A$, $B$ ou $E$, ce qui
permet une cascade de choix valides sans jamais créer de conflit entre $C$ et $D$. Le graphe devient parfaitement
3-coloriable.

##### Bilan de la réduction

Nous avons transformé $\Phi$ en un graphe $G$. La taille de $G$ est proportionnelle au nombre de variables et de
clauses (création de nœuds en temps polynomial).

* Si $\Phi$ est satisfaisable, on peut assigner les couleurs $V$ et $F$ aux variables, et tous les gadgets seront
  coloriables.
* Si $G$ est 3-coloriable, en lisant la couleur ($V$ ou $F$) des sommets $x_i$, on obtient une affectation booléenne qui
  valide la formule $\Phi$.

La démonstration est complète : **3-SAT se réduit bien à la 3-Coloration de Graphes**.

### Partie Pratique (TD)

#### Vue d’ensemble

Cette feuille porte sur deux grands thèmes : la complexité algorithmique via des réductions polynomiales entre problèmes
de graphes, puis la modélisation d’un problème d’ordonnancement comme une programmation linéaire en nombres entiers. Les
compétences clés sont : raisonner avec des définitions de graphes, construire des réductions de Karp, comparer problèmes
de décision et d’optimisation, et encoder proprement un problème combinatoire en ILP.

<a id="seance-10-exercice-1"></a>

##### 1. Couvertures, cliques et stables dans un graphe

On considère un graphe non orienté G=(V,E).

Définitions importantes :

* Un stable ou ensemble indépendant S\subseteq V : aucun couple de sommets de S n’est relié par une arête dans G.
* Une clique : tous les sommets de S sont deux à deux reliés.
* Une couverture de sommets C\subseteq V : chaque arête du graphe touche au moins un sommet de C.
* Le graphe complémentaire \bar G : il contient exactement les arêtes qui ne sont pas dans G.

⸻

1.a) Montrer que S est stable dans G ssi S est une clique dans \bar G

Reformulation

On veut montrer qu’un ensemble sans arêtes dans G devient un ensemble complètement connecté dans le complémentaire \bar
G.

Preuve

Par définition, S est stable dans G signifie :

$$
\forall a,b\in S,\ a\neq b,\ (a,b)\notin E.
$$

Or, dans le graphe complémentaire \bar G=(V,\bar E), on a :

(a,b)\in \bar E \iff (a,b)\notin E.

Donc :

$$
\forall a,b\in S,\ a\neq b,\ (a,b)\in \bar E.
$$

C’est exactement la définition d’une clique dans \bar G.

Donc :

S \text{ stable dans } G \iff S \text{ clique dans } \bar G.

Intuition

Le complémentaire inverse les relations : les non-arêtes deviennent des arêtes. Donc un ensemble où personne n’est
connecté devient un ensemble où tout le monde est connecté.

⸻

1.b) Montrer que S est stable dans G ssi V-S est une couverture

Reformulation

On veut montrer que si S ne contient aucune arête interne, alors son complément touche toutes les arêtes du graphe.

Preuve

On note :

C = V-S.

On veut montrer :

S \text{ stable } \iff C \text{ couverture}.

Sens direct

Supposons que S est stable.

Prenons une arête quelconque :

(u,v)\in E.

Comme S est stable, il est impossible que u\in S et v\in S en même temps, sinon il y aurait une arête entre deux sommets
de S.

Donc au moins un des deux sommets n’est pas dans S. Ainsi :

u\in V-S \quad \text{ou} \quad v\in V-S.

Donc toute arête touche au moins un sommet de V-S. Ainsi V-S est une couverture.

Sens réciproque

Supposons que V-S est une couverture.

Raisonnons par l’absurde. Supposons que S n’est pas stable. Alors il existe deux sommets u,v\in S tels que :

(u,v)\in E.

Mais comme u,v\in S, aucun des deux n’appartient à V-S.

Donc l’arête (u,v) n’est pas couverte par V-S, contradiction.

Donc S est stable.

Conclusion

S \text{ stable dans } G \iff V-S \text{ couverture dans } G.

Piège classique

Il ne faut pas confondre :

$$
S \text{ stable}
$$

et

S \text{ couverture}.

Ce n’est pas S qui devient une couverture, mais son complément V-S.

⸻

<a id="seance-10-exercice-2"></a>

##### 2. Montrer que \text{CLIQUE} \leq_P \text{INDEPENDENT-SET}

Reformulation

On veut transformer une instance de CLIQUE en une instance de INDEPENDENT-SET, en temps polynomial.

Une instance de CLIQUE est :

(G,k).

On demande s’il existe une clique de taille k dans G.

Stratégie

Utiliser le graphe complémentaire \bar G.

On sait déjà que :

S \text{ clique dans } G \iff S \text{ stable dans } \bar G.

Réduction

À partir de (G,k), on construit :

(\bar G,k).

Puis on pose la question :

Existe-t-il un stable de taille k dans \bar G ?

Correction de la réduction

On a :

$$
G \text{ contient une clique de taille } k
$$

ssi il existe S\subseteq V, |S|=k, tel que tous les sommets de S sont reliés dans G.

Cela équivaut à dire que dans \bar G, aucun couple de sommets de S n’est relié.

Donc :

$$
G \text{ contient une clique de taille } k
$$
$$
\iff
$$
$$
\bar G \text{ contient un stable de taille } k.
$$

Complexité

Si le graphe est représenté par matrice d’adjacence, construire \bar G prend :

O(n^2)

car il suffit d’inverser les valeurs hors diagonale de la matrice.

Donc la réduction est polynomiale.

Conclusion

$$
\boxed{\text{CLIQUE} \leq_P \text{INDEPENDENT-SET}}
$$

⸻

<a id="seance-10-exercice-3"></a>

##### 3. Montrer que \text{INDEPENDENT-SET} \leq_P \text{VERTEX-COVER}

Reformulation

À partir d’une instance de INDEPENDENT-SET :

(G,k),

on veut construire une instance de VERTEX-COVER.

Stratégie

Utiliser la propriété :

S \text{ stable} \iff V-S \text{ couverture}.

Si S a taille k, alors V-S a taille :

|V|-k.

Réduction

À partir de (G,k), on construit :

(G, |V|-k).

On demande :

Existe-t-il une couverture de taille |V|-k ?

Correction

Si G possède un stable S de taille k, alors V-S est une couverture de taille :

|V|-k.

Donc l’instance de VERTEX-COVER est positive.

Réciproquement, si G possède une couverture C de taille |V|-k, alors V-C est un stable de taille :

|V|-|C|=k.

Donc l’instance de INDEPENDENT-SET est positive.

Conclusion

$$
\boxed{\text{INDEPENDENT-SET} \leq_P \text{VERTEX-COVER}}
$$

⸻

<a id="seance-10-exercice-4"></a>

##### 4. Si l’un des trois problèmes n’a pas d’algorithme polynomial, alors aucun des trois n’en a

On a déjà :

$$
\text{CLIQUE} \leq_P \text{INDEPENDENT-SET}
$$

et

$$
\text{INDEPENDENT-SET} \leq_P \text{VERTEX-COVER}.
$$

Il manque aussi les réductions inverses, mais elles viennent des mêmes propriétés :

$$
\text{INDEPENDENT-SET} \leq_P \text{CLIQUE}
$$

en passant au complémentaire, et

$$
\text{VERTEX-COVER} \leq_P \text{INDEPENDENT-SET}
$$

en remplaçant k par |V|-k.

Donc les trois problèmes sont polynomialement équivalents.

On a :

$$
\text{CLIQUE} \equiv_P \text{INDEPENDENT-SET} \equiv_P \text{VERTEX-COVER}.
$$

Cela veut dire que si l’un avait un algorithme polynomial, les autres en auraient aussi.

Donc, par contraposée :

si l’un des trois n’a pas d’algorithme polynomial, alors aucun des trois n’a d’algorithme polynomial.

⸻

<a id="seance-10-exercice-5"></a>

##### 5. Problèmes de calcul de cardinal optimal et problème de décision CLIQUE

On compare ici :

* calculer la taille maximale d’une clique ;
* calculer la taille maximale d’un stable ;
* calculer la taille minimale d’une couverture ;
* décider s’il existe une clique de taille k.

Idée principale

Un problème d’optimisation est souvent plus fort qu’un problème de décision.

Si on sait calculer :

$$
\omega(G)=\text{taille maximale d’une clique},
$$

alors on peut répondre à CLIQUE en testant :

$$
\omega(G)\geq k.
$$

Donc :

$$
\text{optimisation} \Rightarrow \text{décision}.
$$

Réciproquement, si on sait résoudre CLIQUE en temps polynomial, on peut trouver la taille maximale en testant plusieurs
valeurs de k.

⸻

Sens 1 : si on sait calculer le cardinal maximal d’une clique

Supposons qu’on a un algorithme polynomial qui calcule :

\omega(G).

Alors pour décider CLIQUE(G,k), on calcule \omega(G), puis :

$$
G \text{ contient une clique de taille } k
$$
$$
\iff
$$
$$
\omega(G)\geq k.
$$

Donc CLIQUE est polynomial.

⸻

Sens 2 : si CLIQUE est polynomial

Supposons qu’on a un algorithme polynomial pour CLIQUE.

On veut calculer :

\omega(G).

Méthode simple :

Tester successivement :

k=1,2,\dots,n.

On garde le plus grand k pour lequel CLIQUE(G,k) répond oui.

Cela fait n appels à un algorithme polynomial, donc reste polynomial.

On peut aussi faire une recherche dichotomique sur k, mais ce n’est pas nécessaire.

⸻

Pour le stable maximal

On utilise :

\alpha(G)=\omega(\bar G),

où \alpha(G) est la taille maximale d’un stable.

Donc calculer le stable maximal se ramène à calculer une clique maximale dans le complémentaire.

⸻

Pour la couverture minimale

On utilise :

S \text{ stable} \iff V-S \text{ couverture}.

Donc :

\tau(G)=|V|-\alpha(G),

où :

* \tau(G) est la taille minimale d’une couverture ;
* \alpha(G) est la taille maximale d’un stable.

Donc si on sait calculer \alpha(G), on sait calculer \tau(G).

Conclusion

Les trois problèmes de cardinal optimal sont polynomiaux si et seulement si CLIQUE est polynomial.

⸻

<a id="seance-10-exercice-6"></a>

##### 6. Problèmes d’optimisation : trouver une solution optimale

On considère maintenant :

* MAX-CLIQUE : trouver une clique maximale ;
* MAX-INDEPENDENT-SET : trouver un stable maximal ;
* MIN-VERTEX-COVER : trouver une couverture minimale.

Attention : ici on ne demande plus seulement la taille, mais l’ensemble lui-même.

Équivalence entre les trois problèmes

MAX-CLIQUE et MAX-INDEPENDENT-SET

Une clique dans G correspond à un stable dans \bar G.

Donc si on sait résoudre MAX-INDEPENDENT-SET, on peut résoudre MAX-CLIQUE en appliquant l’algorithme à \bar G.

Et inversement.

Donc :

$$
\text{MAX-CLIQUE} \equiv_P \text{MAX-INDEPENDENT-SET}.
$$

MAX-INDEPENDENT-SET et MIN-VERTEX-COVER

Si S est un stable maximum, alors :

V-S

est une couverture minimale.

Inversement, si C est une couverture minimale, alors :

V-C

est un stable maximum.

Donc :

$$
\text{MAX-INDEPENDENT-SET} \equiv_P \text{MIN-VERTEX-COVER}.
$$

Conclusion

Les trois problèmes d’optimisation sont polynomialement équivalents.

Donc si l’un n’admet pas d’algorithme polynomial, alors aucun des trois n’en admet.

⸻

Que dire si CLIQUE décision est polynomial ?

Si CLIQUE décision est polynomial, alors on peut non seulement calculer la taille maximale d’une clique, mais aussi
trouver une clique maximale.

Méthode constructive

On commence avec le graphe G et la taille optimale \omega(G).

Pour reconstruire une clique :

1. Prendre un sommet v.
2. Tester s’il existe encore une clique optimale contenant v.
3. Si oui, garder v et restreindre le graphe aux voisins de v.
4. Sinon, supprimer v.
5. Répéter.

Chaque étape utilise l’algorithme de décision CLIQUE.

Comme il y a au plus n sommets, on fait un nombre polynomial d’appels.

Donc si CLIQUE décision est polynomial, alors MAX-CLIQUE est polynomial.

Par équivalence, MAX-INDEPENDENT-SET et MIN-VERTEX-COVER sont aussi polynomiaux.

Conclusion

Si CLIQUE décision est polynomial, alors les trois problèmes d’optimisation sont polynomiaux.

⸻

<a id="seance-10-exercice-7"></a>

##### 7. Autre représentation du graphe

Le graphe est représenté par :

* un entier n ;
* une méthode existeArete(i,j) ;
* un itérateur sur les m arêtes.

7.a) Justifier la taille de représentation

Chaque sommet est un entier entre 0 et n-1.

Pour encoder un sommet, il faut :

O(\log n)

bits.

Pour encoder une arête (i,j), il faut encoder deux sommets, donc :

O(\log n)+O(\log n)=O(\log n).

S’il y a m arêtes, encoder toutes les arêtes prend :

O(m\log n)

bits.

On doit aussi encoder n, ce qui prend :

O(\log n).

Donc une représentation naturelle prend :

O(\log n + m\log n)

bits.

Mais on peut aussi encoder le complément si le graphe est dense. Le nombre de non-arêtes est :

\frac{n(n-1)}{2}-m.

Donc on encode le plus petit des deux ensembles :

\min\left(m,\frac{n(n-1)}{2}-m\right).

La taille devient :

O\left(\log n+\min\left(m,\frac{n(n-1)}{2}-m\right)\log n\right).

C’est polynomial en :

m+\log n.

Intuition

Si le graphe est clairsemé, on liste ses arêtes.

Si le graphe est très dense, il est plus efficace de lister ses non-arêtes.

⸻

7.b) Les résultats précédents restent-ils valides ?

Il faut être prudent.

Avec une matrice d’adjacence, construire le complémentaire \bar G est polynomial en n^2, donc en la taille d’entrée.

Mais avec cette nouvelle représentation, si le graphe est très clairsemé, son complémentaire peut avoir :

\Theta(n^2)

arêtes.

Or la taille d’entrée peut être seulement :

O(m\log n).

Si m est petit, produire explicitement \bar G peut être exponentiellement plus grand que l’entrée, car n peut être
énorme relativement à \log n.

Donc les réductions qui construisent explicitement \bar G ne sont plus forcément polynomiales en la taille de cette
représentation.

Résultat

Les réductions utilisant seulement V-S, comme :

$$
\text{INDEPENDENT-SET} \leq_P \text{VERTEX-COVER},
$$

restent valides.

Mais les réductions passant par le complémentaire doivent être justifiées avec soin. Elles ne sont pas automatiquement
valides si on doit matérialiser explicitement toutes les arêtes du complémentaire.

Idée clé

Changer la représentation d’un graphe peut changer la complexité des transformations.

⸻

<a id="seance-10-exercice-8"></a>

##### 2. Programmation linéaire en nombres entiers et ordonnancement

On considère le problème ORDONNANCEMENT :

Entrée :

* m machines identiques ;
* n tâches indépendantes ;
* durées entières t_1,\dots,t_n ;
* borne L.

Question :

Existe-t-il un ordonnancement de durée totale au plus L ?

Autrement dit : peut-on répartir les tâches sur les machines de sorte que la charge maximale d’une machine soit au plus
L ?

⸻

<a id="seance-10-exercice-9"></a>

##### 1. Taille de l’entrée

Reformulation

On veut évaluer combien de bits sont nécessaires pour écrire l’entrée.

L’entrée contient :

m,n,t_1,\dots,t_n,L.

Un entier x se code en :

\Theta(\log x)

bits.

Donc :

* m coûte \Theta(\log m) bits ;
* L coûte \Theta(\log L) bits ;
* chaque durée t_i coûte \Theta(\log t_i) bits ;
* il faut aussi représenter la liste des n tâches, ce qui ajoute un coût \Theta(n) pour la structure de la liste.

Donc la taille est :

$$
\Theta\left(\log m+n+\sum_{i=1}^{n}\log t_i+\log L\right).
$$

Dans l’énoncé, il y a écrit \log_2 L, ce qui signifie probablement logarithme en base 2 de L, pas (\log L)^2.

⸻

Pourquoi O(n^2m^3) est polynomial pour les valeurs non triviales de m

Un point subtil : comme m est codé en binaire, \log m fait partie de l’entrée, pas m directement.

Donc un algorithme polynomial en m n’est pas forcément polynomial en \log m.

Mais pour l’ordonnancement, si :

m>n,

alors il y a plus de machines que de tâches. Dans ce cas, chaque tâche peut être mise seule sur une machine, donc le
problème devient trivial :

$$
\max_i t_i \leq L.
$$

Les cas non triviaux vérifient donc :

m\leq n.

Alors :

O(n^2m^3)\leq O(n^2n^3)=O(n^5).

Comme n apparaît explicitement dans l’entrée, O(n^5) est polynomial en la taille de l’entrée.

Conclusion

Pour les valeurs non triviales, m\leq n, donc O(n^2m^3) est polynomial.

⸻

<a id="seance-10-exercice-10"></a>

##### 2. Montrer que \text{ORDONNANCEMENT} \leq_P \text{ILP}

Reformulation

On veut transformer une instance d’ordonnancement en une instance de programmation linéaire en nombres entiers.

Idée

On va créer des variables binaires :

x_{ij}

où :

x_{ij}=1

si la tâche i est affectée à la machine j, et :

x_{ij}=0

sinon.

⸻

Variables

Pour chaque tâche i\in\{1,\dots,n\} et chaque machine j\in\{1,\dots,m\}, on introduit :

x_{ij}\in\{0,1\}.

Il y a donc :

nm

variables.

⸻

Contraintes 1 : chaque tâche est affectée exactement une fois

Pour chaque tâche i :

$$
\sum_{j=1}^{m} x_{ij}=1.
$$

Cela force la tâche i à être placée sur une seule machine.

Comme l’ILP de l’énoncé utilise des contraintes de type :

$$
Ax\geq b
$$

on peut remplacer l’égalité par deux inégalités :

$$
\sum_{j=1}^{m} x_{ij}\geq 1
$$

et

-\sum_{j=1}^{m} x_{ij}\geq -1.

⸻

Contraintes 2 : chaque machine a une charge au plus L

Pour chaque machine j, la charge est :

$$
\sum_{i=1}^{n} t_i x_{ij}.
$$

On impose :

$$
\sum_{i=1}^{n} t_i x_{ij}\leq L.
$$

Sous forme Ax\geq b, on écrit :

-\sum_{i=1}^{n} t_i x_{ij}\geq -L.

⸻

Contraintes 3 : variables binaires

On veut :

x_{ij}\in\{0,1\}.

Comme les variables ILP sont entières et vérifient déjà x\geq 0, il suffit d’ajouter :

x_{ij}\leq 1.

Sous forme Ax\geq b :

-x_{ij}\geq -1.

Ainsi :

x_{ij}\in\mathbb Z,\quad x_{ij}\geq 0,\quad x_{ij}\leq 1

implique :

x_{ij}\in\{0,1\}.

⸻

Objectif

Le problème ILP de l’énoncé demande s’il existe x tel que :

$$
\langle c,x\rangle \leq k.
$$

Ici, on n’a pas vraiment besoin d’optimiser une fonction objectif. On peut prendre :

c=0

et :

k=0.

Alors :

$$
\langle c,x\rangle =0\leq 0
$$

est toujours vraie. Toute la difficulté est dans les contraintes.

⸻

Correction de la réduction

Si un ordonnancement existe

Alors pour chaque tâche i, on connaît sa machine j.

On pose :

x_{ij}=1

si la tâche i est sur la machine j, et 0 sinon.

Chaque tâche est affectée une fois, donc les contraintes d’affectation sont satisfaites.

Chaque machine a une charge au plus L, donc les contraintes de charge sont satisfaites.

Donc l’ILP est faisable.

Si l’ILP est faisable

Les contraintes binaires garantissent que chaque x_{ij} vaut 0 ou 1.

Les contraintes :

$$
\sum_{j=1}^{m}x_{ij}=1
$$

garantissent que chaque tâche est affectée à exactement une machine.

Les contraintes de charge garantissent que chaque machine a une durée totale au plus L.

Donc on obtient un ordonnancement de durée au plus L.

Conclusion

$$
\boxed{\text{ORDONNANCEMENT} \leq_P \text{ILP}}
$$

⸻

#### Résumé final de la feuille

Les exercices montrent que plusieurs problèmes classiques sur les graphes sont très étroitement liés :

$$
\text{CLIQUE}
$$
\equiv_P
$$
\text{INDEPENDENT-SET}
$$
\equiv_P
$$
\text{VERTEX-COVER}.
$$

Les liens principaux sont :

$$
S \text{ stable dans } G \iff S \text{ clique dans } \bar G
$$

et

S \text{ stable dans } G \iff V-S \text{ couverture dans } G.

Ensuite, la feuille montre qu’un problème d’ordonnancement peut être formulé comme une ILP grâce à des variables
binaires d’affectation.

#### Méthodes clés

* Passer au graphe complémentaire.
* Prendre le complément d’un ensemble de sommets.
* Transformer une instance (G,k) en une autre instance (G',k').
* Utiliser un problème de décision pour calculer une valeur optimale.
* Reconstruire une solution optimale à partir d’un oracle de décision.
* Encoder un choix combinatoire avec des variables binaires x_{ij}.

#### Formules importantes

$$
S \text{ stable dans } G \iff S \text{ clique dans } \bar G
$$

$$
S \text{ stable dans } G \iff V-S \text{ couverture dans } G
$$

\alpha(G)=\omega(\bar G)

\tau(G)=|V|-\alpha(G)

Pour l’ordonnancement :

$$
\sum_{j=1}^{m}x_{ij}=1
$$

$$
\sum_{i=1}^{n}t_i x_{ij}\leq L
$$

x_{ij}\in\{0,1\}

#### Pièges fréquents

* Confondre clique dans G et clique dans \bar G.
* Oublier de remplacer k par |V|-k dans la réduction vers VERTEX-COVER.
* Dire qu’une réduction est polynomiale sans vérifier la taille de la représentation.
* Confondre problème de décision et problème d’optimisation.
* En ILP, oublier d’imposer que chaque tâche est affectée exactement une fois.
* Oublier les contraintes x_{ij}\leq 1 pour forcer les variables à être binaires.

#### Questions d’entraînement

##### 1. Montrer que \text{VERTEX-COVER}\leq_P \text{INDEPENDENT-SET}.

    Réponse : transformer (G,k) en (G,|V|-k).

2. Si G a un stable de taille 7 et |V|=20, quelle couverture obtient-on ?
   Réponse : une couverture de taille 13.
3. Si \bar G a une clique de taille 5, que peut-on dire de G ?
   Réponse : G a un stable de taille 5.
4. Dans l’ILP d’ordonnancement, que signifie x_{ij}=1 ?
   Réponse : la tâche i est affectée à la machine j.
5. Pourquoi impose-t-on \sum_j x_{ij}=1 ?
   Réponse : pour garantir que chaque tâche est affectée à exactement une machine.

---

<a id="seance-11"></a>

## Séance 11 — Complexité partie 2 : SAT, inapproximabilité et P-complétude

> Plage source conservée : lignes `5773` à `6501` de `course.txt`.

### Partie Théorique

C'est la dernière ligne droite avec cette onzième séance ! La théorie de la complexité est abstraite et peut donner des
sueurs froides, mais vos notes sont excellentes.

Je vous rassure tout de suite concernant votre annotation personnelle sur le Théorème de Cook : **vous avez parfaitement
raison**. Apprendre par cœur la traduction d'une Machine de Turing en formule booléenne n'a aucun intérêt pour un examen
d'ingénieur. Ce qu'il faut retenir, c'est *l'implication* de ce théorème.

Voici votre cours détaillé, mis au propre et organisé, incluant les notions du TD sur les classes d'espace et la
P-complétude.

---

### Séance 11 : Complexité (Partie 2) - SAT, Inapproximabilité et P-Complétude

**Objectif de la séance :** Identifier le "Père" de tous les problèmes difficiles (le problème SAT via le Théorème de
Cook), comprendre pourquoi l'approximation a ses limites mathématiques, et introduire les classes de complexité liées à
la mémoire (L, NL) et au parallélisme (NC).

#### 1. Le Théorème de Cook-Levin : SAT est NP-Complet

Pour prouver qu'un problème est NP-Complet, il faut montrer qu'il est dans la classe **NP** ET qu'il est **NP-Difficile
**. Mais comment prouver qu'un problème est le *tout premier* problème NP-Difficile, puisqu'on ne peut le réduire à
partir d'aucun autre ? C'est l'exploit du Théorème de Cook.

Le problème **SAT** (Satisfaisabilité Booléenne) : Étant donné une formule logique en forme normale conjonctive (CNF),
par exemple $(x_1 \lor \neg x_2) \land (\neg x_1 \lor x_3)$, est-il possible d'assigner les valeurs Vrai/Faux aux
variables pour que la formule globale soit Vraie ?

* **Étape 1 : SAT est dans NP.** Le certificat est simplement le choix des valeurs (Vrai/Faux) pour chaque variable
  booléenne. Un algorithme vérificateur déterministe peut remplacer les variables par ces valeurs et évaluer la formule
  en un temps polynomial.
* **Étape 2 : SAT est NP-Difficile.**
  C'est la démonstration historique de Cook. Il a prouvé que **n'importe quel calcul** effectué par une Machine de
  Turing Non-Déterministe (ruban, états, tête de lecture, règles de transition) pouvait être traduit mathématiquement
  sous la forme d'une immense formule booléenne SAT.
* **Conclusion :** Si une machine non-déterministe trouve une solution à un problème en temps polynomial (définition de
  NP), alors la formule SAT correspondante est satisfiable. Résoudre SAT revient donc à pouvoir simuler n'importe quelle
  machine NP. **SAT est le problème originel NP-Complet.**

> **Note stratégique pour l'examen :** Ne retenez pas la démonstration de traduction de la Machine de Turing. Retenez
> simplement que la structure même de l'informatique (des bits qui changent d'état selon des portes logiques) se modélise
> parfaitement avec la logique booléenne de SAT.

---

#### 2. Les Limites de l'Approximation (Inapproximabilité)

Dans les premières séances, nous avons vu que face à un problème NP-Complet, on pouvait chercher une solution
approchée (algorithmes gloutons, PTAS, etc.). Mais la théorie de la complexité pose une limite stricte à cette
technique.

**Le concept :** Même si l'on se contente d'une solution "à peu près bonne", certains problèmes NP-Complets refusent de
se laisser approcher en temps polynomial, **à moins que P = NP**. Les preuves d'inapproximabilité reposent toutes sur l'
hypothèse (très probable) que P et NP sont différents.

| Problème                 | Statut d'Approximation | Limite d'Inapproximabilité                                                                                                                                                  |
|:-------------------------|:-----------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Sac à Dos (Knapsack)** | Très bonne             | Possède un PTAS (Schéma d'Approximation en Temps Polynomial). On peut s'approcher de l'optimum d'aussi près qu'on veut $(1 + \epsilon)$.                                    |
| **Vertex Cover**         | Moyenne                | On connaît une 2-approximation simple (vue en séance 1). Cependant, il est mathématiquement prouvé qu'on ne pourra jamais faire mieux qu'un ratio de 1.36 (sauf si P = NP). |
| **Clique**               | Catastrophique         | Il n'existe aucune approximation avec un ratio constant ou même logarithmique. C'est du "tout ou rien".                                                                     |

---

#### 3. Au-delà du Temps : Les Classes d'Espace (L et NL)

Le TD introduit une nouvelle contrainte : la mémoire (l'espace). On ne compte plus le temps de calcul, mais la quantité
de mémoire de travail utilisée.

Pour analyser finement l'espace, le modèle de la Machine de Turing est modifié en 3 zones distinctes :

* **Mémoire A (Lecture seule) :** Contient les données d'entrée de taille $n$.
* **Mémoire C (Écriture seule) :** Contient le résultat final.
* **Mémoire B (Lecture/Écriture) :** C'est la seule mémoire qui compte dans le calcul de complexité spatiale !

**Les classes :**

* **L (Espace Logarithmique Déterministe) :** Problèmes pouvant être résolus avec une mémoire de travail B de
  taille $O(\log n)$.
* **NL (Espace Logarithmique Non-Déterministe) :** Même chose, mais sur une machine non-déterministe.

> **Pourquoi le Logarithme ?** > $O(\log n)$ est l'espace juste suffisant pour stocker des *pointeurs* ou des
*indices* (des adresses) pointant vers la mémoire d'entrée A. Un algorithme en espace logarithmique ne peut stocker
> qu'un nombre constant de variables (compteurs, indices) et ne peut absolument pas copier l'entrée.

---

#### 4. P-Complétude et Réductions Parallèles (NC)

Le TD de cette séance aborde un concept crucial : **Qu'est-ce qu'un problème intrinsèquement séquentiel ?**

* La classe **NC (Nick's Class)** regroupe les problèmes résolubles très rapidement en parallèle (temps
  polylogarithmique $O(\log^k n)$) en utilisant un nombre polynomial de processeurs $O(n^p)$. Ce sont les problèmes "
  faciles à paralléliser".
* Un problème est **P-Complet** s'il est dans P, et que tous les autres problèmes de P peuvent s'y réduire via une *
  *réduction parallèle** (ou log-space).

**L'implication :** Si un problème est P-Complet, il est considéré comme **impossible à paralléliser efficacement**.
Chaque étape de son calcul dépend strictement du résultat de l'étape précédente.

##### L'Exemple du TD : HORN-SAT est P-Complet

Votre TD le démontre en utilisant le problème de l'évaluation de circuit (MCVP - *Monotone Circuit Value Problem*), qui
est le problème P-Complet de référence.

On transforme les portes logiques d'un circuit en clauses de Horn (une clause de Horn est une clause SAT avec **au plus
un seul littéral positif**) :

* Une porte ET ($g_i = g_j \text{ AND } g_k$) se traduit en logique classique par $(g_j \land g_k) \Rightarrow g_i$.
* En logique booléenne, cela s'écrit $\neg g_j \lor \neg g_k \lor g_i$.
* Cette expression contient deux littéraux négatifs et un seul littéral positif : c'est bien une clause de Horn
  parfaite !

Puisque l'on peut transformer n'importe quel circuit booléen arbitraire (MCVP) en un problème HORN-SAT à l'aide d'une
simple transformation de portes (faisable en espace logarithmique), on prouve que **HORN-SAT est P-Complet**. Il est
donc résoluble en temps polynomial, mais terriblement rebelle à la parallélisation.

### Partie Pratique (TD)

#### Vue d’ensemble de la feuille

Cette feuille traite deux blocs de complexité avancée : d’abord les classes L et NL, c’est-à-dire les problèmes
décidables avec très peu de mémoire, puis les classes liées au calcul parallèle, notamment NC et la P-complétude. Les
exercices demandent de manipuler des réductions en espace logarithmique, de montrer que le problème d’accessibilité dans
un graphe est NL-complet, puis de prouver que HORN-SAT est dans P et même P-complet via une réduction depuis MCVP.

1. Partie NL

<a id="seance-11-exercice-1"></a>

##### Exercice 1 — Taille de la sortie d’un algorithme en espace logarithmique

Problème reformulé

Un algorithme utilise :

* une mémoire d’entrée A, en lecture seule ;
* une mémoire de travail B, en lecture/écriture ;
* une mémoire de sortie C, en écriture seule.

L’algorithme est en espace mémoire logarithmique si la mémoire de travail B utilise seulement O(\log n) mots/bits, où n
est la taille de l’entrée. On demande de montrer que la sortie produite dans C a une taille polynomiale en n.

Idée

Même si la mémoire de sortie C peut être grande, l’algorithme ne doit pas pouvoir écrire une sortie de taille
exponentielle sans tourner trop longtemps. En complexité standard, un algorithme de décision ou de réduction en espace
logarithmique est supposé avoir un nombre polynomial de configurations utiles, sinon il boucle.

Raisonnement

La mémoire de travail contient seulement :

O(\log n)

bits.

Donc le nombre de contenus possibles de B est :

2^{O(\log n)} = n^{$O(1)$}.

Autrement dit, il y a seulement un nombre polynomial de configurations possibles de la mémoire de travail.

Une configuration complète utile contient aussi :

* la position de lecture dans A, codable en O(\log n) bits ;
* la position d’écriture dans C, tant que la sortie reste polynomiale ;
* l’état courant de l’algorithme, de taille constante.

Si un algorithme déterministe revient deux fois dans la même configuration sans avoir progressé utilement, il boucle.
Donc, dans un calcul qui termine, le nombre d’étapes utiles est borné par un polynôme.

Comme chaque étape écrit au plus une quantité constante dans C, la taille finale de C est polynomiale.

Conclusion

La sortie d’un algorithme en espace logarithmique est de taille :

O(p(n))

pour un certain polynôme p.

Piège classique

Ne pas dire : “la sortie est logarithmique parce que la mémoire de travail est logarithmique”.

C’est faux. La sortie peut être plus grande que O(\log n), mais elle reste polynomiale.

⸻

<a id="seance-11-exercice-2"></a>

##### Exercice 2 — Montrer que \{a^n b^n : n\geq 0\}\in L

Problème reformulé

On veut décider si un mot est de la forme :

a^n b^n

c’est-à-dire une suite de a, suivie d’une suite de b, avec autant de a que de b.

Exemples acceptés :

\varepsilon,\ ab,\ aabb,\ aaabbb.

Exemples rejetés :

aab,\ abb,\ aba,\ ba.

Ce qu’il faut montrer

Il faut construire un algorithme déterministe utilisant seulement O(\log n) mémoire.

Stratégie

On n’a pas besoin de stocker tout le mot. Il suffit de :

1. vérifier que le mot est bien de la forme a^*b^* ;
2. compter le nombre de a ;
3. compter le nombre de b ;
4. comparer les deux compteurs.

Un compteur allant jusqu’à n se code en :

O(\log n)

bits.

Algorithme

Sur l’entrée x de longueur N :

1. Parcourir le mot de gauche à droite.
2. Compter le nombre de a jusqu’au premier b.
3. Dès qu’on a vu un b, vérifier qu’aucun a ne réapparaît.
4. Compter le nombre de b.
5. Accepter si les deux compteurs sont égaux.

Mémoire utilisée

On stocke :

* un compteur c_a, entre 0 et N ;
* un compteur c_b, entre 0 et N ;
* un bit indiquant si on est dans la zone des a ou des b.

Chaque compteur prend :

O(\log N)

bits.

Donc la mémoire totale est :

O(\log N).

Conclusion

$$
\boxed{\{a^n b^n : n\geq 0\}\in L}
$$

Erreur classique

Confondre avec les automates finis : le langage \{a^n b^n\} n’est pas régulier, mais il est décidable en espace
logarithmique car un algorithme en L peut utiliser des compteurs logarithmiques.

⸻

<a id="seance-11-exercice-3"></a>

##### Exercice 3 — Montrer que CHEMIN appartient à NL

Problème reformulé

Le problème CHEMIN prend en entrée :

* un graphe G ;
* deux sommets s et t.

La question est :

Existe-t-il un chemin de s à t ?

On veut montrer que ce problème est dans NL, c’est-à-dire qu’il existe un algorithme non déterministe utilisant O(\log
n) mémoire.

Stratégie

Un algorithme non déterministe peut “deviner” le chemin sommet par sommet.

Il n’a pas besoin de stocker tout le chemin. Il suffit de stocker :

* le sommet courant ;
* un compteur de longueur pour éviter les boucles infinies.

Algorithme non déterministe

Entrée : G,s,t.

1. Mettre u=s.
2. Pour au plus |V| étapes :
    * si u=t, accepter ;
    * deviner un voisin v de u ;
    * remplacer u par v.
3. Si t n’a pas été atteint, rejeter.

Pourquoi au plus |V| étapes ?

S’il existe un chemin de s à t, alors il existe un chemin simple de s à t, c’est-à-dire sans répétition de sommets.

Un chemin simple contient au plus :

|V|-1

arêtes.

Donc inutile de chercher plus longtemps.

Mémoire utilisée

On stocke :

* le sommet courant u, codé en O(\log |V|) bits ;
* le sommet deviné v, codé en O(\log |V|) bits ;
* un compteur jusqu’à |V|, codé en O(\log |V|) bits.

Donc l’espace total est :

O(\log |V|).

Conclusion

$$
\boxed{\text{CHEMIN}\in NL}
$$

⸻

<a id="seance-11-exercice-4"></a>

##### Exercice 4 — Montrer que X\leq_L Y et Y\in L implique X\in L

Problème reformulé

On suppose :

X\leq_L Y.

Cela signifie qu’il existe une fonction f, calculable en espace logarithmique, telle que :

x\in X \iff f(x)\in Y.

On suppose aussi que Y est décidable en espace logarithmique.

On veut montrer que X est aussi décidable en espace logarithmique.

Difficulté importante

On ne peut pas forcément calculer f(x) entièrement puis la stocker, car f(x) peut être de taille polynomiale, alors que
notre mémoire de travail est seulement logarithmique.

Stratégie

On simule l’algorithme de Y sur l’entrée virtuelle f(x).

Chaque fois que l’algorithme de Y veut lire une case de f(x), on recalcule cette case à la demande avec l’algorithme de
réduction.

Raisonnement

Soit M_Y une machine en espace logarithmique qui décide Y.

Pour décider X sur entrée x, on veut exécuter :

M_Y(f(x)).

Mais au lieu d’écrire tout f(x), on fournit à M_Y un accès simulé à f(x).

Quand M_Y demande le symbole numéro i de f(x), on lance la machine qui calcule f, et on la fait tourner jusqu’à produire
le i-ème symbole.

La mémoire utilisée est :

* O(\log |x|) pour simuler la réduction ;
* O(\log |f(x)|) pour simuler M_Y.

Comme f(x) est de taille polynomiale en |x|, on a :

\log |f(x)| = O(\log |x|).

Donc la mémoire totale reste :

O(\log |x|).

Conclusion

$$
\boxed{X\leq_L Y \text{ et } Y\in L \implies X\in L}
$$

Erreur classique

Dire simplement : “on calcule f(x), puis on lance l’algorithme de Y”.

Ce n’est pas correct en espace logarithmique, car f(x) peut être trop grand pour être stocké.

⸻

<a id="seance-11-exercice-5"></a>

##### Exercice 5 — Montrer que CHEMIN est NL-complet et en déduire NL\subseteq P

Problème reformulé

On veut montrer que CHEMIN est le problème central de NL.

Pour cela, il faut montrer :

1. CHEMIN appartient à NL, déjà fait.
2. Tout problème X\in NL se réduit à CHEMIN en espace logarithmique.

Stratégie

On prend un algorithme non déterministe en espace logarithmique pour X.

Pour une entrée x, on construit un graphe des configurations de calcul.

Les sommets sont les configurations possibles de la machine.

Il y a une arête d’une configuration C vers une configuration C' si la machine peut passer de C à C' en une étape.

Alors :

$$
x\in X
$$

ssi il existe un chemin de la configuration initiale vers une configuration acceptante.

Qu’est-ce qu’une configuration ?

Une configuration contient toute l’information nécessaire pour continuer le calcul :

* l’état courant de la machine ;
* les contenus de la mémoire de travail ;
* les positions des têtes de lecture/écriture ;
* éventuellement des informations sur la sortie si nécessaire.

L’énoncé précise que la taille d’une configuration est O(p(n)) dans leur modèle, avec p polynôme.

Dans le modèle standard pour NL, le nombre de configurations est polynomial, car la mémoire de travail est
logarithmique.

Construction du graphe

Pour une entrée x, on définit un graphe G_x :

* chaque sommet est une configuration possible de la machine sur x ;
* il y a un arc C\to C' si C' est atteignable depuis C en une étape de calcul.

On note :

* C_{\text{init}} la configuration initiale ;
* C_{\text{acc}} une configuration acceptante.

Alors :

$$
x\in X
$$
$$
\iff
$$
$$
\text{il existe un chemin de } C_{\text{init}} \text{ à } C_{\text{acc}} \text{ dans } G_x.
$$

Pourquoi la réduction est en espace logarithmique ?

On n’a pas besoin de construire tout G_x explicitement.

Pour produire une arête (C,C'), il suffit de vérifier localement si C' est un successeur légal de C.

Cette vérification utilise seulement la description de la machine, l’entrée x, et les deux configurations codées.

Cela se fait en espace logarithmique.

Conclusion : CHEMIN est NL-dur

Pour tout problème X\in NL, on a :

X\leq_L \text{CHEMIN}.

Comme CHEMIN est aussi dans NL, on obtient :

$$
\boxed{\text{CHEMIN est } NL\text{-complet}}
$$

⸻

En déduire que NL\subseteq P

Le graphe des configurations a un nombre polynomial de sommets.

Pourquoi ?

Parce qu’une configuration utilise O(\log n) mémoire de travail dans le modèle standard, donc le nombre de
configurations possibles est :

2^{O(\log n)}=n^{$O(1)$}.

On peut alors résoudre le problème d’accessibilité dans ce graphe en temps polynomial, par exemple avec :

* BFS ;
* DFS ;
* Warshall ;
* exploration exhaustive.

Donc tout problème de NL peut être résolu en temps polynomial.

Conclusion :

$$
\boxed{NL\subseteq P}
$$

Attention : l’énoncé rappelle que la question NL=P est ouverte. On sait :

$$
L\subseteq NL\subseteq P,
$$

mais on ne sait pas si ces inclusions sont strictes.

⸻

2. Partie NC

<a id="seance-11-exercice-6"></a>

##### Exercice 1 — Montrer que HORN-SAT appartient à P

Problème reformulé

Une clause de Horn est une clause contenant au plus un littéral positif.

Exemples :

(x)

(\neg x\vee \neg y)

(\neg x\vee \neg y\vee \neg z\vee t)

La dernière peut se réécrire :

(x\wedge y\wedge z)\Rightarrow t.

On veut montrer que la satisfaisabilité d’un ensemble de clauses de Horn se décide en temps polynomial.

Idée principale

Les clauses de Horn peuvent être vues comme des règles d’implication.

Une clause :

(\neg x_1\vee \neg x_2\vee \dots \vee \neg x_k \vee y)

équivaut à :

(x_1\wedge x_2\wedge \dots \wedge x_k)\Rightarrow y.

Une clause sans littéral positif :

(\neg x_1\vee \dots \vee \neg x_k)

équivaut à :

(x_1\wedge \dots \wedge x_k)\Rightarrow \text{faux}.

Algorithme polynomial

On utilise l’algorithme de propagation avant.

1. Initialiser toutes les variables à faux.
2. Pour chaque clause de type :
   (x_1\wedge \dots \wedge x_k)\Rightarrow y,
   si tous les x_i sont vrais, alors rendre y vrai.
3. Répéter jusqu’à stabilisation.
4. Si une clause de type :
   (x_1\wedge \dots \wedge x_k)\Rightarrow \text{faux}
   a tous ses antécédents vrais, alors l’ensemble est insatisfaisable.
5. Sinon, il est satisfaisable.

Pourquoi ça marche ?

On commence avec l’affectation minimale : toutes les variables à faux.

Puis on force à vrai uniquement les variables qui doivent nécessairement être vraies à cause des clauses unitaires ou
des implications.

Si on arrive à une contradiction, aucune affectation ne peut satisfaire la formule.

Sinon, l’affectation obtenue satisfait toutes les clauses.

Complexité

Chaque variable peut passer de faux à vrai au plus une fois.

Donc il y a au plus n changements de valeur.

En parcourant naïvement les clauses après chaque changement, on obtient un temps polynomial, par exemple :

O(nm)

où :

* n est le nombre de variables ;
* m est le nombre de clauses.

Il existe même des implémentations linéaires, mais O(nm) suffit pour montrer l’appartenance à P.

Conclusion

$$
\boxed{\text{HORN-SAT}\in P}
$$

Piège classique

Ne pas appliquer l’algorithme général de SAT. SAT est NP-complet, mais HORN-SAT est beaucoup plus structuré.

⸻

<a id="seance-11-exercice-7"></a>

##### Exercice 2 — Montrer que HORN-SAT est P-complet

Problème reformulé

On admet que MCVP, le problème d’évaluation d’un circuit booléen monotone, est P-complet.

On veut montrer que HORN-SAT est P-complet.

Pour cela, il faut montrer deux choses :

1. HORN-SAT appartient à P.
2. MCVP se réduit à HORN-SAT par une réduction NC.

Le premier point vient de l’exercice précédent.

Il reste donc à montrer :

$$
\text{MCVP}\leq_{NC}\text{HORN-SAT}.
$$

Rappel de MCVP

L’entrée est une suite :

g_1,\dots,g_n

où chaque g_i est défini par :

1. g_i := vrai
2. g_i := faux
3. g_i := g_j \vee g_k, avec j,k<i
4. g_i := g_j \wedge g_k, avec j,k<i

La question est :

g_n \text{ vaut-il vrai ?}

Construction donnée par l’énoncé

On associe à chaque porte g_i une variable booléenne g_i.

L’énoncé donne une traduction vers des clauses de Horn. Attention : elle utilise une convention inversée. On admet que :

C \text{ s’évalue à vrai}
$$
\iff
$$
H \text{ est satisfiable avec } g_n=faux.

Puis on ajoute une clause imposant g_n=faux.

Idée intuitive

On encode les relations logiques entre les portes par des clauses de Horn.

Une clause de Horn représente une implication :

(a\wedge b)\Rightarrow c.

C’est bien adapté pour simuler les portes ET/OU monotones.

Réduction

À partir du circuit C, on construit en parallèle un ensemble H de clauses de Horn.

Pour chaque porte g_i, on crée une ou plusieurs clauses selon son type.

L’énoncé donne explicitement cette construction :

* si g_i:=vrai, on ajoute une clause associée ;
* si g_i:=faux, on ajoute une clause associée ;
* si g_i:=g_j\vee g_k, on ajoute une clause d’implication ;
* si g_i:=g_j\wedge g_k, on ajoute deux clauses d’implication.

Puis on ajoute la clause imposant la condition sur g_n, de manière à ce que :

$$
g_n \text{ vaut vrai dans le circuit}
$$
$$
\iff
$$
H' \text{ est satisfaisable}.

où :

H'=H\cup\{\text{clause imposant }g_n=faux\}.

Pourquoi la réduction est en NC ?

Chaque porte g_i est traduite indépendamment des autres.

Donc on peut construire toutes les clauses en parallèle.

Pour chaque i, un processeur ou un petit groupe de processeurs lit la description de g_i et écrit les clauses
correspondantes.

Le temps parallèle est polylogarithmique, même O(\log^k n), avec un nombre polynomial de processeurs.

Donc la transformation est une réduction NC.

Preuve de P-complétude

On sait :

$$
\text{HORN-SAT}\in P.
$$

On admet :

$$
\text{MCVP est } P\text{-complet}.
$$

Donc tout problème X\in P se NC-réduit à MCVP :

X\leq_{NC}\text{MCVP}.

Et on vient de montrer :

$$
\text{MCVP}\leq_{NC}\text{HORN-SAT}.
$$

Par transitivité :

X\leq_{NC}\text{HORN-SAT}.

Donc HORN-SAT est P-dur pour les réductions NC.

Comme HORN-SAT est aussi dans P, on obtient :

$$
\boxed{\text{HORN-SAT est } P\text{-complet}}
$$

⸻

#### Résumé final de la feuille

La première partie montre que les problèmes décidables en espace logarithmique non déterministe peuvent être représentés
comme des problèmes de chemin dans un graphe de configurations. Le problème CHEMIN est donc NL-complet, et on en
déduit :

NL\subseteq P.

La seconde partie montre que HORN-SAT est polynomial grâce à un algorithme de propagation, puis qu’il est P-complet car
MCVP, déjà P-complet, se réduit à HORN-SAT en parallèle.

#### Méthodes et techniques clés

* Utiliser des compteurs en O(\log n) espace.
* Deviner un chemin sommet par sommet en NL.
* Construire le graphe des configurations d’une machine.
* Simuler une réduction sans stocker toute sa sortie.
* Traduire des clauses de Horn en implications.
* Utiliser la propagation avant pour HORN-SAT.
* Prouver une P-complétude via une réduction depuis un problème déjà P-complet.

Résultats importants

L\subseteq NL\subseteq P.

$$
\text{CHEMIN est } NL\text{-complet}.
$$

$$
\text{HORN-SAT}\in P.
$$

$$
\text{HORN-SAT est } P\text{-complet}.
$$

Une clause de Horn :

(\neg x_1\vee \dots \vee \neg x_k\vee y)

équivaut à :

(x_1\wedge \dots \wedge x_k)\Rightarrow y.

#### Pièges fréquents

* Croire qu’un algorithme en espace logarithmique ne peut produire qu’une sortie logarithmique.
* Stocker explicitement f(x) dans une réduction L, alors qu’il faut la recalculer à la demande.
* Oublier le compteur de longueur dans l’algorithme non déterministe pour CHEMIN.
* Confondre SAT et HORN-SAT : SAT est difficile, HORN-SAT est dans P.
* Oublier qu’une preuve de P-complétude demande deux choses : appartenance à P et P-dureté.

#### Questions d’entraînement

1. Pourquoi \{a^n b^n\}\notin régulier mais appartient à L ?
   Réponse : un automate fini ne peut pas compter, mais une machine en L peut utiliser des compteurs de taille O(\log
   n).
2. Pourquoi CHEMIN est dans NL ?
   Réponse : on devine non déterministiquement les sommets du chemin en ne stockant que le sommet courant et un
   compteur.
3. Pourquoi NL\subseteq P ?
   Réponse : une machine en espace logarithmique a seulement polynomialement beaucoup de configurations, qu’on peut
   explorer en temps polynomial.
4. Donne la forme implicationnelle de (\neg x\vee \neg y\vee z).
   Réponse : (x\wedge y)\Rightarrow z.
5. Pourquoi HORN-SAT est-il dans P ?
   Réponse : parce qu’on peut propager les variables forcées à vrai jusqu’à stabilisation et détecter les contradictions
   en temps polynomial.

---

<a id="seance-12"></a>

## Séance 12 — Complexité 3 : arbre des réductions et inapproximabilité

> Plage source conservée : lignes `6502` à `7416` de `course.txt`.

### Partie Théorique

C'est la dernière étape de votre voyage au cœur de la complexité algorithmique ! Cette séance 12 vient couronner le tout
en liant la théorie fondamentale (le Théorème de Cook) à la pratique (comment prouver qu'un problème est NP-complet par
réduction) et, surtout, en démontrant une limite mathématique fascinante : **l'inapproximabilité**.

Puisque vous m'avez fourni le TD et sa correction, nous allons construire ce cours directement autour des preuves
magistrales qu'ils contiennent. C'est la meilleure façon de comprendre.

Voici votre cours détaillé et structuré pour la Séance 12.

---

### Séance 12 : Complexité 3 - L'Arbre des Réductions et l'Inapproximabilité

**Objectif de la séance :** Comprendre comment le Théorème de Cook a permis de créer un "arbre généalogique" des
problèmes NP-Complets, apprendre à rédiger des réductions de Karp (Partition, Ordonnancement), et découvrir la technique
de la "Gap Reduction" (réduction avec écart) pour prouver qu'un problème ne peut même pas être approché.

#### 1. Le Théorème de Cook et l'Arbre des Réductions (Rappel Rapide)

Comme vu à la séance précédente, Stephen Cook a prouvé que **SAT est NP-Complet** en traduisant le fonctionnement d'une
machine de Turing en formule logique.

Pourquoi est-ce si important ? Parce que cela nous évite d'avoir à refaire cette preuve monstrueuse ! Pour prouver qu'un
nouveau problème $B$ est NP-Complet, il suffit désormais de faire une **Réduction de Karp** depuis un problème $A$ déjà
connu comme étant NP-Complet ($A \le_p B$).

L'arbre généalogique ressemble à ceci :
`SAT $\rightarrow$ 3-SAT $\rightarrow$ Coloration de Graphes`
`3-SAT $\rightarrow$ Clique $\rightarrow$ Vertex Cover $\rightarrow$ Cycle Hamiltonien $\rightarrow$ Voyageur de Commerce`
`3-SAT $\rightarrow$ Somme (Subset Sum) $\rightarrow$ Partition $\rightarrow$ Ordonnancement / Sac à dos`

Votre TD explore précisément cette dernière branche (les problèmes numériques) et la branche du Voyageur de Commerce.

---

#### 2. Prouver la NP-Complétude en Pratique (Exercice 1 du TD)

Pour prouver qu'un problème $\Pi$ est NP-complet, il y a **toujours deux étapes obligatoires** :

1. **Montrer que $\Pi \in NP$ :** Il faut proposer un "certificat" et montrer qu'on peut le vérifier en temps
   polynomial.
2. **Montrer que $\Pi$ est NP-Difficile :** Choisir un problème $A$ déjà connu comme NP-complet, et construire une
   fonction de réduction $f$ telle que $A \le_p \Pi$ en temps polynomial.

##### Exemple : Preuve que le problème "Ordonnancement" est NP-Complet

* **Le problème (Ordonnancement) :** Étant donné $n$ tâches de durées $a_i$, peut-on les répartir sur $k$ machines pour
  que tout soit fini en un temps maximum $d$ ?
* **Le problème source connu (Partition) :** Étant donné $n$ entiers, peut-on les séparer en 2 sous-ensembles de somme
  identique ?

**Étape 1 : Ordonnancement est dans NP**

* *Le certificat :* Un tableau indiquant pour chaque tâche la machine (de $1$ à $k$) sur laquelle elle est affectée.
* *Le vérifieur :* Un algorithme qui fait la somme des durées pour chaque machine et vérifie que la plus grande somme
  est $\le d$. Cela se fait par une simple boucle, donc en temps polynomial.

**Étape 2 : Partition $\le_p$ Ordonnancement**
Nous devons transformer une instance de *Partition* en une instance *d'Ordonnancement*.

* Prenons les objets $a_1, ..., a_n$ de notre problème de Partition.
* Créons une instance d'Ordonnancement en définissant le nombre de machines $k = 2$.
* Fixons la durée limite $d = \frac{1}{2} \sum_{i=1}^{n} a_i$.
* *Preuve de validité :* Si l'ordonnancement est possible, les tâches sont réparties sur 2 machines sans dépasser $d$.
  Puisque la somme totale est $2d$, chaque machine doit exécuter *exactement* une somme $d$ de tâches. Les tâches
  affectées à la machine 1 forment donc le premier sous-ensemble de la Partition, et celles de la machine 2 le second.
  La réduction est triviale, rapide, et prouve que l'Ordonnancement est NP-Complet !

---

#### 3. L'Inapproximabilité et la "Gap Reduction" (Exercice 2 du TD)

C'est le concept le plus puissant de cette séance. Face à un problème NP-Complet, on se dit souvent "tant pis pour la
solution exacte, je vais coder un algorithme d'approximation".

Le TD démontre que pour le problème du **Voyageur de Commerce (TSP)** général, **c'est mathématiquement impossible** (
sauf si P = NP).

##### La démonstration par l'absurde ("Gap Reduction")

Le problème de décision associé au Voyageur de Commerce (VC-dec) est : "Existe-t-il un circuit passant par toutes les
villes de coût total $\le k$ ?"

On part d'un problème NP-Complet très dur : le **Cycle Hamiltonien** (Existe-t-il un chemin passant par tous les sommets
d'un graphe $G=(V,E)$ une seule fois ?).

**1. La Réduction avec Écart (La construction piège) :**
À partir du graphe $G$ (où l'on cherche un cycle hamiltonien), on crée un problème de Voyageur de Commerce complet (
toutes les villes sont reliées entre elles). On définit les distances de la façon suivante :

* Si l'arête existe dans le graphe d'origine $G$, la distance entre les deux villes est de **$1$**.
* Si l'arête n'existe pas dans le graphe $G$, on "invente" une route mais on lui donne un coût gigantesque de *
  *$\epsilon \cdot n$** (où $n$ est le nombre de villes et $\epsilon$ un grand facteur).

**2. L'analyse des deux mondes (Le Gap) :**

* *MONDE OUI :* Si $G$ possède un cycle hamiltonien, notre Voyageur de Commerce peut utiliser uniquement des arêtes de
  distance 1. Le coût total de son tour sera exactement **$n$**.
* *MONDE NON :* Si $G$ n'a pas de cycle hamiltonien, le Voyageur de Commerce sera *obligé* d'emprunter au moins une
  route "inventée" très chère pour fermer son tour. Son coût sera d'au
  moins $(n-1) \times 1 + 1 \times (\epsilon \cdot n)$, ce qui est **strictement supérieur à $\epsilon \cdot n$**.

**3. L'estocade finale contre l'Approximation :**
Imaginons que vous ayez inventé un super algorithme d'approximation pour le Voyageur de Commerce, capable de garantir
une erreur maximale d'un facteur $\rho$ (par exemple $\rho=10$, votre algo trouve toujours une solution au pire 10 fois
plus longue que l'optimal).

* Choisissons notre coût astronomique $\epsilon$ tel que $\epsilon > \rho$.
* Lançons votre algorithme d'approximation sur notre ville truquée.
* **Si $G$ avait un cycle hamiltonien :** L'optimal est $n$. Votre algorithme garantit de trouver une solution de
  coût $\le \rho \cdot n$.
* **Si $G$ n'avait pas de cycle hamiltonien :** La meilleure solution possible coûte déjà $> \epsilon \cdot n$.
  Comme $\epsilon > \rho$, le coût sera forcément $> \rho \cdot n$.

**Conclusion écrasante :** Si votre algorithme d'approximation renvoie une valeur $\le \rho \cdot n$, vous savez avec
100% de certitude que $G$ possède un Cycle Hamiltonien ! S'il renvoie plus, $G$ n'en a pas.
Votre algorithme d'approximation aurait résolu le problème du Cycle Hamiltonien en temps polynomial. Puisque Cycle
Hamiltonien est NP-Complet, cela voudrait dire que **P = NP** !
Donc, **il ne peut exister aucun algorithme d'approximation** pour le Voyageur de Commerce général avec un ratio
garanti.

---

#### 4. Une note d'espoir : La Pseudo-Polynomialité (Le Sac à Dos)

Le TD termine l'Exercice 1 en rappelant que le **Sac à dos (Knapsack)**, bien qu'étant NP-Complet, possède un **FPTAS
** (Fully Polynomial-Time Approximation Scheme) qui permet de s'approcher de l'optimum avec un ratio de $(1 + 1/k)$.

Pourquoi le Sac à dos est-il "gentil" et approximable, contrairement au Voyageur de Commerce ?
Parce que le Sac à dos est ce qu'on appelle un problème **faiblement NP-Complet**. On peut le résoudre de manière exacte
avec la Programmation Dynamique en un temps $\mathcal{O}(n \cdot V)$, où $V$ est le volume du sac. Ce temps n'est pas
strictement polynomial par rapport à la *taille binaire* de l'entrée, mais on l'appelle **pseudo-polynomial**.
L'inapproximabilité absolue est réservée aux problèmes dits **fortement NP-Complets** (comme le Voyageur de Commerce, la
Clique, ou le Coloriage de Graphe), où même la programmation dynamique ne peut rien sauver.

#### Vue d’ensemble de la feuille

### Partie Pratique (TD)

Cette feuille porte sur la NP-complétude et les réductions polynomiales. Les thèmes principaux sont : Partition, Somme /
Subset-Sum, Ordonnancement, Sac à dos, Voyageur de commerce et Cycle hamiltonien. Les compétences clés sont : montrer
qu’un problème est dans NP, construire une réduction depuis un problème NP-complet, et comprendre le lien entre
optimisation, décision et approximation.

1. Partition

Définitions

On a trois problèmes principaux.

Partition à k parts

Entrée :

k,\ a_1,\dots,a_n

Question : peut-on répartir les a_i en k sous-ensembles disjoints I_1,\dots,I_k, couvrant tous les éléments, tels que
chaque sous-ensemble ait la même somme ?

La somme totale est :

A=\sum_{i=1}^n a_i.

Chaque partie doit donc avoir somme :

\frac{A}{k}.

⸻

Ordonnancement

Entrée :

k,\ d,\ a_1,\dots,a_n

où k est le nombre de machines, d la durée maximale autorisée, et a_i la durée de la tâche i.

Question : peut-on placer toutes les tâches sur k machines de sorte que chaque machine ait une charge au plus d ?

⸻

Somme

Entrée :

S,\ a_1,\dots,a_n

Question : existe-t-il un sous-ensemble dont la somme vaut exactement S ?

⸻

<a id="seance-12-exercice-1"></a>

##### 1.1. Si Partition est NP-complet, prouver que Ordonnancement est NP-complet

Reformulation

On suppose que Partition est déjà NP-complet. On veut montrer qu’Ordonnancement est NP-complet.

Pour cela, il faut montrer deux choses :

1. Ordonnancement appartient à NP.
2. Partition se réduit polynomialement à Ordonnancement.

⸻

Étape 1 : Ordonnancement appartient à NP

Un certificat est une affectation de chaque tâche à une machine.

Par exemple :

f(i)=s

signifie que la tâche i est mise sur la machine s.

Pour vérifier le certificat :

1. On calcule la charge de chaque machine :

L_s=\sum_{i:f(i)=s} a_i.

2. On vérifie que :

$$
L_s\leq d
$$

pour toute machine s.

Cette vérification est polynomiale en la taille de l’entrée.

Donc :

$$
\text{Ordonnancement}\in NP.
$$

⸻

Étape 2 : réduction de Partition vers Ordonnancement

On prend une instance de Partition :

(k,a_1,\dots,a_n).

On construit une instance d’Ordonnancement avec :

k' = k,

les mêmes tâches :

a_1,\dots,a_n,

et une borne :

d=\frac{1}{k}\sum_{i=1}^n a_i.

Si la somme totale n’est pas divisible par k, alors l’instance de Partition est directement négative. On peut dans ce
cas produire une instance triviale négative d’Ordonnancement.

⸻

Correction de la réduction

Sens direct

Supposons que Partition admette une solution.

Alors il existe :

I_1,\dots,I_k

tels que :

$$
\sum_{a\in I_s} a = d
$$

pour tout s.

On affecte les tâches du sous-ensemble I_s à la machine s.

Chaque machine a alors une charge exactement égale à d, donc inférieure ou égale à d.

Donc l’instance d’Ordonnancement est positive.

⸻

Sens réciproque

Supposons que l’instance d’Ordonnancement soit positive.

Alors on peut répartir les tâches sur k machines avec une charge au plus d.

La somme totale des charges est :

$$
\sum_{i=1}^n a_i = kd.
$$

Comme chaque machine a une charge au plus d, et que la somme totale est exactement kd, chaque machine doit avoir charge
exactement d.

Donc les ensembles de tâches affectés aux machines forment une partition équilibrée.

Donc l’instance de Partition est positive.

⸻

Conclusion

On a une réduction polynomiale :

$$
\text{Partition}\leq_P \text{Ordonnancement}.
$$

Comme Partition est NP-complet et Ordonnancement appartient à NP :

$$
\boxed{\text{Ordonnancement est NP-complet}.}
$$

⸻

<a id="seance-12-exercice-2"></a>

##### 1.2. Si Somme est NP-complet, prouver que Partition et Ordonnancement sont NP-complets

Partie A — Montrer que Partition est NP-complet

Reformulation

On suppose que Somme est NP-complet. On veut réduire Somme à Partition.

Le problème Somme demande :

$$
\exists I\subseteq \{1,\dots,n\},\quad \sum_{i\in I} a_i = S ?
$$

On veut transformer cela en une question de partition en deux parts égales.

⸻

Stratégie

On veut créer une instance de Partition telle que choisir un sous-ensemble de somme S corresponde à couper l’ensemble en
deux parties de même somme.

Pour cela, on ajoute un nombre auxiliaire.

Soit :

A=\sum_{i=1}^n a_i.

On veut forcer une partie à contenir les a_i choisis plus un élément spécial, afin que sa somme soit exactement la
moitié de la somme totale.

Une réduction classique de Somme vers Partition consiste à ajouter deux nombres :

B+S

et

B+A-S

avec B suffisamment grand.

⸻

Construction

À partir de l’instance Somme :

(S,a_1,\dots,a_n),

on construit l’instance Partition à k=2 :

a_1,\dots,a_n,\ B+S,\ B+A-S,

où :

A=\sum_{i=1}^n a_i

et B est un entier strictement plus grand que A, par exemple :

B=A+1.

La somme totale vaut :

A+(B+S)+(B+A-S)=2A+2B.

La moitié vaut donc :

A+B.

⸻

Correction

Sens direct

Supposons qu’il existe un sous-ensemble I tel que :

$$
\sum_{i\in I} a_i=S.
$$

Alors considérons l’ensemble :

J = \{a_i : i\notin I\}\cup \{B+S\}.

Sa somme vaut :

$$
\sum_{i\notin I}a_i + B+S.
$$

Or :

$$
\sum_{i\notin I}a_i=A-S.
$$

Donc :

(A-S)+B+S=A+B.

Ainsi J forme une partie de somme égale à la moitié totale. Donc il existe une partition en deux parts égales.

⸻

Sens réciproque

Supposons qu’il existe une partition en deux parts égales de somme :

A+B.

Comme :

B>A,

les deux grands nombres B+S et B+A-S ne peuvent pas être dans la même partie, car leur somme vaut :

2B+A > A+B.

Donc ils sont séparés.

Considérons la partie contenant B+S. Elle doit atteindre A+B. Elle contient donc, en plus, certains a_i de somme :

(A+B)-(B+S)=A-S.

Donc les a_i qui ne sont pas dans cette partie ont somme :

A-(A-S)=S.

On obtient un sous-ensemble de somme S.

Donc l’instance Somme est positive.

⸻

Conclusion

$$
\text{Somme}\leq_P \text{Partition}.
$$

Comme Somme est NP-complet et Partition est dans NP :

$$
\boxed{\text{Partition est NP-complet}.}
$$

⸻

Partie B — Ordonnancement est NP-complet

D’après la question 1, on a :

$$
\text{Partition}\leq_P \text{Ordonnancement}.
$$

Comme on vient de montrer que Partition est NP-complet, on en déduit :

$$
\boxed{\text{Ordonnancement est NP-complet}.}
$$

⸻

<a id="seance-12-exercice-3"></a>

##### 1.3. Réduction de Somme vers Sac à dos

Problème reformulé

Le problème du sac à dos consiste à maximiser le gain total d’objets placés dans un sac de capacité V.

Chaque objet i possède :

* un volume v_i ;
* un gain g_i.

On veut montrer que le sac à dos n’admet pas d’algorithme polynomial exact, sauf si :

$P=NP$.

⸻

Stratégie

On part du problème Somme, supposé NP-complet.

On transforme une instance de Somme :

(S,a_1,\dots,a_n)

en une instance de Sac à dos.

Idée simple :

v_i = a_i,\qquad g_i=a_i,\qquad V=S.

On demande ensuite s’il existe une solution de gain au moins S.

⸻

Construction

Pour chaque entier a_i, on crée un objet i tel que :

v_i=a_i

et

g_i=a_i.

La capacité du sac est :

V=S.

On considère la version décisionnelle du sac à dos :

Existe-t-il un sous-ensemble d’objets de volume total au plus V et de gain total au moins S ?

⸻

Correction

Si Somme a une solution, alors il existe un sous-ensemble I tel que :

$$
\sum_{i\in I}a_i=S.
$$

Dans le sac à dos, le même sous-ensemble a volume :

$$
\sum_{i\in I}v_i=\sum_{i\in I}a_i=S=V
$$

et gain :

$$
\sum_{i\in I}g_i=\sum_{i\in I}a_i=S.
$$

Donc il existe une solution de gain au moins S.

Réciproquement, supposons qu’il existe un sous-ensemble d’objets avec :

$$
\sum v_i\leq S
$$

et

$$
\sum g_i\geq S.
$$

Mais comme :

v_i=g_i=a_i,

on a :

$$
\sum v_i=\sum g_i.
$$

Donc :

S\leq \sum g_i=\sum v_i\leq S.

Ainsi :

$$
\sum_{i\in I}a_i=S.
$$

Donc Somme a une solution.

⸻

Conclusion

On a :

$$
\text{Somme}\leq_P \text{Sac à dos décision}.
$$

Donc si le sac à dos exact avait un algorithme polynomial, alors Somme aurait un algorithme polynomial.

Comme Somme est NP-complet, cela impliquerait :

$P=NP$.

Donc :

\boxed{\text{Le sac à dos exact n’admet pas d’algorithme polynomial sauf si }$P=NP$.}

⸻

<a id="seance-12-exercice-4"></a>

##### 1.4. Sac à dos approximable en O(n^{k+1}) avec ratio 1+\frac{1}{k}. Qu’en déduire ?

Reformulation

On sait que le sac à dos exact est difficile, mais qu’il existe un algorithme d’approximation polynomial avec ratio :

1+\frac{1}{k}

pour tout entier k.

On demande ce que cela implique.

⸻

Analyse

Pour un k fixé, le temps est :

O(n^{k+1}).

C’est polynomial en n, car k est une constante.

Le ratio :

1+\frac{1}{k}

peut être rendu aussi proche de 1 qu’on veut en prenant k grand.

Par exemple :

* k=1 donne ratio 2 ;
* k=10 donne ratio 1.1 ;
* k=100 donne ratio 1.01.

Donc le sac à dos possède un schéma d’approximation polynomial, appelé PTAS.

⸻

Conclusion

Même si le sac à dos exact est NP-difficile, il est très bien approximable.

On en déduit :

$$
\boxed{\text{Le sac à dos admet un PTAS.}}
$$

Mais attention : ce n’est pas forcément un FPTAS, car le temps :

O(n^{k+1})

devient très grand quand on veut une précision très fine.

Si on pose :

\varepsilon=\frac{1}{k},

alors le temps devient environ :

O(n^{1+1/\varepsilon}).

Ce n’est pas polynomial en 1/\varepsilon.

Donc c’est un PTAS, pas nécessairement un FPTAS.

⸻

2. Voyageur de commerce

Définition

Le problème du voyageur de commerce, ou TSP / VC, demande :

étant donné des villes et des coûts entre villes, trouver un circuit de coût minimal passant exactement une fois par
chaque ville et revenant au point de départ.

⸻

<a id="seance-12-exercice-5"></a>

##### 2.1. Écrire VC-dec, le problème de décision correspondant

Reformulation

Le problème d’optimisation demande de minimiser le coût d’un tour.

La version décisionnelle ajoute une borne B et demande si un tour de coût au plus B existe.

VC-dec

Entrée :

* un ensemble de villes V ;
* un coût c(u,v) pour chaque paire de villes ;
* une borne B.

Question :

Existe-t-il un circuit passant une et une seule fois par chaque ville, revenant au point de départ, et de coût total au
plus B ?

Formellement :

$$
\exists \text{ permutation } (v_1,\dots,v_n)
$$

telle que :

c(v_1,v_2)+c(v_2,v_3)+\dots+c(v_n,v_1)\leq B.

⸻

<a id="seance-12-exercice-6"></a>

##### 2.2. Réduction du Cycle hamiltonien vers VC-dec

Problème reformulé

On sait que le problème du cycle hamiltonien est NP-complet.

On veut montrer :

$$
\text{Cycle Hamiltonien}\leq_P \text{VC-dec}.
$$

⸻

Stratégie

À partir d’un graphe G=(V,E), on construit une instance de TSP où :

* les arêtes existantes dans G coûtent peu ;
* les arêtes absentes coûtent cher.

Ainsi, un tour de faible coût correspond exactement à un cycle hamiltonien dans G.

⸻

Construction

Soit G=(V,E) avec :

|V|=n.

On construit un graphe complet sur les mêmes sommets.

Pour chaque paire de sommets u,v, on définit :

c(u,v)=
$$
\begin{cases}
$$
1 & \text{si } (u,v)\in E,\\
2 & \text{si } (u,v)\notin E.
\end{cases}

On fixe la borne :

B=n.

⸻

Correction

Sens direct

Supposons que G possède un cycle hamiltonien.

Ce cycle passe une fois par chaque sommet et utilise exactement n arêtes de G.

Dans l’instance TSP, chaque arête du cycle coûte 1.

Donc le coût total est :

n.

Ainsi il existe un tour de coût au plus B=n.

Donc VC-dec répond oui.

⸻

Sens réciproque

Supposons que l’instance VC-dec possède un tour de coût au plus :

n.

Un tour passant par n villes utilise exactement n arêtes.

Chaque arête coûte au moins 1.

Donc si le coût total est au plus n, toutes les arêtes du tour doivent coûter exactement 1.

Cela signifie que toutes les arêtes du tour sont des arêtes de G.

Donc ce tour correspond à un cycle hamiltonien dans G.

⸻

Conclusion

$$
\boxed{\text{Cycle Hamiltonien}\leq_P \text{VC-dec}.}
$$

Comme Cycle Hamiltonien est NP-complet, VC-dec est NP-difficile.

Et VC-dec appartient à NP, car un certificat est simplement l’ordre des villes, vérifiable en temps polynomial.

Donc :

$$
\boxed{\text{VC-dec est NP-complet}.}
$$

⸻

<a id="seance-12-exercice-7"></a>

##### 2.3. Montrer que VC est inapproximable sauf si $P=NP$

Reformulation

On veut montrer qu’il n’existe pas d’algorithme polynomial garantissant une approximation du TSP général avec un facteur
constant, sauf si $P=NP$.

Attention : cela concerne le TSP général, sans inégalité triangulaire.

⸻

Stratégie

On renforce la réduction précédente.

On choisit des coûts :

1

pour les arêtes de G, et un très grand coût M pour les non-arêtes.

Si un cycle hamiltonien existe, le coût optimal est :

n.

Sinon, tout tour doit utiliser au moins une non-arête, donc son coût est au moins :

M.

En choisissant M suffisamment grand, un algorithme d’approximation pourrait distinguer les deux cas. Cela résoudrait
Cycle Hamiltonien en temps polynomial, contradiction sauf si $P=NP$.

⸻

Preuve pour un facteur constant \rho

Supposons qu’il existe un algorithme polynomial d’approximation de ratio \rho, avec \rho\geq 1.

À partir d’un graphe G à n sommets, on construit une instance TSP complète :

c(u,v)=
$$
\begin{cases}
$$
1 & \text{si } (u,v)\in E,\\
M & \text{sinon}.
\end{cases}

On choisit :

M>\rho n.

Par exemple :

M=\rho n+1.

⸻

Cas 1 : G a un cycle hamiltonien

Alors il existe un tour de coût :

n.

Donc :

OPT=n.

Un algorithme de ratio \rho doit retourner une solution de coût au plus :

\rho OPT=\rho n.

Donc il retourne un tour de coût strictement inférieur à M.

⸻

Cas 2 : G n’a pas de cycle hamiltonien

Alors tout tour utilise au moins une non-arête.

Donc tout tour a un coût au moins :

M.

L’algorithme retourne donc nécessairement un tour de coût au moins M.

⸻

Décision du cycle hamiltonien

On exécute l’algorithme d’approximation TSP.

* Si le coût retourné est inférieur à M, on répond : G a un cycle hamiltonien.
* Si le coût retourné est au moins M, on répond : G n’a pas de cycle hamiltonien.

Cela résout Cycle Hamiltonien en temps polynomial.

Comme Cycle Hamiltonien est NP-complet, cela impliquerait :

$P=NP$.

⸻

Conclusion

Donc, sauf si :

$P=NP$,

il n’existe pas d’algorithme polynomial d’approximation à facteur constant pour le TSP général.

\boxed{\text{VC général est inapproximable sauf si }$P=NP$.}

⸻

Résumé concis de toute la feuille

La feuille montre que plusieurs problèmes classiques sont NP-complets par réduction :

$$
\text{Somme}\leq_P \text{Partition}\leq_P \text{Ordonnancement}.
$$

Elle montre aussi que le sac à dos exact est NP-difficile via une réduction depuis Somme, mais reste approximable
efficacement par un PTAS. Enfin, elle établit la NP-complétude de la version décisionnelle du voyageur de commerce via
Cycle Hamiltonien, puis son inapproximabilité dans le cas général.

Méthodes clés utilisées

* Réduction de Somme vers Partition en ajoutant deux grands nombres.
* Réduction de Partition vers Ordonnancement avec :
  d=\frac{\sum a_i}{k}.
* Réduction de Somme vers Sac à dos avec :
  v_i=g_i=a_i,\quad V=S.
* Réduction de Cycle Hamiltonien vers TSP en mettant :
  c(u,v)=1
  pour les arêtes et un coût élevé pour les non-arêtes.
* Argument d’inapproximabilité par séparation de deux cas :
  OPT=n
  ou
  OPT\geq M.

#### Formules importantes

Pour Partition :

A=\sum_{i=1}^n a_i

$$
\text{chaque partie doit avoir somme } \frac{A}{k}.
$$

Pour Ordonnancement :

$$
\text{charge machine } s=\sum_{i\in I_s}a_i\leq d.
$$

Pour Sac à dos :

v_i=g_i=a_i,\qquad V=S.

Pour TSP :

c(u,v)=
$$
\begin{cases}
$$
1 & \text{si } (u,v)\in E,\\
M & \text{sinon}.
\end{cases}

#### Pièges fréquents

* Oublier de prouver qu’un problème est dans NP avant de conclure NP-complet.
* Confondre problème d’optimisation et problème de décision.
* Dans la réduction Partition vers Ordonnancement, oublier que si la somme totale vaut kd, alors des charges \leq d
  imposent en fait des charges exactement égales à d.
* Dans TSP, oublier que le graphe du TSP est complet : on encode les non-arêtes avec un coût élevé.
* Croire que “NP-difficile” interdit toute approximation : le sac à dos est NP-difficile mais approximable.
* Confondre TSP général et TSP métrique : l’inapproximabilité ici concerne le TSP général.

#### Questions d’entraînement

##### 1. Montrer que si Partition à k=2 est NP-complet, alors Ordonnancement à deux machines est NP-complet.

    Réponse : prendre d=\frac{\sum a_i}{2}.

2. Dans la réduction Somme vers Sac à dos, pourquoi impose-t-on v_i=g_i=a_i ?
   Réponse : pour que “gain au moins S” et “volume au plus S” forcent exactement une somme égale à S.
3. Pourquoi VC-dec appartient-il à NP ?
   Réponse : un certificat est une permutation des villes ; on vérifie en temps polynomial que le coût du circuit est
   \leq B.
4. Pourquoi un tour TSP de coût \leq n dans la réduction avec coûts 1/2 utilise seulement des arêtes du graphe initial ?
   Réponse : il contient n arêtes, chacune coûte au moins 1, donc pour totaliser au plus n, elles doivent toutes coûter
   1.
5. Pourquoi le sac à dos peut être NP-difficile et approximable ?
   Réponse : la difficulté concerne la solution exacte ; l’approximation peut être beaucoup plus facile.

---
