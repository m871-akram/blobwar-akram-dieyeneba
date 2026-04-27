#include "strategy.h"



void Strategy::applyMove (const movement& mv) {
        // To be completed...
        int dist = std::max(abs(mv.nx - mv.ox), abs(mv.ny - mv.oy));

        _blobs.set(mv.nx, mv.ny, (int)_current_player);

        if (dist == 2){
            _blobs.set(mv.ox, mv.oy, -1);
        }

        for (int x = std::max(0,mv.nx-1) ; x <= std::min(7,mv.nx+1) ; x++){
            for (int y = std::max(0,mv.ny-1) ; x <= std::min(7,mv.ny+1) ; y++){
                Sint16 case_cible = _blobs.get(x,y);

                if(case_cible != 1 && case_cible != (int) _current_player){
                    _blobs.set(x, y, (int) _current_player);
                }
            }
        }
}

Sint32 Strategy::estimateCurrentScore () const {
        // To be completed...
    Sint32 my_score = 0;
    Sint32 opp_score = 0;

    // On parcourt tout le plateau
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (_blobs.get(x, y) == (int)_current_player) {
                my_score++;
            } else if (_blobs.get(x, y) != -1) { // Si ce n'est ni à moi, ni vide, c'est à l'adversaire
                opp_score++;
            }
        }
    }

    // Le score est la différence entre mes pions et ceux de l'adversaire
    return my_score - opp_score;
}

vector<movement>& Strategy::computeValidMoves (vector<movement>& valid_moves) const {
    movement mv(0,0,0,0);
    //iterate on starting position
    for(mv.ox = 0 ; mv.ox < 8 ; mv.ox++) {
        for(mv.oy = 0 ; mv.oy < 8 ; mv.oy++) {
            if (_blobs.get(mv.ox, mv.oy) == (int) _current_player) {
                //iterate on possible destinations
                for(mv.nx = std::max(0,mv.ox-2) ; mv.nx <= std::min(7,mv.ox+2) ; mv.nx++) {
                    for(mv.ny = std::max(0,mv.oy-2) ; mv.ny <= std::min(7,mv.oy+2) ; mv.ny++) {
                        if (_holes.get(mv.nx, mv.ny)) continue;
                        if (_blobs.get(mv.nx, mv.ny) == -1) {
                           valid_moves.push_back(mv); 
                        }
                    }
                }
            }
        }
    }
    return valid_moves;
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

void Strategy::computeBestMove () {
    // To be improved...

    // //The following code finds a valid move.
    // movement mv(0,0,0,0);
    // //iterate on starting position
    // for(mv.ox = 0 ; mv.ox < 8 ; mv.ox++) {
    //     for(mv.oy = 0 ; mv.oy < 8 ; mv.oy++) {
    //         if (_blobs.get(mv.ox, mv.oy) == (int) _current_player) {
    //             //iterate on possible destinations
    //             for(mv.nx = std::max(0,mv.ox-2) ; mv.nx <= std::min(7,mv.ox+2) ; mv.nx++) {
    //                 for(mv.ny = std::max(0,mv.oy-2) ; mv.ny <= std::min(7,mv.oy+2) ; mv.ny++) {
    //                     if (_holes.get(mv.nx, mv.ny)) continue;
    //                     if (_blobs.get(mv.nx, mv.ny) == -1) goto end_choice;
    //                 }
    //             }
    //         }
    //     }
    // }

    vector<movement> moves;
    computeValidMoves(moves);

    if (moves.empty()) {
        goto end_choice;
    }

    Sint32 bestScore = -1000000; // tres bas score arbitraire
    movement mv_to_save = moves[0]; 

    for (const auto& mv : moves) {
        Strategy next_state = *this; 
        next_state.applyMove(mv);
        
        Sint32 score = minMax(next_state, 3, false);
        
        if (score > bestScore) {
            bestScore = score;
            mv_to_save = mv;
        }
    }

end_choice:
     _saveBestMove(mv_to_save);
     return;
}

