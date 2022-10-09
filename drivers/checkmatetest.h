#ifndef CHECKMATETEST_H
#define CHECKMATETEST_H

#include "testcase.h"
using namespace std;

class checkmatetest : public testcase {
    public:
        checkmatetest();
        // Display determines whether or not to output to stdout
        bool basicTest(bool display);
        bool anarchyTest(bool display);
        bool enPassantTest(bool display);
        bool runTests(bool display); 
};

#endif//CHECKMATETEST_H