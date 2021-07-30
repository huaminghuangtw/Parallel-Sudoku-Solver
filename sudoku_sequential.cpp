#include "SudokuBoard.hpp"
#include "TestableSudoku.hpp"
#include "SudokuSolver_SequentialBacktracking.hpp"

#include <iostream>
#include <chrono>


// TODO: checkIfAllFilled & find_empty move to SudokuSolver base class?
// TODO: add recursive depth?
// TODO: solve 16 * 16 (smarter algorithm)


#define PRINT_TIME 1


int main(int argc, char** argv)
{
	// validate arguments
	if ((argc < 2) || (argc > 3)){
		std::cerr << "Usage: " << argv[0] << " <PATH_TO_INPUT_FILE> [<WRITE_TO_SOLUTION_TXT>]" << "\n";
		std::cerr << "Specify 1 to <WRITE_TO_SOLUTION_TXT> if you want to write solution to a text file." << "\n";
		std::cerr << "(By default it's set to 0, i.e., only write solution to the console.)" << "\n";
		exit(-1);
    }
	
	std::cout << "========================================================================================================"
	<< "\n"
	<< R"(
███████╗██╗   ██╗██████╗  ██████╗ ██╗  ██╗██╗   ██╗    ███████╗ ██████╗ ██╗    ██╗   ██╗███████╗██████╗ 
██╔════╝██║   ██║██╔══██╗██╔═══██╗██║ ██╔╝██║   ██║    ██╔════╝██╔═══██╗██║    ██║   ██║██╔════╝██╔══██╗
███████╗██║   ██║██║  ██║██║   ██║█████╔╝ ██║   ██║    ███████╗██║   ██║██║    ██║   ██║█████╗  ██████╔╝
╚════██║██║   ██║██║  ██║██║   ██║██╔═██╗ ██║   ██║    ╚════██║██║   ██║██║    ╚██╗ ██╔╝██╔══╝  ██╔══██╗
███████║╚██████╔╝██████╔╝╚██████╔╝██║  ██╗╚██████╔╝    ███████║╚██████╔╝███████╗╚████╔╝ ███████╗██║  ██║
╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝     ╚══════╝ ╚═════╝ ╚══════╝ ╚═══╝  ╚══════╝╚═╝  ╚═╝
	)"
	<< "\n"
	<< "developed by Hua-Ming Huang"
	<< "\n\n"
	<< "========================================================================================================"
	<< "\n\n\n";
	
    auto board = SudokuBoard(std::string(argv[1]));
	TestableSudoku::testBoard(board);

	int WRITE_TO_SOLUTION_TXT;
	if (argc == 2) {
        WRITE_TO_SOLUTION_TXT = 0;
    } else {
        WRITE_TO_SOLUTION_TXT = std::stoi(argv[2]);
    }

	std::cout << "\n" << "************************************* INPUT GRID *************************************" << "\n\n";
    std::cout << board;
	std::cout << "\n" << "**************************************************************************************" << "\n";

	std::cout << "\n" << "Sudoku solver starts, please wait..." << "\n";

#if PRINT_TIME
    std::chrono::high_resolution_clock::time_point start, stop;
    start = std::chrono::high_resolution_clock::now();
#endif

	SudokuSolver_SequentialBacktracking solver;
	solver = SudokuSolver_SequentialBacktracking(board);

#if PRINT_TIME
	stop = std::chrono::high_resolution_clock::now();
	int time_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
#endif

	switch (solver.get_solver_status())
	{
		case SOLVED:
			std::cout << "Solution: " << "\n";
			std::cout << "************************************* OUTPUT GRID ************************************" << "\n\n";
			print_board(solver.get_solution());
			if (WRITE_TO_SOLUTION_TXT) {
				write_output(solver.get_solution());
			}
			std::cout << "\n" << "**************************************************************************************" << "\n";
			break;
	
		case UNSOLVABLE:
			std::cout << "The given Sudoku board cannot be solved. :(" << "\n";
			break;
    }

#if PRINT_TIME
    std::cout << std::dec << "Operations executed in " << (double)time_in_microseconds / 1000000 << " seconds." << "\n";
#endif

    return 0;
}