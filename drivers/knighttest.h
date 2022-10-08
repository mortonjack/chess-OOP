#ifndef KNIGHTTEST_H
#define KNIGHTTEST_H

#include "piecetest.h"
using namespace std;

class knighttest : public piecetest {
    public:
        knighttest();
        bool movementTest(bool display);
        bool captureTest(bool display);
        bool checkTest(bool display);
};

#endif//KNIGHTTEST_H