#include "../include/Gameboard.h"
#include "../include/Pawn.h"
#include "../include/King.h"
#include "../include/Rook.h"
#include "PawnTest.h"
#include <iostream>
using namespace std;

PawnTest::PawnTest() {
    this->_length = 5;
    this->_failMessage = "Pawn test failed";
    this->_passMessage = "Pawn test succeeded";
    initialiseResults();
}

bool PawnTest::movementTest(bool display) {
    // Test Pawn movement
    bool success = true;

    // Create the Game board and two pawns.
    Gameboard board;
    Pawn whiteCpawn('W');
    Pawn blackFPawn('B');
    Piece* pieces[] = {&whiteCpawn, &blackFPawn};

    // Add the pawns to the Game board
    board.addPiece(5,1, &whiteCpawn);
    board.addPiece(2,6, &blackFPawn);
    
    if (display) board.visualiseTextBoard();

    // Move the pawns to illegal positions
    board.movePiece(2,6, 2,7);
    board.movePiece(5,1, 5,0);
    board.movePiece(2,6, 3,6);
    board.movePiece(5,1, 5,4);

    // Check to ensure nothing has happened
    if (display) board.visualiseTextBoard();
    int coords[] = {5,1, 2,6};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the pawns to legal positions 
    board.movePiece(2,6, 2,4);
    board.movePiece(5,1, 5,2);

    // Check to ensure our moves were successful
    if (display) board.visualiseTextBoard();
    int coords2[] = {5,2, 2,4};
    bool test2 = board.testDriver(pieces, coords2, 2);

    // Move the pawns to illegal positions
    board.movePiece(2,4, 2,2);
    board.movePiece(5,2, 5,4);

    // Check to ensure nothing has happened
    if (display) board.visualiseTextBoard();
    bool test3 = board.testDriver(pieces, coords2, 2);

    // Move the pawns to legal positions
    board.movePiece(2,4, 2,3);
    board.movePiece(5,2, 5,3);
    
    // Check to ensure the moves succeeded
    int coords3[] = {5,3, 2,3};
    bool test4 = board.testDriver(pieces, coords3, 2);

    if (display) {
        if (test1) {
            cout << "Test passed: Pawns didn't move backwards, sideways, and/or up 3 tiles" << endl;
        } else {
            cout << "Test failed: Pawns moved backwards, sideways, and/or up 3 tiles" << endl;
        }

        if (test2) {
            cout << "Test passed: Pawns moved up one and/or two tiles" << endl;
        } else {
            cout << "Test failed: Pawns failed to move up one and/or two tiles" << endl;
        }

        if (test3) {
            cout << "Test passed: Pawns didn't move up two tiles on the second move" << endl;
        } else {
            cout << "Test failed: Pawns moved up two tiles on second move" << endl;
        }

        if (test4) {
            cout << "Test passed: Pawns moved up one tile" << endl;
        } else {
            cout << "Test failed: Pawns didn't move up one tile" << endl;
        }
    }

    success = test1 && test2 && test3 && test4;
    return success;
}

