#ifndef CAPTURETEST_H
#define CAPTURETEST_H

#include "testcase.h"
using namespace std;

class capturetest : public testcase {
    public:
        capturetest();
        bool basicTest(bool display);
        bool teamCapture(bool display);
        bool runTests(bool display);
};

#endif//CAPTURETEST_H