#include "../include/Gameboard.h"
#include "../include/Queen.h"
#include "../include/Rook.h"
#include "../include/Knight.h"
#include "../include/Bishop.h"
#include "CaptureTest.h"
#include <iostream>
using namespace std;

CaptureTest::CaptureTest() {
    this->_length = 2;
    this->_failMessage = "Capture test failed";
    this->_passMessage = "Capture test succeeded";
    initialiseResults();
}

bool CaptureTest::basicTest(bool display) {
    // Original capture test Driver
    bool success;

    // Create the Game board
    Gameboard board;

    // Create pieces
    Queen blackQueen('B');
    Knight whiteGKnight('W');
    Rook whiteARook('W');
    Rook blackARook('B');

    // Add the white pieces
    board.addPiece(0,0,&whiteARook);
    board.addPiece(6,0,&whiteGKnight);

    // Add the black pieces
    board.addPiece(0,7,&blackARook);
    board.addPiece(3,7,&blackQueen);
    
    // Display initial board setup
    if (display) board.visualiseTextBoard();

    // White Rook take black Rook
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
    Piece* pieces[2] = {&whiteGKnight, &whiteARook};
    int coords[4] = {3,7, 0,7};
    bool test5 = board.testDriver(pieces, coords, 2);

    if (display) {
        if (test1) {
            cout << "Test passed: Black Queen captured" << endl;
        } else {
            cout << "Test failed: Black Queen not captured" << endl;
        }

        if (test2) {
            cout << "Test passed: Black Rook captured" << endl;
        } else {
            cout << "Test failed: Black Rook not captured" << endl;
        }
        
        if (test3) {
            cout << "Test passed: White Knight not captured" << endl;
        } else {
            cout << "Test failed: White Knight captured" << endl;
        }

        if (test4) {
            cout << "Test passed: White Rook not captured" << endl;
        } else {
            cout << "Test failed: White Rook captured" << endl;
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

bool CaptureTest::teamCapture(bool display) {
    // Tests that only opposing pieces are captured
    bool success;
    
    // Create board
    Gameboard board;

    // Create pieces
    Queen blackQueen('B');
    Queen whiteQueen('W');
    Bishop blackBishop('B');
    Knight whiteKnight('W');

    // Place pieces
    board.addPiece(5,5, &blackQueen);
    board.addPiece(5,2, &whiteQueen);
    board.addPiece(1,1, &blackBishop);
    board.addPiece(7,6, &whiteKnight);
    if (display) board.visualiseTextBoard();

    // Test 1: Black Bishop take black Queen
    bool test1 = !board.movePiece(1,1, 5,5) && !blackQueen.captured();

    // Test 2: White Queen take black Queen
    bool test2 = board.movePiece(5,2, 5,5) && blackQueen.captured();
    if (display) board.visualiseTextBoard();

    // Test 3: White Knight take white Queen
    bool test3 = !board.movePiece(7,6, 5,5) && !whiteQueen.captured();

    // Test 4: Black Bishop take white Queen
    bool test4 = board.movePiece(1,1, 5,5) && whiteQueen.captured();
    if (display) board.visualiseTextBoard();

    // Test 5: White Knight take black Bishop
    bool test5 = board.movePiece(7,6, 5,5) && blackBishop.captured();

    // Test 6: All pieces in correct positions
    if (display) board.visualiseTextBoard();
    Piece* pieces[] = {&whiteKnight};
    int coords[] = {5,5};
    bool test6 = board.testDriver(pieces, coords, 1);

    // Display error messages
    if (display) {
        if (test1) {
            cout << "Test passed: Black Bishop didn't take own Queen" << endl;
        } else {
            cout << "Test failed: Black Bishop took own Queen" << endl;
        }

        if (test2) {
            cout << "Test passed: White Queen took black Queen" << endl;
        } else {
            cout << "Test failed: White Queen failed to take black Queen" << endl;
        }

        if (test3) {
            cout << "Test passed: White Knight didn't take own Queen" << endl;
        } else {
            cout << "Test failed: White Knight took own Queen" << endl;
        }

        if (test4) {
            cout << "Test passed: Black Bishop took white Queen" << endl;
        } else {
            cout << "Test failed: Black Bishop failed to take white Queen" << endl;
        }

        if (test5) {
            cout << "Test passed: White Knight took black Bishop" << endl;
        } else {
            cout << "Test failed: White Knight failed to take black Bishop" << endl;
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

bool CaptureTest::runTests(bool display) {

    _results[0] = basicTest(display && !_results[0]);
    _results[1] = teamCapture(display && !_results[1]);

    return result();
}