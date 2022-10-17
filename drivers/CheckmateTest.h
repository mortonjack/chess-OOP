#ifndef CHECKMATETEST_H
#define CHECKMATETEST_H

#include "TestCase.h"
using namespace std;

class CheckmateTest : public TestCase {
    private:
        // Specific Tests. Display determines whether to output to stdout.

        // Tests checkmate function in standard conditions
        bool basicTest(bool display);

        // Tests smothered mate
        bool anarchyTest(bool display);

        // Tests checkmate works correctly with en passant
        bool enPassantTest(bool display);

    public:
        // Constructor
        CheckmateTest();

        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display); 
};

#endif//CHECKMATETEST_H