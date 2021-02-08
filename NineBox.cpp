#include "NineBox.h"

using namespace std;

/**
 * Constructor.
 *
 * <p>
 * This method accepts a collection of
 * single boxes and a number representing
 * the index of the nine-box to create. Upon
 * The receipt of these inputs, the method
 * constructs an instance of a nine-box.
 * </p>
 *
 * @param value The collection of single-boxes.
 * @param box The index number of the nine-box.
 */
NineBox::NineBox(vector<SingleBox> values, int box) {
    setBox(box);
    setStatus(false);

    // construct the default possibilities
    for (int i = 1; i < 10; i++) {
        possibilities.push_back(i);
    }

    // fill the nine-box with its single-boxes
    for (int i = 0; i < 9; i++) {
        singleBoxes.push_back(values[i]);
    }
    
    // update the possibilities of the nine-box
    update(singleBoxes[0].getValue(), 0);
}

/**
 * Gets the completion status.
 *
 * <p>
 * This method acquires the
 * completion status for the nine-box.
 * </p>
 *
 * @return The completion status.
 */
bool NineBox::getStatus() {
    return status;
}

/**
 * Gets the index value for the nine-box.
 *
 * <p>
 * This method acquires the index value
 * associated with the nine-box. The value
 * indicates where in the Sudoku table the
 * nine-box resides.
 * </p>
 *
 * @return The index of the nine-box.
 */
int NineBox::getBox() {
    return box;
}

/**
 * Gets the possibilities vector.
 *
 * <p>
 * This method acquires the vector
 * of possibilities that are associated
 * with the nine-box.
 * </p>
 *
 * @return The vector of possibilities.
 */
vector<int> NineBox::getPossibilities() {
    return possibilities;
}

/**
 * Sets the nine-box index.
 *
 * <p>
 * This method accepts a nine-box
 * index as input and sets the index
 * of the nine-box accordingly.
 * </p>
 *
 * @param ninebox The provided nine-box index.
 */
void NineBox::setBox(int ninebox) {
    box = ninebox;
}

/**
 * Sets the completion status.
 *
 * <p>
 * This method accepts a boolean value
 * indicating the current completion status
 * and sets the completion status of the
 * nine-box instance accordingly.
 * </p>
 *
 * @param complete The provided completion status.
 */
void NineBox::setStatus(bool complete) {
    status = complete;
}

/**
 * Updates the nine-box.
 *
 * <p>
 * This method accepts a candidate value
 * and the index of a single box as input
 * and updates the specified single-box
 * in the nine-box. If the status of all
 * single-boxes in the nine-box are
 * complete, then the status of the
 * nine-box is complete.
 * </p>
 *
 * @param number The provided candidate value.
 * @param singlebox The provided single-box index.
 */
void NineBox::update(int number, int singlebox) {
    int zeroesCount = 0;
    bool valid = true;

    // update possibilities of the single-box
    singleBoxes[singlebox].update(number);

    // update possibilities vector of the nine-box
    for (int i = 0; i < singleBoxes.size(); i++) {
        for (int j = 0; j < possibilities.size(); j++) {
            if (singleBoxes[i].getValue() == possibilities[j]) {
                possibilities[j] = 0;
            }
        }
    }
    
    /**
     * Update all of the possibility vectors for all of
     * the single-boxes according to the possibility
     * vector for this nine-box instance.
     */
    for (int i = 0; i < singleBoxes.size(); i++) {
        for (int j = 0; j < possibilities.size(); j++) {
            if (possibilities[j] == 0) {
                singleBoxes[i].setPossibilities(j);
                singleBoxes[i].update(0);
            }
        }
    }

    /**
     * Iterate through the possibilities vector of this
     * nine-box instance in order to determine how
     * incomplete the nine-box is.
     */
    for (int i = 0; i < possibilities.size(); i++) {
        if (possibilities[i] == 0) {
            zeroesCount++;
        }
    }

    /**
     * When there are no more single-boxes to update in this
     * nine-box, then set the non-zero status of the nine-box
     * to true.
     */
    if (zeroesCount == possibilities.size() - 1) {
        setStatus(true);
    }

    for (int i = 0; i < 9; i++) {
        valid = valid && getSingleBoxes()[i].getStatus();
    }

    if (valid) {
        setStatus(true);
    }
}

