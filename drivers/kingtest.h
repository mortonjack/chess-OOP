#ifndef KINGTEST_H
#define KINGTEST_H

#include "piecetest.h"
using namespace std;

class kingtest : public piecetest {
    public:
        kingtest();
        
        bool movementTest(bool display);
        bool castleTest(bool display);
        bool captureTest(bool display);
        bool checkTest(bool display);
        bool runTests(bool display);
};

#endif//KINGTEST_H