#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP


#include "SudokuBoard.hpp"


enum SolverStatus
{
    SOLVED,
    UNSOLVABLE
};


class SudokuSolver
{
protected:
	bool _solved = false;
	SolverStatus _status = UNSOLVABLE;
	SudokuBoard _solution;
	virtual void solve(SudokuBoard& board) = 0;

public:
	SudokuSolver() = default;

	SolverStatus get_solver_status() const;
	SudokuBoard get_solution() const;

	virtual ~SudokuSolver() = default;
};


#endif   // SUDOKUSOLVER_HPP