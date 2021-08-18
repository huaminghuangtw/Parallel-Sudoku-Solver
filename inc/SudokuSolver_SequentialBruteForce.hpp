#ifndef SUDOKUSOLVER_SEQUENTIALBRUTEFORCE_HPP
#define SUDOKUSOLVER_SEQUENTIALBRUTEFORCE_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"


class SudokuSolver_SequentialBruteForce : public SudokuSolver
{
public:
	SudokuSolver_SequentialBruteForce(SudokuBoard& board, bool print_message=true);

	// Solves the given Sudoku board using sequential brute force algorithm
    virtual void solve() override {	solve_kernel(0, 0); }
	void solve_kernel(int row, int col);
};


#endif   // SUDOKUSOLVER_SEQUENTIALBRUTEFORCE_HPP