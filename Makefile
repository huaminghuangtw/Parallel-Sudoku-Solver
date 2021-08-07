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
	./src/SudokuBoard.cpp \
	./src/SudokuBoardDeque.cpp \
	./src/SudokuTest.cpp \
	./src/SudokuSolver.cpp \
	./src/SudokuSolver_SequentialBacktracking.cpp \
	./src/SudokuSolver_SequentialBruteForce.cpp \
	./src/SudokuSolver_ParallelBruteForce.cpp \
	./src/Node.cpp \
	./src/SudokuSolver_SequentialDancingLinks.cpp \
	./src/SudokuSolver_ParallelDancingLinks.cpp

all: $(TARGETS)

sudoku_main: sudoku_main.cpp $(DEPENDENCIES)
	$(CXX) $(CXX_FLAGS) $(OPENMP) -I ./inc -o $@ $^

clean:
	rm -f $(TARGETS) $(OBJECTS) solution.txt