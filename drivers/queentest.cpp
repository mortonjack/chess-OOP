#include "../include/gameboard.h"
#include "../include/queen.h"
#include "queentest.h"
#include <iostream>
using namespace std;

queentest::queentest(): queentest(1) {}
queentest::queentest(int length) {
    this->_failMessage = "Queen test failed";
    this->_passMessage = "Queen test succeeded";
}

bool queentest::movementTest(bool display) {
    // Test queen movement
    bool success = true;

    // Create the game board and two queens.
    gameboard board;
    queen whiteAQueen = queen();
    queen blackAQueen = queen('B');
    piece* pieces[] = {&whiteAQueen, &blackAQueen};

    // Add the queens to the game board
    board.addPiece(0,0,&whiteAQueen);
    board.addPiece(0,7,&blackAQueen);
    if (display) board.visualiseTextBoard();

    // Move the queens to illegal positions
    board.movePiece(0,0, 2,1);
    board.movePiece(0,7, 6,4);

    // Check to ensure our nothing has happened
    if (display) board.visualiseTextBoard();
    int coords[] = {0,0, 0,7};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the queens to legal positions (straight)
    board.movePiece(0,0, 0,3);
    board.movePiece(0,7, 7,7);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords2[] = {0,3, 7,7};
    bool test2 = board.testDriver(pieces, coords2, 2);

    // Move the queens to legal positions (diagonal)
    board.movePiece(0,3, 3,0);
    board.movePiece(7,7, 3,3);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords3[] = {3,0, 3,3};
    bool test3 = board.testDriver(pieces, coords3, 2);

    if (display) {
        if (test1) {
            cout << "Test passed: Queens didn't move to illegal positions" << endl;
        } else {
            cout << "Test failed: Queens moved to illegal positions" << endl;
        }

        if (test2) {
            cout << "Test passed: Queens successfuly moved horizontally and vertically" << endl;
        } else {
            cout << "Test failed: Queens failed to move horizontally or vertically" << endl;
        }

        if (test3) {
            cout << "Test passed: Queens successfully moved diagonally" << endl;
        } else {
            cout << "Test failed: Queens failed to move diagonally" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool queentest::runTests(bool display) {
    bool success = true;
    success = success && this->movementTest(display);
    return success;
}