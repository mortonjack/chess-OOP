#ifndef PAWNTEST_H
#define PAWNTEST_H

#include "PieceTest.h"
using namespace std;

class PawnTest : public PieceTest {
    private:
        // Specific Tests. Display determines whether to output to stdout.

        // Tests en passant
        bool enPassantTest(bool display);

        // Tests pawn promotion
        bool promotionTest(bool display);

        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);

    public:
        // Constructor
        PawnTest();

        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display); 
};

#endif//PAWNTEST_H