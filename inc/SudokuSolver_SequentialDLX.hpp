#ifndef SUDOKUSOLVER_SEQUENTIALDANCINGLINKS_HPP
#define SUDOKUSOLVER_SEQUENTIALDANCINGLINKS_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include "Node.hpp"
#include <vector>


// DLX: apply Dancing Links techniques and Algorithm X to solve the exact cover problem. 
class SudokuSolver_SequentialDLX : public SudokuSolver
{
private:
	SudokuBoard _originalBoard;
	CoverMatrix _coverMatrix;
    ColumnNode* _header;
    std::vector<DancingNode*> _answer;
	int _numberOfColumns;   // _BOARD_SIZE * _BOARD_SIZE * _MAX_VALUE
	int _numberOfRows;      // _BOARD_SIZE * _BOARD_SIZE * _NUM_CONSTRAINTS

public:
    SudokuSolver_SequentialDLX(SudokuBoard& board, bool print_message=true);

	// create the quadruple-chained list to represent the cover matrix 
	ColumnNode* createDLXList(CoverMatrix& coverMatrix);

	// convert the quadruple-chained list to the equivalent resolved Sudoku grid
	SudokuBoard convertToSudokuGrid(std::vector<DancingNode*> answer);

	// Solves the given Sudoku board using sequential dancing links algorithm
    void solve();

	// Implementation of the Algorithm X (https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X) and
	// use of Dancing Links on the quadrupled-chained list to solve the exact cover problem
    void process(int k);

	ColumnNode* selectColumnNodeHeuristic(ColumnNode* c, int k);
};


#endif   // SUDOKUSOLVER_SEQUENTIALDANCINGLINKS_HPP