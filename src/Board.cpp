#include "Board.h"

#include <iostream>

namespace TicTacToe
{
    MoveList Board::GetLegalMoves() const
    {
        MoveList moves;

        for (int i = 0; i < 9; ++i)
        {
            if (((m_Mask >> i) & 1) == 0)
            {
                moves.push_back(i + 1);
            }
        }

        return moves;
    }

    void Board::PlayMove(int move)
    {
        if (((m_Mask >> (move - 1)) & 1) == 0)
        {
            m_Player ^= m_Mask;
            m_Mask |= 1 << (move - 1);
            m_Turn = (m_Turn == PieceType::X) ? PieceType::O : PieceType::X;
        }
    }

    bool Board::HasWon() const
    {
        Bitboard winningPlayer = m_Player ^ m_Mask;

        for (Bitboard condition : WinConditions)
        {
            if ((winningPlayer & condition) == condition)
            {
                return true;
            }
        }

        return false;
    }

    bool Board::IsGameOver() const
    {
        return HasWon() || GetLegalMoves().empty();
    }

    void Board::Print() const
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            if (i > 0 && i % 3 == 0)
            {
                std::cout << "\n---+---+---\n";
            }
            else if (i % 3 != 0)
            {
                std::cout << "|";
            }

            if (((m_Player >> i) & 1) == 1)
            {
                std::cout << ((m_Turn == PieceType::X) ? " X " : " O ");
            }
            else if ((((m_Player ^ m_Mask) >> i) & 1) == 1)
            {
                std::cout << ((m_Turn == PieceType::X) ? " O " : " X ");
            }
            else
            {
                std::cout << " " << (i + 1) << " ";
            }
        }

        std::cout << "\n";
    }
}
