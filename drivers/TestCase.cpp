#include "TestCase.h"
#include "../include/Gameboard.h"

void TestCase::initialiseResults() {
    this->_results = new bool[_length];
    for (int i = 0; i < _length; i++) {
        _results[i] = false;
    }
}

string TestCase::getMessage(bool pass) {
    if (pass) return _passMessage;
    else return _failMessage;
}

bool TestCase::result() {
    int success = true;
    for (int i = 0; i < _length; i++) {
        success = success && _results[i];
    }
    return success;
}

TestCase::~TestCase() {
    delete [] _results;
}