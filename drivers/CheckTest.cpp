#include "../include/Gameboard.h"
#include "../include/King.h"
#include "../include/Bishop.h"
#include "../include/Rook.h"
#include "../include/Queen.h"
#include "../include/Pawn.h"
#include "../include/Knight.h"
#include "CheckTest.h"
#include <iostream>
using namespace std;

CheckTest::CheckTest() {
    this->_length = 5;
    this->_failMessage = "Check test failed";
    this->_passMessage = "Check test succeeded";
    initialiseResults();
}

bool CheckTest::movementTest(bool display) {
    // Ensure moves can't place own King in check
    bool success = true;

    // Initialise Gameboard & pieces
    Gameboard board;
    King blackKing('B');
    Queen whiteQueen('W');
    Knight whiteKnight('W');
    Rook blackRook('B');
    Piece* pieces[] = {&blackKing, &whiteQueen, &whiteKnight, &blackRook};

    // Place pieces
    board.addPiece(6, 2, &blackKing);
    board.addPiece(7, 7, &whiteQueen);
    board.addPiece(7, 1, &whiteKnight);
    board.addPiece(5, 5, &blackRook);
    int coords[] = {6,2, 7,7, 7,1, 5,5};
    if (display) board.visualiseTextBoard();

    // Test King can't move into check
    bool test1 = !board.movePiece(6,2, 7,2);
    if (display) board.visualiseTextBoard();

    // Test King doesn't take Piece when it fails to make a move due to check
    board.movePiece(6,2, 7,1);
    bool test2 = board.testDriver(pieces, coords, 4) && !whiteKnight.captured();
    if (display) board.visualiseTextBoard();

    // Ensure, when King is in check, it can't make a move that keeps it in check
    board.movePiece(7,7, 6,7);
    bool test3 = !board.movePiece(6,2, 5,2);
    if (display) board.visualiseTextBoard();

    // Test pinned pieces can't move
    bool test4 = !board.movePiece(5,5, 3,5);
    if (display) board.visualiseTextBoard();

    board.movePiece(6,2, 5,1);
    bool test5 = board.movePiece(5,5, 3,5);

    // Ensure all pieces in correct position
    int coords2[] = {5,1, 6,7, 7,1, 3,5};
    bool test6 = board.testDriver(pieces, coords2, 4);

    if (display) {
        if (test1) {
            cout << "Test passed: King can't move into check" << endl;
        } else {
            cout << "Test failed: King moved into check" << endl;
        }
        
        if (test2) {
            cout << "Test passed: King doesn't take Piece upon failed move" << endl;
        } else {
            cout << "Test failed: King takes Piece despite move failure" << endl;
        }
        
        if (test3) {
            cout << "Test passed: When in check, King must move out of check" << endl;
        } else {
            cout << "Test failed: When in check, King can move into check" << endl;
        }
        
        if (test4) {
            cout << "Test passed: Pinned pieces can't move" << endl;
        } else {
            cout << "Test failed: Pinned pieces can move" << endl;
        }

        if (test4) {
            cout << "Test passed: Rook moved (no longer pinned)" << endl;
        } else {
            cout << "Test failed: Rook failed to move (no longer pinned)" << endl;
        }
        
        if (test6) {
            cout << "Test passed: All pieces in correct positions" << endl;
        } else {
            cout << "Test failed: Some pieces in incorrect positions" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6;
    return success;
}

bool CheckTest::diagonalTest(bool display) {
    // Ensure check works in diagonal direction
    bool success;

    // Initialise Gameboard & pieces
    Gameboard board;
    King blackKing('B');

    King whiteKing('W');
    Pawn whitePawn('W');
    Queen whiteQueen('W');
    Bishop whiteBishop('W');

    // Place pieces
    board.addPiece(4, 5, &blackKing);
    board.addPiece(2, 3, &whiteKing);
    board.addPiece(5, 3, &whitePawn);
    board.addPiece(0, 7, &whiteQueen);
    board.addPiece(7, 4, &whiteBishop);

    // Ensure pieces placed correctly
    if (display) board.visualiseTextBoard();
    Piece* pieces[] = {&blackKing, &whiteKing, &whitePawn, &whiteQueen, &whiteBishop};
    int coords[] = {4,5, 2,3, 5,3, 0,7, 7,4};
    bool test1 = board.testDriver(pieces, coords, 5);

    // Test Queen can check King
    board.movePiece(0,7, 2,7);
    bool test2 = board.isInCheck('B');
    if (display) board.visualiseTextBoard();
    board.movePiece(2,7, 0,7);

    // Test Bishop can check King
    board.movePiece(7,4, 6,3);
    bool test3 = board.isInCheck('B');
    if (display) board.visualiseTextBoard();
    board.movePiece(6,3, 3,0);

    // Test Pawn can check King
    board.movePiece(5,3, 5,4);
    bool test4 = board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test Pawn only checks King if within 1 space
    board.movePiece(4,5, 3,6);
    bool test5 = !board.isInCheck('B');
    if (display) board.visualiseTextBoard();
    board.movePiece(5,4, 5,5);
    board.movePiece(3,6, 4,5);
    
    // Test Pawn doesn't check King from behind
    board.movePiece(5,5, 5,6);
    bool test6 = !board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test King blocks Bishop from checking King
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
            cout << "Test passed: Queen checked King" << endl;
        } else {
            cout << "Test failed: Queen didn't check King" << endl;
        }

        if (test3) {
            cout << "Test passed: Bishop checked King" << endl;
        } else {
            cout << "Test failed: Bishop didn't check King" << endl;
        }

        if (test4) {
            cout << "Test passed: Pawn checked King" << endl;
        } else {
            cout << "Test failed: Pawn didn't check King" << endl;
        }

        if (test5) {
            cout << "Test passed: King escaped check" << endl;
        } else {
            cout << "Test failed: King didn't escape check" << endl;
        }

        if (test6) {
            cout << "Test passed: Pawn didn't check King from behind" << endl;
        } else {
            cout << "Test failed: Pawn checked King from behind" << endl;
        }

        if (test7) {
            cout << "Test passed: Bishop blocked from checking King" << endl;
        } else {
            cout << "Test failed: Bishop checked King through another Piece" << endl;
        }

        if (test8) {
            cout << "Test passed: Board finished correctly" << endl;
        } else {
            cout << "Test failed: Board finished incorrectly" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8;
    return success;
}

bool CheckTest::straightTest(bool display) {
    // Ensure check works in straight direction
    // pretty homophobic if you ask me tbh
    bool success;

    // Initialise Gameboard & pieces
    Gameboard board;
    King whiteKing('W');
    Rook whiteRook('W');

    Rook blackRook('B');
    Queen blackQueen('B');
    Bishop blackBishop('B');

    // Place pieces
    board.addPiece(2, 3, &whiteKing);
    board.addPiece(3, 3, &whiteRook);
    board.addPiece(0, 1, &blackRook);
    board.addPiece(6, 6, &blackQueen);
    board.addPiece(6, 1, &blackBishop);

    // Ensure pieces placed correctly
    if (display) board.visualiseTextBoard();
    Piece* pieces[] = {&whiteKing, &whiteRook, &blackRook, &blackQueen, &blackBishop};
    int coords[] = {2,3, 3,3, 0,1, 6,6, 6,1};
    bool test1 = board.testDriver(pieces, coords, 5);

    // Test white Rook can't check black King
    bool test2 = !board.isInCheck('W');

    // Test black Rook can check white King
    board.movePiece(0,1, 0,3);
    bool test3 = board.isInCheck('W');
    if (display) board.visualiseTextBoard();
    board.movePiece(0,3, 0,1);

    // Test black Queen can check white King
    board.movePiece(6,6, 2,6);
    bool test4 = board.isInCheck('W');
    if (display) board.visualiseTextBoard();

    // Test black Bishop blocks check
    board.movePiece(6,1, 2,5);
    bool test5 = !board.isInCheck('W');
    if (display) board.visualiseTextBoard();

    // Test white Rook blocks check
    board.movePiece(2,6, 5,3);
    bool test6 = !board.isInCheck('W');
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
            cout << "Test passed: White Rook can't check white King" << endl;
        } else {
            cout << "Test failed: White Rook checked white King" << endl;
        }

        if (test3) {
            cout << "Test passed: Rook checked King" << endl;
        } else {
            cout << "Test failed: Rook didn't check King" << endl;
        }

        if (test4) {
            cout << "Test passed: Queen checked King" << endl;
        } else {
            cout << "Test failed: Queen didn't check King" << endl;
        }

        if (test5) {
            cout << "Test passed: Black Bishop blocks black Queen from checking King" << endl;
        } else {
            cout << "Test failed: Black Bishop doesn't block black Queen from checking King" << endl;
        }

        if (test6) {
            cout << "Test passed: White Rook blocks black Queen from checking King" << endl;
        } else {
            cout << "Test failed: White Rook doesn't block black Queen from checking King" << endl;
        }

        if (test7) {
            cout << "Test passed: Board finished correctly" << endl;
        } else {
            cout << "Test failed: Board finished incorrectly" << endl;
        }
    }
    
    success = test1 && test2 && test3 && test4 && test5 && test6 && test7;
    return success;
}

