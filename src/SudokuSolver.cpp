#include "SudokuSolver.hpp"
#include "helper.hpp"
#include <algorithm>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>


SudokuSolver::SudokuSolver(SudokuBoard& board)
	: _board(board)
{ }

bool SudokuSolver::checkIfAllFilled(const SudokuBoard& board) const
{
    for (int i = 0; i < board.get_board_size(); ++i)
	{
        for (int j = 0; j < board.get_board_size(); ++j)
		{
            if (isEmpty(board, i, j))
			{
                return false;
			}
        }
    }
    return true;
}

bool SudokuSolver::checkIfRowFilled(const SudokuBoard& board, int indexOfRows) const
{
	for (int j = 0; j < board.get_board_size(); ++j)
	{
		if (isEmpty(board, indexOfRows, j)) { return false; }
	}

    return true;
}

const std::pair<int, int> SudokuSolver::find_empty(const SudokuBoard& board)
{
	Position empty_cell;
	bool stop = false;

	for (int i = 0; i < board.get_board_size(); ++i)
	{
		for (int j = 0; j < board.get_board_size(); ++j)
		{
			if (isEmpty(board, i, j))
			{
				empty_cell = std::make_pair(i, j);
				stop = true;
				break;
			}
		}
		if (stop) { break; }
	}
	
	return empty_cell;  // (row, col)
}

int SudokuSolver::find_empty_from_row(const SudokuBoard& board, int indexOfRows) const
{
	int empty_cell_col_index = -1;

	for (int j = 0; j < board.get_board_size(); ++j)
	{
		if (isEmpty(board, indexOfRows, j))
		{
			empty_cell_col_index = j;
			return empty_cell_col_index;
		}
	}

	return empty_cell_col_index;
}

bool SudokuSolver::isEmpty(const SudokuBoard& board, int i, int j) const
{
	return (board.at(i, j) == board._EMPTY_CELL_VALUE) ? true : false;
}

bool SudokuSolver::isValidRow(const SudokuBoard& board, int num, Position pos) const
{
    for (int i = 0; i < board.get_board_size(); ++i)
	{
        if ( (i != pos.second) && (board.at(pos.first, i) == num) ) { return false; }
	}

	return true;
}

bool SudokuSolver::isValidColumn(const SudokuBoard& board, int num, Position pos) const
{
	for (int i = 0; i < board.get_board_size(); ++i)
	{
        if ( (i != pos.first) && (board.at(i, pos.second) == num) ) { return false; }
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
            if ( (i != pos.first && j != pos.second) && (board.at(i, j) == num) ) { return false; }
        }
    }

	return true;
}

bool SudokuSolver::isValid(const SudokuBoard& board, int num, Position pos) const
{
    return isValidRow(board, num, pos) && isValidColumn(board, num, pos) && isValidBox(board, num, pos);
}

bool SudokuSolver::isUnique(const SudokuBoard& board, int num, Position pos) const
{
	int local_row = pos.first % board.get_box_size();
	int local_col = pos.second % board.get_box_size();

	int box_x = std::floor(pos.first / board.get_box_size());
    int box_y = std::floor(pos.second / board.get_box_size());

	for (int i = ( (local_row == 0) ? 1 : 0 ); i < board.get_box_size(); ++i)
	{
		if (i == local_row) { continue; }
		std::vector<int> numbersInRow = board.getNumbersInRow(box_x * board.get_box_size() + i);
		if (std::find(numbersInRow.begin(), numbersInRow.end(), num) == numbersInRow.end())
		{
			return false;
		}
	}

	for (int j = ( (local_col == 0) ? 1 : 0 ); j < board.get_box_size(); ++j)
	{
		if (j == local_col) { continue; }
		std::vector<int> numbersInCol = board.getNumbersInCol(box_y * board.get_box_size() + j);
		if (std::find(numbersInCol.begin(), numbersInCol.end(), num) == numbersInCol.end())
		{
			return false;
		}
	}

	return true;
}

void SudokuSolver::show_progress_bar(SudokuBoard& board, int _recursionDepth, int interval /*=5*/)
{
	if (_recursionDepth == 0)
	{
		_current_num_empty_cells = board.get_init_num_empty_cells();
		printProgressBar2(double(board.get_init_num_empty_cells() - _current_num_empty_cells) / board.get_init_num_empty_cells());
		std::this_thread::sleep_for(std::chrono::milliseconds(interval));
	} 
	else
	{
		if (board.get_num_empty_cells() < _current_num_empty_cells)
		{
			_current_num_empty_cells = board.get_num_empty_cells();
			printProgressBar2(double(board.get_init_num_empty_cells() - _current_num_empty_cells) / board.get_init_num_empty_cells());
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		}
	}
}