#include "TestableSudoku.hpp"


// Returns whether the dimensions of the given Sudoku board is valid.
bool TestableSudoku::checkValidSizes(const SudokuBoard& board)
{
	size_t BOARD_SIZE = board.get_board_size();
	size_t ROW_SIZE = board.get_board_data().size();
	size_t COL_SIZE = board.get_board_data()[0].size(); 

	if ( (ROW_SIZE != BOARD_SIZE) || (COL_SIZE != BOARD_SIZE)) {
		return false;
	}

	return true;
}

// Returns whether all the rows are currently valid,
// i.e., whether no rows contain any duplicate numbers.
bool TestableSudoku::checkValidRows(const SudokuBoard& board)
{
	for (size_t row = 0; row < board.get_board_size(); ++row)
	{
		std::set<int> valuesInRow;

		for (size_t col = 0; col <board.get_board_size(); ++col)
		{
			int val = board.get_board_data(row, col);

			if (val == board.get_empty_cell_value()) continue;

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
bool TestableSudoku::checkValidColumns(const SudokuBoard& board)
{
	for (size_t col = 0; col < board.get_board_size(); ++col)
	{
		std::set<int> valuesInCol;

		for (size_t row = 0; row < board.get_board_size(); ++row)
		{
			int val = board.get_board_data(row, col);

			if (val == board.get_empty_cell_value()) continue;

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
bool TestableSudoku::checkValidBoxes(const SudokuBoard& board)
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

					if (val == board.get_empty_cell_value()) continue;

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