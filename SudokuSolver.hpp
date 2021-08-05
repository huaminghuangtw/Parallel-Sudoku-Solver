#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP


#include "SudokuBoard.hpp"
#include <utility>


using Position = std::pair<int, int>;


class SudokuSolver
{	
protected:
	bool _solved = false;
	SudokuBoard _solution;
	int _recursionDepth = 0;
	int _current_num_empty_cells;

public:
	SudokuSolver() = default;

	// Checks if the Sudoku board is ALL filled up
	bool checkIfAllFilled(const SudokuBoard& board) const;
	bool checkIfRowFilled(const SudokuBoard& board, int indexOfRows) const;

	// Finds the first empty cell on the given Sudoku board
	const std::pair<int, int> find_empty(const SudokuBoard& board);
	int find_empty_from_row(const SudokuBoard& board, int indexOfRows) const;

	// Checks if the given cell position is empty
	bool isEmpty(const SudokuBoard& board, int i, int j) const;

	// Checks if num already exists in the given row
	bool isValidRow(const SudokuBoard& board, int num, Position pos) const;

	// Checks if num already exists in the given column
	bool isValidColumn(const SudokuBoard& board, int num, Position pos) const;

    // Checks if num already exists in the given box (subgrid)
	bool isValidBox(const SudokuBoard& board, int num, Position pos) const;

	// Checks if a given number can be inserted at a given cell position
	bool isValid(const SudokuBoard& board, int num, Position pos) const;

	bool get_status() const;
	SudokuBoard get_solution() const;

	virtual ~SudokuSolver() = default;
};


#endif   // SUDOKUSOLVER_HPP