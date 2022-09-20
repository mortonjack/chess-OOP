#include "../include/gameboard.h"
#include "../include/king.h"
#include "kingtest.h"
#include <iostream>
using namespace std;

kingtest::kingtest(): kingtest(1) {}
kingtest::kingtest(int length) {
    this->_failMessage = "King test failed";
    this->_passMessage = "King test succeeded";
}

bool kingtest::movementTest(bool display) {
    // Test king movement
    bool success = true;

    // Create the game board a white king.
    gameboard board;
    king testKing = king();

    // Add the king to the game board
    board.addPiece(3,3,&testKing);
    if (display) board.visualiseTextBoard();

    // Test all valid move directions- move king in a circle
    board.movePiece(3,3, 3,2);
    board.movePiece(3,2, 2,1);
    board.movePiece(2,1, 1,1);
    board.movePiece(1,1, 0,2);
    board.movePiece(0,2, 0,3);
    if (display) board.visualiseTextBoard();
    
    // Run first test
    piece* pieces[1] = {&testKing};
    int coords[2] = {0,3};
    bool test1 = board.testDriver(pieces, coords, 1);

    // Continue to move king
    board.movePiece(0,3, 1,4);
    board.movePiece(1,4, 2,4);
    board.movePiece(2,4, 3,3);
    if (display) board.visualiseTextBoard();
    
    // Run second test
    coords[0] = 3;
    coords[1] = 3;
    bool test2 = board.testDriver(pieces, coords, 1);

    // Test invalid move directions
    board.movePiece(3,3, 1,3);
    board.movePiece(3,3, 2,1);
    board.movePiece(3,3, 5,4);

    // Run third test
    bool test3 = board.testDriver(pieces, coords, 1);
    if (display) board.visualiseTextBoard();

    // Run tests
    if (display) {
        if (test1) {
            cout << "Test passed: King moved halfway around the circle" << endl;
        } else {
            cout << "Test failed: King failed to move halfway around the circle" << endl;
        }

        if (test2) {
            cout << "Test passed: King moved in all 8 directions" << endl;
        } else {
            cout << "Test failed: King failed to move in all 8 directions" << endl;
        }

        if (test3) {
            cout << "Test passed: King didn't make illegal moves" << endl;
        } else {
            cout << "Test failed: King made illegal move" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool kingtest::runTests(bool display) {
    bool success = true;
    success = success && this->movementTest(display);
    return success;
}