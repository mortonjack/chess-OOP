#include "../include/gameboard.h"
#include "../include/pawn.h"
#include "pawntest.h"
#include <iostream>
using namespace std;

pawntest::pawntest(): pawntest(1) {}
pawntest::pawntest(int length) {
    this->_failMessage = "Pawn test failed";
    this->_passMessage = "Pawn test succeeded";
}

bool pawntest::movementTest(bool display) {
    // Test pawn movement
    bool success = true;

    // Create the game board and two pawns.
    gameboard board;
    pawn whiteCpawn = pawn();
    pawn blackFPawn = pawn('B');
    piece* pieces[] = {&whiteCpawn, &blackFPawn};

    // Add the pawns to the game board
    board.addPiece(5,1, &whiteCpawn);
    board.addPiece(2,6, &blackFPawn);
    
    if (display) board.visualiseTextBoard();

    // Move the pawns to illegal positions
    board.movePiece(2,6, 2,7);
    board.movePiece(5,1, 5,0);
    board.movePiece(2,6, 3,6);
    board.movePiece(5,1, 5,4);

    // Check to ensure nothing has happened
    if (display) board.visualiseTextBoard();
    int coords[] = {5,1, 2,6};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the pawns to legal positions 
    board.movePiece(2,6, 2,4);
    board.movePiece(5,1, 5,2);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords2[] = {5,2, 2,4};
    bool test2 = board.testDriver(pieces, coords2, 2);

    // Move the pawns to illegal positions
    board.movePiece(2,4, 2,2);
    board.movePiece(5,2, 5,4);

    // Check to ensure nothing has happened
    if (display) board.visualiseTextBoard();
    bool test3 = board.testDriver(pieces, coords2, 2);

    // Move the pawns to legal positions
    board.movePiece(2,4, 2,3);
    board.movePiece(5,2, 5,3);
    
    // Check to ensure the moves succeeded
    int coords3[] = {5,3, 2,3};
    bool test4 = board.testDriver(pieces, coords3, 2);

    if (display) {
        if (test1) {
            cout << "Test passed: Pawns didn't move backwards, sideways, and/or up 3 tiles" << endl;
        } else {
            cout << "Test failed: Pawns moved backwards, sideways, and/or up 3 tiles" << endl;
        }

        if (test2) {
            cout << "Test passed: Pawns moved up one and/or two tiles" << endl;
        } else {
            cout << "Test failed: Pawns failed to move up one and/or two tiles" << endl;
        }

        if (test3) {
            cout << "Test passed: Pawns didn't move up two tiles on the second move" << endl;
        } else {
            cout << "Test failed: Pawns moved up two tiles on second move" << endl;
        }

        if (test4) {
            cout << "Test passed: Pawns moved up one tile" << endl;
        } else {
            cout << "Test failed: Pawns didn't move up one tile" << endl;
        }
    }

    success = test1 && test2 && test3 && test4;
    return success;
}

bool pawntest::runTests(bool display) {
    bool success = true;
    success = success && this->movementTest(display);
    return success;
}