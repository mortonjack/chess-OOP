#ifndef BOARDNODETEST_H
#define BOARDNODETEST_H
#include "testcase.h"
#include "../include/boardnode.h"
#include "../include/piece.h"

class boardnodetest : public testcase {
    public:
        boardnodetest();
        boardnodetest(int length);
        void visualiseBoard(boardnode node);
        void visualiseBoard(piece* board[8][8]);
        bool basicTest(bool display);
        bool runTests(bool display);
};

#endif//BOARDNODETEST_H