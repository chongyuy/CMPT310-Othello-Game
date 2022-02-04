cmake_minimum_required(VERSION 3.15)
project(a5)

set(CMAKE_CXX_STANDARD 14)

add_executable(a5 main.cpp Reversi.cpp Reversi.h MCTS.cpp MCTS.h heuMCTS.cpp heuMCTS.h)