#include "TestableSudoku.hpp"


// Returns whether all the rows are currently valid,
// i.e., whether no rows contain any duplicate numbers.
bool TestableSudoku::checkValidRows(SudokuBoard& board)
{
	for (size_t row = 0; row < board.get_board_size(); ++row)
	{
		std::set<int> valuesInRow;

		for (size_t col = 0; col <board.get_board_size(); ++col)
		{
			int val = board.get_board_data(row, col);

			if (val == 0) continue;

			if (valuesInRow.find(val) != valuesInRow.end()) {
				return false;
			}

			valuesInRow.insert(val);
		}
	}

	return true;
}

// Returns whether all the columns are currently valid, 
// i.e., whether no columns contain any duplicate numbers.
bool TestableSudoku::checkValidColumns(SudokuBoard& board)
{
	for (size_t row = 0; row < board.get_board_size(); ++row)
	{
		std::set<int> valuesInCol;

		for (size_t col = 0; col < board.get_board_size(); ++col)
		{
			int val = board.get_board_data(row, col);

			if (val == 0) continue;

			if (valuesInCol.find(val) != valuesInCol.end()) {
				return false;
			}

			valuesInCol.insert(val);
		}
	}

	return true;
}

// Returns whether all the boxes are currently valid, 
// i.e., whether no boxes (subgrids) contain any duplicate numbers.
bool TestableSudoku::checkValidBoxes(SudokuBoard& board)
{
	size_t BOX_SIZE = board.get_box_size();

	for (size_t boxX = 0; boxX < BOX_SIZE; ++boxX)
	{
		for (size_t boxY = 0; boxY < BOX_SIZE; ++boxY)
		{
			std::set<int> valuesInBox;

			for (size_t m = 0; m < BOX_SIZE; ++m)
			{
				for (size_t n = 0; n < BOX_SIZE; ++n)
				{
					int val = board.get_board_data(boxX * BOX_SIZE + m, boxY * BOX_SIZE + n);

					if (val == 0) continue;

					if (valuesInBox.find(val) != valuesInBox.end()) {
						return false;
					}

					valuesInBox.insert(val);
				}
			}

		}
	}

	return true;
}

// Returns whether the current cell is valid, i.e., whether its rows, columns,
// and boxes are all valid and do not contain any duplicate numbers.
bool TestableSudoku::checkValid(SudokuBoard& board)
{
	return checkValidRows(board) && checkValidColumns(board) && checkValidBoxes(board);
}