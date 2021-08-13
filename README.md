# Parallelization of a Sudoku Solver

## How to use the code

brute-force search is going to scale very badly. As an order-of-magnitude estimate, observe that the code calls IsValid() around SIZE times for each cell - that's O(n³), where n is the SIZE.

The Forward Checking algorithm consists in verifying, after each assignment of a value
to a variable, all the constraints in which the variable appears. It helps reducing the
domain of the free variables that appear in these constraints.
For example, in Sudoku, each time a value is assigned to a variable, the value is
removed from the domain of the free variables that are either in the same line, in the
same column or in the same square as the assigned variable.


preventing possible future conflicts is more reasonable than recovering from them.

give each thread a puzzle

$ ./sudoku <thread_count> <grid_file_path>

The parallel approach to backtracking can be broken down into two main steps:

Breadth first search from the beginning board to find all possible boards with the first X empty spaces filled. This will return Y possible starting boards for the next step of the algorithm.

Attempt to solve each of these Y boards separately in different threads on the GPU. If a solution is found, terminate the program and return the solution.


Serially generate a list of incomplete solutions through bootstrapping: fill a few empty cells with all possible values, and generate a shared queue of possible board to be solved by each thread
Each thread solve the boards in parallel with the backtracking algorithm
Use dynamic scheduling to balance work load on all threads: each thread will pop a new board from the queue to solve when it finished solving the previous board

you must divide the problem early, i.e. thread #1 starts with the first combination for a node in the backtracking graph, and proceeds to search the rest of that subgraph. Thread #2 starts with the second possible combination at the first and so forth. In short, for n threads find the n possible combinations on the top level of the search space (do not "forward-track"), then assign these n starting points to n threads.

If you have any question or suggestion, feel free to contact me at huaming.huang.tw@gmail.com or open an issue in this repository.