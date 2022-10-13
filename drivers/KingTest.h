#ifndef KINGTEST_H
#define KINGTEST_H

#include "PieceTest.h"
using namespace std;

class KingTest : public PieceTest {
    public:
        KingTest();
        
        bool movementTest(bool display);
        bool castleTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);
        bool runTests(bool display);
};

#endif//KINGTEST_H