# Sudoku Solver
This repository implements a command-line solver for any Sudoku puzzle.

## Background
Sudoku is a number-based puzzle that was original developed in Japan.
In Sudoku, the board is a 9-by-9 grid of cells into which values in
the set {1, 2, 3, 4, 5, 6, 7, 8, 9} can be entered. The constraints
of the puzzle are that there can be no duplicate values in any row
or column of the Sudoku board. A valid solution to a Sudoku puzzle
is a solution that satisfies these constraints.

#### Unsolved Sudoku Board

```
0 0 0 9 0 0 0 0 2
0 2 0 0 1 0 0 9 0
0 9 0 0 2 0 0 0 4
9 0 0 0 0 0 0 4 7
0 0 0 2 0 1 0 5 0
0 0 1 0 9 0 0 0 0
0 6 0 5 8 0 0 0 1
0 0 7 0 3 2 9 0 0
1 0 0 0 6 0 0 8 0
```

#### Solved Sudoku Board

```
Solution to Sudoku table from unsolved.txt

[6 1 8] [9 4 5] [7 3 2]
[3 2 6] [1 5 8] [7 9 4]
[5 4 8] [2 9 7] [1 6 3]
 -----   -----   -----
[9 3 2] [8 5 6] [1 4 7]
[8 4 6] [2 7 1] [3 5 9]
[5 7 1] [3 9 4] [6 2 8]
 -----   -----   -----
[2 6 3] [5 8 9] [4 7 1]
[4 8 7] [1 3 2] [9 6 5]
[1 5 9] [4 6 7] [2 8 3]
```

## Solving a Board
To solve a Sudoku board, the following steps need to be taken:

#### Steps
1. Open a terminal window on your computer.
2. Navigate to the directory with the Sudoku solver code.
3. Enter the following command: `make`
4. Modify the _unsolved.txt_ file to reflect the board to solve.
5. Run the Sudoku solver by entering the following command: `./soduku_solve unsolved.txt solved.txt`
6. View the solution to your sudoku puzzle by opening the _solved.txt_ file
