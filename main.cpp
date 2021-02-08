#include <iostream>
#include <string>
#include <fstream>
#include "SingleBox.h"
#include "NineBox.h"
#include "SudokuTable.h"

using namespace std;

int main(int argc, const char * argv[])
{
    if ( argc != 3 ) {
        std::cout << "Usage: " << argv[0] << " [input filename] [output filename]" << endl;
        return 1;
    }
    
    const char* inputFile = argv[1];
    const char* outputFile = argv[2];
    
    SudokuTable sud = SudokuTable( inputFile, outputFile );
    
    sud.printTable();
    sud.solveTable();
    sud.recordSolution();
    
    std::cout << "solution written to " << outputFile << std::endl;
    
    return 0;
}
