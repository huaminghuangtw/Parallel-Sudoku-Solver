CXX = g++
CXX_FLAGS = --std=c++17 -Wall -Wextra -O3
OPENMP = -fopenmp

executables = sudoku_main

dependencies = \
	SudokuBoard.cpp \
	TestableSudoku.cpp \
	SudokuSolver.cpp \
	SudokuSolver_SequentialBacktracking.cpp \
	SudokuSolver_ParallelBacktracking.cpp \

all: $(executables)

sudoku_main: sudoku_main.cpp $(dependencies)
	$(CXX) $(CXX_FLAGS) $(OPENMP) -o $@ $^

clean:
	rm -f $(executables) *.o *.out solution.txt