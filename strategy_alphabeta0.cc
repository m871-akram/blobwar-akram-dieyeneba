#include "move.h"
#include "strategy.h"
#include <algorithm>
#include <atomic>
#include <cstdlib>

static const Sint32 STRATEGY_INF = 999999;
static const int ALPHABETA0_DEPTH = 4;
static std::atomic<unsigned long long> TRACE_NODES(0);
static std::atomic<unsigned long long> TRACE_CUTOFFS(0);

static const int WEIGHT[8][8] = {
    {2, 3, 4, 4, 4, 4, 3, 2},
    {3, 4, 5, 6, 6, 5, 4, 3},
    {4, 5, 7, 8, 8, 7, 5, 4},
    {4, 6, 8, 10, 10, 8, 6, 4},
    {4, 6, 8, 10, 10, 8, 6, 4},
    {4, 5, 7, 8, 8, 7, 5, 4},
    {3, 4, 5, 6, 6, 5, 4, 3},
    {2, 3, 4, 4, 4, 4, 3, 2}
};

static bool insideBoard(int x, int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

static void resetTrace()
{
    TRACE_NODES.store(0, std::memory_order_relaxed);
    TRACE_CUTOFFS.store(0, std::memory_order_relaxed);
}

static void printTrace(int depth)
{
    cout << "BW_TRACE algo=alphabeta0 depth=" << depth
        << " nodes=" << TRACE_NODES.load(std::memory_order_relaxed)
        << " cutoffs=" << TRACE_CUTOFFS.load(std::memory_order_relaxed)
        << endl;
}

Uint16 Strategy::opponentOf(Uint16 player) const
{
    return (player == 0) ? 1 : 0;
}

void Strategy::applyMove(const movement& mv)
{
    int dist = std::max(std::abs(mv.nx - mv.ox), std::abs(mv.ny - mv.oy));

    // Saut: le pion part de l'ancienne case.
    if (dist == 2)
    {
        _blobs.set(mv.ox, mv.oy, -1);
    }

    // La destination prend la couleur du joueur courant.
    _blobs.set(mv.nx, mv.ny, _current_player);

    // Conversion des voisins directs.
    for (int ox = -1; ox <= 1; ox++)
    {
        for (int oy = -1; oy <= 1; oy++)
        {
            int x = mv.nx + ox;
            int y = mv.ny + oy;
            if (!insideBoard(x, y))
            {
                continue;
            }
            if (_blobs.get(x, y) != -1 && _blobs.get(x, y) != (int)_current_player)
            {
                _blobs.set(x, y, _current_player);
            }
        }
    }
}

int Strategy::mobilityBalanceFor(Uint16 me, Uint16 opponent) const
{
    int myMoves = 0;
    int opponentMoves = 0;

    // Difference entre mes coups possibles et ceux de l'adversaire.
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            Sint16 owner = _blobs.get(x, y);
            if (owner != (int)me && owner != (int)opponent)
            {
                continue;
            }

            for (int nx = std::max(0, x - 2); nx <= std::min(7, x + 2); nx++)
            {
                for (int ny = std::max(0, y - 2); ny <= std::min(7, y + 2); ny++)
                {
                    if (nx == x && ny == y)
                    {
                        continue;
                    }
                    if (_holes.get(nx, ny) || _blobs.get(nx, ny) != -1)
                    {
                        continue;
                    }
                    if (owner == (int)me)
                    {
                        myMoves++;
                    }
                    else
                    {
                        opponentMoves++;
                    }
                }
            }
        }
    }

    return myMoves - opponentMoves;
}

Sint32 Strategy::estimateCurrentScore() const
{
    Uint16 me = _current_player;
    Uint16 opponent = opponentOf(me);
    int material = 0;
    int empty = 0;
    int playable = 0;
    int positionBalance = 0;

    // On calcule materiel, cases vides et position en une passe.
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (_holes.get(x, y))
            {
                continue;
            }

            playable++;
            Sint16 owner = _blobs.get(x, y);
            if (owner == -1)
            {
                empty++;
                continue;
            }

            int sign = (owner == (int)me) ? 1 : -1;
            material += sign;
            if (owner == (int)me || owner == (int)opponent)
            {
                positionBalance += sign * WEIGHT[x][y];
            }
        }
    }

    int mobility = mobilityBalanceFor(me, opponent);
    // En fin de partie, le nombre de pions compte plus.
    if (empty * 5 < playable)
    {
        return 220 * material + mobility;
    }

    if (empty * 2 > playable)
    {
        return 115 * material + 3 * mobility + 4 * positionBalance;
    }

    return 145 * material + 2 * mobility + 3 * positionBalance;
}

