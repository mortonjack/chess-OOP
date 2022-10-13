#ifndef BISHOPTEST_H
#define BISHOPTEST_H

#include "PieceTest.h"
using namespace std;

class BishopTest : public PieceTest {
    public:
        BishopTest();
        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);
};

#endif//BISHOPTEST_H