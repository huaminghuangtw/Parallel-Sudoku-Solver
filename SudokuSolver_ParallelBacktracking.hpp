#ifndef SUDOKUSOLVER_PARALLELBACKTRACKING_HPP
#define SUDOKUSOLVER_PARALLELBACKTRACKING_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"


class SudokuSolver_ParallelBacktracking : public SudokuSolver
{
public:
	SudokuSolver_ParallelBacktracking(bool print_message=true);

	// Solves the given Sudoku board using parallel backtracking algorithm
	void solve(SudokuBoard& board);
};


#endif   // SUDOKUSOLVER_PARALLELBACKTRACKING_HPP