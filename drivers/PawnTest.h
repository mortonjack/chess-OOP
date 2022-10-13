#ifndef PAWNTEST_H
#define PAWNTEST_H

#include "PieceTest.h"
using namespace std;

class PawnTest : public PieceTest {
    public:
        PawnTest();
        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);
        bool enPassantTest(bool display);
        bool runTests(bool display); 
};

#endif//PAWNTEST_H