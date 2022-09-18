#include "../include/gameboard.h"
#include "../include/queen.h"
#include "../include/rook.h"
#include "../include/knight.h"
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

bool capturetest::runTests(bool display) {
    bool success = true;
    success = success && this->basicTest(display);
    return success;
}