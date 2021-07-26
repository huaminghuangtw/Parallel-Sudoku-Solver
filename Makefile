CXX = g++
CXX_FLAGS = --std=c++17 -Wall -Wextra -fopenmp -O3

all: sudoku_sequential sudoku_parallel

sudoku_sequential: sudoku_sequential.cpp utility.cpp utility.hpp
	$(CXX) $(CXX_FLAGS) -o sudoku_sequential sudoku_sequential.cpp utility.cpp

sudoku_parallel: sudoku_parallel.cpp utility.cpp utility.hpp
	$(CXX) $(CXX_FLAGS) -o sudoku_parallel sudoku_parallel.cpp utility.cpp

clean:
	rm -f sudoku_sequential sudoku_parallel *.o *.out