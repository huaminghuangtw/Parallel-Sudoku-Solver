CXX = g++
CXX_FLAGS = --std=c++17 -Wall -Wextra -fopenmp -O3

all: sudoku_sequential sudoku_parallel

sudoku_sequential:
	$(CXX) $(CXX_FLAGS) -o sudoku_sequential sudoku_sequential.cpp SudokuBoard.cpp SudokuSolver.cpp TestableSudoku.cpp SudokuSolver_SequentialBacktracking.cpp

sudoku_parallel:
	$(CXX) $(CXX_FLAGS) -o sudoku_parallel sudoku_parallel.cpp SudokuBoard.cpp SudokuSolver.cpp TestableSudoku.cpp SudokuSolver_SequentialBacktracking.cpp SudokuSolver_ParallelBacktracking.cpp

clean:
	rm -f sudoku_sequential sudoku_parallel *.o *.out solution.txt