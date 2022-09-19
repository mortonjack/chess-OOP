#ifndef COLLISIONTEST_H
#define COLLISIONTEST_H

#include "testcase.h"
using namespace std;

class collisiontest : public testcase {
    public:
        collisiontest();
        collisiontest(int length);
        bool baseTest(bool display); // display determines whether 
        bool vertTest(bool display); // or not to output to stdout
        bool runTests(bool display);
};

#endif//COLLISIONTEST_H