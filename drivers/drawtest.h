#ifndef DRAWTEST_H
#define DRAWTEST_H

#include "testcase.h"
using namespace std;

class drawtest : public testcase {
    public:
        drawtest();
        // Display determines whether or not to output to stdout
        bool stalemateTest(bool display);
        bool threefoldTest(bool display);
        bool fiftyMoveTest(bool display);
        bool mutualTest(bool display);
        bool deadTest(bool display);
        bool runTests(bool display); 
};

#endif//DRAWTEST_H