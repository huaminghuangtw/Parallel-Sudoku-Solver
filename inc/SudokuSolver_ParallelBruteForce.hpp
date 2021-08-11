#ifndef SUDOKUSOLVER_PARALLELBRUTEFORCE_HPP
#define SUDOKUSOLVER_PARALLELBRUTEFORCE_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include "SudokuBoardDeque.hpp"
#include <deque>


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
	virtual void solve() override { solve_kernel1(); }
	void solve_kernel1();
	void solve_kernel2();
};


#endif   // SUDOKUSOLVER_PARALLELBRUTEFORCE_HPP