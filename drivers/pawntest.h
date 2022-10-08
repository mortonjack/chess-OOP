#ifndef PAWNTEST_H
#define PAWNTEST_H

#include "piecetest.h"
using namespace std;

class pawntest : public piecetest {
    public:
        pawntest();
        bool movementTest(bool display);
        bool captureTest(bool display);
        bool checkTest(bool display);
        bool enPassantTest(bool display);
        bool runTests(bool display); 
};

#endif//PAWNTEST_H