#include "../include/gameboard.h"
#include "../include/king.h"
#include "../include/bishop.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include "../include/pawn.h"
#include "../include/knight.h"
#include "checkmatetest.h"
#include <iostream>
using namespace std;

checkmatetest::checkmatetest(): checkmatetest(1) {}
checkmatetest::checkmatetest(int length) {
    this->_failMessage = "Checkmate test failed";
    this->_passMessage = "Checkmate test succeeded";
}

bool checkmatetest::basicTest(bool display) {
    bool success = false;

    // Initialise objects
    gameboard board;
    king whiteKing('W');
    queen whiteQueen('W');
    rook blackARook('B');
    rook blackHRook('B');
    bishop blackBishop('B');
    queen blackQueen('B');

    // Basic checkmate
    board.addPiece(7, 0, &whiteKing);
    board.addPiece(6, 4, &blackARook);
    board.addPiece(6, 7, &blackHRook);

    // Test 1: Not in checkmate when not in check
    bool test1 = !board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 2: In checkmate when two rooks block columns
    board.movePiece(6,7, 7,7);
    if (display) board.visualiseTextBoard();
    bool test2 = board.isInCheckmate('W');

    // Test 3: Not in checkmate when rook can be taken
    board.movePiece(6,4, 6,1);
    bool test3 = !board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 4: In checkmate when taking rook keeps king in check
    board.addPiece(0,7, &blackBishop);
    bool test4 = board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 5: In checkmate when queen can take rook
    board.addPiece(0, 1, &whiteQueen);
    bool test5 = board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 6: Not in checkmate when queen can take queen and block bishop
    board.removePiece(7, 7);
    board.removePiece(6,1);
    board.addPiece(6,1, &blackQueen);
    bool test6 = !board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 7: In checkmate when queen is removed
    board.removePiece(0,1);
    bool test7 = board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Display results
    if (display) {
        if (test1) {
            cout << "Test passed: Not in checkmate" << endl;
        } else {
            cout << "Test failed: White in checkmate" << endl;
        }

        if (test2) {
            cout << "Test passed: White in checkmate" << endl;
        } else {
            cout << "Test failed: White not in checkmate" << endl;
        }

        if (test3) {
            cout << "Test passed: Not in checkmate" << endl;
        } else {
            cout << "Test failed: White in checkmate" << endl;
        }

        if (test4) {
            cout << "Test passed: White in checkmate" << endl;
        } else {
            cout << "Test failed: White not in checkmate" << endl;
        }

        if (test5) {
            cout << "Test passed: White in checkmate" << endl;
        } else {
            cout << "Test failed: White not in checkmate" << endl;
        }

        if (test6) {
            cout << "Test passed: Not in checkmate" << endl;
        } else {
            cout << "Test failed: White in checkmate" << endl;
        }

        if (test7) {
            cout << "Test passed: White in checkmate" << endl;
        } else {
            cout << "Test failed: White not in checkmate" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6 && test7;
    return success;
}

bool checkmatetest::anarchyTest(bool display) {
    // Testing a really cool case I saw on twitter last week!
    // No idea if this does anything important :3
    // + a quick little back-rank test
    bool success = false;

    // Initialise objects
    gameboard board;

    pawn whitePawnOne;
    pawn whitePawnTwo;
    king whiteKing;
    knight whiteKnight;
    rook whiteRook;
    bishop whiteBishop;

    king blackKing('B');
    rook blackRook('B');
    queen blackQueenOne('B');
    queen blackQueenTwo('B');
    queen blackQueenThree('B');
    queen blackQueenFour('B');
    queen blackQueenFive('B');
    queen blackQueenSix('B');
    queen blackQueenSeven('B');
    queen blackQueenEight('B');

    // Place pieces
    board.addPiece(0, 0, &whiteKing);
    board.addPiece(0, 1, &whitePawnOne);
    board.addPiece(1, 1, &whitePawnTwo);
    board.addPiece(3, 0, &whiteRook);
    board.addPiece(2, 2, &whiteKnight);
    board.addPiece(6, 2, &whiteBishop);

    board.addPiece(3, 5, &blackKing);
    board.addPiece(7, 0, &blackRook);
    board.addPiece(4, 4, &blackQueenOne);
    board.addPiece(3, 4, &blackQueenTwo);
    board.addPiece(2, 4, &blackQueenThree);
    board.addPiece(2, 5, &blackQueenFour);
    board.addPiece(2, 6, &blackQueenFive);
    board.addPiece(3, 6, &blackQueenSix);
    board.addPiece(4, 6, &blackQueenSeven);
    board.addPiece(4, 5, &blackQueenEight);

    if (display) board.visualiseTextBoard('B');

    // Test 1: Neither in checkmate
    bool test1 = !board.isInCheckmate('W') && !board.isInCheckmate('B');

    // Test 2: Knight to E4 (checkmate)
    board.movePiece(2,2, 4,3);
    if (display) board.visualiseTextBoard('B');
    bool test2 = board.isInCheckmate('B');
    bool test3 = !board.isInCheckmate('W');

    // Test 3: Knight to F6, black rook takes D1 (checkmate)
    board.movePiece(4,3, 5,5);
    board.movePiece(7,0, 3,0);
    if (display) board.visualiseTextBoard('B');
    bool test4 = board.isInCheckmate('W');
    bool test5 = !board.isInCheckmate('B');

    // Display results
    if (display) {
        if (test1) {
            cout << "Test passed: No one in checkmate" << endl;
        } else {
            cout << "Test failed: Someone in checkmate" << endl;
        }

        if (test2) {
            cout << "Test passed: Black in checkmate" << endl;
        } else {
            cout << "Test failed: Black not in checkmate" << endl;
        }

        if (test3) {
            cout << "Test passed: White not in checkmate" << endl;
        } else {
            cout << "Test failed: White in checkmate" << endl;
        }

        if (test4) {
            cout << "Test passed: White in checkmate" << endl;
        } else {
            cout << "Test failed: White not in checkmate" << endl;
        }

        if (test5) {
            cout << "Test passed: Black not in checkmate" << endl;
        } else {
            cout << "Test failed: Black in checkmate" << endl;
        }
    }

    success = test1 && test2 && test3 & test4 && test5;
    return success;
}

bool checkmatetest::runTests(bool display) {
    bool success = true;

    success = success && this->basicTest(display);
    success = success && this->anarchyTest(display);

    return success;
}