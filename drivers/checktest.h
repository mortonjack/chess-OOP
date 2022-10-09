#ifndef CHECKTEST_H
#define CHECKTEST_H

#include "testcase.h"
using namespace std;

class checktest : public testcase {
    public:
        checktest();
        bool movementTest(bool display);
        bool diagonalTest(bool display);
        bool straightTest(bool display);
        bool knightTest(bool display); 
        bool enPassantTest(bool display);
        bool runTests(bool display);
};

#endif//CHECKTEST_H