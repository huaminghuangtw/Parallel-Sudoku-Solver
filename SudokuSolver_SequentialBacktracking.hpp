#ifndef SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP
#define SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include <utility>


class SudokuSolver_SequentialBacktracking : public SudokuSolver
{
private:
	// Solves the given Sudoku board using backtracking algorithm
	virtual void solve(SudokuBoard& board) override;

public:
	SudokuSolver_SequentialBacktracking() = default;
	SudokuSolver_SequentialBacktracking(SudokuBoard& board);

	// Checks if the Sudoku board is ALL filled up
	bool checkIfAllFilled(SudokuBoard& board) const;

	// Finds the first empty cell on the given Sudoku board
	const std::pair<size_t, size_t> find_empty(SudokuBoard& board);
};


#endif   // SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP