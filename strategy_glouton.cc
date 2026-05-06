#include "move.h"
#include "strategy.h"
#include <algorithm>
#include <cstdlib>

void Strategy::applyMove(const movement& mv)
{
    int dist = std::max(std::abs(mv.nx - mv.ox), std::abs(mv.ny - mv.oy));

    // Si c'est un saut, le pion quitte sa case de depart.
    if (dist == 2)
    {
        _blobs.set(mv.ox, mv.oy, -1);
    }

    // La case d'arrivee devient a nous dans tous les cas.
    _blobs.set(mv.nx, mv.ny, _current_player);

    // Tous les voisins adverses sont retournes.
    for (int i = std::max(0, (int)mv.nx - 1); i <= std::min(7, (int)mv.nx + 1); i++)
    {
        for (int j = std::max(0, (int)mv.ny - 1); j <= std::min(7, (int)mv.ny + 1); j++)
        {
            if (_blobs.get(i, j) != -1 && _blobs.get(i, j) != _current_player)
            {
                _blobs.set(i, j, _current_player);
            }
        }
    }
}

Sint32 Strategy::estimateCurrentScore() const
{
    Sint32 mon_score = 0;
    Sint32 opp_score = 0;

    // Score basique: mes pions moins les pions adverses.
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (_blobs.get(i, j) == _current_player)
            {
                mon_score++;
            }
            else if (_blobs.get(i, j) != -1)
            {
                opp_score++;
            }
        }
    }

    return mon_score - opp_score;
}

vector<movement>& Strategy::computeValidMoves(vector<movement>& valid_moves) const
{
    valid_moves.clear();

    // On regarde toutes les destinations possibles autour de mes pions.
    for (int ox = 0; ox < 8; ox++)
    {
        for (int oy = 0; oy < 8; oy++)
        {
            if (_blobs.get(ox, oy) == (int)_current_player)
            {
                for (int nx = std::max(0, ox - 2); nx <= std::min(7, ox + 2); nx++)
                {
                    for (int ny = std::max(0, oy - 2); ny <= std::min(7, oy + 2); ny++)
                    {
                        if (nx == ox && ny == oy)
                        {
                            continue;
                        }
                        if (_holes.get(nx, ny))
                        {
                            continue;
                        }
                        if (_blobs.get(nx, ny) == -1)
                        {
                            valid_moves.push_back(movement(ox, oy, nx, ny));
                        }
                    }
                }
            }
        }
    }

    return valid_moves;
}

void Strategy::computeBestMove()
{
    vector<movement> valid_moves;
    computeValidMoves(valid_moves);

    if (valid_moves.empty())
    {
        cout << "BW_TRACE algo=glouton depth=1 nodes=0 cutoffs=0" << endl;
        return;
    }

    Sint32 best_score = -999999;
    movement best_move = valid_moves[0];
    unsigned long long nodes = 0;

    // Glouton: on teste chaque coup une seule fois.
    for (const movement& mv : valid_moves)
    {
        Strategy simulated_game(*this);
        simulated_game.applyMove(mv);

        Sint32 current_score = simulated_game.estimateCurrentScore();
        // Ici un noeud correspond a un coup candidat teste.
        nodes++;
        if (current_score > best_score)
        {
            best_score = current_score;
            best_move = mv;
        }
    }

    _saveBestMove(best_move);
    cout << "BW_TRACE algo=glouton depth=1 nodes=" << nodes << " cutoffs=0" << endl;
}
