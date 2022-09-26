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

    // Test pawn only checks king if within 1 space
    board.movePiece(4,5, 3,6);
    bool test5 = board.isInCheck('B');
    if (display) board.visualiseTextBoard();
    board.movePiece(3,6, 4,5);
    board.movePiece(5,4, 5,5);
    
    // Test pawn doesn't check king from behind
    board.movePiece(5,5, 5,6);
    bool test6 = !board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test king blocks bishop from checking king
    board.movePiece(3,0, 1,2);
    bool test7 = !board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Ensure pieces in right position
    int coords2[] = {4,5, 2,3, 5,6, 0,7, 1,2};
    bool test8 = board.testDriver(pieces, coords2, 5);

    // Output test results
    if (display) {
        if (test1) {
            cout << "Test passed: Board set up correctly" << endl;
        } else {
            cout << "Test failed: Board set up incorrectly" << endl;
        }

        if (test2) {
            cout << "Test passed: Queen checked king" << endl;
        } else {
            cout << "Test failed: Queen didn't check king" << endl;
        }

        if (test3) {
            cout << "Test passed: Bishop checked king" << endl;
        } else {
            cout << "Test failed: Bishop didn't check king" << endl;
        }

        if (test4) {
            cout << "Test passed: Pawn checked king" << endl;
        } else {
            cout << "Test failed: Pawn didn't check king" << endl;
        }

        if (test7) {
            cout << "Test passed: King escaped check" << endl;
        } else {
            cout << "Test failed: King didn't escape check" << endl;
        }

        if (test6) {
            cout << "Test passed: Pawn didn't check king from behind" << endl;
        } else {
            cout << "Test failed: Pawn checked king from behind" << endl;
        }

        if (test7) {
            cout << "Test passed: Bishop blocked from checking king" << endl;
        } else {
            cout << "Test failed: Bishop checked king through another piece" << endl;
        }

        if (test8) {
            cout << "Test passed: Board finished correctly" << endl;
        } else {
            cout << "Test failed: Board finished incorrectly" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6 && test7;
    return success;
}

bool checktest::straightTest(bool display) {
    // Ensure check works in straight direction
    // pretty homophobic if you ask me tbh
    bool success;

    // Initialise gameboard & pieces
    gameboard board;
    king whiteKing;
    rook whiteRook;
    cout << "hi\n";

    rook blackRook('B');
    queen blackQueen('B');
    bishop blackBishop('B');

    // Place pieces
    board.addPiece(2, 3, &whiteKing);
    board.addPiece(3, 3, &whiteRook);
    board.addPiece(0, 1, &blackRook);
    board.addPiece(6, 6, &blackQueen);
    board.addPiece(6, 1, &blackBishop);

    // Ensure pieces placed correctly
    if (display) board.visualiseTextBoard();
    piece* pieces[] = {&whiteKing, &whiteRook, &blackRook, &blackQueen, &blackBishop};
    int coords[] = {2,3, 3,3, 0,1, 6,6, 6,1};
    bool test1 = board.testDriver(pieces, coords, 5);

    // Test white rook can't check black king
    bool test2 = !board.isInCheck();

    // Test black rook can check white king
    board.movePiece(0,1, 0,3);
    bool test3 = board.isInCheck();
    if (display) board.visualiseTextBoard();
    board.movePiece(0,3, 0,1);

    // Test black queen can check white king
    board.movePiece(6,6, 2,6);
    bool test4 = board.isInCheck();
    if (display) board.visualiseTextBoard();

    // Test black bishop blocks check
    board.movePiece(6,1, 2,5);
    bool test5 = !board.isInCheck();
    if (display) board.visualiseTextBoard();

    // Test white rook blocks check
    board.movePiece(2,6, 5,3);
    bool test6 = !board.isInCheck();
    if (display) board.visualiseTextBoard();

    // Ensure pieces in right position
    int coords2[] = {2,3, 3,3, 0,1, 5,3, 2,5};
    bool test7 = board.testDriver(pieces, coords2, 5);

    // Output test results
    if (display) {
        if (test1) {
            cout << "Test passed: Board set up correctly" << endl;
        } else {
            cout << "Test failed: Board set up incorrectly" << endl;
        }

        if (test2) {
            cout << "Test passed: White rook can't check white king" << endl;
        } else {
            cout << "Test failed: White rook checked white king" << endl;
        }

        if (test3) {
            cout << "Test passed: Rook checked king" << endl;
        } else {
            cout << "Test failed: Rook didn't check king" << endl;
        }

        if (test4) {
            cout << "Test passed: Queen checked king" << endl;
        } else {
            cout << "Test failed: Queen didn't check king" << endl;
        }

        if (test5) {
            cout << "Test passed: Black bishop blocks black queen from checking king" << endl;
        } else {
            cout << "Test failed: Black bishop doesn't block black queen from checking king" << endl;
        }

        if (test6) {
            cout << "Test passed: White rook blocks black queen from checking king" << endl;
        } else {
            cout << "Test failed: White rook doesn't block black queen from checking king" << endl;
        }

        if (test7) {
            cout << "Test passed: Board finished correctly" << endl;
        } else {
            cout << "Test failed: Board finished incorrectly" << endl;
        }
    }
    
    success = test1 && test2 && test3 && test4 && test5 && test6 && test7;
    return false;
    return success;
}

bool checktest::knightTest(bool display) {
    // Ensure check works for knights
    bool success = false;

    
    return success;
}

bool checktest::runTests(bool display) {
    bool success = true;
    success = success && this->diagonalTest(display);
    cout << "Straight\n";
    success = success && this->straightTest(display);
    cout << "Straight\n";
    success = success && this->knightTest(display);
    return success;
}