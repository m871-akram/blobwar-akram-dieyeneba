#include "move.h"
#include "strategy_op.h"



void Strategy::applyMove (const movement& mv) {
        // To be completed...

    int dx = std::abs(mv.nx - mv.ox);
    int dy = std::abs(mv.ny - mv.oy);

    if ( std::max(dx,dy) == 2)
    {
        _blobs.set(mv.ox, mv.oy, -1);
    }

    _blobs.set(mv.nx, mv.ny, _current_player);

    for ( int i = std::max(0, mv.nx - 1) ; i <= std::min(7, mv.nx + 1) ; i++)
    {
        for ( int j = std::max(0, mv.ny - 1) ; j <= std::min(7, mv.ny + 1) ; j++)
        {
            if (_blobs.get(i, j) != -1 && _blobs.get(i, j) != _current_player)
            {
                _blobs.set(i, j, _current_player);
            }
        }
    }
}

Sint32 Strategy::estimateCurrentScore () const { // En mode 4 joueurs, il additionne tous les autres joueurs comme un seul adversaire. C’est acceptable comme heuristique simple, mais pas très stratégique.

    Sint32 mon_score = 0;
    Sint32 opp_score = 0;

    for (int i = 0 ; i < 8 ; i++)
    {
        for (int j = 0 ; j < 8 ; j++)
        {
            if (_blobs.get(i, j) ==  _current_player)
            {
                mon_score++;
            } else if ( _blobs.get(i, j) != -1) { // Si ce n'est ni à moi, ni vide, c'est à l'adversaire ( !! je dois rechecker le cas des holes )
                opp_score++;

            }

        }
    }
    return mon_score - opp_score;
}

vector<movement>& Strategy::computeValidMoves (vector<movement>& valid_moves) const {

    valid_moves.clear();

    for (int ox = 0 ; ox < 8 ; ox++) {
        for (int oy = 0 ; oy < 8 ; oy++) {
            if (_blobs.get(ox, oy) == (int) _current_player) {
                for (int nx = std::max(0, ox - 2) ; nx <= std::min(7, ox + 2) ; nx++) {
                    for (int ny = std::max(0, oy - 2) ; ny <= std::min(7, oy + 2) ; ny++) {
                        if (nx == ox && ny == oy) continue; // On ne peut pas rester sur place
                        if (_holes.get(nx, ny)) continue;
                        if (_blobs.get(nx, ny) == -1) {
                            valid_moves.push_back(movement(ox, oy, nx, ny));
                        }
                    }
                }
            }
        }
    }

    return valid_moves;
}

// // cette fonction c est notre maestro : Algorithme Glouton
// void Strategy::computeBestMove () {
//
//
//     std::vector<movement> valid_moves;
//     computeValidMoves(valid_moves);
//
//     if (valid_moves.empty()) {
//         return; // bloqué !! on doit gerer ce cas . Si aucun coup valide n’existe, computeBestMove() fait juste return sans appeler _saveBestMove. Dans le flux normal du jeu, rules::next_turn() évite normalement d’appeler l’IA si le joueur ne peut pas jouer, donc ce n’est pas bloquant. Mais en test isolé, ça peut laisser un ancien coup en mémoire partagée.
//     }
//
//     Sint32 best_score = -999999; // On initialise avec un score très bas
//     movement best_move = valid_moves[0]; // On prend le premier par défaut
//
//     // Pour chaque mouvement possible...
//     for (const movement& mv : valid_moves) {
//         // on crée une copie virtuelle de notre plateau actuel
//         Strategy simulated_game(*this);
//
//         //  on simule le coup
//         simulated_game.applyMove(mv);
//
//         Sint32 current_score = simulated_game.estimateCurrentScore();
//
//         // Si ce score est meilleur que notre meilleur score trouvé jusqu'à présent, on le garde
//         if (current_score > best_score) {
//             best_score = current_score;
//             best_move = mv;
//         }
//     }
//
//     // On sauvegarde le meilleur mouvement trouvé
//     _saveBestMove(best_move);
//
//
// }