bool CheckTest::KnightTest(bool display) {
    // Ensure check works for knights
    bool success;

    // Intiialise Gameboard & pieces
    Gameboard board;
    King whiteKing('W');
    Knight blackKnight('B');
    Queen blackQueen('B');
    Pawn blackPawn('B');

    // Check King isn't in check on empty board
    board.addPiece(3, 3, &whiteKing);
    if (display) board.visualiseTextBoard();
    bool test0 = !board.isInCheck('W');

    // Have Knight check King in all 8 positions
    bool test1[8];
    int files[] = {1, 2, 4, 5, 5, 4, 2, 1};
    int ranks[] = {2, 1, 1, 2, 4, 5, 5, 4};
    bool test1total = true;

    for (int i = 0; i < 8; i++) {
        // add Knight to board
        board.addPiece(files[i], ranks[i], &blackKnight);
        // see if white is in check
        test1[i] = board.isInCheck('W');
        if (!test1[i] && display) board.visualiseTextBoard();
        // remove Knight from board
        board.removePiece(files[i], ranks[i]);
        test1total = test1total && test1[i];
    }

    // Ensure Knight doesn't check King diagonally or forward
    board.addPiece(1, 5, &blackKnight);
    bool test2 = !board.isInCheck('W');
    if (display) board.visualiseTextBoard();
    board.movePiece(1,5, 3,6);
    bool test3 = !board.isInCheck('W');
    if (display) board.visualiseTextBoard();

    // Ensure non-Knight pieces can't check King from Knight position
    board.addPiece(2, 1, &blackQueen);
    board.addPiece(4, 5, &blackPawn);
    bool test4 = !board.isInCheck('W');
    if (display) board.visualiseTextBoard();

    // Output test results
    if (display) {
        if (test0) {
            cout << "Test passed: King not in check in empty board" << endl;
        } else {
            cout << "Test failed: King in check in empty board" << endl;
        }

        if (test1total) {
            cout << "Test passed: Knights check King in all possible positions" << endl;
        } else {
            cout << "Test failed: Knight fails to check King in above position" << endl;
            // note: Gameboard only displayed if test failed earlier
        }

        if (test2) {
            cout << "Test passed: Knight doesn't check King diagonally" << endl;
        } else {
            cout << "Test failed: Knight checks King diagonally" << endl;
        }

        if (test3) {
            cout << "Test passed: Knight doesn't check King vertically" << endl;
        } else {
            cout << "Test failed: Knight checks King vertically" << endl;
        }

        if (test4) {
            cout << "Test passed: Non-Knight pieces can't check King like knights" << endl;
        } else {
            cout << "Test failed: Non-Knight pieces check King like knights" << endl;
        }
    }
    
    success = test0 && test1total && test2 && test3 && test4;
    return success;
}

