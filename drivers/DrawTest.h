#ifndef DRAWTEST_H
#define DRAWTEST_H

#include "TestCase.h"
using namespace std;

class DrawTest : public TestCase {
    public:
        DrawTest();
        // Display determines whether or not to output to stdout
        bool stalemateTest(bool display);
        bool threefoldTest(bool display);
        bool fiftyMoveTest(bool display);
        bool insufficientTest(bool display);
        bool runTests(bool display); 
};

#endif//DRAWTEST_H