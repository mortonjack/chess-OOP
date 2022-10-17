#ifndef KINGTEST_H
#define KINGTEST_H

#include "PieceTest.h"
using namespace std;

class KingTest : public PieceTest {
    private:
        // Specific Tests. Display determines whether to output to stdout.

        // Tests castling
        bool castleTest(bool display);

        bool movementTest(bool display);
        bool CaptureTest(bool display);
        bool checkTest(bool display);

    public:
        // Constructor
        KingTest();

        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display);
};

#endif//KINGTEST_H