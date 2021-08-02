#include "SudokuSolver_SequentialBacktracking.hpp"
#include "SudokuTest.hpp"
#include <iostream>


SudokuSolver_SequentialBacktracking::SudokuSolver_SequentialBacktracking()
{
	std::cout << "\n" << "Sequential Sudoku solver using backtracking algorithm starts, please wait..." << "\n";
}

void SudokuSolver_SequentialBacktracking::solve(SudokuBoard& board)
{
    if (checkIfAllFilled(board))   // base case
    {
		std::cout << "Solved!" << "\n";
        _solved = true;
		_status = SolverStatus::SOLVED;
		_solution = board;
		SudokuTest::testBoard(_solution);
		return;
    }
    else
    {
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
            }
			
			// Backtrack to the most recently filled cell
			board.set_board_data(row, col, board.get_empty_cell_value());
        }

        // None of the values solved the Sudoku
		_solved = false;
        return;
    }
}
