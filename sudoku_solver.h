#ifndef __sudoku_solver__sudoku_solver__
#define __sudoku_solver__sudoku_solver__

#include <vector>
#include <iostream>
#include "sudoku_table.h"

using namespace std;

/**
 * A Sudoku solver.
 *
 * <p>
 * The SudokuSolver class provides a
 * means for solving Sudoku puzzles
 * with a backtracking algorithm.
 * </p>
 */
class SudokuSolver {

    public:

        // constructors
        SudokuSolver();

        // solvers
        bool solve(SudokuTable &table);

    private:

        // helper methods
        bool usedInRow(SudokuTable &table, int row, int value);
        bool usedInColumn(SudokuTable &table, int column, int value);
        bool usedInBox(SudokuTable &table, int boxStartRow, int boxStartColumn, int value);
        bool noConflicts(SudokuTable &table, int row, int column, int value);
        bool findUnassignedLocation(SudokuTable &table, int &row, int &column);
};

#endif
