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
            cout << "Test passed: Rooks didn't make illegal moves" << endl;
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

bool rooktest::firstMovementTest(bool display) {
    // Check for weird moves- outside the board, into own position, etc
    bool success;

    // Create the game board and two rooks
    gameboard board;
    rook white_a_rook = rook('W');
    rook black_a_rook = rook('B');

    // Add the rooks to the game board
    board.addPiece(0,0,&white_a_rook);
    board.addPiece(7,0,&black_a_rook);
    
    if (display) board.visualiseTextBoard();

    // Move the rooks to illegal positions
    board.movePiece(0,0, 1,1);
    board.movePiece(7,0, 4,6);

    if (display) board.visualiseTextBoard();

    // Move the rooks to legal positions
    board.movePiece(0,0, 0,3);
    board.movePiece(7,0, 7,7);

    // Move the rooks to their own positions
    board.movePiece(0,3, 0,3);
    board.movePiece(7,7, 7,7);

    // Move the rooks outside the game board
    board.movePiece(0,3, -1,3);
    board.movePiece(7,7, 7,8);
    board.movePiece(0,32, 1,3);
    board.movePiece(-7,7, 8,7);

    if (display) board.visualiseTextBoard();

    // Test: Both rooks uncaptured
    bool test1 = (!white_a_rook.captured() && !black_a_rook.captured());

    // Test: rooks in correct positions
    piece* pieces[] = {&white_a_rook, &black_a_rook};
    int coords[] = {0,3, 7,7};
    bool test2 = (board.testDriver(pieces, coords, 2));

    if (display) {
        if (test1) {
            cout << "Test passed: Neither rook captured" << endl;
        } else {
            cout << "Test failed: Rook captured" << endl;
        }
        if (test2) {
            cout << "Test passed: All pieces in correct position" << endl;
        } else {
            cout << "Test failed: Pieces in incorrect position" << endl;
        }
    }

    success = test1 && test2;
    return success;
}

bool rooktest::runTests(bool display) {
    bool success = true;
    success = success && this->movementTest(display);
    success = success && this->firstMovementTest(display);
    return success;
}