#ifndef SUDOKUSOLVER_SEQUENTIALFORWARDCHECKING_HPP
#define SUDOKUSOLVER_SEQUENTIALFORWARDCHECKING_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"


// +++ The implementation of this algorithm is still under construction. +++
// http://ktiml.mff.cuni.cz/~bartak/constraints/propagation.html
class SudokuSolver_SequentialForwardChecking : public SudokuSolver
{
private:
	StateMatrix _stateMatrix;

public:
    SudokuSolver_SequentialForwardChecking(SudokuBoard& board, bool print_message=true);

	SudokuBoard convertToSudokuGrid(StateMatrix& stateMatrix);

	// Solves the given Sudoku board using sequential forward checking algorithm
    virtual void solve() override { solve_kernel(_stateMatrix); }
    void solve_kernel(StateMatrix& stateMatrix);

	/*
     * Propagate one step.
     *
     * @return: boolean value that indicates whether the propagation changed the state.
     */
	bool propagate_step(StateMatrix& stateMatrix);

	/*
     * Propagate until we don't change the state anymore.
     */
	void propagate(StateMatrix& stateMatrix);
	
	/*
     * Check if we have reached the solution.
     */
	bool done(StateMatrix& stateMatrix);
};


#endif   // SUDOKUSOLVER_SEQUENTIALFORWARDCHECKING_HPP
