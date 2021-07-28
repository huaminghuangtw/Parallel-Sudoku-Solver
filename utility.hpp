#ifndef UTILITY_HPP
#define UTILITY_HPP


#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <math.h>
#include <vector>


extern int BOX_SIZE;
extern int SUDOKU_SIZE;


using SudokuBoard = std::vector<std::vector<int>>;


// Returns a 2D array reading from a file containing the initial Sudoku board in space separated format
// (empty cells are represented by 0s)
SudokuBoard readInput(const std::string& filename);

// Prints the Sudoku board
void print_board(SudokuBoard board);

// Checks if the Sudoku board is ALL filled up
bool checkIfAllFilled(SudokuBoard board);

// Finds the first empty cell on the given Sudoku board
std::pair<int, int> find_empty(SudokuBoard board);

// Checks if a given number can be inserted at a given cell position
bool isValid(SudokuBoard board, int num, std::pair<int, int> pos);


#endif   // UTILITY_HPP