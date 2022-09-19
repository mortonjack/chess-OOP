#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/rook.h"
#include "../include/bishop.h"
#include <iostream>
using namespace std;

int main() {
    // Create the game board and two rooks & two bishops
    gameboard board;
    rook whiteARook = rook('W');
    rook blackARook = rook('B');
    bishop whiteCBishop = bishop();
    bishop blackCBishop = bishop('B');
    piece* pieces[] = {&whiteARook, &blackARook};


    // Add the rooks to the game board
    board.addPiece(0,0,&whiteARook);
    board.addPiece(7,0,&blackARook);
    
    board.visualiseTextBoard();

    // Move the rooks to illegal positions
    board.movePiece(0,0, 1,1);
    board.movePiece(7,0, 4,6);

    // Check to ensure our nothing has happened
    board.visualiseTextBoard();
    int coords[] = {0,0, 7,0};
    bool test1 = board.testDriver(pieces, coords, 2);

    // Move the rooks to legal positions
    board.movePiece(0,0, 0,3);
    board.movePiece(7,0, 7,7);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();
    int coords2[] = {0,3, 7,7};
    bool test2 = board.testDriver(pieces, coords2, 2);
    
    // Add the bishops to the board
    board.addPiece(0,2,&whiteCBishop);
    board.addPiece(7,2,&blackCBishop);
    piece* pieces2[] = {&whiteARook, &blackARook, &whiteCBishop, &blackCBishop};

    board.visualiseTextBoard();

    // Move the bishops to legal positions
    board.movePiece(0,2,1,3);
    board.movePiece(7,2,5,4);

    // Check to ensure our moves were successful
    board.visualiseTextBoard();
    int coords3[] = {0,3, 7,7, 1,3, 5,4};
    bool test3 = board.testDriver(pieces2, coords3, 4);

    // Move the bishops to illegal positions
    board.movePiece(1,3, 1,1);
    board.movePiece(7,2, 4,6);

    // Check to ensure our nothing has happened
    board.visualiseTextBoard();
    bool test4 = board.testDriver(pieces2, coords3, 4);

    // Display test results
    if (test1) {
        cout << "Test passed: Rooks didn't move" << endl;
    } else {
        cout << "Test failed: Rooks made illegal moves" << endl;
    }

    if (test2) {
        cout << "Test passed: Rooks moved properly" << endl;
    } else {
        cout << "Test failed: Rooks failed to move" << endl;
    }
    
    if (test3) {
        cout << "Test passed: Bishops moved properly" << endl;
    } else {
        cout << "Test failed: Bishops failed to move" << endl;
    }

    if (test4) {
        cout << "Test passed: Bishops didn't move" << endl;
    } else {
        cout << "Test failed: Bishops made illegal moves" << endl;
    }

    return 0;
}