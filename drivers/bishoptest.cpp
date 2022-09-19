#include "../include/gameboard.h"
#include "../include/bishop.h"
#include "bishoptest.h"
#include <iostream>
using namespace std;

bishoptest::bishoptest(): bishoptest(1) {}
bishoptest::bishoptest(int length) {
    this->_failMessage = "Bishop test failed";
    this->_passMessage = "Bishop test succeeded";
}

bool bishoptest::movementTest(bool display) {
    // Test bishop movement
    bool success = true;

    // Create the gameboard and two bishops
    gameboard board;
    bishop whiteCBishop = bishop();
    bishop blackCBishop = bishop('B');

    // Add the bishops to the board
    board.addPiece(0,2,&whiteCBishop);
    board.addPiece(7,2,&blackCBishop);
    piece* pieces[] = {&whiteCBishop, &blackCBishop};
    if (display) board.visualiseTextBoard();

    // Move the bishops to legal positions
    board.movePiece(0,2,1,3);
    board.movePiece(7,2,5,4);

    // Check to ensure our moves were successful
    int coords[] = {1,3, 5,4};
    bool test = board.testDriver(pieces, coords, 2);
    if (display) board.visualiseTextBoard();

    // Move the bishops to illegal positions
    board.movePiece(1,3, 1,1);
    board.movePiece(7,2, 4,6);

    // Check to ensure our nothing has happened
    bool test2 = board.testDriver(pieces, coords, 2);
    if (display) board.visualiseTextBoard();

    // Check results
    if (display) {
        if (test) {
            cout << "Test passed: Bishops moved properly" << endl;
        } else {
            cout << "Test failed: Bishops failed to move" << endl;
        }

        if (test2) {
            cout << "Test passed: Bishops didn't move" << endl;
        } else {
            cout << "Test failed: Bishops made illegal moves" << endl;
        }
    }

    success = test && test2;
    return success;
}

bool bishoptest::runTests(bool display) {
    bool success = true;
    success = success && this->movementTest(display);
    return success;
}

string bishoptest::getMessage(bool pass) {
    if (pass) return _passMessage;
    else return _failMessage;
}