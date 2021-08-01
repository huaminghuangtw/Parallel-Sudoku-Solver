#include "SudokuSolver_SequentialBacktracking.hpp"
#include <iostream>


SudokuSolver_SequentialBacktracking::SudokuSolver_SequentialBacktracking()
{
	std::cout << "\n" << "Sequential Sudoku solver using backtracking algorithm starts, please wait..." << "\n";
}

void SudokuSolver_SequentialBacktracking::solve(SudokuBoard& board)
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
                board.set_board_data(row, col, num);
                solve(board);
            }

			board.set_board_data(row, col, 0);   // backtrack to the most recently filled cell
        }

        // None of the values solved the Sudoku
		_solved = false;
        return;
    }
}
