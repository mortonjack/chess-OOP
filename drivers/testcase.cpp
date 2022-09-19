#include "testcase.h"
#include "../include/gameboard.h"

testcase::testcase(): testcase(1) {}
testcase::testcase(int length): _length(length) {
    this->_results = new bool[1];
    this->_failMessage = "Test failed";
    this->_passMessage = "Test succeeded";
}
testcase::~testcase() {
    delete [] _results;
}