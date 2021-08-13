#include "SudokuSolver_SequentialForwardChecking.hpp"
#include "helper.hpp"
#include <algorithm>
#include <vector>


SudokuSolver_SequentialForwardChecking::SudokuSolver_SequentialForwardChecking(SudokuBoard& board, bool print_message /*=true*/)
	: SudokuSolver(board)
{
	_mode = MODES::SEQUENTIAL_FORWARDCHECKING;
	if (print_message)
	{
		std::cout << "\n" << "Sequential Sudoku solver using forward checking algorithm starts, please wait..." << "\n";
	}
	board.createStateMatrix(_stateMatrix);
	board.convertToStateMatrix(_stateMatrix);
}

bool SudokuSolver_SequentialForwardChecking::propagate_step(StateMatrix& stateMatrix)
{
    bool new_units = false;
	random_selector<> selector{ };

	int BOARD_SIZE = _board.get_board_size();
	int BOX_SIZE = _board.get_box_size();

    // propagate row rule
    for (int i = 0; i < BOARD_SIZE; ++i)
	{
		std::vector<MultiType> row = stateMatrix[i];

        std::set<int> setOfFilledValuesInRow;
		for (auto& e : row)
		{
			if (std::holds_alternative<int>(e))   // if the element row[i] is of type int
			{
				setOfFilledValuesInRow.insert(std::get<int>(e));
			}
		}

        for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (std::holds_alternative<std::set<int>>(stateMatrix[i][j]))   // if the element stateMatrix[i][j] is of type std::set<int>
			{
				auto state = std::get<std::set<int>>(stateMatrix[i][j]);
				std::set<int> temp;
				std::set_difference(state.begin(), state.end(),
									setOfFilledValuesInRow.begin(), setOfFilledValuesInRow.end(),
									std::inserter(temp, temp.begin()));
				stateMatrix[i][j] = temp;

				if (state.size() == 1)
				{
					int val = selector(state);
					state.erase(val);
					stateMatrix[i][j] = val;
					setOfFilledValuesInRow.insert(val);
					new_units = true;
				}
			}
		}
	}     

    // propagate column rule
    for (int j = 0; j < BOARD_SIZE; ++j)
	{
		std::vector<MultiType> column;
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			column.push_back(stateMatrix[i][j]);
		}
		
		std::set<int> setOfFilledValuesInCol;
		for (auto& e : column)
		{
			if (std::holds_alternative<int>(e))   // if the element column[i] is of type int
			{
				setOfFilledValuesInCol.insert(std::get<int>(e));
			}
		}

		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			if (std::holds_alternative<std::set<int>>(stateMatrix[i][j]))   // if the element stateMatrix[i][j] is of type std::set<int>
			{
				auto state = std::get<std::set<int>>(stateMatrix[i][j]);
				std::set<int> temp;
				std::set_difference(state.begin(), state.end(),
									setOfFilledValuesInCol.begin(), setOfFilledValuesInCol.end(),
									std::inserter(temp, temp.begin()));
				stateMatrix[i][j] = temp;

				if (state.size() == 1)
				{
					int val = selector(state);
					state.erase(val);
					stateMatrix[i][j] = val;
					setOfFilledValuesInCol.insert(val);
					new_units = true;
				}
			}
		}
	}

    // propagate box rule
	for (int i = 0; i < BOX_SIZE; ++i)
	{
		for (int j = 0; j < BOX_SIZE; ++j)
		{
			std::set<int> setOfFilledValuesInBox;

            for (int s = BOX_SIZE * i; s < BOX_SIZE * i + BOX_SIZE; ++s)
			{
				for (int t = BOX_SIZE * j; t < BOX_SIZE * j + BOX_SIZE; ++t)
				{
                    if (std::holds_alternative<int>(stateMatrix[i][j]))   // if the element column[i] is of type int
					{
						setOfFilledValuesInBox.insert(std::get<int>(stateMatrix[i][j]));
					}
				}
			}

            for (int s = BOX_SIZE * i; s < BOX_SIZE * i + BOX_SIZE; ++s)
			{
				for (int t = BOX_SIZE * j; t < BOX_SIZE * j + BOX_SIZE; ++t)
				{
					if (std::holds_alternative<std::set<int>>(stateMatrix[i][j]))   // if the element stateMatrix[i][j] is of type std::set<int>
					{
						auto state = std::get<std::set<int>>(stateMatrix[i][j]);
						std::set<int> temp;
						std::set_difference(state.begin(), state.end(),
											setOfFilledValuesInBox.begin(), setOfFilledValuesInBox.end(),
											std::inserter(temp, temp.begin()));
						stateMatrix[i][j] = temp;

						if (state.size() == 1)
						{
							int val = selector(state);
							state.erase(val);
							stateMatrix[i][j] = val;
							setOfFilledValuesInBox.insert(val);
							new_units = true;
						}
					}
				}
			}
		}
	}

    return new_units;
}

void SudokuSolver_SequentialForwardChecking::propagate(StateMatrix& stateMatrix)
{
	while (true)
	{
        if (!propagate_step(stateMatrix)) { return; }
	}
}

bool SudokuSolver_SequentialForwardChecking::done(StateMatrix& stateMatrix)
{
	for (int i = 0; i < _board.get_board_size(); ++i)
	{
		for (int j = 0; j < _board.get_board_size(); ++j)
		{
			if (std::holds_alternative<std::set<int>>(stateMatrix[i][j]))   // if the element stateMatrix[i][j] is of type std::set<int>
			{
				return false;
			}
		}
	}

	return true;
}

SudokuBoard SudokuSolver_SequentialForwardChecking::convertToSudokuGrid(StateMatrix& stateMatrix)
{
	SudokuBoard tmpBoard = SudokuBoard(_board);

	for (int i = 0; i < _board.get_board_size(); ++i)
	{
		for (int j = 0; j < _board.get_board_size(); ++j)
		{
			if (std::holds_alternative<int>(stateMatrix[i][j]))
			{
				tmpBoard.set_board_data(i, j, std::get<int>(stateMatrix[i][j]));
			}
		}
	}

	return tmpBoard;
}

void SudokuSolver_SequentialForwardChecking::solve_kernel(StateMatrix& stateMatrix)
{
	if (_solved) return;

	propagate(stateMatrix);

    if (done(stateMatrix))
	{
		_solved = true;
		_solution = convertToSudokuGrid(stateMatrix);
		return;
	}
	else
	{ 
		for (int i = 0; i < _board.get_board_size(); ++i)
		{
			for (int j = 0; j < _board.get_board_size(); ++j)
			{
				if (std::holds_alternative<std::set<int>>(stateMatrix[i][j]))   // if the element stateMatrix[i][j] is of type std::set<int>
				{
					for (const auto& value : std::get<std::set<int>>(stateMatrix[i][j]))
					{
						StateMatrix newStateMatrix = stateMatrix;
						newStateMatrix[i][j] = value;
						solve_kernel(newStateMatrix);
					}
				}
			}
		}    
	}
}