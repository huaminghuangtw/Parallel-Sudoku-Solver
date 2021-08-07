#ifndef SUDOKUSOLVER_PARALLELDANCINGLINKS_HPP
#define SUDOKUSOLVER_PARALLELDANCINGLINKS_HPP


#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include "Node.hpp"
#include <vector>


// DLX: apply Dancing Links techniques and Algorithm X to solve the exact cover problem. 
class SudokuSolver_ParallelDLX : public SudokuSolver
{
private:
	SudokuBoard _originalBoard;
	CoverMatrix _coverMatrix;
    ColumnNode* _header;
    std::vector<DancingNode*> _answer;
	int _numberOfColumns;   // _BOARD_SIZE * _BOARD_SIZE * _MAX_VALUE
	int _numberOfRows;      // _BOARD_SIZE * _BOARD_SIZE * _NUM_CONSTRAINTS

public:
    SudokuSolver_ParallelDLX(SudokuBoard& board, bool print_message=true);

	ColumnNode* createDLXList(CoverMatrix& coverMatrix);

	SudokuBoard convertToSudokuGrid(std::vector<DancingNode*> answer);

	// Solves the given Sudoku board using parallel dancing links algorithm
    void solve();

    void process(int k);

	ColumnNode* selectColumnNodeHeuristic(ColumnNode* c, int k);
};


#endif   // SUDOKUSOLVER_PARALLELDANCINGLINKS_HPP