#ifndef MOVENODETEST_H
#define MOVENODETEST_H
#include "TestCase.h"
#include "../include/MoveNode.h"
#include "../include/Piece.h"

class MoveNodeTest : public TestCase {
    private:
        // Checks all pieces in both input boards have the same
        // type, colour, and movecount.
        bool testBoardEquality(Piece* first[8][8], Piece* second[8][8]);

        // Copies the pointer to each piece in the input board 'copy'
        // into the same position of the second input board 'paste'
        void copyBoard(Piece* copy[8][8], Piece* paste[8][8]);

        // Same as Gameboard::visualiseTextBoard()
        // Outputs the board to stdout
        void visualiseBoard(Piece* board[8][8]);

        // Specific test. Display determines whether to output to stdout.
        bool basicTest(bool display);

    public:
        // Constructor
        MoveNodeTest();


        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display);
};

#endif//MOVENODETEST_H