// #include "strategy.h"
//
//
//
// void Strategy::applyMove (const movement& mv) {
//     // Calculer la distance du déplacement
//     int dx = std::abs(mv.nx - mv.ox);
//     int dy = std::abs(mv.ny - mv.oy);
//
//     // Si la distance max est de 2, c'est un saut : on vide la case de départ
//     if (std::max(dx, dy) == 2) {
//         _blobs.set(mv.ox, mv.oy, -1);
//     }
//
//     // Dans tous les cas (saut ou clonage), on place le pion sur la case d'arrivée
//     _blobs.set(mv.nx, mv.ny, _current_player);
//
//     // Phase d'infection : on regarde les 8 cases autour de la case d'arrivée
//     for (int ix = std::max(0, (int)mv.nx - 1); ix <= std::min(7, (int)mv.nx + 1); ix++) {
//         for (int iy = std::max(0, (int)mv.ny - 1); iy <= std::min(7, (int)mv.ny + 1); iy++) {
//             // Si la case n'est pas un trou, n'est pas vide, et appartient à un adversaire
//             if (!_holes.get(ix, iy) && _blobs.get(ix, iy) != -1 && _blobs.get(ix, iy) != _current_player) {
//                 // On infecte le pion adverse
//                 _blobs.set(ix, iy, _current_player);
//             }
//         }
//     }
// }
//
// Sint32 Strategy::estimateCurrentScore () const {
//     Sint32 my_score = 0;
//     Sint32 opp_score = 0;
//
//     // On parcourt tout le plateau
//     for (int x = 0; x < 8; x++) {
//         for (int y = 0; y < 8; y++) {
//             if (_blobs.get(x, y) == _current_player) {
//                 my_score++;
//             } else if (_blobs.get(x, y) != -1) { // Si ce n'est ni à moi, ni vide, c'est à l'adversaire
//                 opp_score++;
//             }
//         }
//     }
//
//     // Le score est la différence entre mes pions et ceux de l'adversaire
//     return my_score - opp_score;
//     // return 0;
// }
//
// vector<movement>& Strategy::computeValidMoves (vector<movement>& valid_moves) const {
//         // To be completed...
//     return valid_moves;
// }
//
// void Strategy::computeBestMove () {
//     // To be improved...
//
//     //The following code finds a valid move.
//     movement mv(0,0,0,0);
//     //iterate on starting position
//     for(mv.ox = 0 ; mv.ox < 8 ; mv.ox++) {
//         for(mv.oy = 0 ; mv.oy < 8 ; mv.oy++) {
//             if (_blobs.get(mv.ox, mv.oy) == (int) _current_player) {
//                 //iterate on possible destinations
//                 for(mv.nx = std::max(0,mv.ox-2) ; mv.nx <= std::min(7,mv.ox+2) ; mv.nx++) {
//                     for(mv.ny = std::max(0,mv.oy-2) ; mv.ny <= std::min(7,mv.oy+2) ; mv.ny++) {
//                         if (_holes.get(mv.nx, mv.ny)) continue;
//                         if (_blobs.get(mv.nx, mv.ny) == -1) goto end_choice;
//                     }
//                 }
//             }
//         }
//     }
//
// end_choice:
//      _saveBestMove(mv);
//      return;
// }
//


// partie min max :


#include "strategy.h"



void Strategy::applyMove (const movement& mv) {
    // Calculer la distance du déplacement
    int dx = std::abs(mv.nx - mv.ox);
    int dy = std::abs(mv.ny - mv.oy);

    // Si la distance max est de 2, c'est un saut : on vide la case de départ
    if (std::max(dx, dy) == 2) {
        _blobs.set(mv.ox, mv.oy, -1);
    }

    // Dans tous les cas (saut ou clonage), on place le pion sur la case d'arrivée
    _blobs.set(mv.nx, mv.ny, _current_player);

    // Phase d'infection : on regarde les 8 cases autour de la case d'arrivée
    for (int ix = std::max(0, (int)mv.nx - 1); ix <= std::min(7, (int)mv.nx + 1); ix++) {
        for (int iy = std::max(0, (int)mv.ny - 1); iy <= std::min(7, (int)mv.ny + 1); iy++) {
            // Si la case n'est pas un trou, n'est pas vide, et appartient à un adversaire
            if (!_holes.get(ix, iy) && _blobs.get(ix, iy) != -1 && _blobs.get(ix, iy) != _current_player) {
                // On infecte le pion adverse
                _blobs.set(ix, iy, _current_player);
            }
        }
    }
}

Sint32 Strategy::estimateCurrentScore () const {
    Sint32 my_score = 0;
    Sint32 opp_score = 0;

    // On parcourt tout le plateau
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (_blobs.get(x, y) == _current_player) {
                my_score++;
            } else if (_blobs.get(x, y) != -1) { // Si ce n'est ni à moi, ni vide, c'est à l'adversaire
                opp_score++;
            }
        }
    }

    // Le score est la différence entre mes pions et ceux de l'adversaire
    return my_score - opp_score;
    // return 0;
}

vector<movement>& Strategy::computeValidMoves (vector<movement>& valid_moves) const {
        // To be completed...
    return valid_moves;
}

void Strategy::computeBestMove () {
    // To be improved...

    //The following code finds a valid move.
    movement mv(0,0,0,0);
    //iterate on starting position
    for(mv.ox = 0 ; mv.ox < 8 ; mv.ox++) {
        for(mv.oy = 0 ; mv.oy < 8 ; mv.oy++) {
            if (_blobs.get(mv.ox, mv.oy) == (int) _current_player) {
                //iterate on possible destinations
                for(mv.nx = std::max(0,mv.ox-2) ; mv.nx <= std::min(7,mv.ox+2) ; mv.nx++) {
                    for(mv.ny = std::max(0,mv.oy-2) ; mv.ny <= std::min(7,mv.oy+2) ; mv.ny++) {
                        if (_holes.get(mv.nx, mv.ny)) continue;
                        if (_blobs.get(mv.nx, mv.ny) == -1) goto end_choice;
                    }
                }
            }
        }
    }

end_choice:
     _saveBestMove(mv);
     return;
}


