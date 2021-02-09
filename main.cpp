#include <iostream>
#include "sudoku_table.h"
#include "sudoku_solver.h"

using namespace std;

/**
 * Driver for the Sudoku solver program.
 *
 * <p>
 * This function constructs a Sudoku table
 * from information in a file specified in the
 * command-line input and runs the Sudoku
 * solver on the result to produce the solved
 * Sudoku table in an output file.
 * </p>
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 */
int main(int argc, const char* argv[]) {

    if (argc != 3) {
        cout << "Usage: " << argv[0] << " [input filename] [output filename]" << endl;
        return 1;
    }

    const char* input = argv[1];
    const char* output = argv[2];
    
    SudokuTable table = SudokuTable(input, output);
    SudokuSolver solver = SudokuSolver();

    solver.solve(table);

    table.print();
    table.record();

    cout << "solution written to " << output << endl;
    
    return 0;
}
