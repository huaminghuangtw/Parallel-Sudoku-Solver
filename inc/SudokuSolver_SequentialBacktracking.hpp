#ifndef SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP
#define SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include <thread>
#include <chrono>


class SudokuSolver_SequentialBacktracking : public SudokuSolver
{
public:
	SudokuSolver_SequentialBacktracking(bool print_message=true);

	// Solves the given Sudoku board using sequential backtracking algorithm
	bool solve(SudokuBoard& board);
};


#endif   // SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP