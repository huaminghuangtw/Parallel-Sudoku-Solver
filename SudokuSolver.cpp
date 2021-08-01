#include "SudokuSolver.hpp"
#include <cmath>


bool SudokuSolver::checkIfAllFilled(const SudokuBoard& board) const
{
    for (size_t i = 0; i < board.get_board_size(); ++i) {
        for (size_t j = 0; j < board.get_board_size(); ++j) {
            if (board.at(i, j) == board.get_empty_cell_value())
                return false;

        }
    }
    return true;
}

const std::pair<size_t, size_t> SudokuSolver::find_empty(const SudokuBoard& board)
{
	Position empty_cell;
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

bool SudokuSolver::isValidRow(const SudokuBoard& board, int num, Position pos) const
{
    for (size_t i = 0; i < board.get_board_size(); ++i)
	{
        if ( (i != pos.second) && (board.at(pos.first, i) == num) ) {
            return false;
		}
	}

	return true;
}

bool SudokuSolver::isValidColumn(const SudokuBoard& board, int num, Position pos) const
{
	for (size_t i = 0; i < board.get_board_size(); ++i)
	{
        if ( (i != pos.first) && board.at(i, pos.second) == num ) {
            return false;
		}
	}
	
	return true;
}

bool SudokuSolver::isValidBox(const SudokuBoard& board, int num, Position pos) const
{
	int box_x = std::floor(pos.first / board.get_box_size());
    int box_y = std::floor(pos.second / board.get_box_size());

    for (size_t i = box_x * board.get_box_size(); i < box_x * board.get_box_size() + 3; ++i) {
        for (size_t j = box_y * board.get_box_size(); j < box_y * board.get_box_size() + 3; ++j) {
            if ( (i != pos.first && j != pos.second) && board.at(i, j) == num ) {
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