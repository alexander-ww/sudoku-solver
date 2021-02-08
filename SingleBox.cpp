#include "SingleBox.h"

using namespace std;

/**
 * Constructor.
 *
 * <p>
 * This method accepts the index
 * of a nine-box in the Sudoku board
 * and a value to assign to the single
 * box instance. Upon the receipt of
 * these inputs, the method constructs
 * an instance of a single box as output.
 * </p>
 *
 * @param box The associated nine-box index.
 * @param value The associated value.
 */
SingleBox::SingleBox(int box, int value) {
    setBox(box);
    setValue(value);
    setStatus(false);

    for (int i = 1; i < 10; i++) {
        this->possibilities.push_back(i);
    }

    if (value >= 1 && value <= 9) {
        setStatus(true);
    }
}

/**
 * Sets the nine-box.
 *
 * <p>
 * This method accepts an integer
 * representing the index of the
 * nine-box to associate with this
 * single box instance. Upon the
 * receipt of this input, the method
 * sets the nine-box that is associated
 * with the single box instance.
 * </p>
 *
 * @param ninebox The associated nine-box.
 */
void SingleBox::setBox(int ninebox) {
    this->box = ninebox;
}

/**
 * Sets the value.
 *
 * <p>
 * This method accepts an integer
 * representing the value of the
 * single box and sets the value
 * of the single box accordingly.
 * </p>
 *
 * @param value The associated value.
 */
 void SingleBox::setValue(int value) {
     this->value = value;
 }

/**
 * Sets the completion status.
 *
 * <p>
 * This method accepts a new status
 * and sets the completion status of
 * the single box instance accordingly.
 * </p>
 *
 * @param complete The completion status.
 */
 void SingleBox::setStatus(bool complete) {
     this->status = complete;
 }
 
 /**
  * Gets the completion status.
  *
  * <p>
  * This method returns the
  * completion status of the
  * single box instance.
  * </p>
  *
  * @return The completion status.
  */
 bool SingleBox::getStatus() {
     return this->status;
 }
 
 /**
  * Gets the assigned value.
  *
  * <p>
  * This method acquires the
  * assigned value of the single
  * box instance.
  * </p>
  *
  * @return The assigned value.
  */
 int SingleBox::getValue() {
     return this->value;
 }
 
 /**
  * Gets the assigned nine-box index.
  *
  * <p>
  * This method acquires the index
  * of the assigned nine-box.
  * </p>
  *
  * @return The nine-box index.
  */
 int SingleBox::getBox() {
     return this->box;
 }
 
 /**
  * Updates value possibilities.
  *
  * <p>
  * This method accepts a number
  * representing a candidate value
  * as input and sets the given
  * number to zero, in the maintained
  * possibilities vector for the
  * single-box, if the number currently
  * exists as a possibility in the
  * possibilities vector.
  * </p>
  *
  * @param number The provided value.
  */
 void SingleBox::update(int number) {
     int zeroesCount = 0;   // counter for zeroes in possibilities vector
     int value = 0;         // temporary value for the SingleBox
 
     /**
      * Only update the possibilities vector for
      * this SingleBox if it is not already complete.
      */
     if (getStatus() == false) {
     
         /** 
          * Iterate through the possibilities
          * vector for this single-box if its
          * completion status if false.
          */
         for (int i = 0; i < possibilities.size(); i++) {
             if (possibilities[i] == number) {
                 possibilities[i] = 0;
                 break;
             }
         }

         /**
          * Iterate through the possibilities vector
          * for this single-box and count the number
          * of zeros contained in the possibilities
          * vector.
          */
         for (int i = 0; i < possibilities.size(); i++) {
             if (possibilities[i] == 0) {
                 zeroesCount++;
             }
             else {
                 value = possibilities[i];
             }
         }

         /**
          * The presence of only one value in the
          * possibilities vector for this single-box
          * indicates that the single-box has a 
          * non-zero value and hence is complete.
          */
         if (zeroesCount == possibilities.size() - 1) {
             setValue(value);
             setStatus(true);
         }
     }
 }
 
 /**
  * Prints to console for debugging.
  *
  * <p>
  * This method prints the contents
  * of the single-box to the console
  * for debugging.
  * </p>
  */
 void SingleBox::debugPrinter() {
     cout << endl;

     // set the format to be printed to the console
     cout << "SingleBox class contains the following: " << endl;
     cout << " - Completion status = " << getStatus() << endl;
     cout << " - NineBoxNumber     = " << getBox() << endl;
     cout << " - BoxValue          = " << getValue() << endl;
     cout << " - Possibilities     = [";

     /**
      * Iterate through the possibilities vector for this
      * single-box and print all values of that vector in
      * the appropriate format to the console.
      */
     for (int i = 0; i < getPossibilities().size(); i++) {
         cout << getPossibilities()[i];
         if (i != getPossibilities().size() - 1) {
             cout << ", ";
         }
     }

     cout << "]" << endl;
}

/**
 * Gets the possibilities vector.
 *
 * <p>
 * This method acquires the possibilities
 * vector of the single-box instance.
 * </p>
 *
 * @return The possibilities vector.
 */
vector<int> SingleBox::getPossibilities() {
    return possibilities;
}

/**
 * Erases a possibility.
 *
 * <p>
 * This method accepts the index of
 * a possibility as input and sets
 * the value of that index in the
 * possibilities vector to zero to
 * indicate that the possibility
 * is being used or is no longer
 * viable.
 * </p>
 *
 * @param index The provided index.
 */
void SingleBox::erasePossibility(int index) {
    possibilities[index] = 0;
}

/**
 * Checks equality.
 *
 * <p>
 * This method accepts a single-box
 * instance as input and determines
 * whether that single-box instance is
 * equal to this single-box instance. If
 * the two instances are equal a value of
 * true is returned; Otherwise, a value of
 * false is returned.
 * </p>
 *
 * @param singlebox The single-box to compare against.
 *
 * @return True if equal; False otherwise.
 */
bool SingleBox::isEqual(SingleBox singlebox) {
    bool samePossibilities = true;

    // determine if possibility vectors are the same
    for (int i = 0; i < 9; i++) {
        samePossibilities = samePossibilities && possibilities[i] == singlebox.getPossibilities()[i];
    }

    if (box == singlebox.getBox() &&
        value == singlebox.getValue() &&
        status == singlebox.getStatus() &&
        samePossibilities) {

        return true;
    }

    else {
        return false;
    }
}
