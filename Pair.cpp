#include "Pair.h"

Pair::Pair(int index, int first, int second) {
    setIndex(index);
    setFirst(first);
    setSecond(second);
}

void Pair::setIndex(int index) {
    this->index = index;
}

void Pair::setFirst(int first) {
    this->first = first;
}

void Pair::setSecond(int second) {
    this->second = second;
}

int Pair::getFirst() {
    return first;
}

int Pair::getSecond() {
    return second;
}

int Pair::getIndex() {
    return index;
}

bool Pair::isEqual(Pair pair) {
    if (first == pair.getFirst() &&
        second == pair.getSecond()) {
        return true;
    }
    else {
        return false;
    }
}
