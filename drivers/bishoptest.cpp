#include "../include/gameboard.h"
#include "../include/bishop.h"
#include "../include/knight.h"
#include "../include/pawn.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include "../include/king.h"
#include "bishoptest.h"
#include <iostream>
using namespace std;

bishoptest::bishoptest() {
    this->_length = 3;
    this->_failMessage = "Bishop test failed";
    this->_passMessage = "Bishop test succeeded";
    initialiseResults();
}

bool bishoptest::movementTest(bool display) {
    // Test bishop movement
    bool success = true;

    // Create the gameboard and two bishops
    gameboard board;
    bishop whiteCBishop('W');
    bishop blackCBishop('B');

    // Add the bishops to the board
    board.addPiece(2,0,&whiteCBishop);
    board.addPiece(2,7,&blackCBishop);
    piece* pieces[] = {&whiteCBishop, &blackCBishop};
    if (display) board.visualiseTextBoard();

    // Move the bishops to legal positions
    board.movePiece(2,0, 3,1);
    board.movePiece(2,7, 4,5);

    // Check to ensure our moves were successful
    int coords[] = {3,1, 4,5};
    bool test = board.testDriver(pieces, coords, 2);
    if (display) board.visualiseTextBoard();

    // Move the bishops to illegal positions
    board.movePiece(3,1, 1,1);
    board.movePiece(2,7, 6,4);

    // Check to ensure our nothing has happened
    bool test2 = board.testDriver(pieces, coords, 2);
    if (display) board.visualiseTextBoard();

    // Check results
    if (display) {
        if (test) {
            cout << "Test passed: Bishops moved properly" << endl;
        } else {
            cout << "Test failed: Bishops failed to move properly" << endl;
        }

        if (test2) {
            cout << "Test passed: Bishops didn't make illegal moves" << endl;
        } else {
            cout << "Test failed: Bishops made illegal move" << endl;
        }
    }

    success = test && test2;
    return success;
}

bool bishoptest::captureTest(bool display) {
    bool success = false;

    // Initialise objects
    gameboard board;
    bishop blackBishop('B');
    bishop whiteBishop('W');
    knight whiteKnight('W');
    pawn whitePawn('W');
    rook whiteRook('W');
    queen whiteQueen('W');

    // Set up board
    board.addPiece(4,5, &blackBishop);
    board.addPiece(2,3, &whiteBishop);
    board.addPiece(4,1, &whiteKnight);
    board.addPiece(3,0, &whitePawn);
    board.addPiece(1,2, &whiteRook);
    board.addPiece(6,7, &whiteQueen);

    // Test 1: Bishop can't take straight
    bool test1 = !board.movePiece(4,5, 4,1);
    if (display) board.visualiseTextBoard();

    // Test 2: Bishop take bishop
    bool test2 = board.movePiece(4,5, 2,3) && whiteBishop.captured();
    if (display) board.visualiseTextBoard();

    // Test 3: Bishop take knight
    bool test3 = board.movePiece(2,3, 4,1) && whiteKnight.captured();
    if (display) board.visualiseTextBoard();

    // Test 4: Bishop take pawn
    bool test4 = board.movePiece(4,1, 3,0) && whitePawn.captured();
    if (display) board.visualiseTextBoard();

    // Test 5: Bishop take rook
    bool test5 = board.movePiece(3,0, 1,2) && whiteRook.captured();
    if (display) board.visualiseTextBoard();

    // Test 6: Bishop take queen
    bool test6 = board.movePiece(1,2, 6,7) && whiteQueen.captured();
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Bishop can't take straight" << endl;
        } else {
            cout << "Test failed: Bishop takes straight" << endl;
        }

        if (test2) {
            cout << "Test passed: Bishop takes bishop" << endl;
        } else {
            cout << "Test failed: Bishop doesn't take bishop" << endl;
        }

        if (test3) {
            cout << "Test passed: Bishop takes knight" << endl;
        } else {
            cout << "Test failed: Bishop doesn't take knight" << endl;
        }

        if (test4) {
            cout << "Test passed: Bishop takes pawn" << endl;
        } else {
            cout << "Test failed: Bishop doesn't take pawn" << endl;
        }

        if (test5) {
            cout << "Test passed: Bishop takes rook" << endl;
        } else {
            cout << "Test failed: Bishop doesn't take rook" << endl;
        }

        if (test6) {
            cout << "Test passed: Bishop takes queen" << endl;
        } else {
            cout << "Test failed: Bishop doesn't take queen" << endl;
        }
    }

    return test1 && test2 && test3 && test4 && test5 && test6;
    return success;
}

bool bishoptest::checkTest(bool display) {
    bool success = false;

    // Initialise objects
    gameboard board;
    king blackKing('B');
    king whiteKing('W');
    bishop bishopOne('W');
    bishop bishopTwo('W');

    // Place pieces
    board.addPiece(1,0, &blackKing);
    board.addPiece(1,2, &whiteKing);
    board.addPiece(0,2, &bishopOne);
    board.addPiece(2,3, &bishopTwo);

    // Test 1: Not in check
    bool test1 = !board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test 2: Check
    bool test2 = board.movePiece(2,3, 3,2) && board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test 3: Checkmate
    bool test3 = board.movePiece(0,2, 1,1) && board.isInCheckmate('B');
    if (display) board.visualiseTextBoard();

    // Test 4: Stalemate
    bool test4 = board.movePiece(3,2, 2,3) && board.isInStalemate('B');
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Not in check" << endl;
        } else {
            cout << "Test failed: Black in check" << endl;
        }

        if (test2) {
            cout << "Test passed: Black in check" << endl;
        } else {
            cout << "Test failed: Black not in check" << endl;
        }

        if (test3) {
            cout << "Test passed: Black in checkmate" << endl;
        } else {
            cout << "Test failed: Black not in checkmate" << endl;
        }

        if (test4) {
            cout << "Test passed: Black in stalemate" << endl;
        } else {
            cout << "Test failed: Black not in stalemate" << endl;
        }
    }

    success = test1 && test2 && test3 && test4;
    return success;
}