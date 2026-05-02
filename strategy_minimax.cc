#include "move.h"
#include "strategy_minimax.h"
#include <algorithm>

static unsigned long long TRACE_NODES = 0;

static const Sint32 STRATEGY_INF = 1000000;

static Uint16 nextPlayer(Uint16 player) {
    // Projet en duel: joueur 0 puis joueur 1.
    return (player == 0) ? 1 : 0;
}


void Strategy::applyMove (const movement& mv) {
    int dist = std::max(abs(mv.nx - mv.ox), abs(mv.ny - mv.oy));

    // Distance 2 = saut, donc on vide la source.
    if ( dist == 2)
    {
        _blobs.set(mv.ox, mv.oy, -1);
    }

    // On pose le pion sur la destination.
    _blobs.set(mv.nx, mv.ny, _current_player);

    // Puis on convertit les voisins adverses.
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

Sint32 Strategy::estimateCurrentScore () const {

    Sint32 mon_score = 0;
    Sint32 opp_score = 0;

    // Heuristique volontairement simple pour comparer avec alpha-beta.
    for (int i = 0 ; i < 8 ; i++)
    {
        for (int j = 0 ; j < 8 ; j++)
        {
            if (_blobs.get(i, j) ==  _current_player)
            {
                mon_score++;
            } else if ( _blobs.get(i, j) != -1) { // Ce qui n'est pas a moi est compte adversaire.
                opp_score++;

            }

        }
    }
    return mon_score - opp_score;
}

vector<movement>& Strategy::computeValidMoves (vector<movement>& valid_moves) const {

    valid_moves.clear();

    // On genere les coups du joueur courant uniquement.
    for (int ox = 0 ; ox < 8 ; ox++) {
        for (int oy = 0 ; oy < 8 ; oy++) {
            if (_blobs.get(ox, oy) == (int) _current_player) {
                for (int nx = std::max(0, ox - 2) ; nx <= std::min(7, ox + 2) ; nx++) {
                    for (int ny = std::max(0, oy - 2) ; ny <= std::min(7, oy + 2) ; ny++) {
                        if (nx == ox && ny == oy) continue; // On ne reste pas sur la meme case.
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

// Choix du coup racine pour Minimax.
void Strategy::computeBestMove () {
    vector<movement> moves;
    computeValidMoves(moves);
    TRACE_NODES = 0;

    if (moves.empty()) {
        cout << "BW_TRACE algo=minimax depth=3 nodes=0 cutoffs=0" << endl;
        return;
    }

    Sint32 bestScore = -STRATEGY_INF;
    movement mv_to_save = moves[0];
    // On sauve un coup valide avant la recherche.
    _saveBestMove(mv_to_save);

    // Minimax teste chaque coup puis simule la reponse adverse.
    for (const auto& mv : moves) {
        Strategy next_state = *this;
        next_state.applyMove(mv);
        next_state._current_player = nextPlayer(_current_player);

        Sint32 score = minMax(next_state, 3, false);

        if (score > bestScore) {
            bestScore = score;
            mv_to_save = mv;
        }
    }

    _saveBestMove(mv_to_save);
    cout << "BW_TRACE algo=minimax depth=3 nodes=" << TRACE_NODES << " cutoffs=0" << endl;
}


Sint32 Strategy::minMax(Strategy current_state, int depth, bool max){
    TRACE_NODES++;
    // La profondeur limite la recherche, sinon ca explose trop vite.
    if (depth == 0) {
        return max ? current_state.estimateCurrentScore() : -current_state.estimateCurrentScore();
    }

    vector<movement> moves;
    current_state.computeValidMoves(moves);

    if (moves.empty()) {
        // Si le joueur ne peut pas jouer, on passe son tour.
        Strategy opponent_state = current_state;
        opponent_state._current_player = nextPlayer(current_state._current_player);
        vector<movement> opponent_moves;
        opponent_state.computeValidMoves(opponent_moves);

        if (opponent_moves.empty()) {
            return max ? current_state.estimateCurrentScore() : -current_state.estimateCurrentScore();
        }

        return minMax(opponent_state, depth - 1, !max);
    }

    if (max) {
        Sint32 maxEval = -STRATEGY_INF;
        for (const auto& mv : moves) {
            // On cree une copie locale pour simuler ce chemin.
            Strategy next_state = current_state;
            next_state.applyMove(mv);
            next_state._current_player = nextPlayer(current_state._current_player);

            // Noeud max: on garde le meilleur score.
            Sint32 eval = minMax(next_state, depth - 1, false);

            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    }
    else {
        Sint32 minEval = STRATEGY_INF;
        for (const auto& mv : moves) {
            Strategy next_state = current_state;
            next_state.applyMove(mv);
            next_state._current_player = nextPlayer(current_state._current_player);

            Sint32 eval = minMax(next_state, depth - 1, true);

            // Noeud min: l'adversaire choisit le pire pour nous.
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}
