#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/pawn.h"
#include <iostream>
using namespace std;

int main() {
    // Create the game board and two pawns.
    gameboard board;
    pawn whiteCpawn = pawn();
    pawn blackFPawn = pawn('B');


    // Add the pawns to the game board
    board.addPiece(6,2,&whiteCpawn);
    board.addPiece(1,5,&blackFPawn);
    
    // Check to ensure our pawns were added properly
    board.visualiseTextBoard();

    // Move the pawns to illegal positions
    board.movePiece(6,2, 7,2);
    board.movePiece(1,5, 0,5);
    board.movePiece(6,2, 6,3);
    board.movePiece(1,5, 1,4);

    // Check to ensure our nothing has happened
    board.visualiseTextBoard();

    // Move the pawns to legal positions 
    board.movePiece(6,2, 5,2);
    board.movePiece(1,5, 2,5);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();

    return 0;
}