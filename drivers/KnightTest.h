#ifndef KNIGHTTEST_H
#define KNIGHTTEST_H

#include "PieceTest.h"
using namespace std;

class KnightTest : public PieceTest {
    private:
        // Specific Tests. Display determines whether to output to stdout.
        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);

    public:
        // Constructor
        KnightTest();
};

#endif//KNIGHTTEST_H