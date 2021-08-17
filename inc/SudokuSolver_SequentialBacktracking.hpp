#ifndef SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP
#define SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"


class SudokuSolver_SequentialBacktracking : public SudokuSolver
{
public:
	SudokuSolver_SequentialBacktracking(SudokuBoard& board, bool print_message=true);

	// Solves the given Sudoku board using sequential backtracking algorithm
    virtual void solve() { solve_kernel(); }
	bool solve_kernel();
};


#endif   // SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP