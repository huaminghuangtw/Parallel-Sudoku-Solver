#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP


#include <vector>
#include <string>
#include <iostream>
#include <variant>
#include <set>


using Board = std::vector<std::vector<int>>;
// Size: _BOARD_SIZE * _BOARD_SIZE

using CoverMatrix = std::vector<std::vector<int>>;
// Size: (_BOARD_SIZE * _BOARD_SIZE * _MAX_VALUE) * (_BOARD_SIZE * _BOARD_SIZE * _NUM_CONSTRAINTS)

using MultiType = std::variant<int, std::set<int>>;
using StateMatrix = std::vector<std::vector<MultiType>>;
// Size: _BOARD_SIZE * _BOARD_SIZE


class SudokuBoard
{
	friend class SudokuSolver;
	friend class SudokuTest;

private:
	Board _board_data;
	int _BOX_SIZE;
	int _BOARD_SIZE;
	int _MIN_VALUE = 1;
	int _MAX_VALUE = _BOARD_SIZE;
	int _NUM_CONSTRAINTS = 4;   // 4 constraints : cell, row, column, box
	int _INIT_NUM_EMPTY_CELLS;
	int _EMPTY_CELL_VALUE = 0;
	std::string _EMPTY_CELL_CHARACTER = ".";
	int _COVER_MATRIX_START_INDEX = 1;
	
public:
	// Returns a 2D vector reading from a file containing the initial Sudoku board in space separated format
	// (empty cells are represented by 0s)
	const Board read_input(const std::string& filename);

	// Writes solution to a text file (solution.txt)
	friend void write_output(const SudokuBoard& solutionBoard);

	SudokuBoard() = default;
	SudokuBoard(const std::string& filename);
	// copy constructor
	SudokuBoard(const SudokuBoard& anotherSudokuBoard);

	void set_board_data(int row, int col, int num) { _board_data[row][col] = num; }
	int get_board_data(int row, int col) const { return _board_data[row][col]; }
	Board get_board_data() const { return _board_data; }
	int at(int row, int col) const { return _board_data[row][col]; }

	int get_box_size() const { return _BOX_SIZE; }
	int get_board_size() const { return _BOARD_SIZE; }
	int get_min_value() const { return _MIN_VALUE; }
	int get_max_value() const { return _MAX_VALUE; }
	int get_init_num_empty_cells() const { return _INIT_NUM_EMPTY_CELLS; }
	int get_empty_cell_value() const { return _EMPTY_CELL_VALUE; }
	std::string get_empty_cell_character() const { return _EMPTY_CELL_CHARACTER; }

	int get_num_total_cells() const;
	int get_num_empty_cells() const;

	std::vector<int> getNumbersInRow(int indexOfRows) const;
	std::vector<int> getNumbersInCol(int indexOfColumns) const;

	// copy-assignment operator
	SudokuBoard& operator= (const SudokuBoard& another_sudokuboard);
	
	// Prints the input Sudoku board
    friend std::ostream& operator<< (std::ostream &out, const SudokuBoard& board);
	
	// Prints the output Sudoku board
	friend void print_board(const SudokuBoard& board);

	// Transforms the Sudoku problem into an instance of exact cover problem, i.e.,
	// models a Sudoku grid in the form of a cover matrix with size:
	// (_BOARD_SIZE * _BOARD_SIZE * _MAX_VALUE) * (BOARD_SIZE * _BOARD_SIZE * _NUM_CONSTRAINTS)
	int indexInCoverMatrix(int row, int col, int num);
	int createBoxConstraints(CoverMatrix& coverMatrix, int header);
	int createColumnConstraints(CoverMatrix& coverMatrix, int header);
	int createRowConstraints(CoverMatrix& coverMatrix, int header);
	int createCellConstraints(CoverMatrix& coverMatrix, int header);
	void createCoverMatrix(CoverMatrix& coverMatrix);
	void convertToCoverMatrix(CoverMatrix& coverMatrix);

	// Adds state information to the Sudoku board
	// by replacing empty cell, i.e., 0, with a set of possible values
	void createStateMatrix(StateMatrix& stateMatrix);
	void convertToStateMatrix(StateMatrix& stateMatrix);
};


#endif   // SUDOKUBOARD_HPP