bool CheckTest::enPassantTest(bool display) {
    // Ensure check works for knights
    bool success;

    // Intiialise Gameboard & pieces
    Gameboard board;
    King whiteKing('W');

    Pawn whiteEPawn('W');
    Pawn blackDPawn('B');

    Pawn whiteAPawn('W');
    Pawn blackBPawn('B');

    // Check King isn't in check on empty board
    board.addPiece(5,1, &whiteKing);
    if (display) board.visualiseTextBoard();
    bool test0 = !board.isInCheck('W');

    // Place pawns on the board
    board.addPiece(4,1, &whiteEPawn);
    board.addPiece(3,6, &blackDPawn);

    // Move the pawns up into a position where black can en passant
    board.movePiece(3,6, 3,4);
    board.movePiece(3,4, 3,3);
    board.movePiece(4,1, 4,3);
    if (display) board.visualiseTextBoard();

    // Peform en passant, checking the King
    board.movePiece(3,3, 4,2);
    if (display) board.visualiseTextBoard();
    bool test1 = board.isInCheck('W');

    // Reset the board, removing all peices
    board.clearBoard();

    // Place King and pawns on the board
    board.addPiece(2,3, &whiteKing);
    board.addPiece(0,4, &whiteAPawn);
    board.addPiece(1,6, &blackBPawn);

    // Move the black Pawn, checking the white King but leaving it susceptible to en passant
    board.movePiece(1,6, 1,4);
    if (display) board.visualiseTextBoard();
    bool test2 = board.isInCheck('W');

    // Capture the black Pawn with en passant, bringing the white King out of check
    board.movePiece(0,4, 1,5);
    if (display) board.visualiseTextBoard();
    bool test3 = !board.isInCheck('W');


    // Output test results
    if (display) {
        if (test0) {
            cout << "Test passed: King not in check in empty board" << endl;
        } else {
            cout << "Test failed: King in check in empty board" << endl;
        }

        if (test1) {
            cout << "Test passed: En passant can check King" << endl;
        } else {
            cout << "Test failed: En passant fails to check King" << endl;
        }

        if (test2) {
            cout << "Test passed: Two-tile Pawn move checks King" << endl;
        } else {
            cout << "Test failed: Two-tile Pawn move fails to check King" << endl;
        }

        if (test3) {
            cout << "Test passed: En passant can bring King out of check" << endl;
        } else {
            cout << "Test failed: En passant does not save King from check" << endl;
        }
    }
    
    success = test0 && test1 && test2 && test3;
    return success;
}

bool CheckTest::runTests(bool display) {

    _results[0] = movementTest(display && !_results[0]);
    _results[1] = diagonalTest(display && !_results[1]);
    _results[2] = straightTest(display && !_results[2]);
    _results[3] = KnightTest(display && !_results[3]);
    _results[4] = enPassantTest(display && !_results[4]);

    return result();
}

