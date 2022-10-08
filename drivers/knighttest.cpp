#include "../include/gameboard.h"
#include "../include/knight.h"
#include "../include/king.h"
#include "../include/pawn.h"
#include "knighttest.h"
#include <iostream>
using namespace std;

knighttest::knighttest() {
    this->_length = 3;
    this->_failMessage = "Knight test failed";
    this->_passMessage = "Knight test succeeded";
    initialiseResults();
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
    bool success = false;

    // Initialise objects
    gameboard board;
    pawn whitePawnOne('W');
    pawn whitePawnTwo('W');
    pawn whitePawnThree('W');
    pawn whitePawnFour('W');
    pawn whitePawnFive('W');
    knight blackKnight('B');

    // Add pieces to board
    board.addPiece(3,3, &blackKnight);
    board.addPiece(2,1, &whitePawnOne);
    board.addPiece(4,1, &whitePawnTwo);
    board.addPiece(4,5, &whitePawnThree);
    board.addPiece(1,4, &whitePawnFour);
    board.addPiece(1,3, &whitePawnFive);

    // Test 1: Take pawn 1
    if (display) board.visualiseTextBoard();
    board.movePiece(3,3, 2,1);
    if (display) board.visualiseTextBoard();
    board.movePiece(2,1, 3,3);
    bool test1 = whitePawnOne.captured();

    // Test 2: Take pawn 2
    board.movePiece(3,3, 4,1);
    if (display) board.visualiseTextBoard();
    board.movePiece(4,1, 3,3);
    bool test2 = whitePawnTwo.captured();

    // Test 3: Take pawn 3
    board.movePiece(3,3, 4,5);
    if (display) board.visualiseTextBoard();
    board.movePiece(4,5, 3,3);
    bool test3 = whitePawnThree.captured();

    // Test 4: Take pawn 4
    board.movePiece(3,3, 1,4);
    if (display) board.visualiseTextBoard();
    board.movePiece(1,4, 3,3);
    bool test4 = whitePawnFour.captured();

    // Test 5: Don't take pawn 5
    if (display) board.visualiseTextBoard();
    bool test5 = !board.movePiece(3,3, 1,3);

    if (display) {
        if (test1) {
            cout << "Test passed: First pawn taken" << endl;
        } else {
            cout << "Test failed: Pawn not taken" << endl;
        }

        if (test2) {
            cout << "Test passed: Second pawn taken" << endl;
        } else {
            cout << "Test failed: Pawn not taken" << endl;
        }

        if (test3) {
            cout << "Test passed: Third pawn taken" << endl;
        } else {
            cout << "Test failed: Pawn not taken" << endl;
        }

        if (test4) {
            cout << "Test passed: Fourth pawn taken" << endl;
        } else {
            cout << "Test failed: Pawn not taken" << endl;
        }

        if (test5) {
            cout << "Test passed: Pawn not taken" << endl;
        } else {
            cout << "Test failed: Fifth pawn taken" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5;
    return success;
}

bool knighttest::checkTest(bool display) {
    bool success = false;

    // Initialise objects
    gameboard board;
    king blackKing('B');
    king whiteKing('W');
    knight knightOne('B');
    knight knightTwo('B');

    // Place pieces
    board.addPiece(0,0, &whiteKing);
    board.addPiece(0,2, &blackKing);
    board.addPiece(3,3, &knightOne);
    board.addPiece(3,4, &knightTwo);

    // Test 1: Not in check
    bool test1 = !board.isInCheck('W');
    if (display) board.visualiseTextBoard();

    // Test 2: Check
    board.movePiece(3,3, 1,2);
    bool test2 = board.isInCheck('W');
    if (display) board.visualiseTextBoard();

    // Test 3: Checkmate
    board.movePiece(3,4, 2,2);
    bool test3 = board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 4: Stalemate
    board.movePiece(1,2, 3,3);
    bool test4 = board.isInStalemate('W');
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Not in check" << endl;
        } else {
            cout << "Test failed: White in check" << endl;
        }

        if (test2) {
            cout << "Test passed: King in check" << endl;
        } else {
            cout << "Test failed: Not in check" << endl;
        }

        if (test3) {
            cout << "Test passed: Checkmate" << endl;
        } else {
            cout << "Test failed: Not in checkmate" << endl;
        }

        if (test4) {
            cout << "Test passed: Stalemate" << endl;
        } else {
            cout << "Test failed: Not in stalemate" << endl;
        }
    }

    return test1 && test2 && test3 && test4;
    return success;
}