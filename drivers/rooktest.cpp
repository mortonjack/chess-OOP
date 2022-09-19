#include "../include/gameboard.h"
#include "../include/rook.h"
#include "rooktest.h"
#include <iostream>
using namespace std;

rooktest::rooktest(): rooktest(1) {}
rooktest::rooktest(int length) {
    this->_failMessage = "Rook test failed";
    this->_passMessage = "Rook test succeeded";
}

bool rooktest::movementTest(bool display) {
    // Test rook movement
    bool success = true;

    // Create the gameboard and two rooks
    gameboard board;
    rook whiteARook = rook('W');
    rook blackARook = rook('B');

    // Add the rooks to the board
    board.addPiece(0,0,&whiteARook);
    board.addPiece(7,0,&blackARook);
    piece* pieces[] = {&whiteARook, &blackARook};
    if (display) board.visualiseTextBoard();

    // Move the rooks to legal positions
    board.movePiece(0,0,3,0);
    board.movePiece(7,0,4,0);
    
    // Check to ensure the moves were made
    if (display) board.visualiseTextBoard();
    int coords[] = {3,0, 4,0};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the rooks to illegal positions
    board.movePiece(3,0, 1,1);
    board.movePiece(4,0, 6,2);

    // Check to ensure our nothing has happened
    if (display) board.visualiseTextBoard();
    bool test2 = board.testDriver(pieces, coords, 2);

    // Move the rooks to legal positions
    board.movePiece(3,0, 3,3);
    board.movePiece(4,0, 2,0);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords2[] = {3,3, 2,0};
    bool test3 = board.testDriver(pieces, coords2, 2);

    // Check results
    if (display) {
        if (test1) {
            cout << "Test passed: Rooks moved properly" << endl;
        } else {
            cout << "Test failed: Rooks failed to move" << endl;
        }

        if (test2) {
            cout << "Test passed: Rooks didn't move" << endl;
        } else {
            cout << "Test failed: Rooks made illegal moves" << endl;
        }

        if (test3) {
            cout << "Test passed: Rooks moved properly" << endl;
        } else {
            cout << "Test failed: Rooks failed to move" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool rooktest::runTests(bool display) {
    bool success = true;
    success = success && this->movementTest(display);
    return success;
}