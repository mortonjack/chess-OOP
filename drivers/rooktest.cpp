#include "../include/gameboard.h"
#include "../include/rook.h"
#include "rooktest.h"
#include <iostream>
using namespace std;

rooktest::rooktest() {
    this->_length = 3;
    this->_failMessage = "Rook test failed";
    this->_passMessage = "Rook test succeeded";
    initialiseResults();
}

bool rooktest::movementTest(bool display) {
    // Test rook movement
    bool success = true;

    // Create the gameboard and two rooks
    gameboard board;
    rook whiteARook('W');
    rook blackARook('B');

    // Add the rooks to the board
    board.addPiece(0,0,&whiteARook);
    board.addPiece(0,7,&blackARook);
    piece* pieces[] = {&whiteARook, &blackARook};
    if (display) board.visualiseTextBoard();

    // Move the rooks to legal positions
    board.movePiece(0,0,0,3);
    board.movePiece(0,7,0,4);
    
    // Check to ensure the moves were made
    if (display) board.visualiseTextBoard();
    int coords[] = {0,3, 0,4};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the rooks to illegal positions
    board.movePiece(0,3, 1,1);
    board.movePiece(0,4, 2,6);

    // Check to ensure our nothing has happened
    if (display) board.visualiseTextBoard();
    bool test2 = board.testDriver(pieces, coords, 2);

    // Move the rooks to legal positions
    board.movePiece(0,3, 3,3);
    board.movePiece(0,4, 0,2);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords2[] = {3,3, 0,2};
    bool test3 = board.testDriver(pieces, coords2, 2);

    // Move rooks to own positions
    bool test4 = !board.movePiece(3,3, 3,3) && !board.movePiece(0,2, 0,2);

    // Move rooks outside the gameboard
    bool test5 = !board.movePiece(3,3, 3,8) && !board.movePiece(0,2, -3,4);
    if (display) board.visualiseTextBoard();

    // Check results
    if (display) {
        if (test1) {
            cout << "Test passed: Rooks moved properly" << endl;
        } else {
            cout << "Test failed: Rooks failed to move" << endl;
        }

        if (test2) {
            cout << "Test passed: Rooks didn't make illegal moves" << endl;
        } else {
            cout << "Test failed: Rooks made illegal moves" << endl;
        }

        if (test3) {
            cout << "Test passed: Rooks moved properly" << endl;
        } else {
            cout << "Test failed: Rooks failed to move" << endl;
        }

        if (test4) {
            cout << "Test passed: Pieces can't move to own position" << endl;
        } else {
            cout << "Test failed: Pieces can move to their own position" << endl;
        }

        if (test5) {
            cout << "Test passed: Pieces can't move outside the gameboard" << endl;
        } else {
            cout << "Test failed: Pieces can move outside the gameboard" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5;
    return success;
}

bool rooktest::captureTest(bool display) {
    return true;
}

bool rooktest::checkTest(bool display) {
    return true;
}