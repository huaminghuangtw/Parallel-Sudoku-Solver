#include "SudokuBoard.hpp"
#include "helper.hpp"
#include "termcolor.hpp"
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>


const Board SudokuBoard::read_input(const std::string& filename)
{
	std::ifstream inputFile(filename);   // open file

	if (!inputFile)
	{
		std::cerr << termcolor::red << "Error opening file " << filename
		          << "! Please make sure the file specified exists." << termcolor::reset << "\n";
		exit(1);
	}
	
	inputFile >> _BOARD_SIZE;
	_BOX_SIZE = std::sqrt(_BOARD_SIZE);

	Board sudokuBoard(_BOARD_SIZE, std::vector<int>(_BOARD_SIZE, 0));

	int num_empty_cells = 0;
	for (int row = 0; row < _BOARD_SIZE; ++row)
	{
		for (int col = 0; col < _BOARD_SIZE; ++col)
		{
			int value;
			inputFile >> value;
			sudokuBoard[row][col] = value;
			num_empty_cells += (value == 0);
		}
	}
	_INIT_NUM_EMPTY_CELLS = num_empty_cells;
	
	inputFile.close();   // close file

	return sudokuBoard;
}

void write_output(const SudokuBoard& solutionBoard)
{
	Board solution = solutionBoard.get_board_data();
	int BOARD_SIZE = solutionBoard.get_board_size();
	int BOX_SIZE = solutionBoard.get_box_size();

	std::ofstream outputFile("solution.txt");

    int digit = log10(BOARD_SIZE) + 1;

    for (int r = 0; r < BOARD_SIZE; ++r)
	{
        for (int c = 0; c < BOARD_SIZE; ++c)
		{
			outputFile << std::setw(digit) << solution[r][c];

			if (c != BOARD_SIZE - 1)
			{
				outputFile << " ";
			}

			if (c % BOX_SIZE == (BOX_SIZE - 1))
			{
				if (c != BOARD_SIZE - 1)
				{
					outputFile << "  ";
				}
			}
		}
		
		if (r != BOARD_SIZE - 1)
		{
			outputFile << "\n";
			if (r % BOX_SIZE == (BOX_SIZE - 1))
			{
				outputFile << "\n";
			}
		}
    }

	outputFile.close();
}

SudokuBoard::SudokuBoard(const std::string& filename)
	: _board_data(read_input(filename))
{
	std::cout << "Load the initial Sudoku board from "
	          << termcolor::yellow << filename << termcolor::reset << "..." << "\n";
}

SudokuBoard::SudokuBoard(const SudokuBoard& anotherSudokuBoard)
	: _board_data(anotherSudokuBoard._board_data),
	  _BOX_SIZE(anotherSudokuBoard._BOX_SIZE),
	  _BOARD_SIZE(anotherSudokuBoard._BOARD_SIZE),
	  _MIN_VALUE(anotherSudokuBoard._MIN_VALUE),
	  _MAX_VALUE(anotherSudokuBoard._MAX_VALUE),
	  _NUM_CONSTRAINTS(anotherSudokuBoard._NUM_CONSTRAINTS),
	  _INIT_NUM_EMPTY_CELLS(anotherSudokuBoard._INIT_NUM_EMPTY_CELLS),
	  _EMPTY_CELL_VALUE(anotherSudokuBoard._EMPTY_CELL_VALUE),
	  _EMPTY_CELL_CHARACTER(anotherSudokuBoard._EMPTY_CELL_CHARACTER),
	  _COVER_MATRIX_START_INDEX(anotherSudokuBoard._COVER_MATRIX_START_INDEX)
{ }

int SudokuBoard::get_num_total_cells() const
{
	return _BOARD_SIZE * _BOARD_SIZE;
}

int SudokuBoard::get_num_empty_cells() const
{
	int n = 0;
    for (int i = 0; i < _BOARD_SIZE; ++i)
	{
		for (int j = 0; j < _BOARD_SIZE; ++j)
		{
			n += (this->at(i, j) == get_empty_cell_value());
		}
	}
    return n;
}

std::vector<int> SudokuBoard::getNumbersInRow(int indexOfRows) const
{
	std::vector<int> numbersInRow;

	for (int col = 0; col < _BOARD_SIZE; ++col)
	{
		int num = _board_data[indexOfRows][col];
		if (num == _EMPTY_CELL_VALUE) continue;
		numbersInRow.push_back(num);
	}

	return numbersInRow;
}

