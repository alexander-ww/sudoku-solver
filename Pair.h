#ifndef __Sudoku_Solver__Pair__
#define __Sudoku_Solver__Pair__

#include <iostream>
#include <vector>

class Pair {

    public:

        // constructor
        Pair(int index, int first, int second);
    
        // comparators
        bool isEqual(Pair pair);
    
        // getters
        int getIndex(  );
        int getFirst(  );
        int getSecond(  );
    
    private:

        // attributes
        int index;
        int first;
        int second;
    
        // setters
        void setIndex(int index);
        void setFirst(int first);
        void setSecond(int second);
};

#endif
