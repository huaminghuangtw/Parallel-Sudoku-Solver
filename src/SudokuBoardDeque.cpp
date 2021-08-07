/*
 * Define a deque of boards to help the implementation of the OpenMP version of the Sudoku solver.
 */

#include <vector>
#include <random>
#include <algorithm>
#include "SudokuBoardDeque.hpp"


SudokuBoardDeque::SudokuBoardDeque(const SudokuBoard& board) { boardDeque.push_back(board); }

SudokuBoardDeque::~SudokuBoardDeque() { while (boardDeque.size() > 0) boardDeque.pop_front(); }

int SudokuBoardDeque::size() const { return boardDeque.size(); }

SudokuBoard& SudokuBoardDeque::front() { return boardDeque.front(); } 

SudokuBoard& SudokuBoardDeque::back() { return boardDeque.back(); } 

SudokuBoard& SudokuBoardDeque::operator[] (int i) { return boardDeque[i]; }

void SudokuBoardDeque::pop_front() { boardDeque.pop_front(); }

void SudokuBoardDeque::pop_back() { boardDeque.pop_back(); }

void SudokuBoardDeque::push_front(SudokuBoard& board) { boardDeque.push_front(board); }

void SudokuBoardDeque::push_back(SudokuBoard& board) { boardDeque.push_back(board); }