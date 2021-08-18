#include "SudokuBoard.hpp"
#include "SudokuTest.hpp"
#include "SudokuSolver.hpp"
#include "SudokuSolver_SequentialBacktracking.hpp"
#include "SudokuSolver_SequentialBruteForce.hpp"
#include "SudokuSolver_ParallelBruteForce.hpp"
#include "SudokuSolver_SequentialDLX.hpp"
#include "SudokuSolver_ParallelDLX.hpp"
#include "SudokuSolver_SequentialForwardChecking.hpp"

#include "termcolor.hpp"

#include <iostream>
#include <chrono>
#include <omp.h>
#include <memory>


#define PRINT_TIME 1


std::unique_ptr<SudokuSolver> CreateSudokuSolver(MODES mode, SudokuBoard& board)
{
    switch (mode)
    {
        case MODES::SEQUENTIAL_BACKTRACKING:
            return std::make_unique<SudokuSolver_SequentialBacktracking>(board);

        case MODES::SEQUENTIAL_BRUTEFORCE:
            return std::make_unique<SudokuSolver_SequentialBruteForce>(board);

		case MODES::PARALLEL_BRUTEFORCE:
            return std::make_unique<SudokuSolver_ParallelBruteForce>(board);

		case MODES::SEQUENTIAL_DANCINGLINKS:
            return std::make_unique<SudokuSolver_SequentialDLX>(board);

		case MODES::PARALLEL_DANCINGLINKS:
            return std::make_unique<SudokuSolver_ParallelDLX>(board);

		case MODES::SEQUENTIAL_FORWARDCHECKING:
            return std::make_unique<SudokuSolver_SequentialForwardChecking>(board);

		default:
			std::cerr << termcolor::red << "Available options for <MODE>: " << "\n";
			std::cerr << "		- 0: sequential mode with backtracking algorithm" << "\n";
			std::cerr << "		- 1: sequential mode with brute force algorithm" << "\n";
			std::cerr << "		- 2: parallel mode with brute force algorithm" << "\n";
			std::cerr << "		- 3: sequential mode with DLX algorithm" << "\n";
			std::cerr << "		- 4: parallel mode with DLX algorithm" << "\n";
			std::cerr << "		- 5: sequential mode with forward checking algorithm" << "\n";
			std::cerr << "Please try again." << termcolor::reset << "\n";
			exit(-1);
    }
}


int main(int argc, char** argv)
{	
	std::cout
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
	<< "developed by Hua-Ming Huang (version: " << VERSION << ")"
	<< "\n\n\n";
	
	// validate command-line arguments
	if (argc < 3 || argc > 5)
	{
		std::cerr << termcolor::red << "Usage: " << argv[0] << " <PATH_TO_INPUT_FILE> <MODE> [<NUM_THREADS>] [<WRITE_TO_SOLUTION_TXT>]" << "\n";
		std::cerr << "		1. <MODE>: " << "\n";
		std::cerr << "			- 0: sequential mode with backtracking algorithm" << "\n";
		std::cerr << "			- 1: sequential mode with brute force algorithm" << "\n";
		std::cerr << "			- 2: parallel mode with brute force algorithm" << "\n";
		std::cerr << "			- 3: sequential mode with DLX algorithm" << "\n";
		std::cerr << "			- 4: parallel mode with DLX algorithm" << "\n";
		std::cerr << "			- 5: sequential mode with forward checking algorithm" << "\n";
		std::cerr << "		2. <NUM_THREADS>: " << "\n";
		std::cerr << "			If you set 2 or 4 for <MODE>, you need to also set <NUM_THREADS> (default = 2)" << "\n";
		std::cerr << "		3. <WRITE_TO_SOLUTION_TXT>: " << "\n";
		std::cerr << "			- 0 (default): only print solution to the console" << "\n";
		std::cerr << "			- 1: also write solution to a text file called solution.txt under the project root directory" << "\n";
		std::cerr << "Please try again." << termcolor::reset << "\n";
		exit(-1);
    }

	auto board = SudokuBoard(std::string(argv[1]));
	SudokuTest::testBoard(board);

	MODES mode = static_cast<MODES>(std::stoi(argv[2]));

	int NUM_THREADS = 2;
	int WRITE_TO_SOLUTION_TXT = 0;
	if (mode == MODES::PARALLEL_BRUTEFORCE || mode == MODES::PARALLEL_DANCINGLINKS)
	{
		NUM_THREADS = (argc >= 4) ? std::stoi(argv[3]) : 2;
		WRITE_TO_SOLUTION_TXT = (argc >= 5) ? std::stoi(argv[4]) : 0;
	}
	else
	{
		WRITE_TO_SOLUTION_TXT = (argc >= 4) ? std::stoi(argv[3]) : 0;
	}


	std::cout << "\n" << termcolor::magenta << "************************************* INPUT GRID *************************************" << termcolor::reset << "\n\n";
    std::cout << board;
	std::cout << "\n" << termcolor::magenta << "**************************************************************************************" << termcolor::reset << "\n";


#if PRINT_TIME
    std::chrono::high_resolution_clock::time_point start, stop;
    start = std::chrono::high_resolution_clock::now();
#endif


	auto solver = CreateSudokuSolver(mode, board);
	if (mode == MODES::PARALLEL_BRUTEFORCE || mode == MODES::PARALLEL_DANCINGLINKS)
	{
		omp_set_num_threads(NUM_THREADS);
		
		#pragma omp parallel
		{
			#pragma omp single
			{
				std::cout << "Using " << termcolor::bright_red << omp_get_num_threads() << termcolor::reset
		                  << " OMP threads" << "\n";
				solver->solve();
			}
		}
	}
	else
	{
		solver->solve();
	}


#if PRINT_TIME
	stop = std::chrono::high_resolution_clock::now();
	int time_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
#endif


	// Assume all input Sudoku boards are solvable
	std::cout << "\n" << termcolor::green << "SOLVED!" << termcolor::reset << "\n";
	SudokuTest::testBoard(solver->get_solution());
	std::cout << termcolor::magenta << "************************************* OUTPUT GRID ************************************" << termcolor::reset << "\n\n";
	print_board(solver->get_solution());
	if (WRITE_TO_SOLUTION_TXT) {
		write_output(solver->get_solution());
	}
	std::cout << "\n" << termcolor::magenta << "**************************************************************************************" << termcolor::reset << "\n";


#if PRINT_TIME
    std::cout << std::dec << "[Solved in " << (double) time_in_microseconds / 1e6 << " seconds.]" << "\n";
#endif


    return 0;
}