/**
 * Prints to the console for debugging.
 *
 * <p>
 * This method prints the contents
 * of the nine-box to the console
 * for debugging.
 * </p>
 */
void NineBox::debugPrinter() {
    cout << endl;
    
    // set the format to be printed to the console
    cout << "NineBox class contains the following " << endl;
    cout << " - Completion status = " << getStatus() << endl;
    cout << " - NineBoxNumber     = " << getBox() << endl;
    cout << " - Possibilities     = [";
    
    /**
     * Iterate through the possibilities vector for
     * this NineBox and print all values of that
     * vector in the appropriate format to the console.
     */
    for (int i = 0; i < possibilities.size(); i++) {
        cout << possibilities[i];
        if (i != possibilities.size() - 1) {
            cout << ", ";
        }
    }

    cout << "]" << endl << endl;
    cout << " - NineBox visual representation:" << endl;

    // print the nine-box in board format to the console
    for (int i = 0; i < singleBoxes.size(); i++) {
        if (i % 3 == 0) {
            cout << "   [";
            cout << singleBoxes[i].getValue();
            cout << " ";
        }
        else if (i % 3 == 1) {
            cout << singleBoxes[i].getValue();
            cout << " ";
        }
        else {
            cout << singleBoxes[i].getValue();
            cout << "]" << endl;
        }
    }

    cout << endl;
}

/**
 * Prints the single-box info.
 *
 * <p>
 * This method prints the information of
 * the single-boxes that are inside the
 * nine-box to the console for viewing.
 * </p>
 */
void NineBox::printSingleBoxes() {
    cout << endl;
    cout << "Printing info of all single-boxes in nine-box #" << getBox() << " :" << endl;
    cout << "-------------------------------------------------" << endl;

    /**
     * Iterate through all single-boxes and print
     * the contents of each single-box to the console.
     */
    for (int i = 0; i < singleBoxes.size(); i++) {
        singleBoxes[i].debugPrinter();
    }
    
    cout << "-------------------------------------------------" << endl;
}

/**
 * Gets the single-boxes.
 *
 * <p>
 * This method acquires the single-boxes
 * that are present in the nine-box.
 * </p>
 *
 * @return The single-boxes of the nine-box.
 */
vector<SingleBox> NineBox::getSingleBoxes() {
    return singleBoxes;
}

/**
 * Checks equality.
 *
 * <p>
 * This method accepts a nine-box
 * instance as input and determines
 * whether that nine-box instance is
 * equal to this nine-box instance. If
 * the two instances are equal a value of
 * true is returned; Otherwise, a value of
 * false is returned.
 * </p>
 *
 * @param ninebox The nine-box to compare against.
 *
 * @return True if equal; False otherwise.
 */
bool NineBox::isEqual(NineBox ninebox) {
    bool sameSingleBoxes = true;
    bool samePossibilities = true;

    /**
     * Iterate through all single-boxes of both
     * nine-boxes and perform comparison.
     */
    for (int i = 0; i < 9; i++) {
        sameSingleBoxes = sameSingleBoxes && singleBoxes[i].isEqual(ninebox.getSingleBoxes()[i]);
    }

    /**
     * Iterate through all possibilities of both
     * nine-boxes and perform comparison.
     */
    for (int i = 0; i < 9; i++) {
        samePossibilities = samePossibilities && possibilities[i] == ninebox.getPossibilities()[i];
    }
    
    return sameSingleBoxes && samePossibilities;
}
