#include "../include/Gameboard.h"
#include "../include/Queen.h"
#include "../include/Knight.h"
#include "../include/Pawn.h"
#include "../include/Bishop.h"
#include "../include/Rook.h"
#include "../include/King.h"
#include "QueenTest.h"
#include <iostream>
using namespace std;

QueenTest::QueenTest() {
    this->_length = 3;
    this->_failMessage = "Queen test failed";
    this->_passMessage = "Queen test succeeded";
    initialiseResults();
}

bool QueenTest::movementTest(bool display) {
    // Test Queen movement
    bool success = true;

    // Create the Game board and two queens.
    Gameboard board;
    Queen whiteAQueen('W');
    Queen blackAQueen('B');
    Piece* pieces[] = {&whiteAQueen, &blackAQueen};

    // Add the queens to the Game board
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

bool QueenTest::CaptureTest(bool display) {
    // Test Queen capture
    bool success = false;

    // Initialise objects
    Gameboard board;
    Queen blackQueen('B');
    Queen whiteQueen('W');
    Knight whiteKnight('W');
    Pawn whitePawn('W');
    Bishop whiteBishop('W');
    Rook whiteRook('W');

    // Place pieces
    board.addPiece(4,4, &blackQueen);
    board.addPiece(4,0, &whiteQueen);
    board.addPiece(0,0, &whiteRook);
    board.addPiece(6,6, &whitePawn);
    board.addPiece(6,7, &whiteBishop);
    board.addPiece(7,7, &whiteKnight);

    if (display) board.visualiseTextBoard();

    // Test 1: Take white Queen (down)
    bool test1 = board.movePiece(4,4, 4,0);
    if (display) board.visualiseTextBoard();

    // Test 2: Take white Rook (left)
    bool test2 = board.movePiece(4,0, 0,0);
    if (display) board.visualiseTextBoard();

    // Test 3: Take white Pawn (diagonal)
    bool test3 = board.movePiece(0,0, 6,6);
    if (display) board.visualiseTextBoard();

    // Test 4: Take white Bishop (up)
    bool test4 = board.movePiece(6,6, 6,7);
    if (display) board.visualiseTextBoard();

    // Test 5: Take white Knight (right)
    bool test5 = board.movePiece(6,7, 7,7);
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Took white Queen (down)" << endl;
        } else {
            cout << "Test failed: Didn't take white Queen (down)" << endl;
        }

        if (test2) {
            cout << "Test passed: Took white Rook (left)" << endl;
        } else {
            cout << "Test failed: Didn't take white Rook (left)" << endl;
        }

        if (test3) {
            cout << "Test passed: Took white Pawn (diagonal)" << endl;
        } else {
            cout << "Test failed: Didn't take white Pawn (diagonal)" << endl;
        }

        if (test4) {
            cout << "Test passed: Took white Bishop (up)" << endl;
        } else {
            cout << "Test failed: Didn't take white Bishop (up)" << endl;
        }

        if (test5) {
            cout << "Test passed: Took white Knight (right)" << endl;
        } else {
            cout << "Test failed: Didn't take white Knight (right)" << endl;
        }
    }
    
    success = test1 && test2 && test3 && test4 && test5;
    return success;
}

bool QueenTest::checkTest(bool display) {
    // Test Queen can check
    bool success = false;

    // Initialise objects
    Gameboard board;
    King blackKing('B');
    Queen whiteQueenOne('W');
    Queen whiteQueenTwo('W');

    // Place pieces
    board.addPiece(0,7, &blackKing);
    board.addPiece(7,3, &whiteQueenOne);
    board.addPiece(7,6, &whiteQueenTwo);

    // Test 1: Not in check
    bool test1 = !board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test 2: Check straight
    board.movePiece(7,3, 0,3);
    if (display) board.visualiseTextBoard();
    bool test2 = board.isInCheck('B');

    // Test 3: Check diagonal
    board.movePiece(0,3, 4,3);
    if (display) board.visualiseTextBoard();
    bool test3 = board.isInCheck('B');

    // Test 4: Checkmate
    board.movePiece(4,3, 1,6);
    if (display) board.visualiseTextBoard();
    bool test4 = board.isInCheckmate('B');

    // Test 5: Stalemate
    board.movePiece(1,6, 1,0);
    if (display) board.visualiseTextBoard();
    bool test5 = board.isInStalemate('B');

    if (display) {
        if (test1) {
            cout << "Test passed: Not in check" << endl;
        } else {
            cout << "Test failed: Black in check" << endl;
        }

        if (test2) {
            cout << "Test passed: Queen checks straight" << endl;
        } else {
            cout << "Test failed: Queen doesn't check straight" << endl;
        }

        if (test3) {
            cout << "Test passed: Queen checks diagonally" << endl;
        } else {
            cout << "Test failed: Queen doesn't check diagonally" << endl;
        }

        if (test4) {
            cout << "Test passed: Checkmate" << endl;
        } else {
            cout << "Test failed: Not checkmate" << endl;
        }

        if (test5) {
            cout << "Test passed: Stalemate" << endl;
        } else {
            cout << "Test failed: Not stalemate" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5;
    return success;
}