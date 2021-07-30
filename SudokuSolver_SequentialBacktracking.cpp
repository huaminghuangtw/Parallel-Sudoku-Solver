#include "SudokuSolver_SequentialBacktracking.hpp"
#include <iostream>


SudokuSolver_SequentialBacktracking::SudokuSolver_SequentialBacktracking(SudokuBoard& board)
{
	solve(board);
}

bool SudokuSolver_SequentialBacktracking::checkIfAllFilled(SudokuBoard& board) const
{
    for (size_t i = 0; i < board.get_board_size(); ++i) {
        for (size_t j = 0; j < board.get_board_size(); ++j) {
            if (board.at(i, j) == board.get_empty_cell_value())
                return false;

        }
    }
    return true;
}

const std::pair<size_t, size_t> SudokuSolver_SequentialBacktracking::find_empty(SudokuBoard& board)
{
	std::pair<size_t, size_t> empty_cell;
	bool flag = true;

	while (flag)
	{
		for (size_t i = 0; i < board.get_board_size(); ++i)
		{
			for (size_t j = 0; j < board.get_board_size(); ++j)
			{
				if (board.at(i, j) == board.get_empty_cell_value()) {
					empty_cell = std::make_pair(i, j);
					flag = false;
				}
			}
		}
	}
	
	return empty_cell;  // (row, col)
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
        std::pair<int, int> empty_cell_pos = find_empty(board);

        for (int num = 1; num <= int(board.get_board_size()); ++num)
        {
			size_t row = empty_cell_pos.first;
			size_t col = empty_cell_pos.second;

            if (board.isValid(num, empty_cell_pos))
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
