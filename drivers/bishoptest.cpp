#include "../include/gameboard.h"
#include "../include/bishop.h"
#include "bishoptest.h"
#include <iostream>
using namespace std;

bishoptest::bishoptest() {
    this->_length = 3;
    this->_failMessage = "Bishop test failed";
    this->_passMessage = "Bishop test succeeded";
}

bool bishoptest::movementTest(bool display) {
    // Test bishop movement
    bool success = true;

    // Create the gameboard and two bishops
    gameboard board;
    bishop whiteCBishop('W');
    bishop blackCBishop('B');

    // Add the bishops to the board
    board.addPiece(2,0,&whiteCBishop);
    board.addPiece(2,7,&blackCBishop);
    piece* pieces[] = {&whiteCBishop, &blackCBishop};
    if (display) board.visualiseTextBoard();

    // Move the bishops to legal positions
    board.movePiece(2,0, 3,1);
    board.movePiece(2,7, 4,5);

    // Check to ensure our moves were successful
    int coords[] = {3,1, 4,5};
    bool test = board.testDriver(pieces, coords, 2);
    if (display) board.visualiseTextBoard();

    // Move the bishops to illegal positions
    board.movePiece(3,1, 1,1);
    board.movePiece(2,7, 6,4);

    // Check to ensure our nothing has happened
    bool test2 = board.testDriver(pieces, coords, 2);
    if (display) board.visualiseTextBoard();

    // Check results
    if (display) {
        if (test) {
            cout << "Test passed: Bishops moved properly" << endl;
        } else {
            cout << "Test failed: Bishops failed to move properly" << endl;
        }

        if (test2) {
            cout << "Test passed: Bishops didn't make illegal moves" << endl;
        } else {
            cout << "Test failed: Bishops made illegal move" << endl;
        }
    }

    success = test && test2;
    return success;
}

bool bishoptest::captureTest(bool display) {
    return true;
}

bool bishoptest::checkTest(bool display) {
    return true;
}