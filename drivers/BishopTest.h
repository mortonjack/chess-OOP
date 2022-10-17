#ifndef BISHOPTEST_H
#define BISHOPTEST_H

#include "PieceTest.h"
using namespace std;

class BishopTest : public PieceTest {
    private:
        // Specific Tests. Display determines whether to output to stdout.
        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);
        
    public:
        // Constructor
        BishopTest();
};

#endif//BISHOPTEST_H