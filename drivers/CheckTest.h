#ifndef CHECKTEST_H
#define CHECKTEST_H

#include "TestCase.h"
using namespace std;

class CheckTest : public TestCase {
    public:
        CheckTest();
        bool movementTest(bool display);
        bool diagonalTest(bool display);
        bool straightTest(bool display);
        bool KnightTest(bool display); 
        bool enPassantTest(bool display);
        bool runTests(bool display);
};

#endif//CHECKTEST_H