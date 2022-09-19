#include "testcase.h"
#include "../../include/gameboard.h"

testcase::testcase(): testcase(1) {}
testcase::testcase(int length): _length(length) {
    this->_results = new bool[1];
}
testcase::~testcase() {
    delete [] _results;
}