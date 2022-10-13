#ifndef KNIGHTTEST_H
#define KNIGHTTEST_H

#include "PieceTest.h"
using namespace std;

class KnightTest : public PieceTest {
    public:
        KnightTest();
        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);
};

#endif//KNIGHTTEST_H