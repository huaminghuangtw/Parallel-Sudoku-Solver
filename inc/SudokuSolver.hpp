#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP


#include "SudokuBoard.hpp"
#include <utility>


using Position = std::pair<int, int>;


enum class MODES
{
	SEQUENTIAL_BACKTRACKING,     // Sequential mode using backtracking algorithm
	SEQUENTIAL_BRUTEFORCE,       // Sequential mode using brute force algorithm
	PARALLEL_BRUTEFORCE,         // OpenMP mode using brute force algorithm
	SEQUENTIAL_DANCINGLINKS,     // Sequential mode using dancing links algorithm
	PARALLEL_DANCINGLINKS,       // OpenMP mode using dancing links algorithm
	SEQUENTIAL_FORWARDCHECKING   // Sequential mode using forward checking algorithm
};


class SudokuSolver
{	
protected:
	SudokuBoard _board;
	bool _solved = false;
	SudokuBoard _solution;
	int _recursionDepth = 0;
	int _current_num_empty_cells;
	MODES _mode;

public:
	SudokuSolver(SudokuBoard& board);

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

	// Checks the uniqueness of a given valid number by seeing the occurrence of pairs of that number
	// within the neighboring rows and columns in the same box
	bool isUnique(const SudokuBoard& board, int num, Position pos) const;

	virtual void solve() = 0;
	
	void set_mode(MODES mode) { _mode = mode; }
	bool get_status() const { return _solved; }
	SudokuBoard get_solution() const { return _solution; }

	void show_progress_bar(SudokuBoard& board, int recursionDepth, int interval=5);

	virtual ~SudokuSolver() = default;
};


#endif   // SUDOKUSOLVER_HPP