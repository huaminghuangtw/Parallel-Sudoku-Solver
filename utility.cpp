#include "utility.hpp"


std::string operator * (const std::string& str, size_t times)
{
    std::stringstream stream;
    for (size_t i = 0; i < times; i++) stream << str;
    return stream.str();
}

void print_board(int board[N][N])
{
	int box_size = sqrt(N);
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