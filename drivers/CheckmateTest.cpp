#include "../include/Gameboard.h"
#include "../include/King.h"
#include "../include/Bishop.h"
#include "../include/Rook.h"
#include "../include/Queen.h"
#include "../include/Pawn.h"
#include "../include/Knight.h"
#include "CheckmateTest.h"
#include <iostream>
using namespace std;

CheckmateTest::CheckmateTest() {
    this->_length = 3;
    this->_failMessage = "Checkmate test failed";
    this->_passMessage = "Checkmate test succeeded";
    initialiseResults();
}

bool CheckmateTest::basicTest(bool display) {
    bool success = false;

    // Initialise objects
    Gameboard board;
    King whiteKing('W');
    Queen whiteQueen('W');
    Rook blackARook('B');
    Rook blackHRook('B');
    Bishop blackBishop('B');
    Queen blackQueen('B');

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

    // Test 3: Not in checkmate when Rook can be taken
    board.movePiece(6,4, 6,1);
    bool test3 = !board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 4: In checkmate when taking Rook keeps King in check
    board.addPiece(0,7, &blackBishop);
    bool test4 = board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 5: In checkmate when Queen can take Rook
    board.addPiece(0, 1, &whiteQueen);
    bool test5 = board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 6: Not in checkmate when Queen can take Queen and block Bishop
    board.removePiece(7, 7);
    board.removePiece(6,1);
    board.addPiece(6,1, &blackQueen);
    bool test6 = !board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

    // Test 7: In checkmate when Queen is removed
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

bool CheckmateTest::anarchyTest(bool display) {
    // Testing a really cool case I saw on twitter last week!
    // No idea if this does anything important :3
    // + a quick little back-rank test
    bool success = false;

    // Initialise objects
    Gameboard board;

    Pawn whitePawnOne('W');
    Pawn whitePawnTwo('W');
    King whiteKing('W');
    Knight whiteKnight('W');
    Rook whiteRook('W');
    Bishop whiteBishop('W');

    King blackKing('B');
    Rook blackRook('B');
    Queen blackQueenOne('B');
    Queen blackQueenTwo('B');
    Queen blackQueenThree('B');
    Queen blackQueenFour('B');
    Queen blackQueenFive('B');
    Queen blackQueenSix('B');
    Queen blackQueenSeven('B');
    Queen blackQueenEight('B');

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

    // Test 3: Knight to F6, black Rook takes D1 (checkmate)
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

bool CheckmateTest::enPassantTest(bool display) {
    bool success = false;

    // Initialise objects
    Gameboard board;

    King whiteKing('W');
    Pawn whiteCPawn('W');

    King blackKing('B');
    Pawn blackDPawn('B');
    Rook blackRook('B');
    Queen blackQueen('B');

    // Place pieces
    board.addPiece(4,3, &whiteKing);
    board.addPiece(2,4, &whiteCPawn);

    board.addPiece(4,5, &blackKing);
    board.addPiece(3,1, &blackQueen);
    board.addPiece(5,7, &blackRook);
    board.addPiece(3,6, &blackDPawn);

    if (display) board.visualiseTextBoard();

    // Test 1: Neither in checkmate
    bool test1 = !board.isInCheckmate('W') && !board.isInCheckmate('B');

    // Test 2: Black Pawn to D5 (Not checkmate due to en passant)
    board.movePiece(3,6, 3,4);
    if (display) board.visualiseTextBoard();
    bool test2 = board.isInCheck('W') && !board.isInCheckmate('W');

    // Test 3: White Pawn to D6, capturing via en passant
    board.movePiece(2,4, 3,5);
    if (display) board.visualiseTextBoard();
    bool test3 = !board.isInCheck('W') && !board.isInCheckmate('W');

    // Display results
    if (display) {
        if (test1) {
            cout << "Test passed: No one in checkmate" << endl;
        } else {
            cout << "Test failed: Someone in checkmate" << endl;
        }

        if (test2) {
            cout << "Test passed: White in check, but en passant saves them from checkmate" << endl;
        } else {
            cout << "Test failed: White not in check and/or en passant does not save them from checkmate" << endl;
        }

        if (test3) {
            cout << "Test passed: White not in check or checkmate anymore" << endl;
        } else {
            cout << "Test failed: White in check or checkmate" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool CheckmateTest::runTests(bool display) {

    _results[0] = basicTest(display && !_results[0]);
    _results[1] = anarchyTest(display && !_results[1]);
    _results[2] = enPassantTest(display && !_results[2]);

    return result();
}