#ifndef MOVENODETEST_H
#define MOVENODETEST_H
#include "testcase.h"
#include "../include/movenode.h"
#include "../include/piece.h"

class movenodetest : public testcase {
    public:
        movenodetest();
        bool testBoardEquality(piece* first[8][8], piece* second[8][8]);
        void copyBoard(piece* copy[8][8], piece* paste[8][8]);
        void visualiseBoard(piece* board[8][8]);
        bool basicTest(bool display);
        bool runTests(bool display);
};

#endif//MOVENODETEST_H