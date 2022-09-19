#ifndef CAPTURETEST_H
#define CAPTURETEST_H

#include "testcase.h"
using namespace std;

class capturetest : public testcase {
    public:
        capturetest();
        capturetest(int length);
        bool basicTest(bool display); // display determines whether 
        bool runTests(bool display); // or not to output to stdout
};

#endif//CAPTURETEST_H