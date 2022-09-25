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

bool pawntest::captureTest(bool display) {
    // Test pawn movement with capturing
    bool success = true;

    // Create the game board and two pawns.
    gameboard board;
    pawn whiteDpawn = pawn();
    pawn whiteEpawn = pawn();
    pawn blackDpawn = pawn('B');
    pawn blackEpawn = pawn('B');
    piece* pieces[] = {&whiteDpawn, &whiteEpawn, &blackDpawn, &blackEpawn};

    // Add the pawns to the game board
    board.addPiece(3,1, &whiteDpawn);
    board.addPiece(4,1, &whiteEpawn);
    board.addPiece(3,6, &blackDpawn);
    board.addPiece(4,6, &blackEpawn);
    
    if (display) board.visualiseTextBoard();

    // Play the opening moves for the Pirc defense: 1. e4 e5 2. d4 d6
    board.movePiece(4,1, 4,3);
    board.movePiece(4,6, 4,4);
    board.movePiece(3,1, 3,3);
    board.movePiece(3,6, 3,5);

    // Check to ensure this opening was successful
    if (display) board.visualiseTextBoard();
    int coords[] = {3,3, 4,3, 3,5, 4,4};
    bool test1 = board.testDriver(pieces, coords, 4);

    // Try to capture my moving into and through pawns
    board.movePiece(4,3, 4,4);
    board.movePiece(4,3, 4,5);
    board.movePiece(4,4, 4,3);
    board.movePiece(4,4, 4,2);

    // Check to ensure these illegal moves were unsuccessful
    if (display) board.visualiseTextBoard();
    int coords2[] = {3,3, 4,3, 3,5, 4,4};
    bool test2 = board.testDriver(pieces, coords2, 4);
    
    // Capture black's E pawn with white's D pawn, then recapture with black's D pawn 3. dxe5 dxe5
    board.movePiece(3,3, 4,4);
    board.movePiece(3,5, 4,4);

    // Check to ensure the captures were successful
    piece* remainingPieces[] = {&whiteEpawn, &blackDpawn};
    int coords3[] = {4,3, 4,4};
    if (display) board.visualiseTextBoard();
    bool test3 = board.testDriver(remainingPieces, coords3, 2);

    if (display) {
        if (test1) {
            cout << "Test passed: Pawns moved up one and/or two tiles" << endl;
        } else {
            cout << "Test failed: Pawns didn't move up one and/or two tiles" << endl;
        }

        if (test2) {
            cout << "Test passed: Pawns did not move through each other or capture forwards" << endl;
        } else {
            cout << "Test failed: Pawns moved through each other or captured forwards" << endl;
        }

        if (test3) {
            cout << "Test passed: Pawns captured diagonally" << endl;
        } else {
            cout << "Test failed: Pawns did not capture diagonally" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool pawntest::runTests(bool display) {
    bool success = true;
    success = success && this->movementTest(display);
    success = success && this->captureTest(display);
    return success;
}