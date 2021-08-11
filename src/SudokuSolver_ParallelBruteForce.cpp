#include "SudokuSolver_ParallelBruteForce.hpp"
#include "SudokuSolver_SequentialBruteForce.hpp"
#include "termcolor.hpp"
#include <iostream>
#include <vector>
#include <omp.h>


SudokuSolver_ParallelBruteForce::SudokuSolver_ParallelBruteForce(SudokuBoard& board, bool print_message /*=true*/)
	: SudokuSolver(board)
{
	_mode = MODES::PARALLEL_BRUTEFORCE;
	if (print_message) {
		std::cout << "\n" << "Parallel Sudoku solver using brute force algorithm starts, please wait..." << "\n";
	}
}

void SudokuSolver_ParallelBruteForce::bootstrap()
{
	// if no start boards in the board deque, then return
    if (_board_deque.size() == 0) {
        return;
    }

	SudokuBoard board = _board_deque.front();

	if (checkIfAllFilled(board)) {
		return;
	}

	Position empty_cell_pos = find_empty(board);

	int row = empty_cell_pos.first;
	int col = empty_cell_pos.second;

	// fill in all possible numbers to the empty cell and then
	// add the corresponding possible board of solution to the end of board deque
	for (int num = board.get_min_value(); num <= board.get_max_value(); ++num)
	{
		if (isValid(board, num, empty_cell_pos))
		{
			board.set_board_data(row, col, num);
			_board_deque.push_back(board);
		}
	}

	_board_deque.pop_front();
}

void SudokuSolver_ParallelBruteForce::bootstrap(SudokuBoardDeque& boardDeque, int indexOfRows)
{
	// if no start boards in the board deque, then return
    if (boardDeque.size() == 0) return;

	while (!checkIfRowFilled(boardDeque.front(), indexOfRows))
	{
		SudokuBoard board = boardDeque.front();

		int empty_cell_col_index = find_empty_from_row(board, indexOfRows);

		// fill in all possible numbers to the empty cell and then
		// add the corresponding possible board of solution to the end of board deque
		for (int num = board.get_min_value(); num <= board.get_max_value(); ++num)
		{
			Position empty_cell_pos = std::make_pair(indexOfRows, empty_cell_col_index);

			if (isValid(board, num, empty_cell_pos))
			{
				board.set_board_data(indexOfRows, empty_cell_col_index, num);
				boardDeque.push_back(board);
			}
		}

		boardDeque.pop_front();
	}
}

void SudokuSolver_ParallelBruteForce::solve_kernel1()
{
	// push the board onto the board deque as the first element
	_board_deque.push_back(_board);

	// ensure some level of bootstrapping
	int num_bootstraps = omp_get_num_threads();
	#pragma omp parallel for schedule(static) default(none) shared(num_bootstraps)
	for (int i = 0; i < num_bootstraps; ++i)
	{
		bootstrap();
	}

	int numberOfBoards = _board_deque.size();
    
	// For debugging
	// std::cout << "Number of Suodku boards on the board deque: " << numberOfBoards << "\n";
	// for (int i = 0; i < numberOfBoards; ++i)
	// {
	// 	std::cout << "BOARD-" << i << "\n";
	// 	print_board(_board_deque[i]);
	// 	std::cout << "*****" << "\n";
	// }

	std::vector<SudokuSolver_SequentialBruteForce> solvers;

	#pragma omp parallel for schedule(static) default(none) shared(numberOfBoards, solvers)
    for (int indexOfBoard = 0; indexOfBoard < numberOfBoards; ++indexOfBoard)
	{
		solvers.push_back(SudokuSolver_SequentialBruteForce(_board_deque[indexOfBoard], false));

		if (_solved) continue;

		solvers[indexOfBoard].set_mode(MODES::PARALLEL_BRUTEFORCE);
        solvers[indexOfBoard].solve();

		if (solvers[indexOfBoard].get_status() == true)
		{
			_solved = true;
			_solution = solvers[indexOfBoard].get_solution();
		}
	}
}

void SudokuSolver_ParallelBruteForce::solve_kernel2()
{
	std::vector<SudokuBoardDeque> groupOfBoardDeques(_board.get_board_size(), SudokuBoardDeque(_board));
	#pragma omp parallel default(none) shared(groupOfBoardDeques)
	{	
		int SIZE = groupOfBoardDeques.size();

		#pragma omp for nowait schedule(static)
		for (int i = 0; i < SIZE; ++i)
		{
			bootstrap(groupOfBoardDeques[i], i);
			_board_deque.boardDeque.insert(_board_deque.boardDeque.end(),
										   groupOfBoardDeques[i].boardDeque.begin(),
										   groupOfBoardDeques[i].boardDeque.end());
		}
	}

	int numberOfBoards = _board_deque.size();
    
	// For debugging
	// std::cout << "Number of Suodku boards on the board deque: " << numberOfBoards << "\n";
	// for (int i = 0; i < numberOfBoards; ++i)
	// {
	// 	std::cout << "BOARD-" << i << "\n";
	// 	print_board(_board_deque[i]);
	// 	std::cout << "*****" << "\n";
	// }

	std::vector<SudokuSolver_SequentialBruteForce> solvers;

	#pragma omp parallel for schedule(static) default(none) shared(numberOfBoards, solvers)
    for (int indexOfBoard = 0; indexOfBoard < numberOfBoards; ++indexOfBoard)
	{	
		solvers.push_back(SudokuSolver_SequentialBruteForce(_board_deque[indexOfBoard], false));

		if (_solved) continue;

        solvers[indexOfBoard].solve();

		if (solvers[indexOfBoard].get_status() == true)
		{
			_solved = true;
			_solution = solvers[indexOfBoard].get_solution();
		}
	}
}

void SudokuSolver_ParallelBruteForce::solve_kernel3(SudokuBoard& board, int row, int col)
{	
	if (_solved) return;

	int BOARD_SIZE = board.get_board_size();

	int abs_index = row * BOARD_SIZE + col;

    if (abs_index >= board.get_num_total_cells())
	{
		_solved = true;
		_solution = board;
		return;
    }
    
	int row_next = (abs_index + 1) / BOARD_SIZE;
	int col_next = (abs_index + 1) % BOARD_SIZE;

	if (!isEmpty(board, row, col))
	{   
		solve_kernel3(board, row_next, col_next);
    }
	else
	{
		// Fill in all possible numbers
		for (int num = board.get_min_value(); num <= board.get_max_value(); ++num)
		{
			Position pos = std::make_pair(row, col);

            if (isValid(board, num, pos))
			{
				// Needs to work on the new copy of the Sudoku board
				SudokuBoard local_board(board);
				local_board.set_board_data(row, col, num);

				if (isUnique(local_board, num, pos)) num = BOARD_SIZE + 1;

				// Use the final clause in #pragma omp task directive to reduce the overhead of tasks creation, for better scalability
				// If we don't set such a threshold, the workload of a single task is therefore too small and the overhead of task creation
				// become significant compared to the workload of a task
				#pragma omp task default(none) firstprivate(local_board, row_next, col_next) \
				                               final(_recursionDepth > board.get_board_size())
				solve_kernel3(local_board, row_next, col_next);

				// board.set_board_data(row, col, board.get_empty_cell_value());
				// Why don't we need this line? Because we don't modify anything in the original board.
            }
        }
    }

	_recursionDepth++;
}
