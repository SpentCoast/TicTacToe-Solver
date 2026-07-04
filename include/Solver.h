#pragma once

#include "Board.h"

#include <cstdint>

namespace TicTacToe
{
    struct SearchResult
    {
        int BestMove;
        uint64_t NodesEvaluated;
    };

    class Solver
    {
    public:
        [[nodiscard]] SearchResult GetBestMove(const Board& board);

    private:
        [[nodiscard]] int negamax(const Board& board, int alpha, int beta, uint64_t& nodeCount);

        static constexpr int INF = 1000;
    };
}
