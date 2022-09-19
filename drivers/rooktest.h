#ifndef ROOKTEST_H
#define ROOKTEST_H

#include "testcase.h"
using namespace std;

class rooktest : public testcase {
    public:
        rooktest();
        rooktest(int length);
        bool movementTest(bool display); // display determines whether 
        bool firstMovementTest(bool display); // or not to output to stdout
        bool runTests(bool display);
};

#endif//ROOKTEST_H