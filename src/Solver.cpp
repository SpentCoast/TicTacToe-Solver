#include "Solver.h"

namespace TicTacToe
{
    SearchResult Solver::GetBestMove(const Board& board)
    {
        uint64_t nodeCount = 1;

        MoveList moves = board.GetLegalMoves();
        if (moves.empty())
        {
            return { 0, nodeCount };
        }

        int alpha = -INF;
        int beta = INF;
        int bestMove = moves[0];

        for (int move : moves)
        {
            Board next = board;
            next.PlayMove(move);

            int score = -negamax(next, -beta, -alpha, nodeCount);
            if (score > alpha)
            {
                alpha = score;
                bestMove = move;
            }
        }

        return { bestMove, nodeCount };
    }

    int Solver::negamax(const Board& board, int alpha, int beta, uint64_t& nodeCount)
    {
        nodeCount++;

        MoveList moves = board.GetLegalMoves();
        if (board.HasWon())
        {
            return -(static_cast<int>(moves.size()) + 1);
        }

        if (moves.empty())
        {
            return 0;
        }

        int bestScore = -INF;

        for (int move : moves)
        {
            Board next = board;
            next.PlayMove(move);

            int score = -negamax(next, -beta, -alpha, nodeCount);
            if (score > bestScore)
            {
                bestScore = score;
            }
            if (bestScore > alpha)
            {
                alpha = bestScore;
            }
            if (alpha >= beta)
            {
                break;
            }
        }

        return bestScore;
    }

}
