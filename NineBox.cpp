#include "NineBox.h"

using namespace std;

/**
 *
 */
NineBox::NineBox(vector<SingleBox> values, int box) {
    setBox(box);
    setStatus(false);

    // construct the default possibilities
    for (int i = 1; i < 10; i++) {
        possibilities.push_back(i);
    }

    // fill the nine-boxk with its single-boxes
    for (int i = 0; i < 9; i++) {
        singleBoxes.push_back(values[i]);
    }
    
    // update the possibilities of the nine-box
    update(singleBoxes[0].getValue(), 0);
}

bool NineBox::getStatus() {
    return status;
}

int NineBox::getBox() {
    return box;
}

vector<int> NineBox::getPossibilities() {
    return possibilities;
}

void NineBox::setBox(int ninebox) {
    box = ninebox;
}

void NineBox::setStatus(bool complete) {
    status = complete;
}

void NineBox::update(int number, int singlebox) {
    int zeroesCount = 0;
    bool valid = true;

    singleboxes[singlebox].update(number);

    for (int i = 0; i < singleboxes.size(); i++) {
        for (int j = 0; j < possibilities.size(); j++) {
            if (singleboxes[i].getValue() == possibilities[j]) {
                possibilities[j] = 0;
            }
        }
    }
    
    for (int i = 0; i < singleboxes.size(); i++) {
        for (int j = 0; j < possibilities.size(); j++) {
            if (possibilities[j] == 0) {
                singleboxes[i].setPossibilities(j);
                singleboxes[i].update(0);
            }
        }
    }

    for (int i = 0; i < possibilities.size(); i++) {
        if (possibilities[i] == 0) {
            zeroesCount++;
        }
    }

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
    for (int i = 0; i < singleboxes.size(); i++) {
        if (i % 3 == 0) {
            cout << "   [";
            cout << singleboxes[i].getValue();
            cout << " ";
        }
        else if (i % 3 == 1) {
            cout << singleboxes[i].getValue();
            cout << " ";
        }
        else {
            cout << singleboxes[i].getValue();
            cout << "]" << endl;
        }
    }
    
    cout << endl;
}

