#ifndef TESTABLESUDOKU_HPP
#define TESTABLESUDOKU_HPP


#include "SudokuBoard.hpp"
#include <iostream>
#include <cassert>
#include <set>


#define ASSERT_WITH_MESSAGE(condition, message) do { \
if (!(condition)) { printf((message)); } \
assert ((condition)); } while(false)


const int ROWS_VALID = 1;
const int COLUMNS_VALID = 2;
const int BOXES_VALID = 3;
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

    static void testBoard(SudokuBoard& board, int flags = ROWS_VALID | COLUMNS_VALID | BOXES_VALID | BOARD_VALID)
    {
		std::cout << "Check the validity of the given board..." << "\n";

        ASSERT_WITH_MESSAGE(expect(flags, ROWS_VALID) == checkValidRows(board), "+++ Some rows in Sudoku board contain duplicate numbers! +++\n");
        ASSERT_WITH_MESSAGE(expect(flags, COLUMNS_VALID) == checkValidColumns(board), "+++ Some columns in Sudoku board contain duplicate numbers! +++\n");
        ASSERT_WITH_MESSAGE(expect(flags, BOXES_VALID) == checkValidBoxes(board), "+++ Some boxes in Sudoku board contain duplicate numbers! +++\n");
        ASSERT_WITH_MESSAGE(expect(flags, BOARD_VALID) == checkValid(board), "+++ This is NOT a valid Sudoku board! +++\n");

		std::cout << "This is a valid Sudoku board!" << "\n";
		std::cout << "The size of the given Sudoku board: " << board.get_board_size() << " x " << board.get_board_size()  << "\n";
    }
};


#endif   // TESTABLESUDOKU_HPP