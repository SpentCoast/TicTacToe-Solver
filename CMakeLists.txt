cmake_minimum_required(VERSION 3.10)

project(TicTacToe-Solver VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TicTacToe-Solver
    src/Main.cpp
    src/Board.cpp
    src/Solver.cpp)

target_include_directories(TicTacToe-Solver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (MSVC)
    target_compile_options(TicTacToe-Solver PRIVATE /W4 /WX)
else()
    target_compile_options(TicTacToe-Solver PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
