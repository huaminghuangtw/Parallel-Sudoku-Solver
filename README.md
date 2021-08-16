Parallelization of a Sudoku Solver
==================================

> A parallelized Sudoku solver implemented with various solving algorithms in C++.

## Introduction
Sudoku is one of the most popular puzzle games of all time.
The objective of Sudoku is to fill a n by n grid with digits from 1 to n such that each column, row, and box (or called "subgrid", "region", "block") that compose the grid contains every number in the set {1, ... , n} exactly once.

---

## Motivation
This project aims to implement a Sudoku solver that could solve **large** Sudoku puzzles as efficiently as possible by means of various parallelization techniques and algorithms. The details of implementation and performance results are explained in detail in the [final report](./Final_Report.pdf).

---

## How to use the code
### Compile
1. Navigate to the project root directory where the `Makefile` is located.
2. Build the program by running the command:
	```bash
	$ make
	```
3. An executable named `sudoku_main` will appear in the project root directory. 

### Run
To run the solver, supply the executable with command-line arguments for test cases, modes, number of threads and flag for writing solution to a text file.
```bash
$ ./sudoku_main <PATH_TO_INPUT_FILE> <MODE> <NUM_THREADS> [<WRITE_TO_SOLUTION_TXT>]
```
Note:
- `<PATH_TO_INPUT_FILE>` (string): the path to the test case file (e.g., `Test_Cases/9x9_easy.txt`)
- `<MODE>` (int): the mode to run the Sudoku solver
	+ 0: sequential mode with backtracking algorithm
	+ 1: sequential mode with brute-force algorithm
	+ 2: parallel mode with brute-force algorithm
	+ 3: sequential mode with DLX algorithm
	+ 4: parallel mode with DLX algorithm
- `<NUM_THREADS>` (int): if you set 2 or 4 for `<MODE>`, you need to also set `<NUM_THREADS>` (default = 2)
- `<WRITE_TO_SOLUTION_TXT>` (int):
	+ 0 (default): only print solution to the console 
	+ 1: also write solution to a text file called solution.txt under the project root directory

---

## Demonstration
There are many different mode options available for this software. Two of them are shown as follows for demonstration purpose:

#### Sequential mode for brute-force algorithm
<img width="550" src="https://user-images.githubusercontent.com/43208378/129577050-7502179e-f14d-4665-b918-4d5847a9b0cd.png">

#### Parallel mode for brute-force algorithm
<img width="550" src="https://user-images.githubusercontent.com/43208378/129577038-01899e14-7227-42d2-aeaa-fe7006400776.png">

---

## Test cases
A collection of test grids of various sizes and difficulty levels are present in the [`Test_Cases`](./Test_Cases) directory.

---

## Contact
If you have any question or suggestion, feel free to contact me at huaming.huang.tw@gmail.com or open an issue in this repository.
