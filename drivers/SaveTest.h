#ifndef SAVETEST_H
#define SAVETEST_H

#include "../include/State.h"
#include "TestCase.h"

class SaveTest : public TestCase {
    public:
        SaveTest();
        bool directTest(bool display);
        bool gameTest(bool display);
        bool runTests(bool display);
};

#endif//SAVETEST_H