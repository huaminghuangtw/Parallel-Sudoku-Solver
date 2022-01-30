Parallelization of a Sudoku Solver
==================================

<p align="left">
<a href="https://github.com/huaminghuangtw/Parallel-Sudoku-Solver"><img src="https://badges.frapsoft.com/os/v3/open-source.svg?v=103" alt="Open Source Love"></a><br/>
<a href="https://github.com/huaminghuangtw/Parallel-Sudoku-Solver/releases"><img src="https://img.shields.io/github/v/release/huaminghuangtw/Parallel-Sudoku-Solver.svg?display_name=tag&style=plastic&color=lightgrey"></a>
<a href="https://github.com/huaminghuangtw/Parallel-Sudoku-Solver/tags"><img src="https://img.shields.io/github/v/tag/huaminghuangtw/Parallel-Sudoku-Solver.svg?style=plastic&color=lightgrey"></a><br/> 
<a href="https://github.com/huaminghuangtw/Parallel-Sudoku-Solver/stargazers"><img src="https://img.shields.io/github/stars/huaminghuangtw/Parallel-Sudoku-Solver.svg?style=social"></a>
<a href="https://github.com/huaminghuangtw/Parallel-Sudoku-Solver/fork"><img src="https://img.shields.io/github/forks/huaminghuangtw/Parallel-Sudoku-Solver.svg?style=social"></a>
<a href="https://github.com/huaminghuangtw/Parallel-Sudoku-Solver/issues"><img src="https://img.shields.io/github/issues/huaminghuangtw/Parallel-Sudoku-Solver.svg?style=social&logo=github"></a>
<a href="https://github.com/huaminghuangtw/Parallel-Sudoku-Solver/pulls"><img src="https://img.shields.io/github/issues-pr/huaminghuangtw/Parallel-Sudoku-Solver.svg?style=social&logo=github"></a>
</p>

> A parallelized Sudoku solver implemented with various solving algorithms in C++.

### Introduction
Sudoku is one of the most popular puzzle games of all time.
The objective of Sudoku is to fill a _n_-by-_n_ grid with digits from 1 to _n_ such that each column, row, and box (or called "subgrid", "region", "block") contain every number in the set {1, ... , _n_} exactly once.

---

### Motivation
This project aims to implement a Sudoku solver that could solve **large** (e.g., 16-by-16, 25-by-25) Sudoku puzzles as efficiently as possible by means of various parallelization techniques and solving algorithms.
The details of implementation and performance results are explained in depth in the [project report](./Project_Report.pdf).

<p align="center">
    <img src="https://user-images.githubusercontent.com/43208378/148445526-7676376d-6784-439f-8940-b34b0be8955c.png" width=330/>
    <img src="https://user-images.githubusercontent.com/43208378/148445610-c2106f5f-3ce0-4126-b484-74897ab1b38a.png" width=330/>
</p>

---

### How to use the code?
* #### Compile
    1. Navigate to the project root directory where the `Makefile` is located.
    2. Build the program by running the command:
        ```bash
        $ make
        ```
    3. An executable named `sudoku_main` will appear in the project root directory. 

* #### Run
    To run the solver, supply the executable with command-line arguments for test cases, modes, number of threads and flag for writing solution to a text file.
    ```bash
    $ ./sudoku_main <PATH_TO_INPUT_FILE> <MODE> <NUM_THREADS> [<WRITE_TO_SOLUTION_TXT>]
    ```
    ✏️ Note:
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

- #### Sequential mode for brute-force algorithm
    <img width="550" src="https://user-images.githubusercontent.com/43208378/130022178-134a3fd0-ce45-4f8c-b47a-276b759686e2.png">

- #### Parallel mode for brute-force algorithm
    <img width="550" src="https://user-images.githubusercontent.com/43208378/130022182-b1feaf52-36dc-4ae7-81fe-2466ea752575.png">

---

### Test cases
A collection of test grids of various sizes and difficulty levels are present in the [`Test_Cases`](./Test_Cases) directory.

---

### Support the project
Whether you use this project, have learned something from it, or just like it, please consider supporting it by buying me a coffee or making one-time donations via PayPal, so I can dedicate more time on open-source projects like this. 💪🙃

<a href="https://www.buymeacoffee.com/huaming.huang" target="_blank">
    <img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="30" width="127" />
</a>
<a href="https://www.paypal.me/huaminghuang" target="_blank">
    <img src="https://ionicabizau.github.io/badges/paypal.svg" alt="paypal.me/huaminghuang" height="30" width="127" />
</a>

Thanks!:heart: and Cheers!:beers:

---

### Contact
If you have any question or suggestion, feel free to contact me at huaming.huang.tw@gmail.com. Contributions are also welcomed. Please open a [pull-request](https://github.com/huaminghuangtw/Parallel-Sudoku-Solver/compare) or an [issue](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/issues/new) in this repository.

---

### License

This project is licensed under the terms of [![MIT](https://img.shields.io/github/license/huaminghuangtw/Parallel-Sudoku-Solver.svg?style=flat-square&color=black)](./LICENSE).
