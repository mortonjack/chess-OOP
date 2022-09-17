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
    
    // Check to ensure our rooks were added properly
    board.visualiseTextBoard();

    // Move the rooks to illegal positions
    board.movePiece(0,0, 1,1);
    board.movePiece(7,0, 4,6);

    // Check to ensure our nothing has happened
    board.visualiseTextBoard();

    // Move the rooks to legal positions
    board.movePiece(0,0, 0,3);
    board.movePiece(7,0, 7,7);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();

    return 0;
}