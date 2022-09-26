#include "../include/gameboard.h"
#include "../include/pawn.h"
#include "pawntest.h"
#include <iostream>
using namespace std;

pawntest::pawntest(): pawntest(1) {}
pawntest::pawntest(int length) {
    this->_failMessage = "Pawn test failed";
    this->_passMessage = "Pawn test succeeded";
}

bool pawntest::movementTest(bool display) {
    // Test pawn movement
    bool success = true;

    // Create the game board and two pawns.
    gameboard board;
    pawn whiteCpawn = pawn();
    pawn blackFPawn = pawn('B');
    piece* pieces[] = {&whiteCpawn, &blackFPawn};

    // Add the pawns to the game board
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

bool pawntest::captureTest(bool display) {
    // Test pawn movement with capturing
    bool success = true;

    // Create the game board and two pawns.
    gameboard board;
    pawn whiteDpawn = pawn();
    pawn whiteEpawn = pawn();
    pawn blackDpawn = pawn('B');
    pawn blackEpawn = pawn('B');
    piece* pieces[] = {&whiteDpawn, &whiteEpawn, &blackDpawn, &blackEpawn};

    // Add the pawns to the game board
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
    
    // Capture black's E pawn with white's D pawn, then recapture with black's D pawn 3. dxe5 dxe5
    board.movePiece(3,3, 4,4);
    board.movePiece(3,5, 4,4);

    // Check to ensure the captures were successful
    piece* remainingPieces[] = {&whiteEpawn, &blackDpawn};
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

bool pawntest::enPassantTest(bool display) {
    // Test en passant feature
    bool success = false;
    
    // Initialise objects
    gameboard board;
    pawn blackPawnOne('B');
    pawn blackPawnTwo('B');
    pawn blackPawnThree('B');
    pawn blackPawnFour('B');
    pawn blackPawnFive('B');
    pawn whitePawnOne('W');
    pawn whitePawnTwo('W');
    pawn whitePawnThree('W');
    pawn whitePawnFour('W');

    // Place pieces
    board.addPiece(2,6, &blackPawnOne);
    board.addPiece(3,4, &whitePawnOne);
    if (display) board.visualiseTextBoard();
    board.movePiece(2,6, 2,4);
    if (display) board.visualiseTextBoard();

    // Test case 0: move pawn wrong way
    bool test0 = !board.movePiece(3,4, 4,5);

    // Test case 1: regular en passant
    board.movePiece(3,4, 2,5); // White captures
    if (display) board.visualiseTextBoard();

    piece* pieces[1] = {&whitePawnOne};
    int coords[] = {2,5};
    bool test1 = blackPawnOne.captured() && board.testDriver(pieces, coords, 1);

    board.removePiece(2,5);

    // Test case 2: illegal en passant (move piece up twice)
    board.addPiece(2,6, &blackPawnTwo);
    board.addPiece(3,4, &whitePawnTwo);

    board.movePiece(2,6, 2,5);
    if (display) board.visualiseTextBoard();
    board.movePiece(2,5, 2,4);
    if (display) board.visualiseTextBoard();
    board.movePiece(3,4, 2,5); // White attempts to capture
    board.movePiece(2,4, 3,3); // Black attempts to capture
    if (display) board.visualiseTextBoard();

    piece* pieces2[] = {&whitePawnTwo, &blackPawnTwo};
    int coords2[] = {3,4, 2,4};
    bool test2 = board.testDriver(pieces2, coords2, 2);

    board.removePiece(2,4);
    board.removePiece(3,4);

    // Test case 3: illegal en passant (never move piece)
    board.addPiece(2,6, &blackPawnThree);
    board.addPiece(3,4, &whitePawnThree);
    
    board.movePiece(3,4, 3,5);
    board.movePiece(3,5, 3,6);
    if (display) board.visualiseTextBoard();
    board.movePiece(3,6, 4,7); // White attemps to capture

    piece* pieces3[] = {&whitePawnThree, &blackPawnThree};
    int coords3[] = {3,6, 2,6};
    bool test3 = board.testDriver(pieces3, coords3, 2);
    
    if (display) board.visualiseTextBoard();
    board.removePiece(3,6);
    board.removePiece(2,6);

    // Test case 4: Take diagonally with pawn next to piece
    board.addPiece(3,4, &whitePawnFour);
    board.addPiece(4,4, &blackPawnFour);
    board.addPiece(4,5, &blackPawnFive);
    if (display) board.visualiseTextBoard();
    board.movePiece(3,4, 4,5);
    if (display) board.visualiseTextBoard();

    piece* pieces4[] = {&whitePawnFour, &blackPawnFour};
    int coords4[] = {4,5, 4,4};

    bool test4 = board.testDriver(pieces4, coords4, 2);

    // Display results
    if (display) {
        if (test0) {
            cout << "Test passed: Pawn only takes piece en passant at [newFile]" << endl;
        } else {
            cout << "Test failed: Pawn takes piece en passant in wrong file direction" << endl;
        }

        if (test1) {
            cout << "Test passed: Pawn takes piece en passant" << endl;
        } else {
            cout << "Test failed: Pawn doesn't take piece en passant" << endl;
        }

        if (test2) {
            cout << "Test passed: Pawn doesn't take piece en passant which moved up twice" << endl;
        } else {
            cout << "Test failed: Pawn takes piece en passant which moved up twice" << endl;
        }

        if (test3) {
            cout << "Test passed: Pawn doesn't take piece en passant which hasn't moveed" << endl;
        } else {
            cout << "Test failed: Pawn takes piece en passant which hasn't moved" << endl;
        }

        if (test4) {
            cout << "Test passed: Pawn takes correct piece when one pawn is behind another" << endl;
        } else {
            cout << "Test failed: Pawn takes incorrect piece when one pawn is behind another" << endl;
        }
    }

    success = test0 && test1 && test2 && test3 && test4;
    return success;
}

bool pawntest::runTests(bool display) {
    bool success = true;
    //success = success && this->movementTest(display);
    //success = success && this->captureTest(display);
    success = success && this->enPassantTest(display);
    return success;
}