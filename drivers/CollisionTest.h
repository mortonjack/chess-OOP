#ifndef COLLISIONTEST_H
#define COLLISIONTEST_H

#include "TestCase.h"
using namespace std;

class CollisionTest : public TestCase {
    private:
        // Specific Tests. Display determines whether to output to stdout.

        // Tests collision works diagonally & doesn't prevent capture
        bool baseTest(bool display);

        // Tests collision works vertically (pawns blocking rooks, etc)
        bool vertTest(bool display);

    public:
        // Constructor
        CollisionTest();
        
        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display);
};

#endif//COLLISIONTEST_H