#include "SudokuBoard.hpp"
#include "helper.hpp"
#include <cmath>
#include <fstream>
#include <iostream>


const Board SudokuBoard::read_input(const std::string& filename)
{
	std::ifstream inputFile(filename);   // open file

	if (!inputFile)
	{
		std::cout << "Error opening file! Please make sure the file specified exists." << "\n";
		exit(1);
	}
	
	inputFile >> _board_size;
	_box_size = std::sqrt(_board_size);

	Board sudokuBoard(_board_size, std::vector<int> (_board_size, 0));

	for (size_t row = 0; row < _board_size; ++row)
	{
		for (size_t col = 0; col < _board_size; ++col)
		{
			int value;
			inputFile >> value;
			sudokuBoard[row][col] = value;
		}
	}

	inputFile.close();   // close file

	return sudokuBoard;
}

void write_output(const SudokuBoard& solutionBoard)
{
	Board solution = solutionBoard.get_board_data();
	size_t BOARD_SIZE = solutionBoard.get_board_size();
	size_t BOX_SIZE = solutionBoard.get_box_size();

	std::ofstream outputFile("solution.txt");

    int digit = int(log10(BOARD_SIZE)) + 1;

    for (size_t r = 0; r < BOARD_SIZE; r++) {
        for (size_t c = 0; c < BOARD_SIZE; c++) {
			outputFile << std::setw(digit) << solution[r][c];

			if (c != BOARD_SIZE - 1) {
				outputFile << " ";
			}

			if (c % BOX_SIZE == (BOX_SIZE - 1)) {
				if (c != BOARD_SIZE - 1) {
					outputFile << "  ";
				}
			}
		}
		
		if (r != BOARD_SIZE - 1) {
			outputFile << "\n";
			if (r % BOX_SIZE == (BOX_SIZE - 1)) {
				outputFile << "\n";
			}
		}
    }

	outputFile.close();
}

SudokuBoard::SudokuBoard(const std::string& filename)
	: _board_data(read_input(filename))
{
	std::cout << "Load the initial Sudoku board from " << filename << "..." << "\n";
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

int SudokuBoard::get_board_data(size_t row, size_t col) const
{
	return _board_data[row][col];
}

Board SudokuBoard::get_board_data() const
{
	return _board_data;
}

int SudokuBoard::get_empty_cell_value() const
{
	return _empty_cell_value;
}

std::string SudokuBoard::get_empty_cell_character() const
{
	return _empty_cell_character;
}

int SudokuBoard::at(size_t i, size_t j) const
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

bool SudokuBoard::isValidRow(int num, std::pair<size_t, size_t> pos) const
{
    for (size_t i = 0; i < _board_size; ++i)
	{
        if ( (i != pos.second) && (this->at(pos.first, i) == num) ) {
            return false;
		}
	}

	return true;
}

bool SudokuBoard::isValidColumn(int num, std::pair<size_t, size_t> pos) const
{
	for (size_t i = 0; i < _board_size; ++i)
	{
        if ( (i != pos.first) && this->at(i, pos.second) == num ) {
            return false;
		}
	}
	
	return true;
}

bool SudokuBoard::isValidBox(int num, std::pair<size_t, size_t> pos) const
{
	int box_x = std::floor(pos.first / _box_size);
    int box_y = std::floor(pos.second / _box_size);

    for (size_t i = box_x * _box_size; i < box_x * _box_size + 3; ++i) {
        for (size_t j = box_y * _box_size; j < box_y * _box_size + 3; ++j) {
            if ( (i != pos.first && j != pos.second) && this->at(i, j) == num ) {
                return false;
			}
        }
    }

	return true;
}

bool SudokuBoard::isValid(int num, std::pair<size_t, size_t> pos) const
{
    return isValidRow(num, pos) && isValidColumn(num, pos) && isValidBox(num, pos);
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

std::ostream& operator<<(std::ostream &out, const SudokuBoard& board)
{
	Board grid = board.get_board_data();
	size_t BOARD_SIZE = board.get_board_size();
	size_t BOX_SIZE = board.get_box_size();
	int EMPTY_CELL_VALUE = board.get_empty_cell_value();
	std::string EMPTY_CELL_CHARACTER = board.get_empty_cell_character();

	for (size_t i = 0; i < BOARD_SIZE; ++i)
	{
		if (i % BOX_SIZE == 0 && i != 0) {
			std::string s1 = "---";
			std::string s2 = s1 * BOX_SIZE + " + ";
            out << s2 * (BOX_SIZE - 1) << s1 * BOX_SIZE << "\n";
		}

        for (size_t j = 0; j < BOARD_SIZE; ++j)
		{
			if (j % BOX_SIZE == 0 && j != 0) {
                out << "  | ";
			}	

			std::string forPrinting;
			if (grid[i][j] == EMPTY_CELL_VALUE) {
				forPrinting = EMPTY_CELL_CHARACTER;
			} else {
				forPrinting = std::to_string(grid[i][j]);
			}

            if (j == BOARD_SIZE - 1) {
                out << std::setfill(' ') << std::setw(2) << forPrinting << "\n";
			} else if (j % BOX_SIZE == BOX_SIZE - 1) {
				out << std::setfill(' ') << std::setw(2) << forPrinting;
			} else {
                out << std::setfill(' ') << std::setw(2) << forPrinting << " ";
			}
		}
	}

    return out;
}