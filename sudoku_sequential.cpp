#include "utility.hpp"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <iterator>


// TODO: class Sudoku & Solver?
// TODO: add recursive depth?
// TODO: solve 16 * 16 (smarter algorithm)


#define PRINT_TIME 1


bool solved;
SudokuBoard answer;


void solveSudoku_backtracking(SudokuBoard board)
{
	if (solved) return;

    if (checkIfAllFilled(board))   // base case
    {
        solved = true;
		std::copy( board.begin(), board.end(), back_inserter(answer) );   // equivalent to: answer = board;
		return;
    }
    else
    {
        std::pair<int, int> empty_cell = find_empty(board);

        for (int num = 1; num <= SUDOKU_SIZE; ++num)
        {
			int row = empty_cell.first;
			int col = empty_cell.second;

            if (isValid(board, num, empty_cell))
            {
                board[row][col] = num;
                solveSudoku_backtracking(board);
            }

			board[row][col] = 0;   // backtrack to the most recently filled cell
        }

        // None of the values solved the Sudoku
		solved = false;
        return;
    }
}


int main(int argc, char** argv)
{
	// validate arguments
	if (argc != 2){
		std::cerr << "Usage: " << argv[0] << " <PATH_TO_INPUT_FILE>" << "\n";
        exit(-1);
    }

    SudokuBoard board = readInput(argv[1]);

	std::cout << "************************ INPUT GRID ************************" << "\n";

    print_board(board);

	std::cout << "************************************************************" << "\n";

	std::cout << "Sudoku solver starts, please wait..." << "\n";

#if PRINT_TIME
    std::chrono::high_resolution_clock::time_point start, stop;
    start = std::chrono::high_resolution_clock::now();
#endif

	solveSudoku_backtracking(board);

#if PRINT_TIME
	stop = std::chrono::high_resolution_clock::now();
	int time_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
#endif

	std::cout << "************************ OUTPUT GRID ***********************" << "\n";

    print_board(answer);

	std::cout << "************************************************************" << "\n";

#if PRINT_TIME
    std::cout << std::dec << "Operations executed in " << (double)time_in_microseconds / 1000000 << " seconds" << "\n";
#endif

    // if (solveSudoku_backtracking(board)) {
    //     std::cout << "--------------------" << std::endl;
    //     print_board(board);
    // } else {
    //     std::cout << "No solution exists." << std::endl;
    // }

    return 0;
}