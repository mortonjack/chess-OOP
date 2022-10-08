#ifndef DRAWTEST_H
#define DRAWTEST_H

#include "testcase.h"
using namespace std;

class drawtest : public testcase {
    public:
        drawtest();
        drawtest(int length);
        // Display determines whether or not to output to stdout
        bool stalemateTest(bool display);
        bool threefoldTest(bool display);
        bool fiftyMoveTest(bool display);
        bool mutualTest(bool display);
        bool deadTest(bool display);
        bool runTests(bool display); 
};

#endif//DRAWTEST_H