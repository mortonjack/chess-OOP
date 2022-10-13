#include "../include/Gameboard.h"
#include "../include/Rook.h"
#include "../include/King.h"
#include "../include/Knight.h"
#include "../include/Bishop.h"
#include "RookTest.h"
#include <iostream>
using namespace std;

RookTest::RookTest() {
    this->_length = 3;
    this->_failMessage = "Rook test failed";
    this->_passMessage = "Rook test succeeded";
    initialiseResults();
}

bool RookTest::movementTest(bool display) {
    // Test Rook movement
    bool success = true;

    // Create the Gameboard and two rooks
    Gameboard board;
    Rook whiteARook('W');
    Rook blackARook('B');

    // Add the rooks to the board
    board.addPiece(0,0,&whiteARook);
    board.addPiece(0,7,&blackARook);
    Piece* pieces[] = {&whiteARook, &blackARook};
    if (display) board.visualiseTextBoard();

    // Move the rooks to legal positions
    board.movePiece(0,0,0,3);
    board.movePiece(0,7,0,4);
    
    // Check to ensure the moves were made
    if (display) board.visualiseTextBoard();
    int coords[] = {0,3, 0,4};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the rooks to illegal positions
    board.movePiece(0,3, 1,1);
    board.movePiece(0,4, 2,6);

    // Check to ensure our nothing has happened
    if (display) board.visualiseTextBoard();
    bool test2 = board.testDriver(pieces, coords, 2);

    // Move the rooks to legal positions
    board.movePiece(0,3, 3,3);
    board.movePiece(0,4, 0,2);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords2[] = {3,3, 0,2};
    bool test3 = board.testDriver(pieces, coords2, 2);

    // Move rooks to own positions
    bool test4 = !board.movePiece(3,3, 3,3) && !board.movePiece(0,2, 0,2);

    // Move rooks outside the Gameboard
    bool test5 = !board.movePiece(3,3, 3,8) && !board.movePiece(0,2, -3,4);
    if (display) board.visualiseTextBoard();

    // Check results
    if (display) {
        if (test1) {
            cout << "Test passed: Rooks moved properly" << endl;
        } else {
            cout << "Test failed: Rooks failed to move" << endl;
        }

        if (test2) {
            cout << "Test passed: Rooks didn't make illegal moves" << endl;
        } else {
            cout << "Test failed: Rooks made illegal moves" << endl;
        }

        if (test3) {
            cout << "Test passed: Rooks moved properly" << endl;
        } else {
            cout << "Test failed: Rooks failed to move" << endl;
        }

        if (test4) {
            cout << "Test passed: Pieces can't move to own position" << endl;
        } else {
            cout << "Test failed: Pieces can move to their own position" << endl;
        }

        if (test5) {
            cout << "Test passed: Pieces can't move outside the Gameboard" << endl;
        } else {
            cout << "Test failed: Pieces can move outside the Gameboard" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5;
    return success;
}

bool RookTest::CaptureTest(bool display) {
    bool success = false;

    // Initialise objects
    Gameboard board;
    Rook whiteRook('W');
    Bishop whiteBishop('W');
    Rook blackRookOne('B');
    Rook blackRookTwo('B');
    Knight blackKnight('B');
    Bishop blackBishopOne('B');
    Bishop blackBishopTwo('B');

    // Add pieces to board
    board.addPiece(4,6, &whiteBishop);
    board.addPiece(4,4, &whiteRook);
    board.addPiece(2,4, &blackRookOne);
    board.addPiece(6,4, &blackBishopOne);
    board.addPiece(6,0, &blackKnight);
    board.addPiece(6,7, &blackRookTwo);
    board.addPiece(4,7, &blackBishopTwo);

    // Test 1: Can't take Bishop through friendly Piece
    bool test1 = !board.movePiece(4,4, 4,7);
    if (display) board.visualiseTextBoard();

    // Test 2: Takes across the rank
    board.movePiece(4,4, 2,4);
    if (display) board.visualiseTextBoard();
    bool test2 = board.movePiece(2,4, 6,4) && blackRookOne.captured();
    if (display) board.visualiseTextBoard();

    // Test 3: Takes across the file
    board.movePiece(6,4, 6,0);
    if (display) board.visualiseTextBoard();
    board.movePiece(6,0, 6,7);
    if (display) board.visualiseTextBoard();
    bool test3 = blackKnight.captured() && blackRookTwo.captured();

    // Test 4: Now takes Bishop
    bool test4 = board.movePiece(6,7, 4,7);
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Can't take Bishop through friendly Piece" << endl;
        } else {
            cout << "Test failed: Takes Bishop through friendly Piece" << endl;
        }

        if (test2) {
            cout << "Test passed: Takes across rank" << endl;
        } else {
            cout << "Test failed: Doesn't take across rank" << endl;
        }

        if (test3) {
            cout << "Test passed: Takes across file" << endl;
        } else {
            cout << "Test failed: Doesn't take across file" << endl;
        }

        if (test4) {
            cout << "Test passed: Now takes Bishop" << endl;
        } else {
            cout << "Test failed: Doesn't take Bishop" << endl;
        }
    }
    
    success = test1 && test2 && test3 && test4;
    return success;
}

bool RookTest::checkTest(bool display) {
    bool success = false;

    // Initialise objects
    Gameboard board;
    King blackKing('B');
    Rook rookOne('W');
    Rook rookTwo('W');

    // Place pieces
    board.addPiece(1,1, &blackKing);
    board.addPiece(2,7, &rookOne);
    board.addPiece(7,2, &rookTwo);

    // Test 1: Rooks control rank and file
    bool test1 = !board.movePiece(1,1, 1,2) && !board.movePiece(1,1, 2,1);
    if (display) board.visualiseTextBoard();

    // Test 2: Rooks check across file
    bool test2 = board.movePiece(2,7, 1,7) && board.isInCheck('B');
    test2 = test2 && board.movePiece(1,1, 0,1) && !board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test 3: Rooks check across rank
    bool test3 = board.movePiece(7,2, 7,1) && board.isInCheck('B');
    test3 = test3 && board.movePiece(0,1, 0,0) && !board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test 4: Stalemate
    bool test4 = board.isInStalemate('B');
    board.movePiece(7,1, 7,2);
    if (display) board.visualiseTextBoard();

    // Test 5: Checkmate
    board.movePiece(7,2, 0,2);
    bool test5 = board.isInCheckmate('B');
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Rooks control rank and file" << endl;
        } else {
            cout << "Test failed: Rooks don't control rank and file" << endl;
        }

        if (test2) {
            cout << "Test passed: Rooks check across file" << endl;
        } else {
            cout << "Test failed: Rooks don't check across file" << endl;
        }

        if (test3) {
            cout << "Test passed: Rooks check across rank" << endl;
        } else {
            cout << "Test failed: Rooks don't check across rank" << endl;
        }

        if (test4) {
            cout << "Test passed: Stalemate" << endl;
        } else {
            cout << "Test failed: Not in stalemate" << endl;
        }

        if (test5) {
            cout << "Test passed: Checkmate" << endl;
        } else {
            cout << "Test failed: Not in checkmate" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5;
    return success;
}