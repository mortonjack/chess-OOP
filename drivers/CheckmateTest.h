#ifndef CHECKMATETEST_H
#define CHECKMATETEST_H

#include "TestCase.h"
using namespace std;

class CheckmateTest : public TestCase {
    public:
        CheckmateTest();
        // Display determines whether or not to output to stdout
        bool basicTest(bool display);
        bool anarchyTest(bool display);
        bool enPassantTest(bool display);
        bool runTests(bool display); 
};

#endif//CHECKMATETEST_H