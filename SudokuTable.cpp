#include <fstream>
#include "SudokuTable.h"
#include "SingleBox.h"
#include "Pair.h"

const int MAXLINE = 18;

using namespace std;

/**
 * Constructor.
 *
 * <p>
 * This method accepts a string representing
 * the absolute path to an input file and a string
 * representing the absolute path to an output
 * file. Upon the receipt of these inputs, the
 * method constructs an instance of a Sudoku
 * table.
 * </p>
 *
 * @param inputFile The path to an input file.
 * @param outputFile The path to an output file.
 */
SudokuTable::SudokuTable(const char* inputFile, const char* outputFile) {
    vector<int> rawTable;
    int zeroesCount = 0;

    // read in Sudoku table from file
    ifstream inFile(inputFile);
    char oneline[MAXLINE];

    // read the entire input file
    while (inFile) {
        inFile.getline(oneline, MAXLINE);
        for (int i = 0; i < MAXLINE - 1; i += 2) {
            int entry = oneline[i] - '0';
            rawTable.push_back(entry);
            if (entry == 0) {
                zeroesCount++;
            }
        }
    }

    // close the input file
    inFile.close();

    // set completion status
    status = zeroesCount == 0;

    // set the files
    this->inputFile = inputFile;
    this->outputFile = outputFile;

    // populate the table
    populate(rawTable);
}

/**
 * Populates a Sudoku table.
 *
 * <p>
 * This method accepts a vector of
 * integers representing Sudoku table
 * values and populates the nine-boxes
 * and single boxes of the Sudoku table
 * with the integers in that vector.
 * </p>
 *
 * @param rawTable The vector of integers.
 */
void SudokuTable::populate(vector<int> rawTable) {
    vector<SingleBox> list1;
    vector<SingleBox> list2;
    vector<SingleBox> list3;

    int firstNineBox = 0;
    int passed = 0;

    for (int i = 0; i < 81; i++) {
        if (i % 9 == 0 || i % 9 == 1 || i % 9 == 2) {
            list1.push_back(SingleBox(firstNineBox, rawTable[i]));
        }
        else if (i % 9 == 3 || i % 9 == 4 || i % 9 == 5) {
            list2.push_back(SingleBox(firstNineBox + 1, rawTable[i]));
        }
        else if (i % 9 == 6 || i % 9 == 7 || i % 9 == 8) {
            list3.push_back(SingleBox(firstNineBox + 2, rawTable[i]));
            passed++;

            if (passed == 9) {
                nineBoxBoard.push_back(NineBox(list1, firstNineBox));
                nineBoxBoard.push_back(NineBox(list2, firstNineBox + 1));
                nineBoxBoard.push_back(NineBox(list3, firstNineBox + 2));

                firstNineBox += 3;
                passed = 0;
                
                list1.clear();
                list2.clear();
                list3.clear();
            }
        }
    }
}

/**
 * Gets the completion status.
 *
 * <p>
 * This method acquires the completion
 * status for the Sudoku table.
 * </p>
 *
 * @return The completion status.
 */
bool SudokuTable::getStatus() {
    return status;
}

/**
 * Prints the number of remaining boxes.
 *
 * <p>
 * This method prints the number of remaining
 * unsolved single-boxes in the Sudoku table
 * to the console for viewing.
 * </p>
 */
void SudokuTable::printRemaining() {
    int remaining = 0;
    
    for (int i = 0; i < nineBoxBoard.size(); i++) {
        for (int j = 0; j < 8; j++) {
            if (nineBoxBoard[i].getSingleBoxes()[j].getValue() == 0) {
                remaining++;
            }
        }
    }
    
    cout << remaining << " unsolved boxes remaining in Sudoku table." << endl;
}

/**
 * Checks equality.
 *
 * <p>
 * This method accepts a Sudoku table as
 * input and checks whether the provided
 * Sudoku table is equal to this instance of
 * the Sudoku table. If both instances are
 * equal a value of true is returned; Otherwise,
 * a value of false is returned.
 * </p>
 *
 * @param sudokuTable The provided Sudoku table.
 *
 * @return True if equal; False otherwise.
 */
bool SudokuTable::isEqual(SudokuTable sudokuTable) {
    bool sameNineBox = true;

    for (int i = 0; i < 9; i++) {
        sameNineBox = sameNineBox && nineBoxBoard[i].isEqual(sudokuTable.nineBoxBoard[i]);
    }

    if (sameNineBox &&
        status == sudokuTable.getStatus() &&
        inputFile == sudokuTable.inputFile &&
        outputFile == sudokuTable.outputFile) {
        return true;
    }

    else {
        return false;
    }
}

