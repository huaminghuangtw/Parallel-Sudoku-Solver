#ifndef SUDOKUSOLVER_SEQUENTIALBRUTEFORCE_HPP
#define SUDOKUSOLVER_SEQUENTIALBRUTEFORCE_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"


class SudokuSolver_SequentialBruteForce : public SudokuSolver
{
public:
	SudokuSolver_SequentialBruteForce();

	// Solves the given Sudoku board using sequential brute force algorithm
	void solve(SudokuBoard& board, size_t row=0, size_t col=0);
};


#endif   // SUDOKUSOLVER_SEQUENTIALBRUTEFORCE_HPP