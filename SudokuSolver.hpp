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
	virtual void solve(SudokuBoard& board) = 0;
	SolverStatus _status = UNSOLVABLE;

public:
	SudokuSolver() = default;
	SolverStatus get_solver_status() const;
	virtual ~SudokuSolver() = default;
};


#endif   // SUDOKUSOLVER_HPP