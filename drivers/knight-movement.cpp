#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/knight.h"
#include <iostream>
using namespace std;

int main() {
    // Create the game board and two knights.
    gameboard board;
    knight whiteAknight = knight();
    knight blackAknight = knight('B');
    piece* pieces[] = {&whiteAknight, &blackAknight};

    // Add the knights to the game board
    board.addPiece(0,0,&whiteAknight);
    board.addPiece(7,0,&blackAknight);
    
    board.visualiseTextBoard();

    // Move the knights to illegal positions
    board.movePiece(0,0, 2,2);
    board.movePiece(7,0, 4,0);

    // Check to ensure our nothing has happened
    board.visualiseTextBoard();
    int coords[] = {0,0, 7,0};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the knights to legal positions 
    board.movePiece(0,0, 1,2);
    board.movePiece(7,0, 5,1);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();
    int coords2[] = {1,2, 5,1};
    bool test2 = board.testDriver(pieces, coords2, 2);

    // Move the knights to legal positions 
    board.movePiece(1,2, 2,4);
    board.movePiece(5,1, 7,2);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();
    int coords3[] = {2,4, 7,2};
    bool test3 = board.testDriver(pieces, coords3, 2);

    if (test1) {
        cout << "Test passed: Knights didn't move" << endl;
    } else {
        cout << "Test failed: Knights made illegal moves" << endl;
    }

    if (test2) {
        cout << "Test passed: Knights moved properly" << endl;
    } else {
        cout << "Test failed: Knights failed to move" << endl;
    }

    if (test3) {
        cout << "Test passed: Knights moved properly" << endl;
    } else {
        cout << "Test failed: Knights failed to move" << endl;
    }

    return 0;
}