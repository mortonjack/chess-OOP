#include "../include/gameboard.h"
#include "../include/bishop.h"
#include "../include/queen.h"
#include "../include/rook.h"
#include "../include/pawn.h"
#include "../include/knight.h"
#include "collisiontest.h"
#include <iostream>
using namespace std;

collisiontest::collisiontest(): collisiontest(1) {}
collisiontest::collisiontest(int length) {
    this->_failMessage = "Collision test failed";
    this->_passMessage = "Collision test succeeded";
}

bool collisiontest::baseTest(bool display) {
    // Test collisions
    bool success = true;

    // Create the game board
    gameboard board;

    // Create pieces
    queen whiteQueen = queen();
    bishop blackFBishop = bishop('B');
    knight whiteGKnight = knight();
    rook blackARook = rook('B');
    pawn whiteDPawn = pawn();
    pawn blackEPawn = pawn('B');
    
    piece* pieces[] = {&whiteQueen, &whiteGKnight, &whiteDPawn, &blackARook, &blackFBishop, &blackEPawn};

    // Add the white pieces
    board.addPiece(0,3,&whiteQueen);
    board.addPiece(0,6,&whiteGKnight);
    board.addPiece(1,3,&whiteDPawn);

    // Add the black pieces
    board.addPiece(7,0,&blackARook);
    board.addPiece(7,5,&blackFBishop);
    board.addPiece(6,4,&blackEPawn);

    // Check to ensure the board was setup properly
    if (display) board.visualiseTextBoard();
    int coords0[] = {0,3, 0,6, 1,3, 7,0, 7,5, 6,4};
    bool test0 = board.testDriver(pieces, coords0, 6);

    // Make legal moves with some of the pieces
    // According to the line 1. Pd4 pe5 2. Nf3 bc5 3. Qa4 ra5

    // 1. Testing the pawns
    board.movePiece(1,3, 3,3);
    board.movePiece(6,4, 5,4);
    int coords1[] = {0,3, 0,6, 3,3, 7,0, 7,5, 5,4};
    bool test1 = board.testDriver(pieces, coords1, 6);
    if (display) board.visualiseTextBoard();

    // 2. Testing the knight and bishop
    board.movePiece(0,6, 2,5);
    board.movePiece(7,5, 4,2);
    int coords2[] = {0,3, 2,5, 3,3, 7,0, 4,2, 5,4};
    bool test2 = board.testDriver(pieces, coords2, 6);
    if (display) board.visualiseTextBoard();

    // 3. Testing the queen and rook
    board.movePiece(0,3, 3,0);
    board.movePiece(7,0, 4,0);
    int coords3[] = {3,0, 2,5, 3,3, 4,0, 4,2, 5,4};
    bool test3 = board.testDriver(pieces, coords3, 6);
    if (display) board.visualiseTextBoard();

    // Try to move the rook through the queen, the queen through the d-pawn 
    // and the bishop through the d-pawn
    board.movePiece(4,0, 2,0);
    board.movePiece(3,0, 3,5);
    board.movePiece(4,2, 2,4);

    if (display) board.visualiseTextBoard();
    bool test4 = board.testDriver(pieces, coords3, 6);

    // Have the bishop capture the pawn, the knight capture the bishop, 
    // and the queen capture the rook
    board.movePiece(4,2, 3,3);
    board.movePiece(2,5, 3,3);
    board.movePiece(3,0, 4,0);

    if (display) board.visualiseTextBoard();
    piece* pieces2[] = {&whiteQueen, &whiteGKnight, &blackEPawn};
    int coords4[] = {4,0, 3,3, 5,4};
    bool test5 = board.testDriver(pieces2, coords4, 3);

    // Ensure correct pieces captured
    bool test6 = blackARook.captured() && blackFBishop.captured() && whiteDPawn.captured();
    bool test7 = !whiteQueen.captured() && !whiteGKnight.captured() && !blackEPawn.captured();

    // Output error messages
    if (display) {
        if (test0) {
            cout << "Test passed: Board set up correctly" << endl;
        } else {
            cout << "Test failed: Board set up incorrectly" << endl;
        }

        if (test1) {
            cout << "Test passed: Pawns moved successfully" << endl;
        } else {
            cout << "Test failed: Pawns failed to move" << endl;
        }

        if (test2) {
            cout << "Test passed: Knight and bishop moved successfully" << endl;
        } else {
            cout << "Test failed: Knight and bishop failed to move" << endl;
        }

        if (test3) {
            cout << "Test passed: Queen and rook moved successfully" << endl;
        } else {
            cout << "Test failed: Queen and rook failed to move" << endl;
        }

        if (test4) {
            cout << "Test passed: Collision prevented illegal movement" << endl;
        } else {
            cout << "Test failed: Illegal movement (collision detection not working)" << endl;
        }

        if (test5) {
            cout << "Test passed: Captures succesful" << endl;
        } else {
            cout << "Test failed: Captures failed to succeed" << endl;
        }

        if (test6) {
            cout << "Test passed: Correct pieces successfully captured" << endl;
        } else {
            cout << "Test failed: Some pieces not captured" << endl;
        }

        if (test7) {
            cout << "Test passed: Correct pieces uncaptured" << endl;
        } else {
            cout << "Test failed: Some pieces incorrectly captured" << endl;
        }
    }

    success = test0 && test1 && test2 && test3 && test4 && test5 && test6 && test7;
    return success;
}

