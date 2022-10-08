#include "testcase.h"
#include "../include/gameboard.h"

void testcase::initialiseResults() {
    this->_results = new bool[_length];
    for (int i = 0; i < _length; i++) {
        _results[i] = false;
    }
}

string testcase::getMessage(bool pass) {
    if (pass) return _passMessage;
    else return _failMessage;
}

bool testcase::result() {
    int success = true;
    for (int i = 0; i < _length; i++) {
        success = success && _results[i];
    }
    return success;
}

testcase::~testcase() {
    delete [] _results;
}