bool PawnTest::CaptureTest(bool display) {
    // Test Pawn movement with capturing
    bool success = true;

    // Create the Game board and two pawns.
    Gameboard board;
    Pawn whiteDpawn('W');
    Pawn whiteEpawn('W');
    Pawn blackDpawn('B');
    Pawn blackEpawn('B');
    Piece* pieces[] = {&whiteDpawn, &whiteEpawn, &blackDpawn, &blackEpawn};

    // Add the pawns to the Game board
    board.addPiece(3,1, &whiteDpawn);
    board.addPiece(4,1, &whiteEpawn);
    board.addPiece(3,6, &blackDpawn);
    board.addPiece(4,6, &blackEpawn);
    
    if (display) board.visualiseTextBoard();

    // Play the opening moves for the Pirc defense: 1. e4 e5 2. d4 d6
    board.movePiece(4,1, 4,3);
    board.movePiece(4,6, 4,4);
    board.movePiece(3,1, 3,3);
    board.movePiece(3,6, 3,5);

    // Check to ensure this opening was successful
    if (display) board.visualiseTextBoard();
    int coords[] = {3,3, 4,3, 3,5, 4,4};
    bool test1 = board.testDriver(pieces, coords, 4);

    // Try to capture my moving into and through pawns
    board.movePiece(4,3, 4,4);
    board.movePiece(4,3, 4,5);
    board.movePiece(4,4, 4,3);
    board.movePiece(4,4, 4,2);

    // Check to ensure these illegal moves were unsuccessful
    if (display) board.visualiseTextBoard();
    int coords2[] = {3,3, 4,3, 3,5, 4,4};
    bool test2 = board.testDriver(pieces, coords2, 4);
    
    // Capture black's E Pawn with white's D Pawn, then recapture with black's D Pawn 3. dxe5 dxe5
    board.movePiece(3,3, 4,4);
    board.movePiece(3,5, 4,4);

    // Check to ensure the captures were successful
    Piece* remainingPieces[] = {&whiteEpawn, &blackDpawn};
    int coords3[] = {4,3, 4,4};
    if (display) board.visualiseTextBoard();
    bool test3 = board.testDriver(remainingPieces, coords3, 2);

    if (display) {
        if (test1) {
            cout << "Test passed: Pawns moved up one and/or two tiles" << endl;
        } else {
            cout << "Test failed: Pawns didn't move up one and/or two tiles" << endl;
        }

        if (test2) {
            cout << "Test passed: Pawns did not move through each other or capture forwards" << endl;
        } else {
            cout << "Test failed: Pawns moved through each other or captured forwards" << endl;
        }

        if (test3) {
            cout << "Test passed: Pawns captured diagonally" << endl;
        } else {
            cout << "Test failed: Pawns did not capture diagonally" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool PawnTest::enPassantTest(bool display) {
    // Test en passant feature
    bool success = false;
    
    // Initialise objects
    Gameboard board;
    Pawn blackPawnOne('B');
    Pawn blackPawnTwo('B');
    Pawn blackPawnThree('B');
    Pawn blackPawnFour('B');
    Pawn blackPawnFive('B');
    Pawn blackPawnSix('B');
    Pawn whitePawnOne('W');
    Pawn whitePawnTwo('W');
    Pawn whitePawnThree('W');
    Pawn whitePawnFour('W');

    // Place pieces
    board.addPiece(2,6, &blackPawnOne);
    board.addPiece(3,4, &whitePawnOne);
    if (display) board.visualiseTextBoard();
    board.movePiece(2,6, 2,4);
    if (display) board.visualiseTextBoard();

    // Test case 0: move Pawn wrong way
    bool test0 = !board.movePiece(3,4, 4,5);

    // Test case 1: regular en passant
    board.movePiece(3,4, 2,5); // White captures
    if (display) board.visualiseTextBoard();

    Piece* pieces[1] = {&whitePawnOne};
    int coords[] = {2,5};
    bool test1 = blackPawnOne.captured() && board.testDriver(pieces, coords, 1);

    board.removePiece(2,5);

    // Test case 2: illegal en passant (move Piece up twice)
    board.addPiece(2,6, &blackPawnTwo);
    board.addPiece(3,4, &whitePawnTwo);

    board.movePiece(2,6, 2,5);
    if (display) board.visualiseTextBoard();
    board.movePiece(2,5, 2,4);
    if (display) board.visualiseTextBoard();
    board.movePiece(3,4, 2,5); // White attempts to capture
    board.movePiece(2,4, 3,3); // Black attempts to capture
    if (display) board.visualiseTextBoard();

    Piece* pieces2[] = {&whitePawnTwo, &blackPawnTwo};
    int coords2[] = {3,4, 2,4};
    bool test2 = board.testDriver(pieces2, coords2, 2);

    board.removePiece(2,4);
    board.removePiece(3,4);

    // Test case 3: illegal en passant (never move Piece)
    board.addPiece(2,6, &blackPawnThree);
    board.addPiece(3,4, &whitePawnThree);
    
    board.movePiece(3,4, 3,5);
    board.movePiece(3,5, 3,6);
    if (display) board.visualiseTextBoard();
    board.movePiece(3,6, 4,7); // White attempts to capture

    Piece* pieces3[] = {&whitePawnThree, &blackPawnThree};
    int coords3[] = {3,6, 2,6};
    bool test3 = board.testDriver(pieces3, coords3, 2);
    
    if (display) board.visualiseTextBoard();
    board.removePiece(3,6);
    board.removePiece(2,6);

    // Test case 4: Take diagonally with Pawn next to Piece
    board.addPiece(3,4, &whitePawnFour);
    board.addPiece(4,4, &blackPawnFour);
    board.addPiece(4,5, &blackPawnFive);
    if (display) board.visualiseTextBoard();
    board.movePiece(3,4, 4,5);
    if (display) board.visualiseTextBoard();

    Piece* pieces4[] = {&whitePawnFour, &blackPawnFour};
    int coords4[] = {4,5, 4,4};

    bool test4 = board.testDriver(pieces4, coords4, 2);

    // Test case 5: Cannot take en passant if 2 moves have elapsed
    board.clearBoard();
    board.addPiece(5,6, &blackPawnSix);
    board.addPiece(1,6, &blackPawnFour);
    board.addPiece(4,3, &whitePawnFour);
    if (display) board.visualiseTextBoard();

    board.movePiece(5,6, 5,4);
    if (display) board.visualiseTextBoard();

    board.movePiece(4,3, 4,4);
    board.movePiece(1,6, 1,5);
    bool test5 = !board.movePiece(4,4, 5,5);
    if (display) board.visualiseTextBoard();

    // Display results
    if (display) {
        if (test0) {
            cout << "Test passed: Pawn only takes Piece en passant at [newFile]" << endl;
        } else {
            cout << "Test failed: Pawn takes Piece en passant in wrong file direction" << endl;
        }

        if (test1) {
            cout << "Test passed: Pawn takes Piece en passant" << endl;
        } else {
            cout << "Test failed: Pawn doesn't take Piece en passant" << endl;
        }

        if (test2) {
            cout << "Test passed: Pawn doesn't take Piece en passant which moved up twice" << endl;
        } else {
            cout << "Test failed: Pawn takes Piece en passant which moved up twice" << endl;
        }

        if (test3) {
            cout << "Test passed: Pawn doesn't take Piece en passant which hasn't moveed" << endl;
        } else {
            cout << "Test failed: Pawn takes Piece en passant which hasn't moved" << endl;
        }

        if (test4) {
            cout << "Test passed: Pawn takes correct Piece when one Pawn is behind another" << endl;
        } else {
            cout << "Test failed: Pawn takes incorrect Piece when one Pawn is behind another" << endl;
        }

        if (test5) {
            cout << "Test passed: En passant cannot be played after one turn has elapsed" << endl;
        } else {
            cout << "Test failed: En passant can be played after one turn has elapsed" << endl;
        }
    }

    success = test0 && test1 && test2 && test3 && test4 && test5;
    return success;
}

bool PawnTest::checkTest(bool display) {
    bool success = false;

    // Initialise objects
    Gameboard board;
    Pawn whitePawnOne('W');
    Pawn whitePawnTwo('W');
    Pawn whitePawnThree('W');
    Pawn whitePawnFour('W');
    King whiteKing('W');
    King blackKing('B');

    // Place pieces
    board.addPiece(1,7, &whiteKing);
    board.addPiece(1,4, &blackKing);
    board.addPiece(1,3, &whitePawnFour);
    board.addPiece(1,2, &whitePawnThree);
    board.addPiece(0,2, &whitePawnTwo);
    board.addPiece(2,2, &whitePawnOne);

    // Test 1: Not in check nor mate
    bool test1 = !board.isInMate('B') && !board.isInCheck('B');
    if (display) board.visualiseTextBoard();

    // Test 2: Stalemate
    board.movePiece(1,7, 1,6);
    if (display) board.visualiseTextBoard();
    bool test2 = board.isInStalemate('B');

    // Test 3: Checkmate
    board.movePiece(2,2, 2,3);
    if (display) board.visualiseTextBoard();
    bool test3 = board.isInCheckmate('B');

    // Test 4: Check
    board.movePiece(1,6, 1,7);
    if (display) board.visualiseTextBoard();
    bool test4 = board.isInCheck('B') && !board.isInMate('B');

    // Display results
    if (display) {
        if (test1) {
            cout << "Test passed: Not in check nor mate" << endl;
        } else {
            cout << "Test failed: In check and/or mate" << endl;
        }

        if (test2) {
            cout << "Test passed: Stalemate" << endl;
        } else {
            cout << "Test failed: Not in stalemate" << endl;
        }

        if (test3) {
            cout << "Test passed: Checkmate" << endl;
        } else {
            cout << "Test failed: Not in checkmate" << endl;
        }

        if (test4) {
            cout << "Test passed: Check" << endl;
        } else {
            cout << "Test failed: Not in check, or in mate" << endl;
        }
    }

    success = test1 && test2 && test3 && test4;
    return success;
}

bool PawnTest::promotionTest(bool display) {
    // Checks pawns are promoted to queens 
    // when reaching the other side of the board
    bool success = false;

    // Initialise objects
    Gameboard board;
    Pawn whitePawnOne('W');
    Pawn whitePawnTwo('W');
    Pawn blackPawnOne('B');
    Pawn blackPawnTwo('B');
    Rook whiteRook('W');
    Rook blackRook('B');

    // Place pieces
    board.addPiece(0,6, &whitePawnOne);
    board.addPiece(1,6, &whitePawnTwo);
    board.addPiece(2,7, &blackRook);
    board.addPiece(7,1, &blackPawnOne);
    board.addPiece(6,1, &blackPawnTwo);
    board.addPiece(5,0, &whiteRook);

    if (display) board.visualiseTextBoard();

    // Test 1: White pawn promotes
    board.movePiece(0,6, 0,7);
    bool test1 = board.getPiece(0,7)->getType() == 'q';
    if (display) board.visualiseTextBoard();

    // Test 2: White pawn promotes on capture
    board.movePiece(1,6, 2,7);
    bool test2 = board.getPiece(2,7)->getType() == 'q';
    if (display) board.visualiseTextBoard();

    // Test 3: Black pawn promotes
    board.movePiece(7,1, 7,0);
    bool test3 = board.getPiece(7,0)->getType() == 'q';
    if (display) board.visualiseTextBoard();

    // Test 4: Black pawn promotes on capture
    board.movePiece(6,1, 5,0);
    bool test4 = board.getPiece(5,0)->getType() == 'q';
    if (display) board.visualiseTextBoard();

    // Display results
    if (display) {
        if (test1) {
            cout << "Test passed: White pawn promotes when reaching end of board" << endl;
        } else {
            cout << "Test failed: White pawn doesn't promote to queen when reaching end of board" << endl;
        }

        if (test2) {
            cout << "Test passed: White pawn promotes when capturing" << endl;
        } else {
            cout << "Test failed: White pawn doesn't promote when capturing" << endl;
        }
        
        if (test3) {
            cout << "Test passed: Black pawn promotes when reaching end of board" << endl;
        } else {
            cout << "Test failed: Black pawn doesn't promote to queen when reaching end of board" << endl;
        }

        if (test4) {
            cout << "Test passed: Black pawn promotes when capturing" << endl;
        } else {
            cout << "Test failed: Black pawn doesn't promote when capturing" << endl;
        }
    }

    // Return
    success = test1 && test2 && test3 && test4;
    return success;
}

bool PawnTest::runTests(bool display) {

    _results[3] = enPassantTest(display && !_results[3]);
    _results[4] = promotionTest(display && !_results[4]);

    return PieceTest::runTests(display);
}