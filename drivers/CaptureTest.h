#ifndef CAPTURETEST_H
#define CAPTURETEST_H

#include "TestCase.h"
using namespace std;

class CaptureTest : public TestCase {
    private:
        // Specific Tests. Display determines whether to output to stdout.

        // Tests capture of enemy pieces
        bool basicTest(bool display);

        // Tests friendly pieces can't be captured
        bool teamCapture(bool display);

    public:
        // Constructor
        CaptureTest();

        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display);
};

#endif//CAPTURETEST_H