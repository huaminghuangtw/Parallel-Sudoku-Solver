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

// pushes the first board of this SudokuBoardDeque object to the end of another SudokuBoardDeque object
void SudokuBoardDeque::passFB(SudokuBoardDeque& bq)
{
    bq.boardDeque.push_back(boardDeque.front());
    boardDeque.pop_front();
}

// pushes the first board of this SudokuBoardDeque object to the front of another SudokuBoardDeque object
void SudokuBoardDeque::passFF(SudokuBoardDeque& bq)
{
    bq.boardDeque.push_front(boardDeque.front());
    boardDeque.pop_front();
}

// pushes the last board of this SudokuBoardDeque object to the front of another SudokuBoardDeque object
void SudokuBoardDeque::passBF(SudokuBoardDeque& bq)
{
    bq.boardDeque.push_front(boardDeque.back());
    boardDeque.pop_back();
}

// pushes the last board of this SudokuBoardDeque object to the end of another SudokuBoardDeque object
void SudokuBoardDeque::passBB(SudokuBoardDeque& bq)
{
    bq.boardDeque.push_back(boardDeque.back());
    boardDeque.pop_back();
}