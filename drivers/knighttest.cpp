#include "../include/gameboard.h"
#include "../include/knight.h"
#include "knighttest.h"
#include <iostream>
using namespace std;

knighttest::knighttest(): knighttest(1) {}
knighttest::knighttest(int length) {
    this->_failMessage = "Knight test failed";
    this->_passMessage = "Knight test succeeded";
}

bool knighttest::movementTest(bool display) {
    // Test knight movement
    bool success = true;

    // Create the game board and two knights.
    gameboard board;
    knight whiteAknight = knight();
    knight blackAknight = knight('B');
    piece* pieces[] = {&whiteAknight, &blackAknight};

    // Add the knights to the game board
    board.addPiece(0,0,&whiteAknight);
    board.addPiece(7,0,&blackAknight);
    
    if (display) board.visualiseTextBoard();

    // Move the knights to illegal positions
    board.movePiece(0,0, 2,2);
    board.movePiece(7,0, 4,0);

    // Check to ensure our nothing has happened
    if (display) board.visualiseTextBoard();
    int coords[] = {0,0, 7,0};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the knights to legal positions 
    board.movePiece(0,0, 1,2);
    board.movePiece(7,0, 5,1);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords2[] = {1,2, 5,1};
    bool test2 = board.testDriver(pieces, coords2, 2);

    // Move the knights to legal positions 
    board.movePiece(1,2, 3,1);
    board.movePiece(5,1, 7,2);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords3[] = {3,1, 7,2};
    bool test3 = board.testDriver(pieces, coords3, 2);

    if (display) {
        if (test1) {
            cout << "Test passed: Knights didn't move" << endl;
        } else {
            cout << "Test failed: Knights made illegal moves" << endl;
        }

        if (test2) {
            cout << "Test passed: Knights moved properly" << endl;
        } else {
            cout << "Test failed: Knights failed to move" << endl;
        }

        if (test3) {
            cout << "Test passed: Knights moved properly" << endl;
        } else {
            cout << "Test failed: Knights failed to move" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool knighttest::runTests(bool display) {
    bool success = true;
    success = success && this->movementTest(display);
    return success;
}