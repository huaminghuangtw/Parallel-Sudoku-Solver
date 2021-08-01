#include "SudokuSolver_SequentialBruteForce.hpp"
#include <iostream>


SudokuSolver_SequentialBruteForce::SudokuSolver_SequentialBruteForce()
{
	std::cout << "\n" << "Sequential Sudoku solver using brute force algorithm starts, please wait..." << "\n";
}

void SudokuSolver_SequentialBruteForce::solve(SudokuBoard& board, size_t row, size_t col)
{
	size_t BOARD_SIZE = board.get_board_size();

	if (_solved)
	{
		_status = SolverStatus::SOLVED;
		return;
	}

	size_t abs_index = row * BOARD_SIZE + col;

    if (int(abs_index) >= board.get_num_total_cells())
	{
		_solved = true;
		_status = SolverStatus::SOLVED;
		_solution = board;
		return;
    }
    
	size_t row_next = (abs_index + 1) / BOARD_SIZE;
	size_t col_next = (abs_index + 1) % BOARD_SIZE;

	if (!isEmpty(board, row, col))
	{   
		solve(board, row_next, col_next);
    }
	else
	{
		Position pos = std::make_pair(row, col);

		// Fill in all possible numbers
        for (int num = 1; num <= int(BOARD_SIZE); ++num)
		{
            if (isValid(board, num, pos))
			{
                board.set_board_data(row, col, num);
				// Try next cell recursively
                solve(board, row_next, col_next);
                board.set_board_data(row, col, 0);
            }
        }
    }
}