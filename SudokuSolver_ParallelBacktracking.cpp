#include "SudokuSolver_ParallelBacktracking.hpp"
#include <iostream>
#include <omp.h>


SudokuSolver_ParallelBacktracking::SudokuSolver_ParallelBacktracking()
{
	std::cout << "\n" << "Parallel Sudoku solver using backtracking algorithm starts, please wait..." << "\n";
	std::cout << "Using " << omp_get_num_threads() << " OMP threads" << "\n";
}

void SudokuSolver_ParallelBacktracking::solve(SudokuBoard& board)
{
	if (_solved)
	{
		_status = SolverStatus::SOLVED;
		return;
	}

    if (checkIfAllFilled(board))   // base case
    {
        _solved = true;
		_status = SolverStatus::SOLVED;
		_solution = board;
		return;
    }
    else
    {
        Position empty_cell_pos = find_empty(board);

        for (int num = 1; num <= int(board.get_board_size()); ++num)
        {
			size_t row = empty_cell_pos.first;
			size_t col = empty_cell_pos.second;

            if (isValid(board, num, empty_cell_pos))
            {
				// Needs to work on the new copy of the Sudoku board
				SudokuBoard local_board(board);
                local_board.set_board_data(row, col, num);

				// To reduce the number of tasks created (which also means the increase of the workload of a task), you can use either the final or if clause in #pragma omp task directive. 
				// The workload of a single task is therefore too small and the overhead of task creation become significant compared to the workload of a task.
				#pragma omp task default(none) firstprivate(local_board)
                solve(local_board);
            }

			board.set_board_data(row, col, 0);   // backtrack to the most recently filled cell
        }
		// Why no board[row][col] = 0;?

        // None of the values solved the Sudoku
		// Instead of the wait for each task, put a "taskgroup" before the loop, so that the iterations become spawned in parallel and finish as a group.
		#pragma omp taskwait
		_solved = false;
        return;
    }
}