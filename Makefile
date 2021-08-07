# the compiler: gcc for C program, g++ for C++ program
CXX = g++

# compiler flags:
#  -g      adds debugging information to the executable file
#  -Wall   turns on most, but not all, compiler warnings
#  -Wextra enables some extra warning flags that are not enabled by -Wall
CXX_FLAGS = --std=c++17 -g -Wall -Wextra -O3
OPENMP = -fopenmp

# All output target executables
TARGETS = sudoku_main

# All object files
OBJECTS = *.o *.out

DEPENDENCIES = \
	SudokuBoard.cpp \
	SudokuBoardDeque.cpp \
	SudokuTest.cpp \
	SudokuSolver.cpp \
	SudokuSolver_SequentialBacktracking.cpp \
	SudokuSolver_SequentialBruteForce.cpp \
	SudokuSolver_ParallelBruteForce.cpp \
	Node.cpp \
	SudokuSolver_SequentialDancingLinks.cpp

all: $(TARGETS)

sudoku_main: sudoku_main.cpp $(DEPENDENCIES)
	$(CXX) $(CXX_FLAGS) $(OPENMP) -o $@ $^

clean:
	rm -f $(TARGETS) $(OBJECTS) solution.txt