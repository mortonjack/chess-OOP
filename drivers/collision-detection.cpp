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

// Tests whether the game's collision detection system is functional
int main() {
    // Create the game board
    gameboard board;

    // Create pieces
    queen whiteQueen = queen();
    bishop blackFBishop = bishop('B');
    knight whiteGKnight = knight();
    rook blackARook = rook('B');
    pawn whiteDPawn = pawn();
    pawn blackEPawn = pawn('B');

    // Add the white pieces
    board.addPiece(0,3,&whiteQueen);
    board.addPiece(0,6,&whiteGKnight);
    board.addPiece(1,3,&whiteDPawn);

    // Add the black pieces
    board.addPiece(7,0,&blackARook);
    board.addPiece(7,5,&blackFBishop);
    board.addPiece(6,4,&blackEPawn);

    // Check to ensure the board was setup properly
    board.visualiseTextBoard();

    // Make legal moves with some of the pieces
    // According to the line 1. Pd4 pe5 2. Nf3 bc5 3. Qa4 ra5

    // 1. Testing the pawns
    board.movePiece(1,3, 3,3);
    board.movePiece(6,4, 5,4);

    // 2. Testing the knight and bishop
    board.movePiece(0,6, 2,5);
    board.movePiece(7,5, 4,2);

    // 3. Testing the queen and rook
    board.movePiece(0,3, 3,0);
    board.movePiece(7,0, 4,0);

    board.visualiseTextBoard();

    // Try to move the rook through the queen, the queen through the d-pawn 
    // and the bishop through the d-pawn
    board.movePiece(4,0, 2,0);
    board.movePiece(3,0, 3,5);
    board.movePiece(4,2, 2,4);

    // Have the bishop capture the pawn, the knight capture the bishop, 
    // and the queen capture the rook
    board.movePiece(4,2, 3,3);
    board.movePiece(2,5, 3,3);
    board.movePiece(3,0, 4,0);

    board.visualiseTextBoard();

    // Check collision detection worked
    piece* pieces[] = {&whiteQueen, &whiteGKnight, &blackEPawn};
    int coords[] = {4,0, 3,3, 5,4};
    if (board.testDriver(pieces, coords, 3)) {
        cout << "Test passed: All pieces in correct position" << endl;
    } else {
        cout << "Test failed: Pieces in incorrect positions" << endl;
    }

    if (blackARook.captured() && blackFBishop.captured() && whiteDPawn.captured()) {
        cout << "Test passed: Correct pieces successfuly captured" << endl;
    } else {
        cout << "Test failed: Some pieces not captured" << endl;
    }

    if (!whiteQueen.captured() && !whiteGKnight.captured() && !blackEPawn.captured() ) {
        cout << "Test passed: Correct pieces uncaptured" << endl;
    } else {
        cout << "Test failed: Some pieces incorrectly captured" << endl;
    }

    return 0; 
}