#ifndef SUDOKUBOARDDEQUE_HPP
#define SUDOKUBOARDDEQUE_HPP


#include <iostream>
#include <iterator>
#include <deque>
#include "SudokuBoard.hpp"


class SudokuBoardDeque
{
public:
    SudokuBoardDeque() = default;

	// copy constructor of class SudokuBoardDeque: construct a new SudokuBoardDeque by saving the board as its first element
    SudokuBoardDeque(const SudokuBoard& board);

    std::deque<SudokuBoard> boardDeque;

    // gets the total number of boards in the deque
    int size() const;

    // gets the first board in the deque
    SudokuBoard& front();

    // gets the last board in the deque
    SudokuBoard& back();

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

    // destructor of class SudokuBoardDeque: delete the board inside the deque one by one
    virtual ~SudokuBoardDeque();
};


#endif   // SUDOKUBOARDDEQUE_HPP
