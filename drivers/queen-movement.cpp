#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/queen.h"
#include <iostream>
using namespace std;

int main() {
    // Create the game board and two queens.
    gameboard board;
    queen whiteAQueen = queen();
    queen blackAQueen = queen('B');


    // Add the quenes to the game board
    board.addPiece(0,0,&whiteAQueen);
    board.addPiece(7,0,&blackAQueen);
    
    // Check to ensure our queens were added properly
    board.visualiseTextBoard();

    // Move the queens to illegal positions
    board.movePiece(0,0, 1,2);
    board.movePiece(7,0, 4,6);

    // Check to ensure our nothing has happened
    board.visualiseTextBoard();

    // Move the queens to legal positions (sideways)
    board.movePiece(0,0, 0,3);
    board.movePiece(7,0, 7,7);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();

    // Move the queens to legal positions (diagonal)
    board.movePiece(0,3, 3,0);
    board.movePiece(7,7, 3,3);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();

    return 0;
}