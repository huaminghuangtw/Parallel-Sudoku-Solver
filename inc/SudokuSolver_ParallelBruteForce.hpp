#ifndef SUDOKUSOLVER_PARALLELBRUTEFORCE_HPP
#define SUDOKUSOLVER_PARALLELBRUTEFORCE_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include "SudokuBoardDeque.hpp"


class SudokuSolver_ParallelBruteForce : public SudokuSolver
{
private:
	SudokuBoardDeque _board_deque;

public:
	SudokuSolver_ParallelBruteForce(SudokuBoard& board, bool print_message=true);

    // Divides one Sudoku problem into several simpler sub-problems and push them to the end of board deque
	void bootstrap();
	void bootstrap(SudokuBoardDeque& boardDeque, int indexOfRows);

	// Solves the given Sudoku board using parallel brute force algorithm
	virtual void solve() override
	{
		/* Choose one of the following kernels to execute */
		solve_kernel_1();
		// solve_kernel_2();
		// solve_bruteforce_par(_board, 0, 0);
	}
	
	void solve_kernel_1();
	void solve_kernel_2();
	void solve_bruteforce_seq(SudokuBoard& board, int row, int col);
	void solve_bruteforce_par(SudokuBoard& board, int row, int col);
};


#endif   // SUDOKUSOLVER_PARALLELBRUTEFORCE_HPP