/*
 * Define a queue of boards to help the implementation of the OpenMP version of the solver.
 */

#include <vector>
#include <random>
#include <algorithm>
#include "SudokuBoardDeque.hpp"


SudokuBoardDeque::SudokuBoardDeque(const SudokuBoard& board)
{
	SudokuBoard* pbnew = new SudokuBoard(board);
    boardDeque.push_back(pbnew); 
}

SudokuBoardDeque::~SudokuBoardDeque()
{
    while (boardDeque.size() > 0) {
		delete boardDeque.front();
        boardDeque.pop_front();
    }
}

int SudokuBoardDeque::size() const { return boardDeque.size(); }

SudokuBoard& SudokuBoardDeque::front() const { return *(boardDeque.front()); } 

SudokuBoard& SudokuBoardDeque::back() const { return *(boardDeque.back()); } 

SudokuBoard& SudokuBoardDeque::operator[] (int i) { return *(boardDeque[i]); }

void SudokuBoardDeque::pop_front()
{
	delete boardDeque.front();
    boardDeque.pop_front();
}

void SudokuBoardDeque::pop_back()
{
	delete boardDeque.back();
    boardDeque.pop_back();
}

void SudokuBoardDeque::push_front(SudokuBoard& board)
{
	SudokuBoard* new_board = new SudokuBoard(board);
    boardDeque.push_front(new_board);
}

void SudokuBoardDeque::push_back(SudokuBoard& board)
{
	SudokuBoard* new_board = new SudokuBoard(board);
    boardDeque.push_back(new_board);
}