#include "../include/Gameboard.h"
#include "../include/King.h"
#include "../include/Rook.h"
#include "../include/Bishop.h"
#include "../include/Knight.h"
#include "../include/Pawn.h"
#include "../include/Queen.h"
#include "KingTest.h"
#include <iostream>
using namespace std;

KingTest::KingTest() {
    this->_length = 4;
    this->_failMessage = "King test failed";
    this->_passMessage = "King test succeeded";
    initialiseResults();
}

bool KingTest::movementTest(bool display) {
    // Test King movement
    bool success = true;

    // Create the Game board a white King.
    Gameboard board;
    King testKing('W');

    // Add the King to the Game board
    board.addPiece(3,3,&testKing);
    if (display) board.visualiseTextBoard();

    // Test all valid move directions- move King in a circle
    board.movePiece(3,3, 3,2);
    board.movePiece(3,2, 2,1);
    board.movePiece(2,1, 1,1);
    board.movePiece(1,1, 0,2);
    board.movePiece(0,2, 0,3);
    if (display) board.visualiseTextBoard();
    
    // Run first test
    Piece* pieces[1] = {&testKing};
    int coords[2] = {0,3};
    bool test1 = board.testDriver(pieces, coords, 1);

    // Continue to move King
    board.movePiece(0,3, 1,4);
    board.movePiece(1,4, 2,4);
    board.movePiece(2,4, 3,3);
    if (display) board.visualiseTextBoard();
    
    // Run second test
    coords[0] = 3;
    coords[1] = 3;
    bool test2 = board.testDriver(pieces, coords, 1);

    // Test invalid move directions
    board.movePiece(3,3, 1,3);
    board.movePiece(3,3, 2,1);
    board.movePiece(3,3, 5,4);

    // Run third test
    bool test3 = board.testDriver(pieces, coords, 1);
    if (display) board.visualiseTextBoard();

    // Run tests
    if (display) {
        if (test1) {
            cout << "Test passed: King moved halfway around the circle" << endl;
        } else {
            cout << "Test failed: King failed to move halfway around the circle" << endl;
        }

        if (test2) {
            cout << "Test passed: King moved in all 8 directions" << endl;
        } else {
            cout << "Test failed: King failed to move in all 8 directions" << endl;
        }

        if (test3) {
            cout << "Test passed: King didn't make illegal moves" << endl;
        } else {
            cout << "Test failed: King made illegal move" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool KingTest::castleTest(bool display) {
    // Test King castling
    bool success = true;

    // Create the Game board a white King.
    Gameboard board;

    King whiteKing('W');
    King whiteKingTwo('W');
    King whiteKingThree('W');

    Rook whiteARook('W');
    Rook whiteHRook('W');
    Rook whiteARookTwo('W');
    Rook whiteHRookTwo('W');
    Rook whiteARookThree('W');
    Rook whiteHRookThree('W');

    Rook blackRook('B');
    Knight blackKnight('B');
    Knight whiteKnight('W');

    // Place the pieces
    board.addPiece(4,0, &whiteKing);
    board.addPiece(7,0, &whiteHRook);
    board.addPiece(0,0, &whiteARook);
    board.addPiece(6,0, &whiteKnight);
    if (display) board.visualiseTextBoard();

    // Attempt castle short
    board.movePiece(4,0, 6,0);
    if (display) board.visualiseTextBoard();

    Piece* pieces0[] = {&whiteKing, &whiteARook, &whiteHRook, &whiteKnight};
    int coords0[] = {4,0, 0,0, 7,0, 6,0};
    bool test0 = board.testDriver(pieces0, coords0, 4);

    board.removePiece(6, 0);
    if (display) board.visualiseTextBoard();

    // Castle short
    board.movePiece(4,0, 6,0);
    if (display) board.visualiseTextBoard();

    Piece* pieces1[] = {&whiteKing, &whiteARook, &whiteHRook};
    int coords1[] = {6,0, 0,0, 5,0};
    bool test1 = board.testDriver(pieces1, coords1, 3);
    

    // Reset the board
    board.clearBoard();

    // Place the pieces
    board.addPiece(4,0, &whiteKingTwo);
    board.addPiece(7,0, &whiteHRookTwo);
    board.addPiece(0,0, &whiteARookTwo);
    board.addPiece(1,0, &blackKnight);
    if (display) board.visualiseTextBoard();

    // Attempt castle long
    bool test2_extra = !board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();
    board.removePiece(1,0);
    if (display) board.visualiseTextBoard();

    // Castle long
    board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();

    Piece* pieces2[] = {&whiteKingTwo, &whiteARookTwo, &whiteHRookTwo};
    int coords2[] = {2,0, 3,0, 7,0};
    bool test2 = board.testDriver(pieces2, coords2, 3);


    // Reset the board
    board.clearBoard();

    // Place the pieces
    board.addPiece(4,0, &whiteKingThree);
    board.addPiece(7,0, &whiteHRookThree);
    board.addPiece(0,0, &whiteARookThree);
    board.addPiece(4,7, &blackRook);
    if (display) board.visualiseTextBoard();

    // Try castling long (out of check) and ensure this failed
    board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();

    Piece* pieces3[] = {&whiteKingThree, &whiteARookThree, &whiteHRookThree, &blackRook};
    int coords3[] = {4,0, 0,0, 7,0, 4,7};
    bool test3 = board.testDriver(pieces3, coords3, 4);


    // Move the black Rook
    board.movePiece(4,7, 3,7);
    if (display) board.visualiseTextBoard();

    // Try castling long (through check) and ensure this failed
    board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();

    int coords4[] = {4,0, 0,0, 7,0, 3,7};
    bool test4 = board.testDriver(pieces3, coords4, 4);


    // Move the black Rook
    board.movePiece(3,7, 2,7);
    if (display) board.visualiseTextBoard();

    // Try castling long (into check) and ensure this failed
    board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();

    int coords5[] = {4,0, 0,0, 7,0, 2,7};
    bool test5 = board.testDriver(pieces3, coords5, 4);


    if (display) {
        if (test0) {
            cout << "Test passed: King doesn't castle through friendly Piece" << endl;
        } else {
            cout << "Test failed: King castled through friendly Piece" << endl;
        }

        if (test1) {
            cout << "Test passed: King successfully castled short" << endl;
        } else {
            cout << "Test failed: King did not castle short" << endl;
        }

        if (test2_extra) {
            cout << "Test passed: King doesn't castle through enemy Piece" << endl;
        } else {
            cout << "Test failed: King castles through enemy Piece" << endl;
        }

        if (test2) {
            cout << "Test passed: King successfully castled long" << endl;
        } else {
            cout << "Test failed: King did not castle long" << endl;
        }

        if (test3) {
            cout << "Test passed: King did not castle out of check" << endl;
        } else {
            cout << "Test failed: King castled out of check" << endl;
        }

        if (test4) {
            cout << "Test passed: King did not castle through check" << endl;
        } else {
            cout << "Test failed: King castled through check" << endl;
        }

        if (test5) {
            cout << "Test passed: King did not castle into check" << endl;
        } else {
            cout << "Test failed: King castled into check" << endl;
        }
    }

    success = test0 && test1 && test2_extra && test2 && test3 && test4 && test5;
    return success;
}

bool KingTest::CaptureTest(bool display) {
    bool success = false;

    // Initialise objects
    Gameboard board;
    King whiteKing('W');
    Pawn blackPawn('B');
    Knight blackKnight('B');
    Rook blackRook('B');
    Bishop blackBishop('B');
    Queen blackQueen('B');

    // Place pieces
    board.addPiece(2,3, &whiteKing);
    board.addPiece(2,4, &blackPawn);
    board.addPiece(3,5, &blackKnight);
    board.addPiece(4,5, &blackBishop);
    board.addPiece(5,6, &blackRook);
    board.addPiece(7,7, &blackQueen);

    if (display) board.visualiseTextBoard();
    
    // Test 1: King takes Pawn
    bool test1 = board.movePiece(2,3, 2,4);
    if (display) board.visualiseTextBoard();

    // Test 2: King takes Knight
    bool test2 = board.movePiece(2,4, 3,5);
    if (display) board.visualiseTextBoard();

    // Test 3: King takes Bishop
    bool test3 = board.movePiece(3,5, 4,5);
    if (display) board.visualiseTextBoard();

    // Test 4: King takes Rook
    bool test4 = board.movePiece(4,5, 5,6);
    board.movePiece(7,7, 5,5);
    if (display) board.visualiseTextBoard();

    // Test 5: King takes Queen
    bool test5 = board.movePiece(5,6, 5,5);
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: King takes Pawn" << endl;
        } else {
            cout << "Test failed: King doesn't take Pawn" << endl;
        }

        if (test2) {
            cout << "Test passed: King takes Knight" << endl;
        } else {
            cout << "Test failed: King doesn't take Knight" << endl;
        }

        if (test3) {
            cout << "Test passed: King takes Bishop" << endl;
        } else {
            cout << "Test failed: King doesn't take Bishop" << endl;
        }

        if (test4) {
            cout << "Test passed: King takes Rook" << endl;
        } else {
            cout << "Test failed: King doesn't take Rook" << endl;
        }

        if (test5) {
            cout << "Test passed: King takes Queen" << endl;
        } else {
            cout << "Test failed: King doesn't take Queen" << endl;
        }
    }
    success = test1 && test2 && test3 && test4 && test5;
    return success;
}

bool KingTest::checkTest(bool display) {
    bool success = false;

    // Initialise objects
    Gameboard board;
    King whiteKing('W');
    King blackKing('B');

    // Place objects
    board.addPiece(3,3, &whiteKing);
    board.addPiece(3,5, &blackKing);

    // Test 1: Both not in check
    if (display) board.visualiseTextBoard();
    bool test1 = !board.isInCheck('W') && !board.isInCheck('B');

    // Test 2: Can't move into each other
    bool test2 = !board.movePiece(3,3, 3,4) && !board.movePiece(3,5, 2,4);
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Neither in check" << endl;
        } else {
            cout << "Test failed: King in check" << endl;
        }

        if (test2) {
            cout << "Test passed: Can't move into check" << endl;
        } else {
            cout << "Test failed: Moves into check" << endl;
        }
    }

    success = test1 && test2;
    return success;
}

bool KingTest::runTests(bool display) {
    
    _results[3] = castleTest(display && !_results[3]);

    return PieceTest::runTests(display);
}