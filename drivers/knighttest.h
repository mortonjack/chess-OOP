#ifndef KNIGHTTEST_H
#define KNIGHTTEST_H

#include "testcase.h"
using namespace std;

class knighttest : public testcase {
    public:
        knighttest();
        knighttest(int length);
        bool movementTest(bool display); // display determines whether 
        bool runTests(bool display); // or not to output to stdout
};

#endif//KNIGHTTEST_H