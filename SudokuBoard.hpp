#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP


#include <vector>
#include <string>
#include <iostream>


using Board = std::vector<std::vector<int>>;


class SudokuBoard
{
	friend class SudokuSolver;
	friend class SudokuTest;

private:
	int _box_size;
	int _board_size;
	Board _board_data;
	int _init_num_empty_cells;
	const int _empty_cell_value = 0;
	const std::string _empty_cell_character = ".";

public:
	// Returns a 2D vector reading from a file containing the initial Sudoku board in space separated format
	// (empty cells are represented by 0s)
	const Board read_input(const std::string& filename);

	// Writes solution to a text file (solution.txt)
	friend void write_output(const SudokuBoard& solutionBoard);

	SudokuBoard() = default;
	SudokuBoard(const std::string& filename);
	// copy constructor
	SudokuBoard(const SudokuBoard& another_sudokuboard);

	int get_box_size() const;
	int get_board_size() const;
	void set_board_data(int row, int col, int num);
	int get_board_data(int row, int col) const;
	Board get_board_data() const;
	int get_empty_cell_value() const;
	std::string get_empty_cell_character() const;
	int get_num_total_cells() const;
	int get_num_empty_cells() const;
	int get_init_num_empty_cells() const;

	int at(int i, int j) const;

	std::vector<int> getNumbersInRow(int indexOfRows) const;
	std::vector<int> getNumbersInCol(int indexOfColumns) const;

	// copy-assignment operator
	SudokuBoard& operator= (const SudokuBoard& another_sudokuboard);
	
	// Prints the Sudoku board
	friend void print_board(const SudokuBoard& board);
    friend std::ostream& operator<< (std::ostream &out, const SudokuBoard& board);
};


#endif   // SUDOKUBOARD_HPP