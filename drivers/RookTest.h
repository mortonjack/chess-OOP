#ifndef ROOKTEST_H
#define ROOKTEST_H

#include "PieceTest.h"
using namespace std;

class RookTest : public PieceTest {
    public:
        RookTest();
        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);
};

#endif//ROOKTEST_H