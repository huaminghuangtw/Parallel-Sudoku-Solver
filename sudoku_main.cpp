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
#include <memory>
#include <omp.h>
#include <type_traits>


#define PRINT_TIME 1


enum class MODES
{
	SEQUENTIAL_BACKTRACKING,     // Sequential mode using backtracking algorithm
	SEQUENTIAL_BRUTEFORCE,       // Sequential mode using brute force algorithm
	PARALLEL_BRUTEFORCE,         // OpenMP mode using brute force algorithm
	SEQUENTIAL_DANCINGLINKS,     // Sequential mode using dancing links algorithm
	PARALLEL_DANCINGLINKS        // OpenMP mode using dancing links algorithm
};


template <typename T>
void DownCastandSolve(std::unique_ptr<SudokuSolver>& solver, SudokuBoard& board)
{
	if constexpr (std::is_same<T, SudokuSolver_SequentialDLX>::value ||
	              std::is_same<T, SudokuSolver_ParallelDLX>::value)
	{
		solver = std::make_unique<T>(board);
	}
	else if constexpr (std::is_same<T, SudokuSolver_SequentialBacktracking>::value ||
	                   std::is_same<T, SudokuSolver_SequentialBruteForce>::value ||
					   std::is_same<T, SudokuSolver_ParallelBruteForce>::value)
	{
		solver = std::make_unique<T>();
	}

    T* child_solver = dynamic_cast<T*>(solver.get());

	if constexpr (std::is_same<T, SudokuSolver_SequentialDLX>::value ||
	              std::is_same<T, SudokuSolver_ParallelDLX>::value)
	{
		child_solver->solve();
	}
	else if constexpr (std::is_same<T, SudokuSolver_SequentialBacktracking>::value ||
	                   std::is_same<T, SudokuSolver_SequentialBruteForce>::value ||
					   std::is_same<T, SudokuSolver_ParallelBruteForce>::value)
	{
		child_solver->solve(board);
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

	MODES mode = static_cast<MODES>(std::stoi(argv[2]));
	if (mode != MODES::SEQUENTIAL_BACKTRACKING &&
		mode != MODES::SEQUENTIAL_BRUTEFORCE &&
		mode != MODES::PARALLEL_BRUTEFORCE &&
		mode != MODES::SEQUENTIAL_DANCINGLINKS &&
		mode != MODES::PARALLEL_DANCINGLINKS)
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
		DownCastandSolve<SudokuSolver_SequentialBacktracking>(solver, board);
	} 
	else if (mode == MODES::SEQUENTIAL_BRUTEFORCE)
	{
		DownCastandSolve<SudokuSolver_SequentialBruteForce>(solver, board);
	}	
	else if (mode == MODES::PARALLEL_BRUTEFORCE)
	{
		int NUM_THREADS = (argc >= 5) ? std::stoi(argv[4]) : 2;
		omp_set_num_threads(NUM_THREADS);
		
		#pragma omp parallel
		{
			#pragma omp single nowait
			{
				DownCastandSolve<SudokuSolver_ParallelBruteForce>(solver, board);
			}
		}
	}
	else if (mode == MODES::SEQUENTIAL_DANCINGLINKS)
	{
		// Implementation of dancing links algorithm written in C++ is based on the following Java tutorial:
		// https://medium.com/javarevisited/building-a-sudoku-solver-in-java-with-dancing-links-180274b0b6c1
		DownCastandSolve<SudokuSolver_SequentialDLX>(solver, board);
	}
	else if (mode == MODES::PARALLEL_DANCINGLINKS)
	{
		int NUM_THREADS = (argc >= 5) ? std::stoi(argv[4]) : 2;
		omp_set_num_threads(NUM_THREADS);

		#pragma omp parallel
		{
			#pragma omp single
			{
				DownCastandSolve<SudokuSolver_ParallelDLX>(solver, board);
			}
		}
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