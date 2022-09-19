#include "testcase.h"
#include "../include/gameboard.h"

testcase::testcase(): testcase(1) {}
testcase::testcase(int length): _length(length) {
    this->_failMessage = "Test failed";
    this->_passMessage = "Test succeeded";
}

string testcase::getMessage(bool pass) {
    if (pass) return _passMessage;
    else return _failMessage;
}