std::vector<int> SudokuBoard::getNumbersInCol(int indexOfColumns) const
{
	std::vector<int> numbersInCol;

	for (int row = 0; row < _BOARD_SIZE; ++row)
	{
		int num = _board_data[row][indexOfColumns];
		if (num == _EMPTY_CELL_VALUE) continue;
		numbersInCol.push_back(num);
	}

	return numbersInCol;
}

SudokuBoard& SudokuBoard::operator= (const SudokuBoard& anotherSudokuBoard)
{
	if (this != &anotherSudokuBoard)
	{
		_board_data = anotherSudokuBoard._board_data;
		_BOX_SIZE = anotherSudokuBoard._BOX_SIZE;
		_BOARD_SIZE = anotherSudokuBoard._BOARD_SIZE;
		_MIN_VALUE = anotherSudokuBoard._MIN_VALUE;
		_MAX_VALUE = anotherSudokuBoard._MAX_VALUE;
		_NUM_CONSTRAINTS = anotherSudokuBoard._NUM_CONSTRAINTS;
		_INIT_NUM_EMPTY_CELLS = anotherSudokuBoard._INIT_NUM_EMPTY_CELLS;
		_EMPTY_CELL_VALUE = anotherSudokuBoard._EMPTY_CELL_VALUE;
		_EMPTY_CELL_CHARACTER = anotherSudokuBoard._EMPTY_CELL_CHARACTER;
		_COVER_MATRIX_START_INDEX = anotherSudokuBoard._COVER_MATRIX_START_INDEX;
	}

	return *this;
}

void print_board(const SudokuBoard& board)
{
	Board grid = board._board_data;

	for (int i = 0; i < board._BOARD_SIZE; ++i)
	{
		if (i % board._BOX_SIZE == 0 && i != 0)
		{
			std::string s1 = "---";
			std::string s2 = s1 * board._BOX_SIZE + " + ";
            std::cout << s2 * (board._BOX_SIZE - 1) << s1 * board._BOX_SIZE << "\n";
		}

        for (int j = 0; j < board._BOARD_SIZE; ++j)
		{
			if (j % board._BOX_SIZE == 0 && j != 0)
			{
                std::cout << "  | ";
			}	

            if (j == board._BOARD_SIZE - 1)
			{
                std::cout << std::setfill(' ') << std::setw(2) << grid[i][j] << "\n";
			}
			else if (j % board._BOX_SIZE == board._BOX_SIZE - 1)
			{
				std::cout << std::setfill(' ') << std::setw(2) << grid[i][j];
			}
			else
			{
                std::cout << std::setfill(' ') << std::setw(2) << grid[i][j] << " ";
			}
		}
	}
}

std::ostream& operator<< (std::ostream &out, const SudokuBoard& board)
{
	Board grid = board.get_board_data();
	int BOARD_SIZE = board.get_board_size();
	int BOX_SIZE = board.get_box_size();
	int EMPTY_CELL_VALUE = board.get_empty_cell_value();
	std::string EMPTY_CELL_CHARACTER = board.get_empty_cell_character();

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		if (i % BOX_SIZE == 0 && i != 0)
		{
			std::string s1 = "---";
			std::string s2 = s1 * BOX_SIZE + " + ";
            out << s2 * (BOX_SIZE - 1) << s1 * BOX_SIZE << "\n";
		}

        for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (j % BOX_SIZE == 0 && j != 0)
			{
                out << "  | ";
			}	

			std::string forPrinting = (grid[i][j] == EMPTY_CELL_VALUE) ? EMPTY_CELL_CHARACTER : std::to_string(grid[i][j]);

            if (j == BOARD_SIZE - 1)
			{
                out << std::setfill(' ') << std::setw(2) << forPrinting << "\n";
			}
			else if (j % BOX_SIZE == BOX_SIZE - 1)
			{
				out << std::setfill(' ') << std::setw(2) << forPrinting;
			}
			else
			{
                out << std::setfill(' ') << std::setw(2) << forPrinting << " ";
			}
		}
	}

    return out;
}

int SudokuBoard::indexInCoverMatrix(int row, int col, int num)
{
    return (row - 1) * _BOARD_SIZE * _BOARD_SIZE + (col - 1) * _BOARD_SIZE + (num - 1);
}

int SudokuBoard::createBoxConstraints(CoverMatrix& coverMatrix, int header)
{
	for (int row = _COVER_MATRIX_START_INDEX; row <= _BOARD_SIZE; row += _BOX_SIZE)
    {
        for (int col = _COVER_MATRIX_START_INDEX; col <= _BOARD_SIZE; col += _BOX_SIZE)
        {
            for (int n = _COVER_MATRIX_START_INDEX; n <= _BOARD_SIZE; ++n, ++header)
            {
                for (int rowDelta = 0; rowDelta < _BOX_SIZE; ++rowDelta)
                {
                    for (int colDelta = 0; colDelta < _BOX_SIZE; ++colDelta)
                    {
                        int index = indexInCoverMatrix(row + rowDelta, col + colDelta, n);
                        coverMatrix[index][header] = 1;
                    }
                }
            }
        }
    }

    return header;
}

