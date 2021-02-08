#ifndef __Sudoku_Solver__NineBox__
#define __Sudoku_Solver__NineBox__

#include <vector>
#include <iostream>
#include "SingleBox.h"

using namespace std;

/**
 * A nine box in a Sudoku puzzle.
 *
 * <p>
 * The NineBox class provides a means
 * to represent each of the larger
 * boxes of nine single-boxes that
 * exist in the Sudoku board.
 * </p>
 *
 * <p>
 * Each of these nine-boxes in the
 * Sudoku board contain nine single
 * boxes, a non-zero status indicator,
 * and a vector of possibilities.
 * </p>
 */
class NineBox {

    public:

        // constructor
        NineBox(vector<SingleBox> values, int box);

        // comparators
        bool isEqual(NineBox ninebox);

        // updaters
        void update(int number, int singlebox);

        // printers
        void debugPrinter();
        void printSingleBoxes();

        // getters
        int getBox();
        bool getStatus();
        vector<int> getPossibilities();
        vector<SingleBox> getSingleBoxes();

    private:

        // attributes
        int box;
        bool status;
        vector<int> possibilities;
        vector<SingleBox> singleBoxes;
 
        // setters
        void setBox(int ninebox);
        void setStatus(bool complete);
};

#endif
