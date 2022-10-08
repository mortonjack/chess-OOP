#include "../include/gameboard.h"
#include "../include/rook.h"
#include "../include/king.h"
#include "../include/knight.h"
#include "../include/bishop.h"
#include "rooktest.h"
#include <iostream>
using namespace std;

rooktest::rooktest() {
    this->_length = 3;
    this->_failMessage = "Rook test failed";
    this->_passMessage = "Rook test succeeded";
    initialiseResults();
}

bool rooktest::movementTest(bool display) {
    // Test rook movement
    bool success = true;

    // Create the gameboard and two rooks
    gameboard board;
    rook whiteARook('W');
    rook blackARook('B');

    // Add the rooks to the board
    board.addPiece(0,0,&whiteARook);
    board.addPiece(0,7,&blackARook);
    piece* pieces[] = {&whiteARook, &blackARook};
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

    // Move rooks outside the gameboard
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
            cout << "Test passed: Pieces can't move outside the gameboard" << endl;
        } else {
            cout << "Test failed: Pieces can move outside the gameboard" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5;
    return success;
}

bool rooktest::captureTest(bool display) {
    bool success = false;

    // Initialise objects
    gameboard board;
    rook whiteRook('W');
    bishop whiteBishop('W');
    rook blackRookOne('B');
    rook blackRookTwo('B');
    knight blackKnight('B');
    bishop blackBishopOne('B');
    bishop blackBishopTwo('B');

    // Add pieces to board
    board.addPiece(4,6, &whiteBishop);
    board.addPiece(4,4, &whiteRook);
    board.addPiece(2,4, &blackRookOne);
    board.addPiece(6,4, &blackBishopOne);
    board.addPiece(6,0, &blackKnight);
    board.addPiece(6,7, &blackRookTwo);
    board.addPiece(4,7, &blackBishopTwo);

    // Test 1: Can't take bishop through friendly piece
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

    // Test 4: Now takes bishop
    bool test4 = board.movePiece(6,7, 4,7);
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Can't take bishop through friendly piece" << endl;
        } else {
            cout << "Test failed: Takes bishop through friendly piece" << endl;
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
            cout << "Test passed: Now takes bishop" << endl;
        } else {
            cout << "Test failed: Doesn't take bishop" << endl;
        }
    }
    
    success = test1 && test2 && test3 && test4;
    return success;
}

bool rooktest::checkTest(bool display) {
    bool success = false;

    // Initialise objects
    gameboard board;
    king blackKing('B');
    rook rookOne('W');
    rook rookTwo('W');

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