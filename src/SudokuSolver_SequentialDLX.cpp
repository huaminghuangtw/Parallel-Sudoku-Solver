#include "SudokuSolver_SequentialDLX.hpp"
#include <iostream>


SudokuSolver_SequentialDLX::SudokuSolver_SequentialDLX(SudokuBoard& board, bool print_message /*=true*/)
	: _originalBoard(board)
{
	if (print_message) {
		std::cout << "\n" << "Sequential Sudoku solver using dancing links algorithm starts, please wait..." << "\n";
	}
	board.createCoverMatrix(_coverMatrix);
	board.convertToCoverMatrix(_coverMatrix);
	_numberOfRows = _coverMatrix.size();         
	_numberOfColumns = _coverMatrix[0].size();
	_header = createDLXList(_coverMatrix);
}

ColumnNode* SudokuSolver_SequentialDLX::createDLXList(CoverMatrix& coverMatrix)
{
	ColumnNode* headerNode = new ColumnNode("header");
	std::vector<ColumnNode*> columnNodes;

	for (int i = 0; i < _numberOfColumns; ++i)
	{
		ColumnNode* n = new ColumnNode(std::to_string(i));
		columnNodes.push_back(n);
		headerNode = (ColumnNode*) headerNode->linkRight(n);
	}

	headerNode = headerNode->right->column;

	for (int i = 0; i < _numberOfRows; ++i)
	{
		DancingNode* prev = NULL;

		for (int j = 0; j < _numberOfColumns; ++j)
		{
			if (coverMatrix[i][j] == 1)
			{
				ColumnNode* col = columnNodes[j];
				DancingNode* newNode = new DancingNode(col);

				if (prev == NULL)
				{
					prev = newNode;
				}

				col->top->linkDown(newNode);
				prev = prev->linkRight(newNode);
				col->size++;
			}
		}
	}

	headerNode->size = _numberOfColumns;

	return headerNode;
}

SudokuBoard SudokuSolver_SequentialDLX::convertToSudokuGrid(std::vector<DancingNode*> answer)
{
	SudokuBoard tmpBoard = SudokuBoard(_originalBoard);

	for (DancingNode* n : answer)
	{
		DancingNode* rcNode = n;
		int min = std::stoi(rcNode->column->name);

		for (DancingNode* tmp = n->right; tmp != n; tmp = tmp->right)
		{
			int val = std::stoi(tmp->column->name);

			if (val < min)
			{
				min = val;
				rcNode = tmp;
			}
		}

		int ans1 = std::stoi(rcNode->column->name);
		int ans2 = std::stoi(rcNode->right->column->name);
		int r = ans1 / _originalBoard.get_board_size();
		int c = ans1 % _originalBoard.get_board_size();
		int num = (ans2 % _originalBoard.get_board_size()) + 1;
		tmpBoard.set_board_data(r, c, num);
	}

	return tmpBoard;
}

void SudokuSolver_SequentialDLX::solve()
{
	process(0);
}

void SudokuSolver_SequentialDLX::process(int k)
{
	if (_header->right == _header)
	{
		_solved = true;
		_solution = convertToSudokuGrid(_answer);
		return;
	}
	else
	{
		ColumnNode* c = (ColumnNode*) _header->right;
		c = selectColumnNodeHeuristic(c, k);
		c->cover();

		for (DancingNode* r = c->bottom; r != c; r = r->bottom)
		{
			_answer.push_back(r);

			for (DancingNode* j = r->right; j != r; j = j->right)
			{
				j->column->cover();
			}

			process(k + 1);

			if (_solved) return;

			r = _answer[_answer.size() - 1];
			_answer.pop_back();
			c = r->column;

			for (DancingNode* j = r->left; j != r; j = j->left)
			{
				j->column->uncover();
			}
		}

		c->uncover();
	}
}

ColumnNode* SudokuSolver_SequentialDLX::selectColumnNodeHeuristic(ColumnNode* c, int k)
{
	if (k == 0)
	{
		c = (ColumnNode*) c->right;
	}
	else
	{
		// afterwards choose constraint with least options to satisfy
		for (ColumnNode* temp = (ColumnNode*) c->right; temp != _header; temp = (ColumnNode*) temp->right)
		{
			if (temp->size < c->size) c = temp;
		}
	}

	return c;
}