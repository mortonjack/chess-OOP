#ifndef MOVENODETEST_H
#define MOVENODETEST_H
#include "TestCase.h"
#include "../include/MoveNode.h"
#include "../include/Piece.h"

class MoveNodeTest : public TestCase {
    public:
        MoveNodeTest();
        bool testBoardEquality(Piece* first[8][8], Piece* second[8][8]);
        void copyBoard(Piece* copy[8][8], Piece* paste[8][8]);
        void visualiseBoard(Piece* board[8][8]);
        bool basicTest(bool display);
        bool runTests(bool display);
};

#endif//MOVENODETEST_H