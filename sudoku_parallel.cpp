#include "utility.hpp"
#include <omp.h>
#include <chrono>
#include <cstring>


#define PRINT_TIME 1
#define NUM_THREADS 4


bool solved;
int answer[N][N] = {0};


void solveSudoku_backtracking(int board[N][N])
{
	if (solved) return;

    if (checkIfAllFilled(board))   // base case
    {
        solved = true;
		std::memcpy(answer, board, SIZEOF_SUDOKU);
		return;
    }
    else
    {
        std::pair<int, int> empty_cell = find_empty(board);

        for (int num = 1; num <= N; num++)
        {
            if (isValid(board, num, empty_cell))
            {	
				int local_board[N][N] = {0};			
				std::memcpy(local_board, board, SIZEOF_SUDOKU);

				int row = empty_cell.first;
				int col = empty_cell.second;

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


int main(void)
{
    // 0 means empty cells
    int board[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                        { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                        { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                        { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                        { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                        { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                        { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    // int board[N][N] =
    // { {0,1,2,0,0,4,0,0,0,0,5,0,0,0,0,0},
    //   {0,0,0,0,0,2,0,0,0,0,0,0,0,14,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},
    //   {11,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0},
    //   {0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,16,0,0,0,0,0,0,2,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0},
    //   {0,0,14,0,0,0,0,0,0,4,0,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,0,0,1,16,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,14,0,0,13,0,0},
    //   {0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {16,0,0,0,0,0,11,0,0,3,0,0,0,0,0,0} };
 
    print_board(board);

	std::cout << "Sudoku solver starts, please wait..." << std::endl;

	omp_set_num_threads(NUM_THREADS);

#if PRINT_TIME
    std::chrono::high_resolution_clock::time_point start, stop;
    start = std::chrono::high_resolution_clock::now();
#endif

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
    std::cout << std::dec << "Operations executed in " << (double)time_in_microseconds / 1000000 << " seconds" << std::endl;
#endif

    print_board(answer);

	std::cout << "Press any key to exit...";
    std::getchar();
    return 0;
}