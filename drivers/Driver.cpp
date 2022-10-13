#include "Driver.h"
#include <iostream>
using namespace std;

Driver::Driver(): Driver(1) {} // default length 1
Driver::Driver(int length): _maxLength(length), _length(0) {
    _cases = new TestCase*[length];
    _results = new bool[length];
}
Driver::~Driver() {
    delete [] _cases;
    delete [] _results;
}

void Driver::addCase(TestCase* newCase) {
    // if array is full
    if (this->_length == this->_maxLength) {
        // backup existing array
        TestCase** oldcases = this->_cases;

        // allocate new array
        this->_maxLength *= 2;
        this->_cases = new TestCase*[this->_maxLength];
        for (int i = 0; i < this->_length; i++) {
            this->_cases[i] = oldcases[i];
        }
        delete [] oldcases;

        // update results array
        delete [] this->_results;
        this->_results = new bool[this->_maxLength];
    }

    // add test to array
    this->_cases[this->_length] = newCase;
    this->_length++;
}

void Driver::runTests() {
    // Run through tests
    for (int i = 0; i < this->_length; i++) {
        this->_results[i] = this->_cases[i]->runTests(false);
        if (this->_results[i]) {
            cout << "Test " << i << " passed: " << 
            this->_cases[i]->getMessage(true) << endl;
        } else {
            cout << "Test " << i << " failed: " <<
            this->_cases[i]->getMessage(false) << endl; 
        }
    }
    // Specific feedback for failed tests
    for (int i = 0; i < this->_length; i++) {
        if (!this->_results[i]) {
            this->_cases[i]->runTests(true);
        }
    }
}