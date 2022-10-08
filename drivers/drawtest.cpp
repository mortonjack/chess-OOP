#include "../include/gameboard.h"
#include "../include/king.h"
#include "../include/bishop.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include "../include/pawn.h"
#include "../include/knight.h"
#include "drawtest.h"
#include <iostream>
using namespace std;

drawtest::drawtest() {
    this->_length = 5;
    this->_failMessage = "Draw test failed";
    this->_passMessage = "Draw test succeeded";
    initialiseResults();
}


bool drawtest::stalemateTest(bool display) {
    // Tests the stalemate function
    // Stalemate occurs when a player 
    // cannot make a legal move on their turn
    bool success = false;

    // Initialise objects
    gameboard board;
    king whiteKing('W');
    king blackKing('B');
    queen whiteQueen('W');

    // Set up board
    board.addPiece(0,7, &blackKing);
    board.addPiece(1,5, &whiteKing);
    board.addPiece(7,6, &whiteQueen);

    // Test 1: Not in stalemate
    if (display) board.visualiseTextBoard();
    bool test1 = !board.isInStalemate('B');

    // Test 2: In stalemate when queen moves to C7
    board.movePiece(7,6, 2,6);
    if (display) board.visualiseTextBoard();
    bool test2 = board.isInStalemate('B');

    // Test 3: White not also in stalemate
    bool test3 = !board.isInStalemate('W');

    // Test 4: Not in stalemate whilst in check
    board.movePiece(2,6, 1,6);
    bool test4 = !board.isInStalemate('B') && board.isInCheckmate('B');
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Not in stalemate" << endl;
        } else {
            cout << "Test failed: Stalemate" << endl;
        }

        if (test2) {
            cout << "Test passed: Stalemate" << endl;
        } else {
            cout << "Test failed: Not in stalemate" << endl;
        }

        if (test3) {
            cout << "Test passed: White not in stalemate" << endl;
        } else {
            cout << "Test failed: White in stalemate" << endl;
        }

        if (test4) {
            cout << "Test passed: Not in stalemate (checkmate)" << endl;
        } else {
            cout << "Test failed: Stalemate" << endl;
        }
    }

    success = test1 && test2 && test3 && test4;
    return success;
}

bool drawtest::threefoldTest(bool display) {
    // Tests the threefold repetition function
    // Threefold repetition occurs when the same
    // board state occurs 3 turns in a row
    // and the player who's turn it is requests a draw
    // their draw request is automatically accepted
    bool success = true;

    return success;
}

bool drawtest::fiftyMoveTest(bool display) {
    // Tests the fifty move function
    // If fifty moves have passed without a piece being captured
    // or a pawn being moved,
    // and the player who's turn it is requests a draw
    // their draw request is automatically accepted
    bool success = true;

    return success;
}

bool drawtest::mutualTest(bool display) {
    // If both players mutually agree to draw,
    // the game will result in a draw
    bool success = true;

    return success;
}

bool drawtest::deadTest(bool display) {
    // If no player can legally checkmate the opponent's king,
    // the game automatically ends in a draw
    bool success = true;

    return success;
}

bool drawtest::runTests(bool display) {
    bool success = true;
    
    success = success && stalemateTest(display);
    success = success && threefoldTest(display);
    success = success && fiftyMoveTest(display);
    success = success && mutualTest(display);
    success = success && deadTest(display);

    return success;
}