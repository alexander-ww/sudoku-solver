#include <string>
#include "sudoku_table.h"

const int MAXLINE = 18;

using namespace std;

/**
 * Constructor.
 *
 * <p>
 * This method accepts a constant size
 * character string representing the absolute
 * path to an input file and a constant size
 * character string representing the absolute
 * path to an output file. Upon the receipt of
 * these two inputs, the method constructs
 * an instance of a Sudoku table as output.
 * </p>
 *
 * @param input The provided input file path.
 * @param output The provided output file path.
 */
SudokuTable::SudokuTable(const char* input, const char* output) {

    // declare values
    vector<int> values = vector<int>();

    // setup input file
    ifstream inFile(input);
    char line[MAXLINE];

    // read from input file
    while (inFile) {
        inFile.getline(line, MAXLINE);
        if (inFile) {
            for (int i = 0; i < MAXLINE - 1; i += 2) {
                if (line[i] != '\0' && line[i] != '\n') {
                    int value = line[i] - '0';
                    values.push_back(value);
                }
            }
        }
    }

    // close input file
    inFile.close();

    // setup files
    this->input = input;
    this->output = output;

    // populate table
    populate(values);
}

/**
 * Populates the Sudoku table.
 *
 * <p>
 * This method accepts a collection
 * of values as input and populates
 * the cells of the Sudoku table.
 * </p>
 *
 * @param value The provided values.
 */
void SudokuTable::populate(vector<int> &values) {

    // initialize row
    vector<int> row = vector<int>();

    // populate table with rows
    for (int i = 0; i < values.size(); i++) {
        if (i % 9 == 0) {
            if (i != 0) {
                grid.push_back(row);
                row = vector<int>();
            }
            row.push_back(values.at(i));
        }
        else {
            row.push_back(values.at(i));
        }
    }
    if (!row.empty()) {
        grid.push_back(row);
    }
}

/**
 * Gets the size of the table.
 *
 * <p>
 * This method acquires the
 * size of the SudokuTable.
 * </p>
 *
 * @return The size of the Sudoku table.
 */
int SudokuTable::size() {
    return grid.size();
}

/**
 * Gets the cell value.
 *
 * <p>
 * This method acquires the value for
 * the cell in the Sudoku table at the
 * specified row and column indices.
 * </p>
 *
 * @param row The provided row index.
 * @param column The provided column index.
 *
 * @return The value of cell in the Sudoku table.
 */
int SudokuTable::getCell(int row, int column) {
    return grid.at(row).at(column);
}

/**
 * Sets the cell value.
 *
 * <p>
 * This method accepts a row index, a
 * column index, and a value as input
 * and sets the cell in the Sudoku table
 * with the row and column indices to
 * the provided value.
 * </p>
 *
 * @param row The provided row index.
 * @param column The provided column index.
 * @param value The provided value.
 */
void SudokuTable::setCell(int row, int column, int value) {
    grid.at(row).at(column) = value;
}

/**
 * Prints the Sudoku table.
 *
 * <p>
 * This method prints the current
 * content of the Sudoku table in
 * a formatted manner to the console.
 * </p>
 */
void SudokuTable::print() {

    // print header content
    cout << endl;
    cout << "Printing contents of Sudoku table:" << endl;
    cout << endl;

    // print the table content
    for (int row = 0; row < grid.size(); row++) {
        for (int column = 0; column < grid.size(); column++) {

            // handle first nine-box
            if (column >= 0 && column <= 2) {
                if (column == 0) {
                    cout << "[";
                    cout << getCell(row, column);
                    cout << " ";
                }
                else if (column == 2) {
                    cout << getCell(row, column);
                    cout << "] ";
                }
                else {
                    cout << getCell(row, column);
                    cout << " ";
                }
            }

            // handle second nine-box
            else if (column >= 3 && column <= 5) {
                if (column == 3) {
                    cout << "[";
                    cout << getCell(row, column);
                    cout << " ";
                }
                else if (column == 5) {
                    cout << getCell(row, column);
                    cout << "] ";
                }
                else {
                    cout << getCell(row, column);
                    cout << " ";
                }
            }

            // handle third nine-box
            else {
                if (column == 6) {
                    cout << "[";
                    cout << getCell(row, column);
                    cout << " ";
                }
                else if (column == 8) {
                    cout << getCell(row, column);
                    cout << "]" << endl;
                }
                else {
                    cout << getCell(row, column);
                    cout << " ";
                }
            }
        }

        // handle printing divider
        if ((row + 1) % 3 == 0 && row != grid.size() - 1) {
            cout << " -----   -----   ----- " << endl;
        }
    }

    // print line separation
    cout << endl;
}

/**
 * Records the Sudoku table.
 *
 * <p>
 * This method records the Sudoku table
 * to the output file of the Sudoku table.
 * </p>
 */
void SudokuTable::record() {

    // set the output file
    ofstream outFile(output);

    // handle no output file
    if (!outFile) {
        cerr << "cannot open " << output << " for output" << endl;
    }

    // indicate solution
    outFile << endl;
    outFile << "Solution to Sudoku table from " << input << endl;
    outFile << endl;
    
    // print the table content
    for (int row = 0; row < grid.size(); row++) {
        for (int column = 0; column < grid.size(); column++) {

            // handle first nine-box
            if (column >= 0 && column <= 2) {
                if (column == 0) {
                    outFile << "[";
                    outFile << getCell(row, column);
                    outFile << " ";
                }
                else if (column == 2) {
                    outFile << getCell(row, column);
                    outFile << "] ";
                }
                else {
                    outFile << getCell(row, column);
                    outFile << " ";
                }
            }

            // handle second nine-box
            else if (column >= 3 && column <= 5) {
                if (column == 3) {
                    outFile << "[";
                    outFile << getCell(row, column);
                    outFile << " ";
                }
                else if (column == 5) {
                    outFile << getCell(row, column);
                    outFile << "] ";
                }
                else {
                    outFile << getCell(row, column);
                    outFile << " ";
                }
            }

            // handle third nine-box
            else {
                if (column == 6) {
                    outFile << "[";
                    outFile << getCell(row, column);
                    outFile << " ";
                }
                else if (column == 8) {
                    outFile << getCell(row, column);
                    outFile << "]" << endl;
                }
                else {
                    outFile << getCell(row, column);
                    outFile << " ";
                }
            }
        }

        // handle printing divider
        if ((row + 1) % 3 == 0 && row != grid.size() - 1) {
            outFile << " -----   -----   ----- " << endl;
        }
    }

    // print line separation
    outFile << endl;
}