vector<movement>& Strategy::computeValidMoves(vector<movement>& valid_moves) const
{
    valid_moves.clear();

    // Meme generation que les autres strategies.
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

Sint32 Strategy::moveOrderingScore(const movement& mv) const
{
    int dx = std::abs(mv.nx - mv.ox);
    int dy = std::abs(mv.ny - mv.oy);
    bool copyMove = std::max(dx, dy) == 1;
    int captured = 0;

    // Plus un coup capture, plus on veut le tester tot.
    for (int x = mv.nx - 1; x <= mv.nx + 1; x++)
    {
        for (int y = mv.ny - 1; y <= mv.ny + 1; y++)
        {
            if (!insideBoard(x, y) || _holes.get(x, y))
            {
                continue;
            }
            if (_blobs.get(x, y) != -1 && _blobs.get(x, y) != (int)_current_player)
            {
                captured++;
            }
        }
    }

    int immediateGain = (copyMove ? 1 : 0) + 2 * captured;
    int copyBonus = copyMove ? 25 : 0;
    int destinationBonus = WEIGHT[mv.nx][mv.ny];

    return 1000 * immediateGain + 20 * destinationBonus + copyBonus;
}

void Strategy::orderMoves(vector<movement>& moves) const
{
    std::sort(moves.begin(), moves.end(), [this](const movement& a, const movement& b)
    {
        return moveOrderingScore(a) > moveOrderingScore(b);
    });
}

void Strategy::computeBestMove()
{
    vector<movement> moves;
    computeValidMoves(moves);
    resetTrace();

    if (moves.empty())
    {
        printTrace(0);
        return;
    }

    orderMoves(moves);
    movement bestMove = moves[0];
    Sint32 bestScore = -STRATEGY_INF;
    int moveCount = (int)moves.size();

    // Version intermediaire: on parallelise juste les coups racine.
#pragma omp parallel for schedule(dynamic) if(moveCount > 1)
    for (int i = 0; i < moveCount; i++)
    {
        Strategy child(*this);
        child.applyMove(moves[i]);
        child._current_player = opponentOf(_current_player);

        Sint32 value = child.alphaBeta(_current_player, -STRATEGY_INF, STRATEGY_INF, false, ALPHABETA0_DEPTH - 1);

#pragma omp critical(strategy_alphabeta0_best)
        {
            if (value > bestScore)
            {
                bestScore = value;
                bestMove = moves[i];
            }
        }
    }

    _saveBestMove(bestMove);
    printTrace(ALPHABETA0_DEPTH);
}

Sint32 Strategy::alphaBeta(Uint16 rootPlayer, Sint32 alpha, Sint32 beta, bool isMax, int depth) const
{
    TRACE_NODES.fetch_add(1, std::memory_order_relaxed);

    // Feuille atteinte: on evalue du point de vue du joueur racine.
    if (depth == 0)
    {
        Strategy evaluated(*this);
        evaluated._current_player = rootPlayer;
        return evaluated.estimateCurrentScore();
    }

    vector<movement> moves;
    computeValidMoves(moves);

    if (moves.empty())
    {
        // Pas de coup: on passe au joueur suivant.
        Strategy opponentState(*this);
        opponentState._current_player = opponentOf(_current_player);
        vector<movement> opponentMoves;
        opponentState.computeValidMoves(opponentMoves);

        if (opponentMoves.empty())
        {
            Strategy evaluated(*this);
            evaluated._current_player = rootPlayer;
            return evaluated.estimateCurrentScore();
        }

        Strategy passed(*this);
        passed._current_player = opponentOf(_current_player);
        return passed.alphaBeta(rootPlayer, alpha, beta, !isMax, depth - 1);
    }

    orderMoves(moves);

    if (isMax)
    {
        for (const movement& mv : moves)
        {
            Strategy child(*this);
            child.applyMove(mv);
            child._current_player = opponentOf(_current_player);

            Sint32 value = child.alphaBeta(rootPlayer, alpha, beta, false, depth - 1);
            if (value > alpha)
            {
                alpha = value;
            }
            if (alpha >= beta)
            {
                // Coupure: le reste ne peut plus changer la decision.
                TRACE_CUTOFFS.fetch_add(1, std::memory_order_relaxed);
                return alpha;
            }
        }
        return alpha;
    }

    for (const movement& mv : moves)
    {
        Strategy child(*this);
        child.applyMove(mv);
        child._current_player = opponentOf(_current_player);

        Sint32 value = child.alphaBeta(rootPlayer, alpha, beta, true, depth - 1);
        if (value < beta)
        {
            beta = value;
        }
        if (beta <= alpha)
        {
            // Meme idee cote min.
            TRACE_CUTOFFS.fetch_add(1, std::memory_order_relaxed);
            return beta;
        }
    }

    return beta;
}
