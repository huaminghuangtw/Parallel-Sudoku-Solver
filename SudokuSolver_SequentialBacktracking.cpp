#include "SudokuSolver_SequentialBacktracking.hpp"
#include <iostream>


SudokuSolver_SequentialBacktracking::SudokuSolver_SequentialBacktracking(bool print_message /*=true*/)
{
	if (print_message) {
		std::cout << "\n" << "Sequential Sudoku solver using backtracking algorithm starts, please wait..." << "\n";
	}
}

bool SudokuSolver_SequentialBacktracking::solve(SudokuBoard& board)
{
	if (_solved) { return _solved; }

	show_progress_bar(board, _recursionDepth);

	if (checkIfAllFilled(board))   // base case
    {
        _solved = true;
		_solution = board;
		return _solved;
    }
    
	Position empty_cell_pos = find_empty(board);
	int row = empty_cell_pos.first;
	int col = empty_cell_pos.second;

	for (int num = board.get_min_value(); num <= board.get_max_value(); ++num)
	{
		if (isValid(board, num, empty_cell_pos))
		{
			board.set_board_data(row, col, num);

			if (isUnique(board, num, empty_cell_pos)) num = board.get_board_size() + 1;

			// Try the next cell recursively
			if (solve(board)) { _solved = true; return _solved; }
			else { board.set_board_data(row, col, board.get_empty_cell_value()); }   // Backtrack to the most recently filled cell
		}
	}
    
	_recursionDepth++;

	// None of the values solved the Sudoku
	_solved = false;
	return _solved;
}

/*
 * Note:
 * A stack is perfectly suited to backtracking, since all you’re doing is either adding the most
 * recent moves (i.e., pushing moves) or removing moves starting from the most recent (i.e.,
 * popping moves). In other words, your access pattern is exactly Last-In-First-Out (LIFO),
 * which is precisely what a stack provides.
 */