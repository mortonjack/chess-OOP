#ifndef BISHOPTEST_H
#define BISHOPTEST_H

#include "piecetest.h"
using namespace std;

class bishoptest : public piecetest {
    public:
        bishoptest();
        bool movementTest(bool display);
        bool captureTest(bool display);
        bool checkTest(bool display);
};

#endif//BISHOPTEST_H