bool collisiontest::vertTest(bool display) {
    // Test vertical collision
    bool success = true;
    // Create the game board and a rook and pawn;
    gameboard board;
    rook blackARook = rook('B');
    pawn whiteCPawn = pawn();
    pawn whiteDPawn = pawn();
    piece* pieces[] = {&blackARook, &whiteCPawn, &whiteDPawn};

    // Add the pieces to the game board
    board.addPiece(7,0,&blackARook);
    board.addPiece(1,2,&whiteCPawn);
    board.addPiece(1,3,&whiteDPawn);

    if (display) board.visualiseTextBoard();

    // Move the rook to a legal position
    board.movePiece(7,0, 7,2);
    board.movePiece(7,2, 4,2);

    // Check to ensure these moves worked
    if (display) board.visualiseTextBoard();
    int coords[] = {4,2, 1,2, 1,3};
    bool test1 = board.testDriver(pieces, coords, 3);

    // Try to move our rook through our pawn
    board.movePiece(4,2, 0,2);

    // Check to ensure this move was unsuccessful
    if (display) board.visualiseTextBoard();
    bool test2 = board.testDriver(pieces, coords, 3);

    // Move our rook in front of the pawn
    board.movePiece(4,2, 2,2);

    // Check to ensure this move worked
    if (display) board.visualiseTextBoard();
    int coords2[] = {2,2, 1,2, 1,3};
    bool test3 = board.testDriver(pieces, coords2, 3);

    // Try to move the pawn through the rook
    board.movePiece(1,2, 3,2);

    // Check to ensure this move was unsuccessful
    if (display) board.visualiseTextBoard();
    bool test4 = board.testDriver(pieces, coords2, 3);

    // Try to move the d-pawn forward
    board.movePiece(1,3, 3,3);

    // Check to ensure this move was successful
    if (display) board.visualiseTextBoard();
    int coords3[] = {2,2, 1,2, 3,3};
    bool test5 = board.testDriver(pieces, coords3, 3);

    if (display) {
        if (test1) {
            cout << "Test passed: Rook moved successfully" << endl;
        } else {
            cout << "Test failed: Rook failed to move" << endl;
        }

        if (test2) {
            cout << "Test passed: Pawn blocked the rook's move" << endl;
        } else {
            cout << "Test failed: Pawn didn't block the rook" << endl;
        }

        if (test3) {
            cout << "Test passed: Rook moved successfully" << endl;
        } else {
            cout << "Test failed: Rook failed to move" << endl;
        }

        if (test4) {
            cout << "Test passed: Rook blocked the pawn's move" << endl;
        } else {
            cout << "Test failed: Rook didn't block the pawn" << endl;
        }

        if (test5) {
            cout << "Test passed: Pawn moved successfully" << endl;
        } else {
            cout << "Test failed: Pawn failed to move" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5;
    return success;
}

bool collisiontest::runTests(bool display) {
    bool success = true;
    success = success && this->baseTest(display);
    success = success && this->vertTest(display);
    return success;
}