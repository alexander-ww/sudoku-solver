#include "sudoku_solver.h"

using namespace std;

/**
 * Constructor.
 *
 * <p>
 * This method constructs an
 * instance of a Sudoku solver.
 * </p>
 */
SudokuSolver::SudokuSolver() {}

/**
 * Solves a Sudoku table.
 *
 * <p>
 * This method accepts a Sudoku table as
 * input and solves the Sudoku table using
 * a backtracking algorithm to find satisfying
 * values for the Sudoku puzzle constraints.
 * </p>
 *
 * @param table The provided Sudoku table.
 *
 * @return True if solved; False otherwise.
 */
bool SudokuSolver::solve(SudokuTable &table) {

    // declare row
    int row;

    // declare column
    int column;

    // every location has been set
    if (!findUnassignedLocation(table, row, column)) {
        return true;
    }

    // continue solving with backtracking
    for (int value = 1; value <= 9; value++) {
        if (noConflicts(table, row, column, value)) {
            table.setCell(row, column, value);
            if (solve(table)) {
                return true;
            }
            table.setCell(row, column, 0);
        }
    }

    return false;
}

/**
 * Determines if a value is used in a row.
 *
 * <p>
 * This method accepts a Sudoku table, an
 * index for a row in the Sudoku table, and
 * a value. If the value is present in the row
 * of the Sudoku table, a value of true is
 * returned; Otherwise, a value of false is
 * returned.
 * </p>
 *
 * @param table The provided Sudoku table.
 * @param row The provided row index.
 * @param value The provided value to locate.
 *
 * @return True if the value is present; False otherwise.
 */
bool SudokuSolver::usedInRow(SudokuTable &table, int row, int value) {
    for (int column = 0; column < table.size(); column++) {
        if (table.getCell(row, column) == value) {
            return true;
        }
    }
    return false;
}

/**
 * Determines if a value is used in a column.
 *
 * <p>
 * This method accepts a Sudoku table, an
 * index for a column in the Sudoku table, and
 * a value. If the value is present in the row of
 * the Sudoku table, a value of true is returned;
 * Otherwise, a value of false is returned.
 * </p>
 *
 * @param table The provided Sudoku table.
 * @param column The provided column index.
 * @param value The provided value to locate.
 *
 * @return True if the value is present; False otherwise.
 */
bool SudokuSolver::usedInColumn(SudokuTable &table, int column, int value) {
    for (int row = 0; row < table.size(); row++) {
        if (table.getCell(row, column) == value) {
            return true;
        }
    }
    return false;
}

/**
 * Determines if a value is used in a 9-box.
 *
 * <p>
 * This method accepts a Sudoku table, an index
 * for the starting row in the Sudoku table for the
 * 9-box, an index for the starting column in the
 * Sudoku table for the 9-box, and a value. Upon
 * the receipt of these inputs, the method determines
 * whether the value is present in the 9-box.
 * </p>
 *
 * @param table The provided Sudoku table.
 * @param boxStartRow The provided starting row for the 9-box.
 * @param boxStartColumn The provided starting column for the 9-box.
 * @param value The provided value to locate.
 *
 * @return True if the value is present; False otherwise.
 */
bool SudokuSolver::usedInBox(SudokuTable &table, int boxStartRow, int boxStartColumn, int value) {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            if (table.getCell(row + boxStartRow, column + boxStartColumn) == value) {
                return true;
            }
        }
    }
    return false;
}

/**
 * Determines whether ther are conflicts.
 *
 * <p>
 * This method accepts a Sudoku table, an index for a row,
 * an index for a column, and a value. Upon the receipt of
 * these inputs, the method determines whether there is
 * any conflict for the placement of the value at the specified
 * row and column location in the Sudoku table. If there are
 * no conflicts with the placement, a value of true is returned;
 * Otherwise, a value of false is returned.
 * </p>
 *
 * @param table The provided Sudoku table.
 * @param row The provided index for the row.
 * @param column The provided index for the column.
 * @param value The provided value.
 *
 * @return True if there are no conflicts; False otherwise.
 */
bool SudokuSolver::noConflicts(SudokuTable &table, int row, int column, int value) {
    return !usedInRow(table, row, value) && !usedInColumn(table, column, value) &&
        !usedInBox(table, row - row % 3, column - column % 3, value);
}

/**
 * Determines if a location is unassigned.
 *
 * <p>
 * This method accepts a Sudoku table, a row index,
 * and a column index as input and determines whether
 * the location that the row and column indices point to
 * is an unassigned location in the Sudoku table. If the
 * location is currently unassigned, a value of true is
 * returned; Otherwise, a value of false is returned.
 * </p>
 *
 * @param table The provided Sudoku table.
 * @param row The provided row index.
 * @param column The provided column index.
 *
 * @return True if the location is unassigned; False otherwise.
 */
bool SudokuSolver::findUnassignedLocation(SudokuTable &table, int &row, int &column) {
    for (row = 0; row < table.size(); row++) {
        for (column = 0; column < table.size(); column++) {
            if (table.getCell(row, column) == 0) {
                return true;
            }
        }
    }
    return false;
}
