#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/rook.h"
#include <iostream>
using namespace std;

int main() {
    // Create the game board and two rooks
    gameboard board;
    rook white_a_rook = rook('W');
    rook black_a_rook = rook('B');

    // Add the rooks to the game board
    board.addPiece(0,0,&white_a_rook);
    board.addPiece(7,0,&black_a_rook);
    
    board.visualiseTextBoard();

    // Move the rooks to illegal positions
    board.movePiece(0,0, 1,1);
    board.movePiece(7,0, 4,6);

    board.visualiseTextBoard();

    // Move the rooks to legal positions
    board.movePiece(0,0, 0,3);
    board.movePiece(7,0, 7,7);

    // Move the rooks to their own positions
    board.movePiece(0,3, 0,3);
    board.movePiece(7,7, 7,7);

    // Move the rooks outside the game board
    board.movePiece(0,3, -1,3);
    board.movePiece(7,7, 7,8);
    board.movePiece(0,32, 1,3);
    board.movePiece(-7,7, 8,7);

    board.visualiseTextBoard();

    // Test: Both rooks uncaptured
    if (!white_a_rook.captured() && !black_a_rook.captured()) {
        cout << "Test passed: Neither rook captured" << endl;
    } else {
        cout << "Test failed: Rook captured" << endl;
    }

    // Test: rooks in correct positions
    piece* pieces[] = {&white_a_rook, &black_a_rook};
    int coords[] = {0,3, 7,7};
    if (board.testDriver(pieces, coords, 2)) {
        cout << "Test passed: All pieces in correct position" << endl;
    } else {
        cout << "Test failed: Pieces in incorrect position" << endl;
    }

    return 0;
}