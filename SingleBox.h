#ifndef __Sudoku_Solver__SingleBox__
#define __Sudoku_Solver__SingleBox__

#include <vector>
#include <iostream>

using namespace std;

/**
 * A single box in a Sudoku puzzle.
 *
 * <p>
 * The SingleBox class provides a means
 * to represent each of the individual
 * nine boxes that are contained within
 * a larger box of nine boxes.
 * </p>
 *
 * <p>
 * Each of these single boxes in the
 * Sudoku puzzle contain a numerical
 * value, a non-zero status indicator,
 * and a vector containing the values
 * that are possible to assume within
 * the context of the entire Sudoku
 * table when it is being solved.
 * </p>
 */
class SingleBox {

    public:

        // constructor
        SingleBox(int nineBoxNum, int boxValue);

        // setters
        void erasePossibility(int index);

        // comparators
        bool isEqual(SingleBox singleBox);

        // updaters
        void update(int number);

        // printers
        void debugPrinter();

        // getters
        int getBox();
        int getValue();
        bool getStatus();
        vector<int> getPossibilities();

    private:

        // attributes
        int box;
        int value;
        bool status;
        vector<int> possibilities;

        // setters
        void setBox(int box);
        void setValue(int value);
        void setStatus(bool complete);
};

#endif
