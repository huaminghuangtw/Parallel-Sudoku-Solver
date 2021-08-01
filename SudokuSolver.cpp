#include "SudokuSolver.hpp"
#include <cmath>


bool SudokuSolver::checkIfAllFilled(const SudokuBoard& board) const
{
    for (int i = 0; i < board.get_board_size(); ++i)
	{
        for (int j = 0; j < board.get_board_size(); ++j)
		{
            if (isEmpty(board, i, j)) {
                return false;
			}
        }
    }
    return true;
}

const std::pair<int, int> SudokuSolver::find_empty(const SudokuBoard& board)
{
	Position empty_cell;
	bool flag = true;

	while (flag)
	{
		for (int i = 0; i < board.get_board_size(); ++i)
		{
			for (int j = 0; j < board.get_board_size(); ++j)
			{
				if (isEmpty(board, i, j)) {
					empty_cell = std::make_pair(i, j);
					flag = false;
				}
			}
		}
	}
	
	return empty_cell;  // (row, col)
}

bool SudokuSolver::isEmpty(const SudokuBoard& board, int i, int j) const
{
	return (board.at(i, j) == board._empty_cell_value) ? true : false;
}

bool SudokuSolver::isValidRow(const SudokuBoard& board, int num, Position pos) const
{
    for (int i = 0; i < board.get_board_size(); ++i)
	{
        if ( (i != pos.second) && (board.at(pos.first, i) == num) ) {
            return false;
		}
	}

	return true;
}

bool SudokuSolver::isValidColumn(const SudokuBoard& board, int num, Position pos) const
{
	for (int i = 0; i < board.get_board_size(); ++i)
	{
        if ( (i != pos.first) && (board.at(i, pos.second) == num) ) {
            return false;
		}
	}
	
	return true;
}

bool SudokuSolver::isValidBox(const SudokuBoard& board, int num, Position pos) const
{
	int BOX_SIZE = board.get_box_size();

	int box_x = std::floor(pos.first / board.get_box_size());
    int box_y = std::floor(pos.second / board.get_box_size());

    for (int i = box_x * BOX_SIZE; i < box_x * BOX_SIZE + BOX_SIZE; ++i)
	{
        for (int j = box_y * BOX_SIZE; j < box_y * BOX_SIZE + BOX_SIZE; ++j)
		{
            if ( (i != pos.first && j != pos.second) && (board.at(i, j) == num) ) {
                return false;
			}
        }
    }

	return true;
}

bool SudokuSolver::isValid(const SudokuBoard& board, int num, Position pos) const
{
    return isValidRow(board, num, pos) && isValidColumn(board, num, pos) && isValidBox(board, num, pos);
}

SolverStatus SudokuSolver::get_solver_status() const
{
	return _status;
}

SudokuBoard SudokuSolver::get_solution() const
{
	return _solution;
}