# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

### [1.0.2](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/compare/v1.0.1...v1.0.2) (2021-08-19)


### Features

* finalize UI and set appropriate error messages ([19f0b9e](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/19f0b9e250bda788ddc77b2397926e546923bb67))
* make git version information available in the source files ([5886e5c](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/5886e5c8c2fa446c741ac98c78df5b8b61e13b11))
* use function template to avoid duplicates of code in sudoku_main.cpp ([79287b7](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/79287b7583f726e6053faf84a5b8b34ff281314f))

### 1.0.1 (2021-08-08)


### Features

* add ASCII art text for welcome message ([cbbb13b](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/cbbb13bb6a8c82715ef960e64ddd898561a9ac01))
* add class SudokuBoardDeque and SudokuSolver_ParallelBruteForce using OpenMP ([be1542a](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/be1542a5a1e64d407e613f09e93c7faa83210c7a))
* add class SudokuSolver_ParallelBacktracking inherited from class SudokuSolver_SequentialBacktracking ([85d5419](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/85d5419caf42dfc0e90bbc1b661deab726c782a3))
* add class SudokuSolver_ParallelDancingLinks ([8ba3464](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/8ba3464d2ec53cae383c663b9e8a449f57eda0cf))
* add class SudokuSolver_SequentialBruteForce ([31f0cdf](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/31f0cdf05cb67f92cf6b0bb15644e037adcc3dc5))
* add class SudokuSolver_SequentialDancingLinks and Node with efficient Dancing Links algorithm ([3a76f7c](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/3a76f7cb0a017491f7483edad954e30e2e4a88e0))
* add function isUnique in class SudokuSolver ([b0ea2c0](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/b0ea2c0a74bc0f8bc3bc4affe00f27da658adc7c))
* add second version of bootstrapping for parallel brute force algorithm ([17138f4](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/17138f45e479e374814f16571eb8e42fe3bc9ce4))
* add TestableSudoku to test the validity of the initial board ([1f92ce5](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/1f92ce5ee14227d3c852858d1bb4c89df2bce03c))
* initialize Sudoku board from files in the Test_Cases folder and specify files in command lines ([af61655](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/af6165564c04a9aca98af28ac3406e4e0cd4b2c0))
* introduce progress bar to display the status of solving process ([d5facaa](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/d5facaa2e506055d16a9ef2e39d0ece1a103dacd))
* introduce termcolor library ([0ebabb4](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/0ebabb4a3d26ef41d413a81914de3a0b1d6a7dd0))
* overload operator << to print the Sudoku board ([e0ab382](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/e0ab38251e5a0d031307df7e2af0a158c8a91497))
* use the final clause in #pragma omp task directive to reduce the overhead of tasks creation, for better scalability ([e758ffa](https://github.com/hmhuang0501/Parallel-Sudoku-Solver/commit/e758ffad1fb3dbe610238f11e00eb2efd4533777))
