#ifndef QUEENTEST_H
#define QUEENTEST_H

#include "PieceTest.h"
using namespace std;

class QueenTest : public PieceTest {
    public:
        QueenTest();
        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);
};

#endif//QUEENTEST_H