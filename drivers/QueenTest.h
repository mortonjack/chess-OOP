#ifndef QUEENTEST_H
#define QUEENTEST_H

#include "PieceTest.h"
using namespace std;

class QueenTest : public PieceTest {
    private:
        // Specific Tests. Display determines whether to output to stdout.
        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);
        
    public:
        // Constructor
        QueenTest();
};

#endif//QUEENTEST_H