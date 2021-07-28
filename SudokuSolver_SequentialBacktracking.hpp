#ifndef SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP
#define SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include <utility>


class SudokuSolver_SequentialBacktracking : public SudokuSolver
{
	friend class SudokuBoard;

private:
	bool _solved = false;
	SudokuBoard _answer;

	// Solves the given Sudoku board using backtracking algorithm
	virtual void solve(SudokuBoard& board) override;

public:
	SudokuSolver_SequentialBacktracking() = default;
	SudokuSolver_SequentialBacktracking(SudokuBoard& board);

	SudokuBoard get_answer() const;

	// Checks if the Sudoku board is ALL filled up
	bool checkIfAllFilled(SudokuBoard& board) const;

	// Finds the first empty cell on the given Sudoku board
	const std::pair<size_t, size_t> find_empty(SudokuBoard& board);

	// Checks if num already exists in the given row
	bool checkValidRow(SudokuBoard& board, int num, std::pair<size_t, size_t> pos) const;

	// Checks if num already exists in the given column
	bool checkValidColumn(SudokuBoard& board, int num, std::pair<size_t, size_t> pos) const;

    // Checks if num already exists in the given box (subgrid)
	bool checkValidBox(SudokuBoard& board, int num, std::pair<size_t, size_t> pos) const;

	// Checks if a given number can be inserted at a given cell position
	bool isValid(SudokuBoard& board, int num, std::pair<size_t, size_t> pos) const;
};


#endif   // SUDOKUSOLVER_SEQUENTIALBACKTRACKING_HPP