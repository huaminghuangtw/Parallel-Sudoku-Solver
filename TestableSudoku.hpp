#ifndef TESTABLESUDOKU_HPP
#define TESTABLESUDOKU_HPP


#include "SudokuBoard.hpp"
#include <iostream>
#include <cassert>
#include <set>


const int ROWS_VALID = 1;
const int COLS_VALID = 2;
const int SQUARES_VALID = 3;
const int BOARD_VALID = 4;


class TestableSudoku
{
private:
	TestableSudoku() { }

public:
	static bool checkValidRows(SudokuBoard& board);
	static bool checkValidColumns(SudokuBoard& board);
	static bool checkValidBoxes(SudokuBoard& board);
	static bool checkValid(SudokuBoard& board);

	static bool expect(int flags, int mask)
    {
        return flags && mask;
    }

    static void testBoard(SudokuBoard& board, int flags = ROWS_VALID | COLS_VALID | SQUARES_VALID | BOARD_VALID)
    {
		std::cout << "Check the validity of the given board..." << "\n";

        assert(expect(flags, ROWS_VALID) == checkValidRows(board));
        assert(expect(flags, COLS_VALID) == checkValidColumns(board));
        assert(expect(flags, SQUARES_VALID) == checkValidBoxes(board));
        assert(expect(flags, BOARD_VALID) == checkValid(board));

		std::cout << "This is a valid Sudoku board!" << "\n";
		std::cout << "The size of the given Sudoku board: " << board.get_board_size() << " x " << board.get_board_size()  << "\n";
    }
};


#endif   // TESTABLESUDOKU_HPP