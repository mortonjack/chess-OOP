#ifndef PAWNTEST_H
#define PAWNTEST_H

#include "testcase.h"
using namespace std;

class pawntest : public testcase {
    public:
        pawntest();
        pawntest(int length);
        bool movementTest(bool display); // display determines whether 
        bool runTests(bool display); // or not to output to stdout
};

#endif//PAWNTEST_H