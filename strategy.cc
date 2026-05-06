#include "move.h"
#include "strategy.h"
#include <algorithm>
#include <atomic>
#include <cmath>

static const Sint32 STRATEGY_INF = 999999;
static const int INITIAL_SEARCH_DEPTH = 3;
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

static void updateAtomicMax(std::atomic<Sint32>& target, Sint32 value)
{
    Sint32 current = target.load(std::memory_order_relaxed);
    // Petit max atomique pour partager le meilleur alpha trouve.
    while (value > current && !target.compare_exchange_weak(current, value, std::memory_order_relaxed))
    {
    }
}

static void resetTrace()
{
    TRACE_NODES.store(0, std::memory_order_relaxed);
    TRACE_CUTOFFS.store(0, std::memory_order_relaxed);
}

static void printTrace(int depth)
{
    cout << "BW_TRACE algo=alphabeta_final depth=" << depth
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
    int dist = std::max(abs(mv.nx - mv.ox), abs(mv.ny - mv.oy));

    // Distance 2 = saut, donc on enleve la source.
    if (dist == 2)
    {
        _blobs.set(mv.ox, mv.oy, -1);
    }

    // La destination appartient au joueur courant.
    _blobs.set(mv.nx, mv.ny, _current_player);

    // Conversion des voisins adverses autour de l'arrivee.
    for (int i = std::max(0, mv.nx - 1); i <= std::min(7, mv.nx + 1); i++)
    {
        for (int j = std::max(0, mv.ny - 1); j <= std::min(7, mv.ny + 1); j++)
        {
            if (_blobs.get(i, j) != -1 && _blobs.get(i, j) != _current_player)
            {
                _blobs.set(i, j, _current_player);
            }
        }
    }
}

int Strategy::mobilityBalanceFor(Uint16 me, Uint16 opponent) const
{
    int myMoves = 0;
    int opponentMoves = 0;

    // La mobilite sert surtout a ne pas se bloquer.
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

    // Une seule boucle pour compter materiel, vides et position.
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
    // Les poids changent selon la phase de la partie.
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

    // On parcourt mes pions, puis les cases a distance 1 ou 2.
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
                        if (nx == ox && ny == oy) continue; // On ne reste pas sur la meme case.
                        if (_holes.get(nx, ny)) continue;
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

    // On met devant les coups qui gagnent vite du materiel.
    for (int x = mv.nx - 1; x <= mv.nx + 1; x++)
    {
        for (int y = mv.ny - 1; y <= mv.ny + 1; y++)
        {
            if (x < 0 || x > 7 || y < 0 || y > 7 || _holes.get(x, y))
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
    // Important pour le timeout: on a toujours un coup valide en memoire.
    _saveBestMove(bestMove);
    printTrace(0);

    for (int depth = INITIAL_SEARCH_DEPTH; ; depth++)
    {
        // On remet le dernier meilleur coup en premier.
        for (size_t i = 0; i < moves.size(); i++)
        {
            if (i != 0 &&
                moves[i].ox == bestMove.ox &&
                moves[i].oy == bestMove.oy &&
                moves[i].nx == bestMove.nx &&
                moves[i].ny == bestMove.ny)
            {
                std::swap(moves[0], moves[i]);
                break;
            }
        }

        Sint32 bestScore = -STRATEGY_INF;
        Sint32 alpha = -STRATEGY_INF;
        movement depthBestMove = bestMove;
        int moveCount = (int)moves.size();
        int sequentialCount = std::min(moveCount, std::max(1, (int)std::sqrt((double)moveCount)));

        // Petit prefixe sequentiel pour obtenir un alpha correct.
        for (int i = 0; i < sequentialCount; i++)
        {
            Strategy child(*this);
            child.applyMove(moves[i]);
            child._current_player = opponentOf(_current_player);

            Sint32 value = child.alphaBeta(_current_player, alpha, STRATEGY_INF, false, depth - 1);
            if (value > bestScore)
            {
                bestScore = value;
                depthBestMove = moves[i];
            }
            if (value > alpha)
            {
                alpha = value;
            }
        }

        std::atomic<Sint32> sharedAlpha(alpha);

        // Le reste des coups racine part en parallele.
#pragma omp parallel for schedule(dynamic) if(moveCount > sequentialCount)
        for (int i = sequentialCount; i < moveCount; i++)
        {
            Sint32 localAlpha = sharedAlpha.load(std::memory_order_relaxed);

            Strategy child(*this);
            child.applyMove(moves[i]);
            child._current_player = opponentOf(_current_player);

            Sint32 value = child.alphaBeta(_current_player, localAlpha, STRATEGY_INF, false, depth - 1);

            if (value > localAlpha)
            {
                updateAtomicMax(sharedAlpha, value);
            }

#pragma omp critical(strategy_root_best)
            {
                if (value > bestScore)
                {
                    bestScore = value;
                    depthBestMove = moves[i];
                }
            }
        }

        bestMove = depthBestMove;
        _saveBestMove(bestMove);
        printTrace(depth);
    }
}

Sint32 Strategy::alphaBeta(Uint16 rootPlayer, Sint32 alpha, Sint32 beta, bool isMax, int depth) const
{
    TRACE_NODES.fetch_add(1, std::memory_order_relaxed);

    // A profondeur 0 on evalue pour le joueur du coup initial.
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
        // Si aucun coup possible, on passe le tour.
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
                // Coupure beta: pas besoin de tester les autres coups.
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
            // Coupure cote joueur min.
            TRACE_CUTOFFS.fetch_add(1, std::memory_order_relaxed);
            return beta;
        }
    }

    return beta;
}
