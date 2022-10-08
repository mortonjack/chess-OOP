#ifndef ROOKTEST_H
#define ROOKTEST_H

#include "piecetest.h"
using namespace std;

class rooktest : public piecetest {
    public:
        rooktest();
        bool movementTest(bool display);
        bool captureTest(bool display);
        bool checkTest(bool display);
};

#endif//ROOKTEST_H