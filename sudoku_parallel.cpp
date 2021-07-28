#include "utility.hpp"
#include <omp.h>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <iterator>


#define PRINT_TIME 1

int NUM_THREADS = 2;

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
				SudokuBoard local_board;
				std::copy( board.begin(), board.end(), back_inserter(local_board) );

                local_board[row][col] = num;

				// To reduce the number of tasks created (which also means the increase of the workload of a task), you can use either the final or if clause in #pragma omp task directive. 
				// The workload of a single task is therefore too small and the overhead of task creation become significant compared to the workload of a task.
				#pragma omp task default(none) firstprivate(local_board)
                solveSudoku_backtracking(local_board);
            }
        }
		// Why no board[row][col] = 0;?

        // None of the values solved the Sudoku
		// Instead of the wait for each task, put a "taskgroup" before the loop, so that the iterations become spawned in parallel and finish as a group.
		#pragma omp taskwait
		solved = false;
        return;
    }
}


int main(int argc, char** argv)
{
	// validate arguments
	if (argc != 3){
		std::cerr << "Usage: " << argv[0] << " <PATH_TO_INPUT_FILE> <NUM_THREADS>" << std::endl;
        exit(-1);
    }

    SudokuBoard board = readInput(argv[1]);
	NUM_THREADS = atoi(argv[2]);

	std::cout << "************************ INPUT GRID ************************" << std::endl;

    print_board(board);

	std::cout << "************************************************************" << std::endl;

	std::cout << "Sudoku solver starts, please wait..." << std::endl;

#if PRINT_TIME
    std::chrono::high_resolution_clock::time_point start, stop;
    start = std::chrono::high_resolution_clock::now();
#endif

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	{
		#pragma omp single
		{
			solveSudoku_backtracking(board);
		}
	}

#if PRINT_TIME
	stop = std::chrono::high_resolution_clock::now();
	int time_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
#endif

	std::cout << "************************ OUTPUT GRID ***********************" << std::endl;

    print_board(answer);

	std::cout << "************************************************************" << std::endl;

#if PRINT_TIME
    std::cout << std::dec << "Operations executed in " << (double)time_in_microseconds / 1000000 << " seconds" << std::endl;
#endif

    return 0;
}