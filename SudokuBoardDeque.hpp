#ifndef SUDOKUBOARDDEQUE_H
#define SUDOKUBOARDDEQUE_H


#include <iostream>
#include <deque>
#include "SudokuBoard.hpp"


class SudokuBoardDeque
{
public:
    SudokuBoardDeque() = default;

	// copy constructor of class SudokuBoardDeque: construct a new SudokuBoardDeque by saving the board as its first element
    SudokuBoardDeque(const SudokuBoard& board);

    std::deque<SudokuBoard*> boardDeque;

    // gets the total number of boards in the deque
    int size() const;

    // gets the first board in the deque
    SudokuBoard& front() const;

    // gets the last board in the deque
    SudokuBoard& back() const;

    // gets the i-th board in the deque
    SudokuBoard& operator[] (int i);

    // removes the first board in the deque and release memory
    void pop_front();

    // removes the last board in the deque and release memory
    void pop_back();

    // pushes a board to the front of the deque
    void push_front(SudokuBoard& board);

    // pushes a board to the end of the deque
    void push_back(SudokuBoard& board);

    // passes the ownership of one board to another container without copying it
    void passFB(SudokuBoardDeque& bq);   // pop_front to push_back
    void passFF(SudokuBoardDeque& bq);   // pop_front to push_front
    void passBF(SudokuBoardDeque& bq);   // pop_back to push front
    void passBB(SudokuBoardDeque& bq);   // pop_back to push back
	
    // shortcut functions
    virtual void pass(SudokuBoardDeque& bq) { passFB(bq); }
    virtual void dump(SudokuBoardDeque& bq, int len=-1) { while (len-- != 0 && size() > 0) passFB(bq); } 
    
    // destructor of class SudokuBoardDeque: delete the board inside the deque one by one
    virtual ~SudokuBoardDeque();
};


#endif   // SUDOKUBOARDDEQUE_H
