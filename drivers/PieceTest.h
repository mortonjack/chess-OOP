#ifndef PIECETEST_H
#define PIECETEST_H

#include "TestCase.h"

class PieceTest : public TestCase {
    public:
        // Display determines whether or not to output to stdout
        virtual bool movementTest(bool display) = 0;
        virtual bool CaptureTest(bool display) = 0;
        virtual bool checkTest(bool display) = 0;
        bool runTests(bool display);
};

#endif//PIECETEST_H