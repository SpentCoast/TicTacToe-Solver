# Tic-Tac-Toe Solver

An optimized (probably), C++ engine that plays a mathematically perfect game of Tic-Tac-Toe. 

Built with **C++20**, the project uses the **Negamax algorithm with Alpha-Beta pruning**.

## Technical Features

* **Zero-Allocation Hot Path:** Completely eliminates heap allocations during the tree search. Moves are generated using a custom, stack-allocated `MoveList` backed by `std::array`, so the AI runs entirely within the CPU's L1/L2 cache.
* **Stateless & Thread-Safe:** The `Solver` class maintains zero internal state between evaluations. Game states and node counts are passed by reference or returned via a `SearchResult` struct, allowing multiple threads to safely share the same solver instance simultaneously.
* **Compile-Time Bitboards:** Board states are managed using 16-bit integers (`uint16_t`), and win-conditions are evaluated against a `std::array` of bitmasks, incurring zero runtime setup overhead.
* **Alpha-Beta Pruning:** Reduces the depth of the search tree by ignoring branches that mathematically cannot yield a better result than previously evaluated moves.

## Getting Started

### Prerequisites
* A C++20 compatible compiler (GCC, Clang, or MSVC)
* CMake (3.10 or higher)

### Build Instructions

```bash
# 1. Clone the repository
git clone [https://github.com/SpentCoast/TicTacToe-Solver.git](https://github.com/SpentCoast/TicTacToe-Solver.git)
cd TicTacToe-Solver

# 2. Configure the CMake project for maximum optimization
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# 3. Compile the executable
cmake --build build

# 4. Run the game
./build/TicTacToe-Solver
```
*(Note: On Windows/MSVC, the executable may be located in `./build/Release/TicTacToe-Solver.exe`)*

## Gameplay & Interactive CLI

When you launch the executable, you will be prompted to select a game mode:
1. You play X (AI plays O)
2. You play O (AI plays X)
3. AI vs AI   (Watch it play)

After every AI turn, the engine outputs real-time performance metrics, including the total nodes evaluated, the calculation time down to the microsecond, and the **Nodes Per Second (NPS)** throughput.

## Project Architecture

```text
TicTacToe-Solver/
├── CMakeLists.txt  # C++20 build config
├── include         # Public iterfaces
│   ├── Board.h     # Bitboard and Movelist definitions
│   └── Solver.h    # Stateless negamax engine
└── src             # Implementations
    ├── Board.cpp   # Move generation and win checks
    ├── Main.cpp    # Interactive CLI and game loop
    └── Solver.cpp  # Negamax search logic

3 directories, 6 files
```
