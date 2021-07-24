#include "utility.hpp"


bool solveSudoku(int board[N][N])
{
    if (checkIfAllFilled(board))
    {
        return true;
    }
    else
    {
        std::pair<int, int> empty_cell = find_empty(board);

        for (int i = 1; i <= N; i++)
        {
            if (isValid(board, i, empty_cell))
            {
                int row = empty_cell.first;
                int col = empty_cell.second;

                board[row][col] = i;

                if (solveSudoku(board)) {
                    return true;
                }

                board[row][col] = 0;
            }
        }

        // None of the values solved the sudoku.
        return false;
    }
}

int main(void)
{
    // 0 means empty cells
    int board[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                        { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                        { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                        { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                        { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                        { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                        { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    // int board[N][N] =
    // { {0,1,2,0,0,4,0,0,0,0,5,0,0,0,0,0},
    //   {0,0,0,0,0,2,0,0,0,0,0,0,0,14,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},
    //   {11,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0},
    //   {0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,16,0,0,0,0,0,0,2,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0},
    //   {0,0,14,0,0,0,0,0,0,4,0,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,0,0,1,16,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,0,0,0,0,0,0,0,0,14,0,0,13,0,0},
    //   {0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //   {16,0,0,0,0,0,11,0,0,3,0,0,0,0,0,0} };
 
    print_board(board);

    if (solveSudoku(board)) {
        std::cout << "--------------------" << std::endl;
        print_board(board);
    } else {
        std::cout << "No solution exists." << std::endl;
    }

    return 0;
}