#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/rook.h"
#include "../include/pawn.h"
#include <iostream>
using namespace std;

int main() {
    // Create the game board and a rook and pawn;
    gameboard board;
    rook blackARook = rook('B');
    pawn whiteCPawn = pawn();

    // Add the pieces to the game board
    board.addPiece(7,0,&blackARook);
    board.addPiece(1,2,&whiteCPawn);
    
    // Check to ensure our pieces were added properly
    board.visualiseTextBoard();

    // Move the rook to a legal position
    board.movePiece(7,0, 7,2);
    board.movePiece(7,2, 4,2);

    // Check to ensure these moves worked
    board.visualiseTextBoard();

    // Try to move our rook through our pawn
    board.movePiece(4,2, 0,2);

    // Check to ensure this move was unsuccessful
    board.visualiseTextBoard();

    // Move our rook in front of the pawn
    board.movePiece(4,2, 2,2);

    // Check to ensure this move worked
    board.visualiseTextBoard();

    // Try to move the pawn through the rook
    board.movePiece(1,2, 3,2);

    // Check to ensure this move was unsuccessful
    board.visualiseTextBoard();

    return 0;
}