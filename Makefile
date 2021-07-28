CXX = g++
CXX_FLAGS = --std=c++17 -Wall -Wextra -fopenmp -O3

all: sudoku_sequential

sudoku_sequential: sudoku_sequential.cpp SudokuBoard.cpp SudokuBoard.hpp SudokuSolver.cpp SudokuSolver.hpp SudokuSolver_SequentialBacktracking.cpp SudokuSolver_SequentialBacktracking.hpp
	$(CXX) $(CXX_FLAGS) -o sudoku_sequential sudoku_sequential.cpp SudokuBoard.cpp SudokuSolver.cpp SudokuSolver_SequentialBacktracking.cpp

clean:
	rm -f sudoku_sequential *.o *.out