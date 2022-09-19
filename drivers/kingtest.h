#ifndef KINGTEST_H
#define KINGTEST_H

#include "testcase.h"
using namespace std;

class kingtest : public testcase {
    public:
        kingtest();
        kingtest(int length);
        bool movementTest(bool display); // display determines whether 
        bool runTests(bool display); // or not to output to stdout
};

#endif//KINGTEST_H