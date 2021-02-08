# Algorithm

## Solving Sudoku (Human Approach)
When solving a Sudoku puzzle as a human, we go to each and every cell
in the Sudoku table and begin the process of eliminating numbers that
cannot be entered into the cell. This process of elimination for each
single cell in the Sudoku table involves the following checks:

#### Column Check
When we observe other numbers that have already been entered in the
same column as our cell, we eliminate those numbers as possibilities
for what we can enter for our cell. The Sudoku rules state that we
cannot have duplicate numbers entered into any column of the Sudoku
table.

#### Row Check
When we observe other numbers that have already been entered in the
same row as our cell, we eliminate those numbers as possibilities
for what we can enter for our cell. The Sudoku rules state that we
cannot have duplicate numbers entered into any row of the Sudoku
table.

#### 9-Box Check
When we observe other numbers that have already been entered into the
same 9-box as our cell, we eliminate those numbers as possibilities
for what we can enter for our cell. The Sudoku rules state that we
cannot have duplicate numbers entered into any 9-box of the Sudoku
table.

#### Edge Case (Decision Making)
When we can reduce our possibilities no further, it usually means that
we need to make a selection between two cells that have the same possibilities
and could assume either possibility as their value. This case is easily
checked against because no other modifications can be made to the Sudoku table.

## Example Walk Through
Let's walk through a difficult Sudoku board with our tracking of possibility vectors.
Below is the example board that we will incrementally solve so as to better understand
our algorithm describing the human approach to Sudoku.

### Step 1: The Original Board
What you can see below is the original state of the board where values in the
set of {1, 2, 3, 4, 5, 6, 7, 8, 9} are the already selected values in the Sudoku
board and values of 0 are values in the Sudoku board that need to be filled in.
Below this board, you can see our tracking of possibilities for the values in
each cell of each 9-box of the Sudoku board. The numbers of the Sudoku 9-boxes
are shown to the right of the original Sudoku board for reference.

#### Sudoku Board and 9-Box Numbers

```
[0 0 0] [9 0 0] [0 0 2]
[0 2 0] [0 1 0] [0 9 0]        0    1    2
[0 9 0] [0 2 0] [0 0 4]
 -----   -----   -----
[9 0 0] [0 0 0] [0 4 7]
[0 0 0] [2 0 1] [0 5 0]        3    4    5
[0 0 1] [0 9 0] [0 0 0]
 -----   -----   -----
[0 6 0] [5 8 0] [0 0 1]
[0 0 7] [0 3 2] [9 0 0]        6    7    8
[1 0 0] [0 6 0] [0 8 0]
```

#### Sudoku 9-Box Possibilities (9-Box 0) (Not Yet Reduced) (Step 1)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 1) (Not Yet Reduced) (Step 1)

```
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 2) (Not Yet Reduced) (Step 1)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
```

#### Sudoku 9-Box Possibilities (9-Box 3) (Not Yet Reduced) (Step 1)

```
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
```

#### Sudoku 9-Box Possibilities (9-Box 4) (Not Yet Reduced) (Step 1)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 5) (Not Yet Reduced) (Step 1)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 6) (Not Yet Reduced) (Step 1)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 7) (Not Yet Reduced) (Step 1)

```
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
```

#### Sudoku 9-Box Possibilities (9-Box 8) (Not Yet Reduced) (Step 1)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```

### Step 2: Reduce Possibilities with Column Check
Now that we have all of our possibility vectors established for our board, we can begin
to reduce the possibilities contained in those vectors by first checking for values that
cannot be selected for each cell based on the values that are already present in the
columns with which those cells are assocated in the Sudoku board. Below we show how this
column-based reduction of possibilities is performed.

#### Sudoku Board and 9-Box Numbers

```
[0 0 0] [9 0 0] [0 0 2]
[0 2 0] [0 1 0] [0 9 0]        0    1    2
[0 9 0] [0 2 0] [0 0 4]
 -----   -----   -----
[9 0 0] [0 0 0] [0 4 7]
[0 0 0] [2 0 1] [0 5 0]        3    4    5
[0 0 1] [0 9 0] [0 0 0]
 -----   -----   -----
[0 6 0] [5 8 0] [0 0 1]
[0 0 7] [0 3 2] [9 0 0]        6    7    8
[1 0 0] [0 6 0] [0 8 0]
```

#### Sudoku 9-Box Possibilities (9-Box 0) (Step 2)

```
[{<b>0<b>, 2, 3, 4, 5, 6, 7, 8, **0**}, {1, **0**, 3, 4, 5, **0**, 7, 8, **0**}, {**0**, 2, 3, 4, 5, 6, **0**, 8, 9}]
[{**0**, 2, 3, 4, 5, 6, 7, 8, **0**}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {**0**, 2, 3, 4, 5, 6, **0**, 8, 9}]
[{**0**, 2, 3, 4, 5, 6, 7, 8, **0**}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {**0**, 2, 3, 4, 5, 6, **0**, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 1) (Step 2)

```
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {**0**, **0**, **0**, 4, 5, **0**, 7, **0**, **0**}, {**0**, **0**, 3, 4, 5, 6, 7, 8, 9}]
[{1, **0**, 3, 4, **0**, 6, 7, 8, **0**}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {**0**, **0**, 3, 4, 5, 6, 7, 8, 9}]
[{1, **0**, 3, 4, **0**, 6, 7, 8, **0**}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {**0**, **0**, 3, 4, 5, 6, 7, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 2) (Step 2)

```
[{1, 2, 3, 4, 5, 6, 7, 8, **0**}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{1, 2, 3, 4, 5, 6, 7, 8, **0**}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, **0**}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
```

#### Sudoku 9-Box Possibilities (9-Box 3) (Step 2)

```
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
```

#### Sudoku 9-Box Possibilities (9-Box 4) (Step 2)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 5) (Step 2)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 6) (Step 2)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```

#### Sudoku 9-Box Possibilities (9-Box 7) (Step 2)

```
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
```

#### Sudoku 9-Box Possibilities (9-Box 8) (Step 2)

```
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}]
[{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
[{1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9}]
```
