#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP

#include <vector>
#include <string>


using Board = std::vector<std::vector<int>>;


class SudokuBoard
{
private:
	size_t _box_size;
	size_t _board_size;
	Board _board_data;

public:
	// Returns a 2D array reading from a file containing the initial Sudoku board in space separated format
	// (empty cells are represented by 0s)
	const Board read_input(const std::string& filename);

	SudokuBoard() = default;
	SudokuBoard(const std::string& filename);
	// copy constructor
	SudokuBoard(const SudokuBoard& another_sudokuboard);

	size_t get_box_size() const;
	size_t get_board_size() const;
	void set_board_data(size_t row, size_t col, int num);
	Board get_board_data() const;

	int operator()(size_t i, size_t j);
	// copy-assignment operator
	SudokuBoard& operator=(const SudokuBoard& another_sudokuboard);
	

	// Prints the Sudoku board
	friend void print_board(const SudokuBoard& board);
};


#endif   // SUDOKUBOARD_HPP