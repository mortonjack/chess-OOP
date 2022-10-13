#ifndef COLLISIONTEST_H
#define COLLISIONTEST_H

#include "TestCase.h"
using namespace std;

class CollisionTest : public TestCase {
    public:
        CollisionTest();
        bool baseTest(bool display);
        bool vertTest(bool display);
        bool runTests(bool display);
};

#endif//COLLISIONTEST_H