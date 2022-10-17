#ifndef ROOKTEST_H
#define ROOKTEST_H

#include "PieceTest.h"
using namespace std;

class RookTest : public PieceTest {
    private:
        // Specific Tests. Display determines whether to output to stdout.
        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);

    public:
        // Constructor
        RookTest();
};

#endif//ROOKTEST_H