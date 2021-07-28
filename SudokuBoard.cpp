#include "SudokuBoard.hpp"
#include "helper.hpp"
#include <cmath>
#include <fstream>
#include <iostream>


const Board SudokuBoard::read_input(const std::string& filename)
{
	std::ifstream infile(filename);   // open file

	if (!infile)
	{
		std::cout << "Error opening file!" << "\n";
		exit(1);
	}

	infile >> _board_size;
	_box_size = std::sqrt(_board_size);

	Board sudokuBoard(_board_size, std::vector<int> (_board_size, 0));

	for (size_t row = 0; row < _board_size; ++row)
	{
		for (size_t col = 0; col < _board_size; ++col)
		{
			int value;
			infile >> value;
			sudokuBoard[row][col] = value;
		}
	}

	infile.close();   // close file

	return sudokuBoard;
}

SudokuBoard::SudokuBoard(const std::string& filename)
	: _board_data(read_input(filename))
{
	std::cout << "Size of Sudoku board: " << _board_size << " by " << _board_size << "\n\n";
}

SudokuBoard::SudokuBoard(const SudokuBoard& another_sudokuboard)
	: _box_size(another_sudokuboard._box_size),
	  _board_size(another_sudokuboard._board_size),
	  _board_data(another_sudokuboard._board_data)
{ }

size_t SudokuBoard::get_box_size() const
{
	return _box_size;
}

size_t SudokuBoard::get_board_size() const
{
	return _board_size;
}

void SudokuBoard::set_board_data(size_t row, size_t col, int num)
{
	_board_data[row][col] = num;
}

Board SudokuBoard::get_board_data() const
{
	return _board_data;
}

int SudokuBoard::operator()(size_t i, size_t j)
{
	return _board_data[i][j];
}

SudokuBoard& SudokuBoard::operator=(const SudokuBoard& another_sudokuboard)
{
	if (this != &another_sudokuboard)
	{
		_box_size = another_sudokuboard._box_size;
		_board_size = another_sudokuboard._board_size;
		_board_data = another_sudokuboard._board_data;
	}

	return *this;
}

void print_board(const SudokuBoard& board)
{
	Board grid = board._board_data;

	for (size_t i = 0; i < board._board_size; ++i)
	{
		if (i % board._box_size == 0 && i != 0) {
			std::string s1 = "---";
			std::string s2 = s1 * board._box_size + " + ";
            std::cout << s2 * (board._box_size - 1) << s1 * board._box_size << "\n";
		}

        for (size_t j = 0; j < board._board_size; ++j)
		{
			if (j % board._box_size == 0 && j != 0) {
                std::cout << "  | ";
			}	

            if (j == board._board_size - 1) {
                std::cout << std::setfill(' ') << std::setw(2) << grid[i][j] << "\n";
			} else if (j % board._box_size == board._box_size - 1) {
				std::cout << std::setfill(' ') << std::setw(2) << grid[i][j];
			} else {
                std::cout << std::setfill(' ') << std::setw(2) << grid[i][j] << " ";
			}
		}
	}
}