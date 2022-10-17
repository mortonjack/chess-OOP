#ifndef PIECETEST_H
#define PIECETEST_H

#include "TestCase.h"

class PieceTest : public TestCase {
    protected:
        // Specific Tests. Display determines whether to output to stdout.

        // Tests the piece's move validity function
        virtual bool movementTest(bool display) = 0;

        // Tests the piece's capture validity function
        virtual bool CaptureTest(bool display) = 0;

        // Tests the piece's interaction with check(mate)/stalemate
        virtual bool checkTest(bool display) = 0;
        
    public:
        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display);
};

#endif//PIECETEST_H