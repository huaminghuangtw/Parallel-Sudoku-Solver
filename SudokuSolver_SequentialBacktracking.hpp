#ifndef SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP
#define SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"


class SudokuSolver_SequentialBacktracking : public SudokuSolver
{
public:
	SudokuSolver_SequentialBacktracking();

	// Solves the given Sudoku board using sequential backtracking algorithm
	void solve(SudokuBoard& board);
};


#endif   // SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP