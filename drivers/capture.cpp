#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/king.h"
#include "../include/queen.h"
#include "../include/rook.h"
#include "../include/bishop.h"
#include "../include/knight.h"
#include "../include/pawn.h"
#include <iostream>
using namespace std;

// Tests piece capture
int main() {
    // Create the game board
    gameboard board;

    // Create pieces
    queen blackQueen = queen('B');
    knight whiteGKnight = knight();
    rook whiteARook = rook();
    rook blackARook = rook('B');

    // Add the white pieces
    board.addPiece(0,0,&whiteARook);
    board.addPiece(0,6,&whiteGKnight);

    // Add the black pieces
    board.addPiece(7,0,&blackARook);
    board.addPiece(7,3,&blackQueen);
    
    // Display initial board setup
    board.visualiseTextBoard();

    // White rook take black rook
    board.movePiece(0,0, 7,0);

    // Knight take Queen
    board.movePiece(0,6, 2,7);
    board.movePiece(2,7, 4,6);
    board.movePiece(4,6, 5,4);
    board.movePiece(5,4, 7,3);

    // Display final board
    board.visualiseTextBoard();

    // Test: Black pieces captured
    if (blackQueen.captured()) {
        cout << "Test passed: Black queen captured." << endl;
    } else {
        cout << "Test failed: Black queen not captured." << endl;
    }
    if (blackARook.captured()) {
        cout << "Test passed: Black rook captured." << endl;
    } else {
        cout << "Test failed: Black rook not captured." << endl;
    }

    // Test: White pieces not captured
    if (!whiteGKnight.captured()) {
        cout << "Test passed: White knight not captured." << endl;
    } else {
        cout << "Test failed: White knight captured." << endl;
    }
    if (!whiteARook.captured()) {
        cout << "Test passed: White rook not captured." << endl;
    } else {
        cout << "Test failed: White rook captured." << endl;
    }

    // Check all pieces in correct spot
    piece* pieces[2] = {&whiteGKnight, &whiteARook};
    int coords[4] = {7,3, 7,0};
    if(board.testDriver(pieces, coords, 2)) {
        cout << "Test passed: All pieces in correct position." << endl;
    } else {
        cout << "Test failed: Pieces not in correct position." << endl;
    }

    return 0;
}