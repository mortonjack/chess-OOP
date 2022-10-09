#ifndef COLLISIONTEST_H
#define COLLISIONTEST_H

#include "testcase.h"
using namespace std;

class collisiontest : public testcase {
    public:
        collisiontest();
        bool baseTest(bool display);
        bool vertTest(bool display);
        bool runTests(bool display);
};

#endif//COLLISIONTEST_H