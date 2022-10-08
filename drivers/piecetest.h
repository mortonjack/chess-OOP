#ifndef PIECETEST_H
#define PIECETEST_H

#include "testcase.h"

class piecetest : public testcase {
    public:
        // Display determines whether or not to output to stdout
        virtual bool movementTest(bool display) = 0;
        virtual bool captureTest(bool display) = 0;
        virtual bool checkTest(bool display) = 0;
        bool runTests(bool display);
};

#endif//PIECETEST_H