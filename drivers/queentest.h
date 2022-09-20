#ifndef QUEENTEST_H
#define QUEENTEST_H

#include "testcase.h"
using namespace std;

class queentest : public testcase {
    public:
        queentest();
        queentest(int length);
        bool movementTest(bool display); // display determines whether 
        bool runTests(bool display); // or not to output to stdout
};

#endif//QUEENTEST_H