/**
 * Prints the Sudoku table.
 *
 * <p>
 * This method prints the Sudoku
 * table to the console for viewing.
 * </p>
 */
void SudokuTable::printTable() {
    int firstNineBox = 0;
    int firstSingleBox = 0;
    int temp = 0;
    
    cout << endl;
    cout << "Printing contents of Sudoku table:" << endl;
    cout << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp = firstNineBox;

            for (int k = 0; k < 3; k++) {
                cout << "[";
                cout << nineBoxBoard[temp].getSingleBoxes()[firstSingleBox].getValue();
                cout << " ";
                cout << nineBoxBoard[temp].getSingleBoxes()[firstSingleBox + 1].getValue();
                cout << " ";
                cout << nineBoxBoard[temp].getSingleBoxes()[firstSingleBox + 2].getValue();
                cout << "] ";
                temp++;
            }
            
            cout << endl;
            firstSingleBox += 3;
        }
        
        if (i != 2) {
            cout << " -----   -----   ----- " << endl;
        }
        
        firstSingleBox = 0;
        firstNineBox += 3;
    }
    
    cout << endl;
}

/**
 * Solves a Sudoku table.
 *
 * <p>
 * This method solves the Sudoku table.
 * </p>
 */
void SudokuTable::solveTable() {
    SudokuTable old = SudokuTable(inputFile, outputFile);
    vector<Pair> pairs;
    int set = 0;
    int zeroesCount = 0;
    int tempFirst = 0;
    int tempSecond = 0;
    int passed = 0;
    int temp = 0;

    while (getStatus() == false) {

        old.copy(*this);

        /**
         * Vertical and horizontal checks for all single-boxes.
         */

        // iterate over all NineBoxes
        for (int i = 0; i < 9; i++) {
            
            // iterate over all SingleBoxes in NineBox
            for (int j = 0; j < 9; j++) {
                
                // if we are in the zeroth Ninebox
                if (i == 0) {
                    
                    // if we are in the zeroth, first, or second SingleBox
                    if (j == 0 || j == 1 || j == 2) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[2].getValue(), j);
                    }
                    
                    if (j == 3 || j == 4 || j == 5) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[5].getValue(), j);
                    }
                    
                    if (j == 6 || j == 7 || j == 8) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[8].getValue(), j);
                    }
                    
                    if (j == 0 || j == 3 || j == 6) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[6].getValue(), j);
                    }
                    
                    if (j == 1 || j == 4 || j == 7) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[7].getValue(), j);
                    }
                    
                    if (j == 2 || j == 5 || j == 8) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[8].getValue(), j);
                    }
                    
                } // end if == 0
                
                // if we are the first NineBox
                if (i == 1) {
                    
                    if (j == 0 || j == 1 || j == 2) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[2].getValue(), j);
                    }
                    
                    if (j == 3 || j == 4 || j == 5) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[5].getValue(), j);
                    }
                    
                    if (j == 6 || j == 7 || j == 8) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[8].getValue(), j);
                    }
                    
                    if (j == 0 || j == 3 || j == 6) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[6].getValue(), j);
                    }
                    
                    if (j == 1 || j == 4 || j == 7) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[7].getValue(), j);
                    }
                    
                    if (j == 2 || j == 5 || j == 8) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[8].getValue(), j);
                    }
                    
                } // end if == 1
                
                // if we are the second NineBox
                if (i == 2) {
                    
                    if (j == 0 || j == 1 || j == 2) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[2].getValue(), j);
                    }
                    
                    if (j == 3 || j == 4 || j == 5) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[5].getValue(), j);
                    }
                    
                    if (j == 6 || j == 7 || j == 8) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[8].getValue(), j);
                    }
                    
                    if (j == 0 || j == 3 || j == 6) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[6].getValue(), j);
                    }
                    
                    if (j == 1 || j == 4 || j == 7) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[7].getValue(), j);
                    }
                    
                    if (j == 2 || j == 5 || j == 8) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[8].getValue(), j);
                    }
                    
                } // end if == 2
                
                // if we are the third NineBox
                if (i == 3) {
                    
                    if (j == 0 || j == 1 || j == 2) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[2].getValue(), j);
                    }
                    
                    if (j == 3 || j == 4 || j == 5) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[5].getValue(), j);
                    }
                    
                    if (j == 6 || j == 7 || j == 8) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[8].getValue(), j);
                    }
                    
                    if (j == 0 || j == 3 || j == 6) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[6].getValue(), j);
                    }
                    
                    if (j == 1 || j == 4 || j == 7) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[7].getValue(), j);
                    }
                    
                    if (j == 2 || j == 5 || j == 8) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[8].getValue(), j);
                    }
                    
                } // end if == 3
                
                // if we are the fourth NineBox
                if (i == 4) {
                    
                    if (j == 0 || j == 1 || j == 2) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[2].getValue(), j);
                    }
                    
                    if (j == 3 || j == 4 || j == 5) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[5].getValue(), j);
                    }
                    
                    if (j == 6 || j == 7 || j == 8) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[8].getValue(), j);
                    }
                    
                    if (j == 0 || j == 3 || j == 6) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[6].getValue(), j);
                    }
                    
                    if (j == 1 || j == 4 || j == 7) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[7].getValue(), j);
                    }
                    
                    if (j == 2 || j == 5 || j == 8) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[8].getValue(), j);
                    }
                    
                } // end if == 4
                
                // if we are the fifth NineBox
                if (i == 5) {
                    
                    if (j == 0 || j == 1 || j == 2) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[2].getValue(), j);
                    }
                    
                    if (j == 3 || j == 4 || j == 5) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[5].getValue(), j);
                    }
                    
                    if (j == 6 || j == 7 || j == 8) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[8].getValue(), j);
                    }
                    
                    if (j == 0 || j == 3 || j == 6) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[6].getValue(), j);
                    }
                    
                    if (j == 1 || j == 4 || j == 7) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[7].getValue(), j);
                    }
                    
                    if (j == 2 || j == 5 || j == 8) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[8].getValue(), j);
                    }
                    
                } // end if == 5
                
                // if we are the sixth NineBox
                if (i == 6) {
                    
                    if (j == 0 || j == 1 || j == 2) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[2].getValue(), j);
                    }
                    
                    if (j == 3 || j == 4 || j == 5) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[5].getValue(), j);
                    }
                    
                    if (j == 6 || j == 7 || j == 8) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[8].getValue(), j);
                    }
                    
                    if (j == 0 || j == 3 || j == 6) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[6].getValue(), j);
                    }
                    
                    if (j == 1 || j == 4 || j == 7) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[7].getValue(), j);
                    }
                    
                    if (j == 2 || j == 5 || j == 8) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[0].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[3].getSingleBoxes()[8].getValue(), j);
                    }
                    
                } // end if == 6
                
                // if we are the seventh NineBox
                if (i == 7) {
                    
                    if (j == 0 || j == 1 || j == 2) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[2].getValue(), j);
                    }
                    
                    if (j == 3 || j == 4 || j == 5) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[5].getValue(), j);
                    }
                    
                    if (j == 6 || j == 7 || j == 8) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[8].getSingleBoxes()[8].getValue(), j);
                    }
                    
                    if (j == 0 || j == 3 || j == 6) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[6].getValue(), j);
                    }
                    
                    if (j == 1 || j == 4 || j == 7) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[7].getValue(), j);
                    }
                    
                    if (j == 2 || j == 5 || j == 8) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[1].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[4].getSingleBoxes()[8].getValue(), j);
                    }
                    
                } // end if == 7
                
                // if we are the eigth NineBox
                if (i == 8) {
                    
                    if (j == 0 || j == 1 || j == 2) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[2].getValue(), j);
                    }
                    
                    if (j == 3 || j == 4 || j == 5) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[5].getValue(), j);
                    }
                    
                    if (j == 6 || j == 7 || j == 8) {

                        // update horizontal possibilities
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[6].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[7].getSingleBoxes()[8].getValue(), j);
                    }
                    
                    if (j == 0 || j == 3 || j == 6) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[6].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[0].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[3].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[6].getValue(), j);
                    }
                    
                    if (j == 1 || j == 4 || j == 7) {

                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[7].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[1].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[4].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[7].getValue(), j);
                    }
                    
                    if (j == 2 || j == 5 || j == 8) {
                        // update vertical possibilities
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[2].getSingleBoxes()[8].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[2].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[5].getValue(), j);
                        nineBoxBoard[i].update(nineBoxBoard[5].getSingleBoxes()[8].getValue(), j);
                    }
                    
                } // end if == 8
                
            } // end SingleBox loop
            
        } // end NineBox loop

        /**
         * Pair checks for all nine-boxes.
         */
        
        if (isEqual(old)) {

            // iterate through all nine-boxes in table
            for( int i = 0; i < 9; i++ ) {

                // conclude the selection of a pair for this iteration
                if (set == 1) {
                    set = 0;
                    break;
                }

                // iterate through single-boxes in nine-box
                for (int j = 0; j < 9; j++) {

                    // iterate through possibilities in single-box
                    for (int k = 0; k < 9; k++) {
                        if (nineBoxBoard[i].getSingleBoxes()[j].getPossibilities()[k] == 0) {
                            zeroesCount++;
                        }
                        if (nineBoxBoard[i].getSingleBoxes()[j].getPossibilities()[k] != 0) {
                            if (passed == 1) {
                                tempSecond = nineBoxBoard[i].getSingleBoxes()[j].getPossibilities()[k];
                            }
                            if (passed == 0) {
                                tempFirst = nineBoxBoard[i].getSingleBoxes()[j].getPossibilities()[k];
                                passed++;
                            }
                        }
                    }
                    
                    // add only valid pairs to the list of pairs for each nine-box
                    if (zeroesCount == 7 ) {
                        pairs.push_back(Pair(j, tempFirst, tempSecond));
                    }
                    
                    zeroesCount = 0;
                    passed = 0;
                }

                // iterate through the list of valid pairs in the nine-box
                for (int j = 0; j < pairs.size(); j++) {
                    for (int k = 0; k < pairs.size(); k++) {
                        if (k != j) {
                            if (pairs[j].isEqual(pairs[k])) {
                                nineBoxBoard[i].update(pairs[j].getFirst(), pairs[j].getIndex());
                                set = 1;
                            }
                        }
                    }
                }

                pairs.clear();
            }
        }

        set = 0;

        /**
         * Check for pairs between nine-boxes.
         */
        
        if (isEqual(old)) {

            // iterate through all nine-boxes of the table
            for (int i = 0; i < 9; i++ ) {
                if (set == 1) {
                    set = 0;
                    break;
                }

                // iterate through all single-boxes in each nine-box
                for (int j = 0; j < 9; j++) {
                    if (nineBoxBoard[i].getSingleBoxes()[j].getStatus() == false) {
                        for (int k = 0; k < 9; k++) {
                            if (nineBoxBoard[ i ].getSingleBoxes()[j].getPossibilities()[k] != 0) {
                                set = 1;
                                temp = nineBoxBoard[i].getSingleBoxes()[j].getPossibilities()[k];
                                for (int l = 0; l < 9; l++) {
                                    if (nineBoxBoard[i].getSingleBoxes()[j].getPossibilities()[l] != temp) {
                                        nineBoxBoard[i].update(nineBoxBoard[i].getSingleBoxes()[j].getPossibilities()[l], j);
                                    }
                                }
                            }
                            if (set == 1) {
                                break;
                            }
                        }
                    }
                    if (set == 1) {
                        break;
                    }
                }
                if (set == 1) {
                    set = 0;
                    break;
                }
            }
        }

        /**
         * Check for table completion.
         */
        bool valid = true;
        for (int i = 0; i < 9; i++) {
            valid = valid && nineBoxBoard[i].getStatus();
        }

        if (valid) {
            status = true;
        }
    }
}

