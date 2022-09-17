#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/king.h"
#include <iostream>
using namespace std;

int main() {
    // Create the game board and two kings.
    gameboard board;
    king testKing = king();

    // Add the king to the game board
    board.addPiece(3,3,&testKing);
    
    // Check to ensure the king was added properly
    board.visualiseTextBoard();

    // Test all valid move directions- move king in a circle
    board.movePiece(3,3, 3,2);
    board.movePiece(3,2, 2,1);
    board.movePiece(2,1, 1,1);
    board.movePiece(1,1, 0,2);
    board.movePiece(0,2, 0,3);
    board.visualiseTextBoard(); // D1
    board.movePiece(0,3, 1,4);
    board.movePiece(1,4, 2,4);
    board.movePiece(2,4, 3,3);
    board.visualiseTextBoard(); // D4

    // Test invalid move directions
    board.movePiece(3,3, 1,3);
    board.movePiece(3,3, 2,1);
    board.movePiece(3,3, 5,4);

    // Check to ensure the king hasn't moved
    board.visualiseTextBoard();

    return 0;
}