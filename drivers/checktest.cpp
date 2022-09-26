#include "../include/gameboard.h"
#include "../include/king.h"
#include "../include/bishop.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include "../include/pawn.h"
#include "../include/knight.h"
#include "checktest.h"
#include <iostream>
using namespace std;

checktest::checktest(): checktest(1) {}
checktest::checktest(int length) {
    this->_failMessage = "Check test failed";
    this->_passMessage = "Check test succeeded";
}

bool checktest::diagonalTest(bool display) {
    // Ensure check works in diagonal direction
    bool success;

    // Initialise gameboard & pieces
    gameboard board;
    king blackKing('B');

    king whiteKing;
    pawn whitePawn;
    queen whiteQueen;
    bishop whiteBishop;

    // Place pieces
    board.addPiece(4, 5, &blackKing);
    board.addPiece(2, 3, &whiteKing);
    board.addPiece(5, 3, &whitePawn);
    board.addPiece(0, 7, &whiteQueen);
    board.addPiece(7, 4, &whiteBishop);

    // Ensure pieces placed correctly
    if (display) board.visualiseTextBoard();
    piece* pieces[] = {&blackKing, &whiteKing, &whitePawn, &whiteQueen, &whiteBishop};
    int coords[] = {4,5, 2,3, 5,3, 0,7, 7,4};
    bool test1 = board.testDriver(pieces, coords, 5);

    // Test queen can check king
    board.movePiece(0,7, 2,7);
    bool test2 = board.isInCheck('B');
    if (display) board.visualiseTextBoard();
    board.movePiece(2,7, 0,7);

    // Test bishop can check king
    board.movePiece(7,4, 6,3);
    bool test3 = board.isInCheck('B');
    if (display) board.visualiseTextBoard();
    board.movePiece(6,3, 3,0);

    // Test pawn can check king
    board.movePiece(5,3, 5,4);
    bool test4 = board.isInCheck('B');
    if (display) board.visualiseTextBoard();
    board.movePiece(5,4, 5,5);
    
    // Test pawn doesn't check king from behind
    board.movePiece(5,5, 5,6);
    bool test5 = board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test king blocks bishop from checking king
    board.movePiece(3,0, 1,2);
    bool test6 = board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Ensure pieces in right position
    int coords2[] = {4,5, 2,3, 5,6, 0,7, 1,2};
    bool test7 = board.testDriver(pieces, coords2, 5);

    // Output test results
    if (display) {
        if (test1) {
            cout << "Test passed: Board set up correctly" << endl;
        }

        if (test2) {
            cout << "Test passed: Queen checked king" << endl;
        }

        if (test3) {
            cout << "Test passed: Bishop checked king" << endl;
        }

        if (test4) {
            cout << "Test passed: Pawn checked king" << endl;
        }

        if (test5) {
            cout << "Test passed: Pawn didn't check king from behind" << endl;
        }

        if (test6) {
            cout << "Test passed: Bishop blocked from checking king" << endl;
        }

        if (test7) {
            cout << "Test passed: Board finished correctly" << endl;
        }
    }

    return false;
    return success;
}

bool checktest::straightTest(bool display) {
    // Ensure check works in straight direction
    // pretty homophobic if you ask me tbh
    bool success;

    return success;
}

bool checktest::knightTest(bool display) {
    // Ensure check works for knights
    bool success;
    
    return success;
}

bool checktest::runTests(bool display) {
    bool success = true;
    success = success && this->diagonalTest(display);
    success = success && this->straightTest(display);
    success = success && this->knightTest(display);
    return success;
}