/**
 * Writes the Sudoku solution to a file.
 *
 * <p>
 * This method writes the solution to
 * a provided Sudoku table to an output file.
 * </p>
 */
void SudokuTable::recordSolution() {
    ofstream outFile(outputFile);

    if (!outFile) {
        cerr << "cannot open " << outputFile << " for output" << endl;
    }

    int firstNBox = 0;
    int firstSBox = 0;
    int temp = 0;

    outFile << endl;
    outFile << "Solution to Sudoku table from " << inputFile << endl;
    outFile << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp = firstNBox;

            for (int k = 0; k < 3; k++) {
                outFile << "[";
                outFile << nineBoxBoard[temp].getSingleBoxes()[firstSBox].getValue();
                outFile << " ";
                outFile << nineBoxBoard[temp].getSingleBoxes()[firstSBox + 1].getValue();
                outFile << " ";
                outFile << nineBoxBoard[temp].getSingleBoxes()[firstSBox + 2].getValue();
                outFile << "] ";
                temp++;
            }
            
            outFile << endl;
            firstSBox += 3;
        }
        
        if (i != 2) {
            outFile << " -----   -----   ----- " << endl;
        }

        firstSBox = 0;
        firstNBox += 3;
    }
    
    outFile << endl;
}

/**
 * Copies a Sudoku table.
 *
 * <p>
 * This method receives a Sudoku table
 * as input and copies that Sudoku table.
 * </p>
 *
 * @param old The provided Sudoku table.
 */
void SudokuTable::copy(SudokuTable old) {
    status = old.getStatus();
    for (int i = 0; i < 9; i++) {
        nineBoxBoard[i] = old.nineBoxBoard[i];
    }
}
