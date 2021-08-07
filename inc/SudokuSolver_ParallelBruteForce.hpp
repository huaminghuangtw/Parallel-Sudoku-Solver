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
	SudokuSolver_ParallelBruteForce(bool print_message=true);

    // Divides one Sudoku problem into several simpler sub-problems and push them to the end of board deque
	void bootstrap();
	void bootstrap(SudokuBoard& board) { _board_deque.push_back(board); bootstrap(); }
	void bootstrap(SudokuBoardDeque& boardDeque, int indexOfRows);

	// Solves the given Sudoku board using parallel brute force algorithm
	void solve(SudokuBoard& board);
	void solve2(SudokuBoard& board);
	void solve3(SudokuBoard& board, int row=0, int col=0);
};


#endif   // SUDOKUSOLVER_PARALLELBRUTEFORCE_HPP