#include "SudokuSolver_SequentialBacktracking.hpp"
#include "helper.hpp"
#include <iostream>
#include <thread>
#include <chrono>


SudokuSolver_SequentialBacktracking::SudokuSolver_SequentialBacktracking(bool print_message /*=true*/)
{
	if (print_message) {
		std::cout << "\n" << "Sequential Sudoku solver using backtracking algorithm starts, please wait..." << "\n";
	}
}

void SudokuSolver_SequentialBacktracking::solve(SudokuBoard& board)
{
	if (_solved) return;

	if (_recursionDepth == 0) {
		_current_num_empty_cells = board.get_init_num_empty_cells();
		printProgressBar2(double(board.get_init_num_empty_cells() - _current_num_empty_cells) / board.get_init_num_empty_cells());
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	} else {
		if (board.get_num_empty_cells() < _current_num_empty_cells)
		{
			_current_num_empty_cells = board.get_num_empty_cells();
			printProgressBar2(double(board.get_init_num_empty_cells() - _current_num_empty_cells) / board.get_init_num_empty_cells());
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	if (checkIfAllFilled(board))   // base case
    {
        _solved = true;
		_solution = board;
		return;
    }
    
	Position empty_cell_pos = find_empty(board);

	for (int num = 1; num <= board.get_board_size(); ++num)
	{
		int row = empty_cell_pos.first;
		int col = empty_cell_pos.second;

		if (isValid(board, num, empty_cell_pos))
		{
			board.set_board_data(row, col, num);

			// Try the next cell recursively
			solve(board);

			// Backtrack to the most recently filled cell
			board.set_board_data(row, col, board.get_empty_cell_value());
		}
	}

	_recursionDepth++;
}

/*
 * Note:
 * A stack is perfectly suited to backtracking, since all you’re doing is either adding the most
 * recent moves (i.e., pushing moves) or removing moves starting from the most recent (i.e.,
 * popping moves). In other words, your access pattern is exactly Last-In-First-Out (LIFO),
 * which is precisely what a stack provides.
 */