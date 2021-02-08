#ifndef __Sudoku_Solver__SudokuTable__
#define __Sudoku_Solver__SudokuTable__

#include <string>
#include <vector>
#include <iostream>
#include "NineBox.h"

using namespace std;

/**
 * A Sudoku table.
 *
 * <p>
 * The SudokuTable class provides
 * a means for representing a Sudoku
 * table with all of its information.
 * </p>
 */
class SudokuTable {

    public:

        // constructor
        SudokuTable(const char* inputFile, const char* outputFile);

        // cloners
        void copy(SudokuTable old);

        // comparators
        bool isEqual(SudokuTable table);

        // updaters
        void solveTable();
        
        // printers
        void recordSolution();
        void printTable();
        void printRemaining();
        
        // getters
        bool getStatus();

    private:
    
        // attributes
        bool status;
        const char* inputFile;
        const char* outputFile;
        vector<NineBox> nineBoxBoard;
        
        // setup methods
        void populate(vector<int> rawTable);
};

#endif
