#include "move.h"
#include "strategy.h"



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

    std::vector<movement> valid_moves;
    computeValidMoves(valid_moves);

    if (valid_moves.empty()) {
        return; // bloqué !! on doit gerer ce cas . Si aucun coup valide n’existe, computeBestMove() fait juste return sans appeler _saveBestMove. Dans le flux normal du jeu, rules::next_turn() évite normalement d’appeler l’IA si le joueur ne peut pas jouer, donc ce n’est pas bloquant. Mais en test isolé, ça peut laisser un ancien coup en mémoire partagée.
    }

    // Identification des joueurs
    Uint16 me = _current_player;
    Uint16 opponent = (me == 0) ? 1 : 0;

    // LE RÉGLAGE LE PLUS IMPORTANT
    int max_depth = 4;


    Sint32 best_score = -999999; // On initialise avec un score très bas
    movement best_move = valid_moves[0]; // On prend le premier par défaut

    // Pour chaque mouvement possible...
    for (const movement& mv : valid_moves) {
        // on crée une copie virtuelle de notre plateau actuel
        Strategy simulated_game(*this);

        //  on simule le coup
        simulated_game.applyMove(mv);

        simulated_game._current_player = opponent; // Après mon coup, c'est à l'adversaire (MIN)

        // // On passe `false` car le prochain joueur à évaluer sera MIN
        // Sint32 current_score = simulated_game.minMax(max_depth - 1, false, me, opponent);

        // pour alpha beta
        Sint32 current_score = simulated_game.alphaBeta(max_depth - 1, -999999, 999999, false, me, opponent);

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

//Le moteur récursif Alpha-Beta
Sint32 Strategy::alphaBeta(int depth, Sint32 alpha, Sint32 beta, bool isMax, Uint16 me, Uint16 opponent) {
    // 1. Condition d'arrêt (identique au Min-Max)
    if (depth == 0) {
        Uint16 old_player = _current_player;
        _current_player = me;
        Sint32 score = estimateCurrentScore();
        _current_player = old_player;
        return score;
    }

    std::vector<movement> valid_moves;
    computeValidMoves(valid_moves);

    if (valid_moves.empty()) {
        Uint16 old_player = _current_player;
        _current_player = me;
        Sint32 score = estimateCurrentScore();
        _current_player = old_player;
        return score;
    }

    // 2. Tour de MAX (Moi)
    if (isMax) {
        Sint32 maxEval = -999999;
        for (const movement& mv : valid_moves) {
            Strategy sim(*this);
            sim.applyMove(mv);
            sim._current_player = opponent;

            Sint32 eval = sim.alphaBeta(depth - 1, alpha, beta, false, me, opponent);
            maxEval = std::max(maxEval, eval);

            // Mise à jour de Alpha
            alpha = std::max(alpha, eval);

            // LA COUPURE ALPHA-BETA !
            if (beta <= alpha) {
                break; // On sort de la boucle "for", on ne teste pas les autres coups !
            }
        }
        return maxEval;
    }
    // 3. Tour de MIN (Adversaire)
    else {
        Sint32 minEval = 999999;
        for (const movement& mv : valid_moves) {
            Strategy sim(*this);
            sim.applyMove(mv);
            sim._current_player = me;

            Sint32 eval = sim.alphaBeta(depth - 1, alpha, beta, true, me, opponent);
            minEval = std::min(minEval, eval);

            // Mise à jour de Beta
            beta = std::min(beta, eval);

            // LA COUPURE ALPHA-BETA !
            if (beta <= alpha) {
                break; // On sort de la boucle "for" !
            }
        }
        return minEval;
    }
}



