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
    if (display) board.visualiseTextBoard();

    // Test 1: Not in checkmate when not in check
    bool test1 = !board.isInCheckmate('W');

    // Test 2: In checkmate when two rooks block columns
    board.movePiece(6,7, 7,7);
    bool test2 = board.isInCheckmate('W');
    if (display) board.visualiseTextBoard();

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

bool checkmatetest::runTests(bool display) {
    bool success = true;

    success = success && this->basicTest(display);

    return success;
}