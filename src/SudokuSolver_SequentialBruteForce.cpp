#include "SudokuSolver_SequentialBruteForce.hpp"
#include <iostream>


SudokuSolver_SequentialBruteForce::SudokuSolver_SequentialBruteForce(SudokuBoard& board, bool print_message /*=true*/)
	: SudokuSolver(board)
{
	_mode = MODES::SEQUENTIAL_BRUTEFORCE;
	if (print_message)
	{
		std::cout << "\n" << "Sequential Sudoku solver using brute force algorithm starts, please wait..." << "\n";
	}
}

void SudokuSolver_SequentialBruteForce::solve_kernel(int row, int col)
{	
	if (_solved) { return; }
	
	if (_mode == MODES::SEQUENTIAL_BRUTEFORCE) { show_progress_bar(_board, _recursionDepth); }

	int BOARD_SIZE = _board.get_board_size();

	int abs_index = row * BOARD_SIZE + col;

    if (abs_index >= _board.get_num_total_cells())
	{
		_solved = true;
		_solution = _board;
		return;
    }
    
	int row_next = (abs_index + 1) / BOARD_SIZE;
	int col_next = (abs_index + 1) % BOARD_SIZE;

	if (!isEmpty(_board, row, col))
	{   
		solve_kernel(row_next, col_next);
    }
	else
	{
		// Fill in all possible numbers
        for (int num = _board.get_min_value(); num <= _board.get_max_value(); ++num)
		{
			Position pos = std::make_pair(row, col);

            if (isValid(_board, num, pos))
			{
                _board.set_board_data(row, col, num);

				if (isUnique(_board, num, pos)) { num = BOARD_SIZE + 1; }   // Force to exit the for-loop

				// Try the next cell recursively
                solve_kernel(row_next, col_next);

				_board.set_board_data(row, col, _board.get_empty_cell_value());
            }
        }
    }

	_recursionDepth++;
}