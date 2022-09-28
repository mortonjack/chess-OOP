#ifndef CHECKMATETEST_H
#define CHECKMATETEST_H

#include "testcase.h"
using namespace std;

class checkmatetest : public testcase {
    public:
        checkmatetest();
        checkmatetest(int length);
        // Display determines whether or not to output to stdout
        bool basicTest(bool display);
        bool runTests(bool display); 
};

#endif//CHECKMATETEST_H