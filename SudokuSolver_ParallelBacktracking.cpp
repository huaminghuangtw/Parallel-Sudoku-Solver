#include "SudokuSolver_ParallelBacktracking.hpp"
#include <iostream>
#include <omp.h>


SudokuSolver_ParallelBacktracking::SudokuSolver_ParallelBacktracking(bool print_message /*=true*/)
{
	if (print_message) {
		std::cout << "\n" << "Parallel Sudoku solver using backtracking algorithm starts, please wait..." << "\n";
		std::cout << "Using " << omp_get_num_threads() << " OMP threads" << "\n";
	}
}

void SudokuSolver_ParallelBacktracking::solve(SudokuBoard& board)
{
	if (_solved) return;

    if (checkIfAllFilled(board))   // base case
    {
        _solved = true;
		_solution = board;
		return;
    }

	Position empty_cell_pos = find_empty(board);

	for (int num = 1; num <= board.get_board_size(); ++num)
	{
		int row = empty_cell_pos.first;
		int col = empty_cell_pos.second;

		if (isValid(board, num, empty_cell_pos))
		{
			// Needs to work on the new copy of the Sudoku board
			SudokuBoard local_board(board);
			local_board.set_board_data(row, col, num);

			// Use the final clause in #pragma omp task directive to reduce the overhead of tasks creation, for better scalability
			// If we don't set such a threshold, the workload of a single task is therefore too small and the overhead of task creation
			// become significant compared to the workload of a task
			#pragma omp task default(none) firstprivate(local_board) final(_recursionDepth > board.get_board_size())
			solve(local_board);
		}

		// board.set_board_data(row, col, board.get_empty_cell_value());   // backtrack to the most recently filled cell
		// Why don't we need this line? Because we don't modify anything in the original board.
		
		_recursionDepth++;
	}
}