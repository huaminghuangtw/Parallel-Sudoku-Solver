#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <math.h>

// N is the size of the 2D matrix : N*N
#define box_size 3
#define N (box_size * box_size)

// Prints the Sudoku board
void print_board(int board[N][N]);

// Checks if the Sudoku board is ALL filled up
bool checkIfAllFilled(int board[N][N]);

// Finds the first empty cell on the given Sudoku board
std::pair<int, int> find_empty(int board[N][N]);

// Checks if a given number can be inserted at a given cell position
bool isValid(int board[N][N], int number, std::pair<int, int> position);