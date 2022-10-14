#include "SaveTest.h"
#include "../include/Game.hpp"
#include <iostream>
using std::cout;
using std::endl;

SaveTest::SaveTest() {
    this->_length = 2;
    this->_failMessage = "Save test failed";
    this->_passMessage = "Save test succeeded";
    initialiseResults();
}

bool SaveTest::directTest(bool display) {
    bool success = false;

    // Initialise objects
    Gameboard board;
    Pawn whitePawnOne('W');
    Pawn whitePawnTwo('W');
    Pawn blackPawn('B');
    Rook blackRook('B');
    King blackKing('B');
    King whiteKing('W');

    // Place pieces
    board.addPiece(5,6, &whitePawnOne);
    board.addPiece(6,1, &whitePawnTwo);
    board.addPiece(3,6, &blackPawn);
    board.addPiece(7,7, &blackKing);
    board.addPiece(0,7, &blackRook);
    board.addPiece(3,0, &whiteKing);
    if (display) board.visualiseTextBoard();

    // Make moves
    board.movePiece(3,6, 3,5);
    board.movePiece(5,6, 5,7);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,7, 5,7);
    board.movePiece(6,1, 6,3);
    board.movePiece(3,5, 3,4);
    if (display) board.visualiseTextBoard();

    // Save game state
    State savestate;

    // Destroy existing objects


    // Load game state


    return success;
}

bool SaveTest::gameTest(bool display) {
    // Tests game.hpp saves/loads correctly
    bool success = true;

    return success;
}

bool SaveTest::runTests(bool display) {
    _results[0] = directTest(display && !_results[0]);
    _results[1] = gameTest(display && !_results[1]);

    return result();
}