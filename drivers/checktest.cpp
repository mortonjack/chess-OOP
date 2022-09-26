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

bool checktest::movementTest(bool display) {
    // Ensure moves can't place own king in check
    bool success = true;

    // Initialise gameboard & pieces
    gameboard board;
    king blackKing('B');
    queen whiteQueen('W');
    knight whiteKnight('W');
    rook blackRook('B');
    piece* pieces[] = {&blackKing, &whiteQueen, &whiteKnight, &blackRook};

    // Place pieces
    board.addPiece(6, 2, &blackKing);
    board.addPiece(7, 7, &whiteQueen);
    board.addPiece(7, 1, &whiteKnight);
    board.addPiece(5, 5, &blackRook);
    int coords[] = {6,2, 7,7, 7,1, 5,5};
    if (display) board.visualiseTextBoard();

    // Test king can't move into check
    bool test1 = !board.movePiece(6,2, 7,2);
    if (display) board.visualiseTextBoard();

    // Test king doesn't take piece when it fails to make a move due to check
    board.movePiece(6,2, 7,1);
    bool test2 = board.testDriver(pieces, coords, 4) && !whiteKnight.captured();
    if (display) board.visualiseTextBoard();

    // Ensure, when king is in check, it can't make a move that keeps it in check
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
            cout << "Test passed: King doesn't take piece upon failed move" << endl;
        } else {
            cout << "Test failed: King takes piece despite move failure" << endl;
        }
        
        if (test3) {
            cout << "Test passed: When in check, king must move out of check" << endl;
        } else {
            cout << "Test failed: When in check, king can move into check" << endl;
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
    bool test5 = !board.isInCheck('B');
    if (display) board.visualiseTextBoard();
    board.movePiece(5,4, 5,5);
    board.movePiece(3,6, 4,5);
    
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

        if (test5) {
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

    success = test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8;
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
    return success;
}

bool checktest::knightTest(bool display) {
    // Ensure check works for knights
    bool success;

    // Intiialise gameboard & pieces
    gameboard board;
    king whiteKing;
    knight blackKnight('B');
    queen blackQueen('B');
    pawn blackPawn('B');

    // Check king isn't in check on empty board
    board.addPiece(3, 3, &whiteKing);
    if (display) board.visualiseTextBoard();
    bool test0 = !board.isInCheck('W');

    // Have knight check king in all 8 positions
    bool test1[8];
    int files[] = {1, 2, 4, 5, 5, 4, 2, 1};
    int ranks[] = {2, 1, 1, 2, 4, 5, 5, 4};
    bool test1total = true;

    for (int i = 0; i < 8; i++) {
        // add knight to board
        board.addPiece(files[i], ranks[i], &blackKnight);
        // see if white is in check
        test1[i] = board.isInCheck('W');
        if (!test1[i] && display) board.visualiseTextBoard();
        // remove knight from board
        board.removePiece(files[i], ranks[i]);
        test1total = test1total && test1[i];
    }

    // Ensure knight doesn't check king diagonally or forward
    board.addPiece(1, 5, &blackKnight);
    bool test2 = !board.isInCheck();
    if (display) board.visualiseTextBoard();
    board.movePiece(1,5, 3,6);
    bool test3 = !board.isInCheck();
    if (display) board.visualiseTextBoard();

    // Ensure non-knight pieces can't check king from knight position
    board.addPiece(2, 1, &blackQueen);
    board.addPiece(4, 5, &blackPawn);
    bool test4 = !board.isInCheck();
    if (display) board.visualiseTextBoard();

    // Output test results
    if (display) {
        if (test0) {
            cout << "Test passed: King not in check in empty board" << endl;
        } else {
            cout << "Test failed: King in check in empty board" << endl;
        }

        if (test1total) {
            cout << "Test passed: Knights check king in all possible positions" << endl;
        } else {
            cout << "Test failed: Knight fails to check king in above position" << endl;
            // note: gameboard only displayed if test failed earlier
        }

        if (test2) {
            cout << "Test passed: Knight doesn't check king diagonally" << endl;
        } else {
            cout << "Test failed: Knight checks king diagonally" << endl;
        }

        if (test3) {
            cout << "Test passed: Knight doesn't check king vertically" << endl;
        } else {
            cout << "Test failed: Knight checks king vertically" << endl;
        }

        if (test4) {
            cout << "Test passed: Non-Knight pieces can't check king like knights" << endl;
        } else {
            cout << "Test failed: Non-Knight pieces check king like knights" << endl;
        }
    }
    
    success = test0 && test1total && test2 && test3 && test4;
    return success;
}

bool checktest::runTests(bool display) {
    bool success = true;
    bool test;

    // idk why this works, but it fixes a bug
    test = this->movementTest(display);
    success = success && test;

    test = this->diagonalTest(display);
    success = success && test;
    
    test = this->straightTest(display);
    success = success && test;

    test = this->knightTest(display);
    success = success && test;

    return success;
}