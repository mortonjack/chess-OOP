#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/knight.h"
#include <iostream>
using namespace std;

int main() {
    // Create the game board and two knights.
    gameboard board;
    knight white_a_knight = knight();
    knight black_a_knight = knight('B');


    // Add the quenes to the game board
    board.addPiece(0,0,&white_a_knight);
    board.addPiece(7,0,&black_a_knight);
    
    // Check to ensure our quenes were added properly
    board.visualiseTextBoard();

    // Move the knights to illegal positions
    board.movePiece(0,0, 2,2);
    board.movePiece(7,0, 4,0);

    // Check to ensure our nothing has happened
    board.visualiseTextBoard();

    // Move the knights to legal positions 
    board.movePiece(0,0, 1,2);
    board.movePiece(7,0, 5,1);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();

    // Move the knights to legal positions 
    board.movePiece(1,2, 2,4);
    board.movePiece(5,1, 7,2);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();

    return 0;
}