#include "Board.h"
#include "Solver.h"

#include <chrono>
#include <iostream>
#include <iomanip>
#include <thread>

void PrintHeader()
{
    std::cout << "=================================\n";
    std::cout << "    TIC-TAC-TOE : NEGAMAX AI     \n";
    std::cout << "=================================\n";
}

int main()
{
    PrintHeader();

    bool aiPlaysX = false;
    bool aiPlaysO = false;

    std::cout << "Select Game Mode:\n";
    std::cout << "1. You play X (AI plays O)\n";
    std::cout << "2. You play O (AI plays X)\n";
    std::cout << "3. AI vs AI   (Watch it play)\n";

    int choice = 0;
    while (true)
    {
        std::cout << "Choice (1-3): ";
        if (std::cin >> choice && choice >= 1 && choice <= 3) break;

        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Please enter 1, 2, or 3.\n";
    }

    if (choice == 2) {
        aiPlaysX = true;
    }
    else if (choice == 3) {
        aiPlaysX = true;
        aiPlaysO = true;
    }
    else {
        aiPlaysO = true;
    }

    std::cout << "\nGame Start!\n";

    TicTacToe::Board board;
    TicTacToe::Solver solver;

    while (!board.IsGameOver())
    {
        board.Print();

        bool isAITurn = (board.GetTurn() == TicTacToe::PieceType::X && aiPlaysX) ||
            (board.GetTurn() == TicTacToe::PieceType::O && aiPlaysO);

        if (isAITurn)
        {
            std::cout << "\nAI (" << (board.GetTurn() == TicTacToe::PieceType::X ? "X" : "O") << ") is thinking...\n";

            auto start = std::chrono::high_resolution_clock::now();
            TicTacToe::SearchResult result = solver.GetBestMove(board);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            double seconds = duration.count();

            board.PlayMove(result.BestMove);

            std::cout << "--- AI Stats ---\n";
            std::cout << "Nodes            : " << result.NodesEvaluated << "\n";
            std::cout << "Time             : " << std::fixed << std::setprecision(5) << seconds << " sec\n";

            if (seconds > 0.0)
            {
                uint64_t nps = static_cast<uint64_t>(result.NodesEvaluated / seconds);
                std::cout << "Nodes Per Second : " << nps << " NPS\n";
            }
            std::cout << "----------------\n";

            if (aiPlaysX && aiPlaysO)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        else
        {
            int move;
            std::cout << "\nYour move (" << (board.GetTurn() == TicTacToe::PieceType::X ? "X" : "O") << ") [1-9]: ";

            if (!(std::cin >> move))
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
                continue;
            }

            TicTacToe::MoveList legal = board.GetLegalMoves();
            bool valid = false;
            for (int m : legal)
            {
                if (m == move) { valid = true; break; }
            }

            if (!valid)
            {
                std::cout << "Illegal move! Try again.\n";
                continue;
            }

            board.PlayMove(move);
        }
    }

    board.Print();
    std::cout << "=================================\n";

    if (board.HasWon())
    {
        std::cout << "             " << (board.GetTurn() == TicTacToe::PieceType::X ? "O" : "X") << " WINS!\n";
    }
    else
    {
        std::cout << "         IT'S A DRAW!\n";
    }
    std::cout << "=================================\n\n";

    return 0;
}