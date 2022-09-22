#include "../include/gameboard.h"
#include "../include/queen.h"
#include "../include/rook.h"
#include "../include/knight.h"
#include "../include/bishop.h"
#include "capturetest.h"
#include <iostream>
using namespace std;

capturetest::capturetest(): capturetest(1) {}
capturetest::capturetest(int length) {
    this->_failMessage = "Capture test failed";
    this->_passMessage = "Capture test succeeded";
}

bool capturetest::basicTest(bool display) {
    // Original capture test driver
    bool success;

    // Create the game board
    gameboard board;

    // Create pieces
    queen blackQueen = queen('B');
    knight whiteGKnight = knight();
    rook whiteARook = rook();
    rook blackARook = rook('B');

    // Add the white pieces
    board.addPiece(0,0,&whiteARook);
    board.addPiece(6,0,&whiteGKnight);

    // Add the black pieces
    board.addPiece(0,7,&blackARook);
    board.addPiece(3,7,&blackQueen);
    
    // Display initial board setup
    if (display) board.visualiseTextBoard();

    // White rook take black rook
    board.movePiece(0,0, 0,7);
    if (display) board.visualiseTextBoard();

    // Knight take Queen
    board.movePiece(6,0, 7,2);
    board.movePiece(7,2, 6,4);
    board.movePiece(6,4, 4,5);
    if (display) board.visualiseTextBoard();
    board.movePiece(4,5, 3,7);

    // Display final board
    if (display) board.visualiseTextBoard();

    // Test: Black pieces captured
    bool test1 = blackQueen.captured();
    bool test2 = blackARook.captured();

    // Test: White pieces not captured
    bool test3 = !whiteGKnight.captured();
    bool test4 = !whiteARook.captured();

    // Check all pieces in correct spot
    piece* pieces[2] = {&whiteGKnight, &whiteARook};
    int coords[4] = {3,7, 0,7};
    bool test5 = board.testDriver(pieces, coords, 2);

    if (display) {
        if (test1) {
            cout << "Test passed: Black queen captured" << endl;
        } else {
            cout << "Test failed: Black queen not captured" << endl;
        }

        if (test2) {
            cout << "Test passed: Black rook captured" << endl;
        } else {
            cout << "Test failed: Black rook not captured" << endl;
        }
        
        if (test3) {
            cout << "Test passed: White knight not captured" << endl;
        } else {
            cout << "Test failed: White knight captured" << endl;
        }

        if (test4) {
            cout << "Test passed: White rook not captured" << endl;
        } else {
            cout << "Test failed: White rook captured" << endl;
        }

        if(test5) {
            cout << "Test passed: All pieces in correct position" << endl;
        } else {
            cout << "Test failed: Pieces not in correct position" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5;
    return success;
}

bool capturetest::teamCapture(bool display) {
    // Tests that only opposing pieces are captured
    bool success;
    
    // Create board
    gameboard board;

    // Create pieces
    queen blackQueen = queen('B');
    queen whiteQueen = queen('W');
    bishop blackBishop = bishop('B');
    knight whiteKnight = knight('W');

    // Place pieces
    board.addPiece(5,5, &blackQueen);
    board.addPiece(5,2, &whiteQueen);
    board.addPiece(1,1, &blackBishop);
    board.addPiece(7,6, &whiteKnight);
    if (display) board.visualiseTextBoard();

    // Test 1: Black bishop take black queen
    bool test1 = !board.movePiece(1,1, 5,5) && !blackQueen.captured();

    // Test 2: White queen take black queen
    bool test2 = board.movePiece(5,2, 5,5) && blackQueen.captured();
    if (display) board.visualiseTextBoard();

    // Test 3: White knight take white queen
    bool test3 = !board.movePiece(7,6, 5,5) && !whiteQueen.captured();

    // Test 4: Black bishop take white queen
    bool test4 = board.movePiece(1,1, 5,5) && whiteQueen.captured();
    if (display) board.visualiseTextBoard();

    // Test 5: White knight take black bishop
    bool test5 = board.movePiece(7,6, 5,5) && blackBishop.captured();

    // Test 6: All pieces in correct positions
    if (display) board.visualiseTextBoard();
    piece* pieces[] = {&whiteKnight};
    int coords[] = {5,5};
    bool test6 = board.testDriver(pieces, coords, 1);

    // Display error messages
    if (display) {
        if (test1) {
            cout << "Test passed: Black bishop didn't take own queen" << endl;
        } else {
            cout << "Test failed: Black bishop took own queen" << endl;
        }

        if (test2) {
            cout << "Test passed: White queen took black queen" << endl;
        } else {
            cout << "Test failed: White queen failed to take black queen" << endl;
        }

        if (test3) {
            cout << "Test passed: White knight didn't take own queen" << endl;
        } else {
            cout << "Test failed: White knight took own queen" << endl;
        }

        if (test4) {
            cout << "Test passed: Black bishop took white queen" << endl;
        } else {
            cout << "Test failed: Black bishop failed to take white queen" << endl;
        }

        if (test5) {
            cout << "Test passed: White knight took black bishop" << endl;
        } else {
            cout << "Test failed: White knight failed to take black bishop" << endl;
        }

        if (test6) {
            cout << "Test passed: All pieces in correct position" << endl;
        } else {
            cout << "Test failed: Pieces in incorrect positions" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6;
    return success;
}

bool capturetest::runTests(bool display) {
    bool success = true;
    success = success && this->basicTest(display);
    success = success && this->teamCapture(display);
    return success;
}