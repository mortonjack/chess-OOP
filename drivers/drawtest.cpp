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

drawtest::drawtest(): drawtest(1) {}
drawtest::drawtest(int length) {
    this->_failMessage = "Draw test failed";
    this->_passMessage = "Draw test succeeded";
}


bool drawtest::stalemateTest(bool display) {
    // Tests the stalemate function
    // Stalemate occurs when a player 
    // cannot make a legal move on their turn
    bool success = false;

    return success;
}

bool drawtest::threefoldTest(bool display) {
    // Tests the threefold repetition function
    // Threefold repetition occurs when the same
    // board state occurs 3 turns in a row
    // and the player who's turn it is requests a draw
    // their draw request is automatically accepted
    bool success = false;

    return success;
}

bool drawtest::fiftyMoveTest(bool display) {
    // Tests the fifty move function
    // If fifty moves have passed without a piece being captured
    // or a pawn being moved,
    // and the player who's turn it is requests a draw
    // their draw request is automatically accepted
    bool success = false;

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
    bool success = false;

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