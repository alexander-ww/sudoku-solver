#ifndef __sudoku_solver__sudoku_table__
#define __sudoku_solver__sudoku_table__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * A Sudoku table.
 *
 * <p>
 * The SudokuTable class provides a
 * means for representing a Sudoku
 * table with the values that it contains.
 * </p>
 */
class SudokuTable {

    public:

        // constructors
        SudokuTable(const char* input, const char* output);

        // getter methods
        int getCell(int row, int column);

        // setter methods
        void setCell(int row, int column, int value);

        // printing methods
        void record();
        void print();

        // size methods
        int size();

    private:

        // attributes
        const char* input;
        const char* output;
        vector< vector<int> > grid;

        // setup methods
        void populate(vector<int> values);
};

#endif
