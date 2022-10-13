#ifndef CAPTURETEST_H
#define CAPTURETEST_H

#include "TestCase.h"
using namespace std;

class CaptureTest : public TestCase {
    public:
        CaptureTest();
        bool basicTest(bool display);
        bool teamCapture(bool display);
        bool runTests(bool display);
};

#endif//CAPTURETEST_H