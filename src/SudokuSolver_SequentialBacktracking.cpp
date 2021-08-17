#include "SudokuSolver_SequentialBacktracking.hpp"
#include <iostream>


SudokuSolver_SequentialBacktracking::SudokuSolver_SequentialBacktracking(SudokuBoard& board, bool print_message /*=true*/)
	: SudokuSolver(board)
{
	_mode = MODES::SEQUENTIAL_BACKTRACKING;
	if (print_message)
	{
		std::cout << "\n" << "Sequential Sudoku solver using backtracking algorithm starts, please wait..." << "\n";
	}
}

bool SudokuSolver_SequentialBacktracking::solve_kernel()
{
	if (_solved) { return _solved; }

	if (_mode == MODES::SEQUENTIAL_BACKTRACKING) { show_progress_bar(_board, _recursionDepth); }

	if (checkIfAllFilled(_board))   // base case
    {
        _solved = true;
		_solution = _board;
		return _solved;
    }
    
	Position empty_cell_pos = find_empty(_board);
	int row = empty_cell_pos.first;
	int col = empty_cell_pos.second;

	for (int num = _board.get_min_value(); num <= _board.get_max_value(); ++num)
	{
		if (isValid(_board, num, empty_cell_pos))
		{
			_board.set_board_data(row, col, num);

			if (isUnique(_board, num, empty_cell_pos)) { num = _board.get_board_size() + 1; }  // Force to exit the for-loop

			// Try the next cell recursively
			if (solve_kernel()) { _solved = true; return _solved; }
			else { _board.set_board_data(row, col, _board.get_empty_cell_value()); }   // Backtrack to the most recently filled cell
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