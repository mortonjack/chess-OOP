#include "../include/gameboard.h"
#include "../include/knight.h"
#include "knighttest.h"
#include <iostream>
using namespace std;

knighttest::knighttest() {
    this->_length = 3;
    this->_failMessage = "Knight test failed";
    this->_passMessage = "Knight test succeeded";
}

bool knighttest::movementTest(bool display) {
    // Test knight movement
    bool success = true;

    // Create the game board and two knights.
    gameboard board;
    knight whiteAknight('W');
    knight blackAknight('B');
    piece* pieces[] = {&whiteAknight, &blackAknight};

    // Add the knights to the game board
    board.addPiece(0,0,&whiteAknight);
    board.addPiece(0,7,&blackAknight);
    
    if (display) board.visualiseTextBoard();

    // Move the knights to illegal positions
    board.movePiece(0,0, 2,2);
    board.movePiece(0,7, 0,4);

    // Check to ensure our nothing has happened
    if (display) board.visualiseTextBoard();
    int coords[] = {0,0, 0,7};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the knights to legal positions 
    board.movePiece(0,0, 2,1);
    board.movePiece(0,7, 1,5);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords2[] = {2,1, 1,5};
    bool test2 = board.testDriver(pieces, coords2, 2);

    // Move the knights to legal positions 
    board.movePiece(2,1, 1,3);
    board.movePiece(1,5, 2,7);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords3[] = {1,3, 2,7};
    bool test3 = board.testDriver(pieces, coords3, 2);

    if (display) {
        if (test1) {
            cout << "Test passed: Knights didn't make illegal moves" << endl;
        } else {
            cout << "Test failed: Knights made illegal move" << endl;
        }

        if (test2) {
            cout << "Test passed: Knights moved properly" << endl;
        } else {
            cout << "Test failed: Knights failed to move properly" << endl;
        }

        if (test3) {
            cout << "Test passed: Knights moved properly" << endl;
        } else {
            cout << "Test failed: Knights failed to move properly" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool knighttest::captureTest(bool display) {
    return true;
}

bool knighttest::checkTest(bool display) {
    return true;
}