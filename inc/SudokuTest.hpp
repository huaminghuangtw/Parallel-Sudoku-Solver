#ifndef TESTABLESUDOKU_HPP
#define TESTABLESUDOKU_HPP


#include "SudokuBoard.hpp"
#include "termcolor.hpp"
#include <iostream>
#include <cassert>
#include <set>


#define ASSERT_WITH_MESSAGE(condition, message) do { \
if (!(condition)) { std::cout << termcolor::red << message << termcolor::reset << "\n"; } \
assert ((condition)); } while(false)


const int SIZES_VALID = 1;
const int ROWS_VALID = 2;
const int COLUMNS_VALID = 3;
const int BOXES_VALID = 4;


class SudokuTest
{
private:
	SudokuTest() { }

public:
	static bool checkValidSizes(const SudokuBoard& board);
	static bool checkValidRows(const SudokuBoard& board);
	static bool checkValidColumns(const SudokuBoard& board);
	static bool checkValidBoxes(const SudokuBoard& board);

	static bool expect(int flags, int mask)
    {
        return flags && mask;
    }

    static void testBoard(const SudokuBoard& board, int flags=SIZES_VALID | ROWS_VALID | COLUMNS_VALID | BOXES_VALID)
    {
		std::cout << "Check the validity of Sudoku board..." << "\n";

		// A set of unit tests
		ASSERT_WITH_MESSAGE(expect(flags, SIZES_VALID) == checkValidSizes(board), "+++ ERROR: The dimension of the Sudoku board is not valid! +++\n");
        ASSERT_WITH_MESSAGE(expect(flags, ROWS_VALID) == checkValidRows(board), "+++ ERROR: Some rows in Sudoku board contain duplicate numbers! +++\n");
        ASSERT_WITH_MESSAGE(expect(flags, COLUMNS_VALID) == checkValidColumns(board), "+++ ERROR: Some columns in Sudoku board contain duplicate numbers! +++\n");
        ASSERT_WITH_MESSAGE(expect(flags, BOXES_VALID) == checkValidBoxes(board), "+++ ERROR: Some boxes in Sudoku board contain duplicate numbers! +++\n");

		std::cout << termcolor::bright_cyan << "This is a valid Sudoku board!" << termcolor::reset << "\n";
		// std::cout << "Size of Sudoku board: " << termcolor::bright_blue
		//           << board.get_board_size() << " x " << board.get_board_size()
		// 		  << termcolor::reset << "\n";
	}
};


#endif   // SUDOKUTEST_HPP