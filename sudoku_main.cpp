#include "SudokuBoard.hpp"
#include "SudokuTest.hpp"
#include "SudokuSolver.hpp"
#include "SudokuSolver_SequentialBacktracking.hpp"
#include "SudokuSolver_SequentialBruteForce.hpp"
#include "SudokuSolver_ParallelBruteForce.hpp"
#include "SudokuSolver_SequentialDLX.hpp"
#include "SudokuSolver_ParallelDLX.hpp"
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

		default:
			std::cerr << termcolor::red << "Available options for <MODE>: " << "\n";
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
	<< "developed by Hua-Ming Huang (version: "
    << VERSION
    << ")"
	<< "\n\n\n";
	
	// validate command-line arguments
	if (argc < 3 || argc > 5)
	{
		std::cerr << termcolor::red << "Usage: " << argv[0] << " <PATH_TO_INPUT_FILE> <MODE> [<WRITE_TO_SOLUTION_TXT>] [<NUM_THREADS>] " << "\n";
		std::cerr << "		1. <MODE>: 0 for sequential mode, 1 for OpenMP mode." << "\n";
		std::cerr << "		2. <WRITE_TO_SOLUTION_TXT>: 0 - only write solution to the console (default), 1 - write solution to a text file." << "\n";
		std::cerr << "		3. <NUM_THREADS>: if you set 1 for <MODE>, you need to also set value to <NUM_THREADS> (default: 2)" << "\n";
		std::cerr << "Please try again." << termcolor::reset << "\n";
		exit(-1);
    }

	auto board = SudokuBoard(std::string(argv[1]));
	SudokuTest::testBoard(board);

	MODES mode = static_cast<MODES>(std::stoi(argv[2]));

	int WRITE_TO_SOLUTION_TXT = (argc >= 4) ? std::stoi(argv[3]) : 0;

	int NUM_THREADS = (argc >= 5) ? std::stoi(argv[4]) : 2;


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
	std::cout << termcolor::magenta << "************************************* OUTPUT GRID ************************************" << termcolor::reset << "\n\n";
	print_board(solver->get_solution());
	if (WRITE_TO_SOLUTION_TXT) {
		write_output(solver->get_solution());
	}
	std::cout << "\n" << termcolor::magenta << "**************************************************************************************" << termcolor::reset << "\n";


#if PRINT_TIME
    std::cout << std::dec << "Operations executed in " << (double) time_in_microseconds / 1000000 << " seconds." << "\n";
#endif


    return 0;
}