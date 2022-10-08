#ifndef QUEENTEST_H
#define QUEENTEST_H

#include "piecetest.h"
using namespace std;

class queentest : public piecetest {
    public:
        queentest();
        bool movementTest(bool display);
        bool captureTest(bool display);
        bool checkTest(bool display);
};

#endif//QUEENTEST_H