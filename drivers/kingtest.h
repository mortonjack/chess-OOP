#ifndef KINGTEST_H
#define KINGTEST_H

#include "testcase.h"
using namespace std;

class kingtest : public testcase {
    public:
        kingtest();
        kingtest(int length);
        // display determines whether or not to output to stdout
        bool movementTest(bool display); 
        bool castleTest(bool display);
        bool runTests(bool display);
};

#endif//KINGTEST_H