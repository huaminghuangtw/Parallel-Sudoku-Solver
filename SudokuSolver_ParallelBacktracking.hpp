#ifndef SUDOKUSOLVER_PARALLELBACKTRACKING_HPP
#define SUDOKUSOLVER_PARALLELBACKTRACKING_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver_SequentialBacktracking.hpp"


class SudokuSolver_ParallelBacktracking : public SudokuSolver_SequentialBacktracking
{
private:
	// Solves the given Sudoku board using parallel backtracking algorithm
	virtual void solve(SudokuBoard& board) override;

public:
	SudokuSolver_ParallelBacktracking() = default;
	SudokuSolver_ParallelBacktracking(SudokuBoard& board);
};


#endif   // SUDOKUSOLVER_PARALLELBACKTRACKING_HPP