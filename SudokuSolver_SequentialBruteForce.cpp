#include "SudokuSolver_SequentialBruteForce.hpp"
#include "SudokuTest.hpp"
#include <iostream>


SudokuSolver_SequentialBruteForce::SudokuSolver_SequentialBruteForce()
{
	std::cout << "\n" << "Sequential Sudoku solver using brute force algorithm starts, please wait..." << "\n";
}

void SudokuSolver_SequentialBruteForce::solve(SudokuBoard& board, int row, int col)
{
	int BOARD_SIZE = board.get_board_size();

	int abs_index = row * BOARD_SIZE + col;

    if (abs_index >= board.get_num_total_cells())
	{
		std::cout << "Solved!" << "\n";
		_solved = true;
		_status = SolverStatus::SOLVED;
		_solution = board;
		SudokuTest::testBoard(_solution);
		return;
    }
    
	int row_next = (abs_index + 1) / BOARD_SIZE;
	int col_next = (abs_index + 1) % BOARD_SIZE;

	if (!isEmpty(board, row, col))
	{   
		solve(board, row_next, col_next);
    }
	else
	{
		Position pos = std::make_pair(row, col);

		// Fill in all possible numbers
        for (int num = 1; num <= BOARD_SIZE; ++num)
		{
            if (isValid(board, num, pos))
			{
                board.set_board_data(row, col, num);
				// Try the next cell recursively
                solve(board, row_next, col_next);
				board.set_board_data(row, col, board.get_empty_cell_value());
            }
        }
    }
}