int SudokuBoard::createColumnConstraints(CoverMatrix& coverMatrix, int header)
{
	for (int col = _COVER_MATRIX_START_INDEX; col <= _BOARD_SIZE; ++col)
    {
        for (int n = _COVER_MATRIX_START_INDEX; n <= _BOARD_SIZE; ++n, ++header)
        {
            for (int row = _COVER_MATRIX_START_INDEX; row <= _BOARD_SIZE; ++row)
            {
                int index = indexInCoverMatrix(row, col, n);
                coverMatrix[index][header] = 1;
            }
        }
    }

    return header;
}

int SudokuBoard::createRowConstraints(CoverMatrix& coverMatrix, int header)
{
	for (int row = _COVER_MATRIX_START_INDEX; row <= _BOARD_SIZE; ++row)
    {
        for (int n = _COVER_MATRIX_START_INDEX; n <= _BOARD_SIZE; ++n, ++header)
        {
            for (int col = _COVER_MATRIX_START_INDEX; col <= _BOARD_SIZE; ++col)
            {
                int index = indexInCoverMatrix(row, col, n);
                coverMatrix[index][header] = 1;
            }
        }
    }

    return header;
}

int SudokuBoard::createCellConstraints(CoverMatrix& coverMatrix, int header)
{
	for (int row = _COVER_MATRIX_START_INDEX; row <= _BOARD_SIZE; ++row)
    {
        for (int col = _COVER_MATRIX_START_INDEX; col <= _BOARD_SIZE; ++col, ++header)
        {
            for (int n = _COVER_MATRIX_START_INDEX; n <= _BOARD_SIZE; ++n)
            {
                int index = indexInCoverMatrix(row, col, n);
                coverMatrix[index][header] = 1;
            }
        }
    }

    return header;
}

void SudokuBoard::createCoverMatrix(CoverMatrix& coverMatrix)
{
	int numberOfRows = _BOARD_SIZE * _BOARD_SIZE * _MAX_VALUE;
	int numberOfCols = _BOARD_SIZE * _BOARD_SIZE * _NUM_CONSTRAINTS;

	coverMatrix.resize(numberOfRows, std::vector<int>(numberOfCols));

    int header = 0;
    header = createCellConstraints(coverMatrix, header);
    header = createRowConstraints(coverMatrix, header);
    header = createColumnConstraints(coverMatrix, header);
    createBoxConstraints(coverMatrix, header);
}

void SudokuBoard::convertToCoverMatrix(CoverMatrix& coverMatrix)
{	
    for (int row = _COVER_MATRIX_START_INDEX; row <= _BOARD_SIZE; ++row)
    {
        for (int col = _COVER_MATRIX_START_INDEX; col <= _BOARD_SIZE; ++col)
        {
            int n = _board_data[row - 1][col - 1];

            if (n != _EMPTY_CELL_VALUE)
            {
                for (int num = _MIN_VALUE; num <= _MAX_VALUE; ++num)
                {
                    if (num != n)
                    {
                        int index = indexInCoverMatrix(row, col, num);
                        for (int i = 0; i < _BOARD_SIZE * _BOARD_SIZE * _NUM_CONSTRAINTS; ++i)
                        {
                            coverMatrix[index][i] = 0;
                        }
                    }
                }
            }
        }
    }
}

void SudokuBoard::createStateMatrix(StateMatrix& stateMatrix)
{
	stateMatrix.resize(_BOARD_SIZE, std::vector<MultiType>(_BOARD_SIZE));
}

void SudokuBoard::convertToStateMatrix(StateMatrix& stateMatrix)
{
	std::set<int> setOfPossibleValues;
	for (int num = _MIN_VALUE; num < _MAX_VALUE; ++num)
	{
		setOfPossibleValues.insert(num);
	}

	for (int i = 0; i < _BOARD_SIZE; ++i)
	{
		for (int j = 0; j < _BOARD_SIZE; ++j)
		{
			stateMatrix[i][j] = _board_data[i][j];
			if (std::get<int>(stateMatrix[i][j]) == _EMPTY_CELL_VALUE)
			{
				stateMatrix[i][j] = setOfPossibleValues;
			}
		}
	}
}