// cette fonction c est notre maestro : Algorithme MiniMax
void Strategy::computeBestMove () {

    std::vector<movement> valid_moves;
    computeValidMoves(valid_moves);

    if (valid_moves.empty()) {
        return; // bloqué !! on doit gerer ce cas . Si aucun coup valide n’existe, computeBestMove() fait juste return sans appeler _saveBestMove. Dans le flux normal du jeu, rules::next_turn() évite normalement d’appeler l’IA si le joueur ne peut pas jouer, donc ce n’est pas bloquant. Mais en test isolé, ça peut laisser un ancien coup en mémoire partagée.
    }

    // Identification des joueurs
    Uint16 me = _current_player;
    Uint16 opponent = (me == 0) ? 1 : 0;

    // === LE RÉGLAGE LE PLUS IMPORTANT ===
    // Attention: à 3, c'est rapide. À 4 ou 5, ça va devenir très lent !
    int max_depth = 3;


    Sint32 best_score = -999999; // On initialise avec un score très bas
    movement best_move = valid_moves[0]; // On prend le premier par défaut

    // Pour chaque mouvement possible...
    for (const movement& mv : valid_moves) {
        // on crée une copie virtuelle de notre plateau actuel
        Strategy simulated_game(*this);

        //  on simule le coup
        simulated_game.applyMove(mv);

        simulated_game._current_player = opponent; // Après mon coup, c'est à l'adversaire (MIN)
        // On passe `false` car le prochain joueur à évaluer sera MIN
        Sint32 current_score = simulated_game.minMax(max_depth - 1, false, me, opponent);

        // Si ce score est meilleur que notre meilleur score trouvé jusqu'à présent, on le garde
        if (current_score > best_score) {
            best_score = current_score;
            best_move = mv;
        }
    }

    // On sauvegarde le meilleur mouvement trouvé
    _saveBestMove(best_move);


}


// Le moteur récursif Min-Max
Sint32 Strategy::minMax(int depth, bool isMax, Uint16 me, Uint16 opponent) {
    // 1. CONDITION D'ARRÊT : On a atteint la profondeur max
    if (depth == 0) {
        // L'heuristique DOIT toujours être évaluée de MON point de vue.
        Uint16 old_player = _current_player;
        _current_player = me;
        Sint32 score = estimateCurrentScore();
        _current_player = old_player; // On restaure
        return score;
    }

    // 2. On génère tous les coups possibles pour le joueur actuel
    std::vector<movement> valid_moves;
    computeValidMoves(valid_moves);

    // Si aucun coup n'est possible (blocage ou fin de partie)
    if (valid_moves.empty()) {
        Uint16 old_player = _current_player;
        _current_player = me;
        Sint32 score = estimateCurrentScore();
        _current_player = old_player;
        return score;
    }

    // 3. Tour de MAX (Moi) : On cherche le score MAXIMUM
    if (isMax) {
        Sint32 maxEval = -999999;
        for (const movement& mv : valid_moves) {
            Strategy sim(*this);            // Copie du plateau
            sim.applyMove(mv);              // Je joue mon coup
            sim._current_player = opponent; // Le prochain tour sera celui de MIN

            // Appel récursif (on descend d'un étage)
            Sint32 eval = sim.minMax(depth - 1, false, me, opponent);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    }
    // 4. Tour de MIN (Adversaire) : On cherche le score MINIMUM
    else {
        Sint32 minEval = 999999;
        for (const movement& mv : valid_moves) {
            Strategy sim(*this);            // Copie du plateau
            sim.applyMove(mv);              // L'adversaire joue son coup
            sim._current_player = me;       // Le prochain tour sera celui de MAX

            // Appel récursif (on descend d'un étage)
            Sint32 eval = sim.minMax(depth - 1, true, me, opponent);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}



