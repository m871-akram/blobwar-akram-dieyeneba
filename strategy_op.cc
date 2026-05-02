#include "move.h"
#include "strategy_op.h"
#include <omp.h>



void Strategy::applyMove (const movement& mv) {
        // To be completed...

    int dist = std::max(abs(mv.nx - mv.ox), abs(mv.ny - mv.oy));

    if ( dist == 2)
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
                        if (nx == ox && ny == oy) continue; // On ne peut pas rester sur place, obliger le blob a bouger , sinon il va rester longtemps entrain de reflechir
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
// //     // To be improved...
// //
// //     //The following code finds a valid move.
// //     movement mv(0,0,0,0);
// //     //iterate on starting position
// //     for(mv.ox = 0 ; mv.ox < 8 ; mv.ox++) {
// //         for(mv.oy = 0 ; mv.oy < 8 ; mv.oy++) {
// //             if (_blobs.get(mv.ox, mv.oy) == (int) _current_player) {
// //                 //iterate on possible destinations
// //                 for(mv.nx = std::max(0,mv.ox-2) ; mv.nx <= std::min(7,mv.ox+2) ; mv.nx++) {
// //                     for(mv.ny = std::max(0,mv.oy-2) ; mv.ny <= std::min(7,mv.oy+2) ; mv.ny++) {
// //                         if (_holes.get(mv.nx, mv.ny)) continue;
// //                         if (_blobs.get(mv.nx, mv.ny) == -1) goto end_choice;
// //                     }
// //                 }
// //             }
// //         }
// //     }
// //
// // end_choice:
// //      _saveBestMove(mv);
// //      return;
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
    vector<movement> moves;
    computeValidMoves(moves);

    Sint32 bestScore = -1000000; // tres bas score arbitraire
    movement mv_to_save(0, 0, 0, 0); // initialisation par defaut

    if (moves.empty()) {
        goto end_choice;
    }

    mv_to_save = moves[0];
    // On utilise une directive OpenMP pour paralléliser la boucle
    // 'shared' : ces variables sont communes à tous les threads
    // 'reduction' ou 'critical' : pour éviter que deux threads écrivent bestScore en même temps
    //#pragma omp parallel for shared(bestScore, mv_to_save)
    for (const auto& mv : moves) {
        Strategy next_state = *this;
        next_state.applyMove(mv);

        Sint32 score = minMax(next_state, 3, false);

        // ZONE CRITIQUE : Seul un thread à la fois peut comparer/modifier le meilleur score
        // #pragma omp critical
        // {
        if (score > bestScore) {
            bestScore = score;
            mv_to_save = mv;
        }
        //}
    }

    end_choice:
         _saveBestMove(mv_to_save);
        return;
}


Sint32 Strategy::minMax(Strategy current_state, int depth, bool max){
    if (depth == 0) {
        return current_state.estimateCurrentScore();
    }

    vector<movement> moves;
    current_state.computeValidMoves(moves);

    if (moves.empty()) {
        return current_state.estimateCurrentScore();
    }

    if (max) {
        Sint32 maxEval = -1000000;
        for (const auto& mv : moves) {
            // On crée une copie locale pour simuler ce chemin
            Strategy next_state = current_state;
            next_state.applyMove(mv); // On modifie la copie

            // Appel récursif sur la copie
            Sint32 eval = minMax(next_state, depth - 1, false);

            maxEval = std::max(maxEval, eval);
        }
        return maxEval; // On remonte le meilleur score
    }
    else {
        Sint32 minEval = 1000000;
        for (const auto& mv : moves) {
            Strategy next_state = current_state;
            next_state.applyMove(mv);

            Sint32 eval = minMax(next_state, depth - 1, true);

            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}
