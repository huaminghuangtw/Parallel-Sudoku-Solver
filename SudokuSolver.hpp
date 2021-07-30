#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP


#include "SudokuBoard.hpp"


enum class SolverStatus
{
    SOLVED,
    UNSOLVABLE
};


class SudokuSolver
{
protected:
	bool _solved = false;
	SolverStatus _status = SolverStatus::UNSOLVABLE;
	SudokuBoard _solution;
	void solve(SudokuBoard& board);

public:
	SudokuSolver() = default;

	SolverStatus get_solver_status() const;
	SudokuBoard get_solution() const;

	virtual ~SudokuSolver() { }
};


#endif   // SUDOKUSOLVER_HPP