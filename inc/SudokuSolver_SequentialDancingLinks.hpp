#ifndef SUDOKUSOLVER_SEQUENTIALDANCINGLINKS_HPP
#define SUDOKUSOLVER_SEQUENTIALDANCINGLINKS_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include "Node.hpp"
#include <vector>
#include <cmath>


class SudokuSolver_SequentialDancingLinks : public SudokuSolver
{
private:
	SudokuBoard _originalBoard;
	CoverMatrix _coverMatrix;
    ColumnNode* _header;
    std::vector<DancingNode*> _answer;
	int _numberOfColumns;   // _BOARD_SIZE * _BOARD_SIZE * _MAX_VALUE
	int _numberOfRows;      // _BOARD_SIZE * _BOARD_SIZE * _NUM_CONSTRAINTS

public:
    SudokuSolver_SequentialDancingLinks(SudokuBoard& board, bool print_message=true);

	ColumnNode* createDLXList(CoverMatrix& coverMatrix);

	SudokuBoard convertToSudokuGrid(std::vector<DancingNode*> answer);

	// Solves the given Sudoku board using sequential dancing links algorithm
    void solve();

    void process(int k);

	ColumnNode* selectColumnNodeHeuristic(ColumnNode* c, int k);
};


#endif   // SUDOKUSOLVER_SEQUENTIALDANCINGLINKS_HPP