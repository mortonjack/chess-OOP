#ifndef CHECKTEST_H
#define CHECKTEST_H

#include "TestCase.h"
using namespace std;

class CheckTest : public TestCase {
    private:
        // Specific Tests. Display determines whether to output to stdout.

        // Tests king can't move into check
        // and moves can't place own king in check
        bool movementTest(bool display);

        // Ensure check works diagonally
        bool diagonalTest(bool display);

        // Ensure check works across rank or file
        bool straightTest(bool display);

        // Ensure knights can check king
        bool KnightTest(bool display); 

        // Ensure check works properly with en passant
        bool enPassantTest(bool display);

    public:
        // Constructor
        CheckTest();

        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display);
};

#endif//CHECKTEST_H