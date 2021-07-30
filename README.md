# Parallelization of a Sudoku Solver

## How to use the code

## To-do List:
* [ ] Build GUI using QT library (https://www.techwithtim.net/tutorials/python-programming/sudoku-solver-backtracking/)
* [ ] Write Unit Tests using common frameworks, e.g., Google Test (for successful messages in green, unsuccessful messages in red)
* [ ] Develop a Sudoku App for Android and Apple ios

give each thread a puzzle

print_board
find_empty
is_valid do not check the same position that we just added in. duplicate
sudoku_solver

At the i-th empty cell on the board:
	for all possible fill-ins:
		fill the number
		if this is the last empty cell:
			return the solution
		else:
			search the (i+1)-th empty cell
	return with no solution

recursive_backtrack():
    if board is valid:
        index = index of first empty spot in board
        for value = 1 to 9:
            set board[index] = value
            if recursive_backtrack():
                return true;  // solved!
            set board[index] = 0
    // if we tried all values, or the board is invalid, backtrack
    return false;

$ ./sudoku <thread_count> <grid_file_path>

The parallel approach to backtracking can be broken down into two main steps:

Breadth first search from the beginning board to find all possible boards with the first X empty spaces filled. This will return Y possible starting boards for the next step of the algorithm.

Attempt to solve each of these Y boards separately in different threads on the GPU. If a solution is found, terminate the program and return the solution.


Serially generate a list of incomplete solutions through bootstrapping: fill a few empty cells with all possible values, and generate a shared queue of possible board to be solved by each thread
Each thread solve the boards in parallel with the backtracking algorithm
Use dynamic scheduling to balance work load on all threads: each thread will pop a new board from the queue to solve when it finished solving the previous board

you must divide the problem early, i.e. thread #1 starts with the first combination for a node in the backtracking graph, and proceeds to search the rest of that subgraph. Thread #2 starts with the second possible combination at the first and so forth. In short, for n threads find the n possible combinations on the top level of the search space (do not "forward-track"), then assign these n starting points to n threads.