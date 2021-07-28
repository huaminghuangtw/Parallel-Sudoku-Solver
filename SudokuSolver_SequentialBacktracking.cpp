#include "SudokuSolver_SequentialBacktracking.hpp"
#include <cmath>
#include <iostream>


SudokuSolver_SequentialBacktracking::SudokuSolver_SequentialBacktracking(SudokuBoard& board)
{
	solve(board);
}

SudokuBoard SudokuSolver_SequentialBacktracking::get_answer() const
{
	return _answer;
}

bool SudokuSolver_SequentialBacktracking::checkIfAllFilled(SudokuBoard& board) const
{
    for (size_t i = 0; i < board.get_board_size(); ++i) {
        for (size_t j = 0; j < board.get_board_size(); ++j) {
            if (board(i, j) == 0)
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
				if (board(i, j) == 0) {
					empty_cell = std::make_pair(i, j);
					flag = false;
				}
			}
		}
	}
	
	return empty_cell;  // (row, col)
}

bool SudokuSolver_SequentialBacktracking::checkValidRow(SudokuBoard& board, int num, std::pair<size_t, size_t> pos) const
{
    for (size_t i = 0; i < board.get_board_size(); ++i)
	{
        if (board(pos.first, i) == num) {
            return false;
		}
	}

	return true;
}

bool SudokuSolver_SequentialBacktracking::checkValidColumn(SudokuBoard& board, int num, std::pair<size_t, size_t> pos) const
{
	for (size_t i = 0; i < board.get_board_size(); ++i)
	{
        if (board(i, pos.second) == num) {
            return false;
		}
	}
	
	return true;
}

bool SudokuSolver_SequentialBacktracking::checkValidBox(SudokuBoard& board, int num, std::pair<size_t, size_t> pos) const
{
	int box_x = std::floor(pos.first / board.get_box_size());
    int box_y = std::floor(pos.second / board.get_box_size());

    for (size_t i = box_x * board.get_box_size(); i < box_x * board.get_box_size() + 3; ++i) {
        for (size_t j = box_y * board.get_box_size(); j < box_y * board.get_box_size() + 3; ++j) {
            if (board(i, j) == num) {
                return false;
			}
        }
    }

	return true;
}

bool SudokuSolver_SequentialBacktracking::isValid(SudokuBoard& board, int num, std::pair<size_t, size_t> pos) const
{
    return checkValidRow(board, num, pos) && checkValidColumn(board, num, pos) && checkValidBox(board, num, pos);
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
		_answer = board;
		return;
    }
    else
    {
        std::pair<int, int> empty_cell = find_empty(board);

        for (int num = 1; num <= int(board.get_board_size()); ++num)
        {
			size_t row = empty_cell.first;
			size_t col = empty_cell.second;

            if (isValid(board, num, empty_cell))
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
