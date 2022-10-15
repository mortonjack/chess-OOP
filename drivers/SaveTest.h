#ifndef SAVETEST_H
#define SAVETEST_H

#include "../include/State.h"
#include "TestCase.h"

class SaveTest : public TestCase {
    public:
        SaveTest();
        bool testBoard(Piece* board1[8][8], Piece* board2[8][8]);
        bool testMoveNode(MoveNode* node1, MoveNode* node2);
        bool directTest(bool display);
        bool gameTest(bool display);
        bool runTests(bool display);
};

#endif//SAVETEST_H