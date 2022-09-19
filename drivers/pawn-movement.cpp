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
    piece* pieces[] = {&whiteCpawn, &blackFPawn};

    // Add the pawns to the game board
    board.addPiece(1,5,&whiteCpawn);
    board.addPiece(6,2,&blackFPawn);
    
    board.visualiseTextBoard();

    // Move the pawns to illegal positions
    board.movePiece(6,2, 7,2);
    board.movePiece(1,5, 0,5);
    board.movePiece(6,2, 6,3);
    board.movePiece(1,5, 4,5);

    // Check to ensure nothing has happened
    board.visualiseTextBoard();
    int coords[] = {1,5, 6,2};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the pawns to legal positions 
    board.movePiece(6,2, 4,2);
    board.movePiece(1,5, 2,5);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();
    int coords2[] = {2,5, 4,2};
    bool test2 = board.testDriver(pieces, coords2, 2);

    // Move the pawns to illegal positions
    board.movePiece(4,2, 2,2);
    board.movePiece(2,5, 4,5);

    // Check to ensure nothing has happened
    board.visualiseTextBoard();
    bool test3 = board.testDriver(pieces, coords2, 2);

    if (test1) {
        cout << "Test passed: Pawns didn't move" << endl;
    } else {
        cout << "Test failed: Pawns moved backwards, sideways, and/or up 3 tiles" << endl;
    }

    if (test2) {
        cout << "Test passed: Pawns moved up" << endl;
    } else {
        cout << "Test failed: Pawns failed to move up one and/or two tiles" << endl;
    }

    if (test3) {
        cout << "Test passed: Pawns didn't move" << endl;
    } else {
        cout << "Test failed: Pawns moved up twice on second move" << endl;
    }

    return 0;
}