#ifndef CHECKTEST_H
#define CHECKTEST_H

#include "testcase.h"
using namespace std;

class checktest : public testcase {
    public:
        checktest();
        checktest(int length);
        bool movementTest(bool display);
        bool diagonalTest(bool display);
        bool straightTest(bool display);
        bool knightTest(bool display); 
        bool enPassantTest(bool display);   // display determines whether 
        bool runTests(bool display);        // or not to output to stdout
};

#endif//CHECKTEST_H