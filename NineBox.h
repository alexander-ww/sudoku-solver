#ifndef __Sudoku_Solver__NineBox__
#define __Sudoku_Solver__NineBox__

#include <vector>
#include <iostream>
#include "SingleBox.h"

using namespace std;


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
