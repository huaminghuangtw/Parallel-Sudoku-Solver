#include "utility.hpp"


int BOX_SIZE;
int SUDOKU_SIZE;


SudokuBoard readInput(const std::string& filename)
{
	std::ifstream infile(filename);   // open file

	if (!infile)
	{
		std::cout << "Error opening file!" << std::endl;
		exit(1);
	}
	else
	{
		infile >> SUDOKU_SIZE;
		BOX_SIZE = std::sqrt(SUDOKU_SIZE);

		SudokuBoard sudokuBoard(SUDOKU_SIZE, std::vector<int> (SUDOKU_SIZE, 0));

		for (int row = 0; row < SUDOKU_SIZE; ++row)
		{
			for (int col = 0; col < SUDOKU_SIZE; ++col)
			{
				int value;
				infile >> value;
				sudokuBoard[row][col] = value;
			}
		}

		return sudokuBoard;
	}

   infile.close();   // close file
}

inline std::string operator * (const std::string& str, size_t times)
{
    std::stringstream stream;
    for (size_t i = 0; i < times; i++) stream << str;
    return stream.str();
}

void print_board(SudokuBoard board)
{
	for (int i = 0; i < SUDOKU_SIZE; ++i)
	{
		if (i % BOX_SIZE == 0 && i != 0) {
			std::string s1 = "---";
			std::string s2 = s1 * BOX_SIZE + " + ";
            std::cout << s2 * (BOX_SIZE - 1) << s1 * BOX_SIZE << std::endl;
		}

        for (int j = 0; j < SUDOKU_SIZE; ++j)
		{
			if (j % BOX_SIZE == 0 && j != 0) {
                std::cout << "  | ";
			}	

            if (j == SUDOKU_SIZE - 1) {
                std::cout << std::setfill(' ') << std::setw(2) << board[i][j] << std::endl;
			} else if (j % BOX_SIZE == BOX_SIZE - 1) {
				std::cout << std::setfill(' ') << std::setw(2) << board[i][j]; 
			} else {
                std::cout << std::setfill(' ') << std::setw(2) << board[i][j] << " ";
			}
		}
	}
}

bool checkIfAllFilled(SudokuBoard board)
{
    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        for (int j = 0; j < SUDOKU_SIZE; ++j) {
            if (board[i][j] == 0)
                return false;
        }
    }
    return true;
}

std::pair<int, int> find_empty(SudokuBoard board)
{
	std::pair<int, int> empty_cell;
	bool flag = true;

	while (flag)
	{
		for (int i = 0; i < SUDOKU_SIZE; ++i)
		{
			for (int j = 0; j < SUDOKU_SIZE; ++j)
			{
				if (board[i][j] == 0) {
					empty_cell = std::make_pair(i, j);
					flag = false;
				}
			}
		}
	}
	
	return empty_cell;  // (row, col)
}

bool isValid(SudokuBoard board, int num, std::pair<int, int> pos)
{
	// Checks if num already exists in the given row
    for (int i = 0; i < SUDOKU_SIZE; ++i)
	{
        if (board[pos.first][i] == num) {
            return false;
		}
	}

	// Checks if num already exists in the given column
    for (int i = 0; i < SUDOKU_SIZE; ++i)
	{
        if (board[i][pos.second] == num) {
            return false;
		}
	}

    // Checks if num already exists in the given box (subgrid)
    int box_x = std::floor(pos.first / BOX_SIZE);
    int box_y = std::floor(pos.second / BOX_SIZE);

    for (int i = box_x * BOX_SIZE; i < box_x * BOX_SIZE + 3; ++i) {
        for (int j = box_y * BOX_SIZE; j < box_y * BOX_SIZE + 3; ++j) {
            if (board[i][j] == num) {
                return false;
			}
        }
    }

    return true;
}