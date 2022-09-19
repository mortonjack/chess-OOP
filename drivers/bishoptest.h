#ifndef BISHOPTEST_H
#define BISHOPTEST_H

#include "testcase.h"

class bishoptest : public testcase {
    public:
        bool movementTest(bool display); // display determines whether 
        bool runTests(bool display); // or not to output to stdout
};

#endif//BISHOPTEST_H