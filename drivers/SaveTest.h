#ifndef SAVETEST_H
#define SAVETEST_H

#include "../include/State.h"
#include "TestCase.h"

class SaveTest : public TestCase {
    private:
        // Tests board1 and board2 pieces are all at the same position
        // with the same type, colour, and movecount
        bool testBoard(Piece* board1[8][8], Piece* board2[8][8]);
        // Tests each node in the linked list contains identical move information
        // and identical pieces (type, colour, movecount)
        bool testMoveNode(MoveNode* node1, MoveNode* node2);

        // Specific Tests. Display determines whether to output to stdout.
        bool directTest(bool display);
        bool gameTest(bool display);

        // Same as Gameboard::visualiseTextBoard().
        // Outputs the input piece array to stdout
        void visualiseBoard(Piece* board[8][8]);

        // Frees all pieces in the gameboard and node
        // This is usually done by the Game object
        void delPieces(Piece* board[8][8], MoveNode* node);

    public:
        // Constructor
        SaveTest();

        // Run tests.
        // Display outputs previously failed tests to stdout.
        bool runTests(bool display);
};

#endif//SAVETEST_H