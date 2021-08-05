#include "SudokuBoard.hpp"
#include "SudokuTest.hpp"
#include "SudokuSolver.hpp"
#include "SudokuSolver_SequentialBacktracking.hpp"
#include "SudokuSolver_ParallelBacktracking.hpp"
#include "SudokuSolver_SequentialBruteForce.hpp"
#include "SudokuSolver_ParallelBruteForce.hpp"
#include "termcolor.hpp"

#include <iostream>
#include <chrono>
#include <memory>
#include <omp.h>


#define PRINT_TIME 1


enum class MODES
{
	SEQUENTIAL_BACKTRACKING,   // Sequential mode using backtracking algorithm
	PARALLEL_BACKTRACKING,     // OpenMP mode using backtracking algorithm
	SEQUENTIAL_BRUTEFORCE,     // Sequential mode using brute force algorithm
	PARALLEL_BRUTEFORCE        // OpenMP mode using brute force algorithm
};


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
	<< "developed by Hua-Ming Huang"
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

	MODES mode = static_cast<MODES>(std::stoi(argv[2]));
	if (mode != MODES::SEQUENTIAL_BACKTRACKING &&
		mode != MODES::PARALLEL_BACKTRACKING &&
		mode != MODES::SEQUENTIAL_BRUTEFORCE &&
		mode != MODES::PARALLEL_BRUTEFORCE)
	{
		std::cerr << termcolor::red << "Available options for <MODE>: " << "\n";
		std::cerr << "Please try again." << termcolor::reset << "\n";
		exit(-1);
	}

    auto board = SudokuBoard(std::string(argv[1]));
	SudokuTest::testBoard(board);

	int WRITE_TO_SOLUTION_TXT = (argc >= 4) ? std::stoi(argv[3]) : 0;

	std::cout << "\n" << termcolor::magenta << "************************************* INPUT GRID *************************************" << termcolor::reset << "\n\n";
    std::cout << board;
	std::cout << "\n" << termcolor::magenta << "**************************************************************************************" << termcolor::reset << "\n";


#if PRINT_TIME
    std::chrono::high_resolution_clock::time_point start, stop;
    start = std::chrono::high_resolution_clock::now();
#endif


	std::unique_ptr<SudokuSolver> solver;
	if (mode == MODES::SEQUENTIAL_BACKTRACKING) 
	{
		solver = std::make_unique<SudokuSolver_SequentialBacktracking>();
		SudokuSolver_SequentialBacktracking* child_solver = dynamic_cast<SudokuSolver_SequentialBacktracking*>(solver.get());
		child_solver->solve(board);
	} 
	else if (mode == MODES::PARALLEL_BACKTRACKING) 
	{
		int NUM_THREADS = (argc >= 5) ? std::stoi(argv[4]) : 2;
		omp_set_num_threads(NUM_THREADS);

		#pragma omp parallel
		{
			#pragma omp single nowait
			{
				solver = std::make_unique<SudokuSolver_ParallelBacktracking>();
				SudokuSolver_ParallelBacktracking* child_solver = dynamic_cast<SudokuSolver_ParallelBacktracking*>(solver.get());
				child_solver->solve(board);
			}
		}
	}
	else if (mode == MODES::SEQUENTIAL_BRUTEFORCE)
	{
		solver = std::make_unique<SudokuSolver_SequentialBruteForce>();
		SudokuSolver_SequentialBruteForce* child_solver = dynamic_cast<SudokuSolver_SequentialBruteForce*>(solver.get());
		child_solver->solve(board);
	}	
	else if (mode == MODES::PARALLEL_BRUTEFORCE)
	{
		int NUM_THREADS = (argc >= 5) ? std::stoi(argv[4]) : 2;
		omp_set_num_threads(NUM_THREADS);
		
		#pragma omp parallel
		{
			#pragma omp single nowait
			{
				solver = std::make_unique<SudokuSolver_ParallelBruteForce>();
				SudokuSolver_ParallelBruteForce* child_solver = dynamic_cast<SudokuSolver_ParallelBruteForce*>(solver.get());
				child_solver->solve(board);
			}
		}
	}


#if PRINT_TIME
	stop = std::chrono::high_resolution_clock::now();
	int time_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
#endif


	std::cout << "\n" << termcolor::green << "SOLVED!" << termcolor::reset << "\n";
	std::cout << termcolor::magenta << "************************************* OUTPUT GRID ************************************" << termcolor::reset << "\n\n";
	print_board(solver->get_solution());
	if (WRITE_TO_SOLUTION_TXT) {
		write_output(solver->get_solution());
	}
	std::cout << "\n" << termcolor::magenta << "**************************************************************************************" << termcolor::reset << "\n";


#if PRINT_TIME
    std::cout << std::dec << "Operations executed in " << (double)time_in_microseconds / 1000000 << " seconds." << "\n";
#endif

    return 0;
}