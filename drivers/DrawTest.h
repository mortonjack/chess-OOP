#ifndef DRAWTEST_H
#define DRAWTEST_H

#include "TestCase.h"
using namespace std;

class DrawTest : public TestCase {
    private:
        // Specific Tests. Display determines whether to output to stdout.

        // Tests stalemate function
        bool stalemateTest(bool display);

        // Tests threefold repetition function
        bool threefoldTest(bool display);
        
        // Tests fifty move rule function
        bool fiftyMoveTest(bool display);

        // Tests insufficient material function
        bool insufficientTest(bool display);

    public:
        // Constructor
        DrawTest();
        
        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display); 
};

#endif//DRAWTEST_H