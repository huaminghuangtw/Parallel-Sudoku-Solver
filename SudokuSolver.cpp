#include "SudokuSolver.hpp"


SolverStatus SudokuSolver::get_solver_status() const
{
	return _status;
}

SudokuBoard SudokuSolver::get_solution() const
{
	return _solution;
}