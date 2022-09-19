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
    pawn whiteDPawn = pawn();
    piece* pieces[] = {&blackARook, &whiteCPawn, &whiteDPawn};

    // Add the pieces to the game board
    board.addPiece(7,0,&blackARook);
    board.addPiece(1,2,&whiteCPawn);
    board.addPiece(1,3,&whiteDPawn);

    board.visualiseTextBoard();

    // Move the rook to a legal position
    board.movePiece(7,0, 7,2);
    board.movePiece(7,2, 4,2);

    // Check to ensure these moves worked
    board.visualiseTextBoard();
    int coords[] = {4,2, 1,2, 1,3};
    bool test1 = board.testDriver(pieces, coords, 3);

    // Try to move our rook through our pawn
    board.movePiece(4,2, 0,2);

    // Check to ensure this move was unsuccessful
    board.visualiseTextBoard();
    bool test2 = board.testDriver(pieces, coords, 3);

    // Move our rook in front of the pawn
    board.movePiece(4,2, 2,2);

    // Check to ensure this move worked
    board.visualiseTextBoard();
    int coords2[] = {2,2, 1,2, 1,3};
    bool test3 = board.testDriver(pieces, coords2, 3);

    // Try to move the pawn through the rook
    board.movePiece(1,2, 3,2);

    // Check to ensure this move was unsuccessful
    board.visualiseTextBoard();
    bool test4 = board.testDriver(pieces, coords2, 3);

    // Try to move the d-pawn forward
    board.movePiece(1,3, 3,3);

    // Check to ensure this move was successful
    board.visualiseTextBoard();
    int coords3[] = {2,2, 1,2, 3,3};
    bool test5 = board.testDriver(pieces, coords3, 3);

    if (test1) {
        cout << "Test passed: Rook moved successfully" << endl;
    } else {
        cout << "Test failed: Rook failed to move" << endl;
    }

    if (test2) {
        cout << "Test passed: Pawn blocked the rook's move" << endl;
    } else {
        cout << "Test failed: Pawn didn't block the rook" << endl;
    }

    if (test3) {
        cout << "Test passed: Rook moved successfully" << endl;
    } else {
        cout << "Test failed: Rook failed to move" << endl;
    }

    if (test4) {
        cout << "Test passed: Rook blocked the pawn's move" << endl;
    } else {
        cout << "Test failed: Rook didn't block the pawn" << endl;
    }

    if (test5) {
        cout << "Test passed: Pawn moved successfully" << endl;
    } else {
        cout << "Test failed: Pawn failed to move" << endl;
    }

    return 0;
}