Parallelization of a Sudoku Solver
==================================

> A parallelized Sudoku solver implemented with various solving algorithms in C++.

### Introduction
Sudoku is one of the most popular puzzle games of all time.
The objective of Sudoku is to fill a _n_-by-_n_ grid with digits from 1 to _n_ such that each column, row, and box (or called "subgrid", "region", "block") that compose the grid contains every number in the set {1, ... , _n_} exactly once.

---

### Motivation
This project aims to implement a Sudoku solver that could solve **large** Sudoku puzzles as efficiently as possible by means of various parallelization techniques and algorithms. The details of implementation and performance results are explained in depth in the [project report](./Project_Report.pdf).

---

### How to use the code
#### Compile
1. Navigate to the project root directory where the `Makefile` is located.
2. Build the program by running the command:
	```bash
	$ make
	```
3. An executable named `sudoku_main` will appear in the project root directory. 

#### Run
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
	+ 1: also write solution to a text file called `solution.txt` under the project root directory

---

### Demonstration
There are many different mode options available for this software. Two of them are shown as follows for demonstration purpose:

#### Sequential mode for brute-force algorithm
<img width="550" src="https://user-images.githubusercontent.com/43208378/130022178-134a3fd0-ce45-4f8c-b47a-276b759686e2.png">

#### Parallel mode for brute-force algorithm
<img width="550" src="https://user-images.githubusercontent.com/43208378/130022182-b1feaf52-36dc-4ae7-81fe-2466ea752575.png">

---

### Test cases
A collection of test grids of various sizes and difficulty levels are present in the [`Test_Cases`](./Test_Cases) directory.

---

### Buy me a coffee
Whether you use this project, have learned something from it, or just like it, please consider supporting it by buying me a coffee, so I can dedicate more time on open-source projects like this.💪🙃

<a href="https://www.buymeacoffee.com/huaming.huang" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png" alt="Buy Me A Coffee" style="height: auto !important;width: auto !important;" ></a>

---

### Contact
If you have any question or suggestion, feel free to contact me at huaming.huang.tw@gmail.com. Contributions are also welcomed. Please open a [pull-request](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/compare) or an [issue](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/issues/new) in this repository.
