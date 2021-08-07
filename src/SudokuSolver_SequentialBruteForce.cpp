#include "SudokuSolver_SequentialBruteForce.hpp"
#include <iostream>


SudokuSolver_SequentialBruteForce::SudokuSolver_SequentialBruteForce(bool print_message /*=true*/)
{
	if (print_message) {
		std::cout << "\n" << "Sequential Sudoku solver using brute force algorithm starts, please wait..." << "\n";
	}
}

void SudokuSolver_SequentialBruteForce::solve(SudokuBoard& board, bool print_progress /*=true*/, int row /*=0*/, int col /*=0*/)
{	
	if (_solved) return;
	
	if (print_progress) show_progress_bar(board, _recursionDepth);

	int BOARD_SIZE = board.get_board_size();

	int abs_index = row * BOARD_SIZE + col;

    if (abs_index >= board.get_num_total_cells())
	{
		_solved = true;
		_solution = board;
		return;
    }
    
	int row_next = (abs_index + 1) / BOARD_SIZE;
	int col_next = (abs_index + 1) % BOARD_SIZE;

	if (!isEmpty(board, row, col))
	{   
		solve(board, print_progress, row_next, col_next);
    }
	else
	{
		// Fill in all possible numbers
        for (int num = board.get_min_value(); num <= board.get_max_value(); ++num)
		{
			Position pos = std::make_pair(row, col);

            if (isValid(board, num, pos))
			{
                board.set_board_data(row, col, num);

				if (isUnique(board, num, pos)) num = BOARD_SIZE + 1;

				// Try the next cell recursively
                solve(board, print_progress, row_next, col_next);

				board.set_board_data(row, col, board.get_empty_cell_value());
            }
        }
    }

	_recursionDepth++;
}