#include "SudokuSolver_ParallelBruteForce.hpp"
#include "SudokuSolver_SequentialBruteForce.hpp"
#include <iostream>
#include <vector>
#include <omp.h>


SudokuSolver_ParallelBruteForce::SudokuSolver_ParallelBruteForce(bool print_message /*=true*/)
{
	if (print_message) {
		std::cout << "\n" << "Parallel Sudoku solver using brute force algorithm starts, please wait..." << "\n";
		std::cout << "Using " << omp_get_num_threads() << " OMP threads" << "\n";
	}
}

void SudokuSolver_ParallelBruteForce::bootstrap()
{
	// if no start boards in the board deque, then return
    if (_board_deque.size() == 0) {
        return;
    }

	SudokuBoard& board = _board_deque.front();

	if (checkIfAllFilled(board)) {
		return;
	}

	Position empty_cell_pos = find_empty(board);

	int row = empty_cell_pos.first;
	int col = empty_cell_pos.second;

	// fill in all possible numbers to the empty cell and then
	// add the corresponding possible board of solution to the end of board deque
	for (int num = 1; num <= board.get_board_size(); ++num)
	{
		if (isValid(board, num, empty_cell_pos))
		{
			board.set_board_data(row, col, num);
			_board_deque.push_back(board);
		}
	}

	_board_deque.pop_front();
}

void SudokuSolver_ParallelBruteForce::solve(SudokuBoard& board)
{
	// push the board onto the board deque as the first element
	_board_deque.push_back(board);

	// ensure some level of bootstrapping
	int num_bootstraps = omp_get_num_threads() * omp_get_num_threads();
	for (int i = 0; i < num_bootstraps; ++i)
	{
		bootstrap();
	}

    int numberOfBoards = _board_deque.size();
    //std::cout << "Number of Suodku boards on the board deque: " << numberOfBoards << "\n";

	std::vector<SudokuSolver_SequentialBruteForce> solvers(numberOfBoards, SudokuSolver_SequentialBruteForce(false));

	#pragma omp parallel for schedule(dynamic, 1) default(none) \
	shared(numberOfBoards, solvers, _solved, _status, _solution)
    for (int indexOfBoard = 0; indexOfBoard < numberOfBoards; ++indexOfBoard)
	{
		if (_solved) continue;

        solvers[indexOfBoard].solve(_board_deque[indexOfBoard]);

		if (solvers[indexOfBoard].get_solver_status() == SolverStatus::SOLVED)
		{
			_solved = true;
			_status = SolverStatus::SOLVED;
			_solution = solvers[indexOfBoard].get_solution();
		}
	}
}