#include "utility.hpp"


std::string operator * (const std::string& str, size_t times)
{
    std::stringstream stream;
    for (size_t i = 0; i < times; i++) stream << str;
    return stream.str();
}

void print_board(int board[N][N])
{
	for (int i = 0; i < N; i++)
	{
		if (i % box_size == 0 && i != 0) {
			std::string s = "-- ";
			size_t times = N + (box_size - 1) - 1;
            std::cout << s * times << "--" << std::endl;
		}

        for (int j = 0; j < N; j++)
		{
			if (j % box_size == 0 && j != 0) {
                std::cout << "  | ";
			}	

            if (j == N - 1) {
                std::cout << std::setfill(' ') << std::setw(2) << board[i][j] << std::endl;
			} else if (j % box_size == box_size - 1) {
				std::cout << std::setfill(' ') << std::setw(2) << board[i][j]; 
			} else {
                std::cout << std::setfill(' ') << std::setw(2) << board[i][j] << " ";
			}
		}
	}
}

bool checkIfAllFilled(int board[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0)
                return false;
        }
    }
    return true;
}

std::pair<int, int> find_empty(int board[N][N])
{
	std::pair<int, int> empty_cell;
	bool flag = true;

	while (flag)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
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

bool isValid(int board[N][N], int num, std::pair<int, int> pos)
{
	int row = pos.first;
	int col = pos.second;

	// Checks if num already exists in the given row
    for (int i = 0; i < N; i++)
	{
        if (i != row && board[pos.first][i] == num) {
            return false;
		}
	}

	// Checks if num already exists in the given column
    for (int i = 0; i < N; i++)
	{
        if (i != col && board[i][pos.second] == num) {
            return false;
		}
	}

    // Checks if num already exists in the given box (subgrid)
    int box_x = std::floor(pos.first / 3);
    int box_y = std::floor(pos.second / 3);

    for (int i = box_x * box_size; i < box_x * box_size + 3; i++) {
        for (int j = box_y * box_size; j < box_y * box_size + 3; j++) {
            if ( (i != row || j != col) && board[i][j] == num ) {
                return false;
			}
        }
    }

    return true;
}
