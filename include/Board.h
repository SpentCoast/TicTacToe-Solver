#pragma once

#include <array>
#include <cstdint>

namespace TicTacToe
{
    using Bitboard = uint16_t;

    constexpr int BOARD_SIZE = 9;

    constexpr std::array<Bitboard, 8> WinConditions = {
        0x0007, 0x0038, 0x01C0, // Rows
        0x0049, 0x0092, 0x0124, // Columns
        0x0111, 0x0054          // Diagonals
    };

    enum class PieceType
    {
        X,
        O
    };

    struct MoveList
    {
        std::array<int, BOARD_SIZE> moves{};
        int count = 0;

        void push_back(int move) { moves[count++] = move; }

        [[nodiscard]] int size() const { return count; }
        [[nodiscard]] bool empty() const { return count == 0; }

        [[nodiscard]] const int* begin() const { return moves.data(); }
        [[nodiscard]] const int* end() const { return moves.data() + count; }
        [[nodiscard]] int operator[](int index) const { return moves[index]; }
    };

    class Board
    {
    public:
        [[nodiscard]] MoveList GetLegalMoves() const;
        void PlayMove(int move);
        [[nodiscard]] bool HasWon() const;
        [[nodiscard]] bool IsGameOver() const;
        void Print() const;

        [[nodiscard]] PieceType GetTurn() const { return m_Turn; }

    private:
        Bitboard m_Player{};
        Bitboard m_Mask{};
        PieceType m_Turn = PieceType::X;
    };
}
