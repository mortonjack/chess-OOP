#include "../include/piece.h"
#include "../include/gameboard.h"
#include "../include/king.h"
#include "../include/queen.h"
#include "../include/rook.h"
#include "../include/bishop.h"
#include "../include/knight.h"
#include "../include/pawn.h"
#include <iostream>
using namespace std;

// This currently has no Makefile
// because we neglected this test
// and never use it.
// but its still here if we want it.

// Tests whether the rank and file system matches the intuition of ranks and files
int main() {
    // Create the game board
    gameboard board;

    // Create kings
    king whiteKing('W');
    king blackKing('B');

    // Create queens
    queen whiteQueen('W');
    queen blackQueen('B');

    // Create bishops
    bishop whiteCBishop('W');
    bishop whiteFBishop('W');
    bishop blackCBishop('B');
    bishop blackFBishop('B');

    // Create knights
    knight whiteBKnight('W');
    knight whiteGKnight('W');
    knight blackBKnight('B');
    knight blackGKnight('B');

    // Create rooks
    rook whiteARook('W');
    rook whiteHRook('W');
    rook blackARook('B');
    rook blackHRook('B');

    // Create e-file and d-file pawns
    pawn whiteEPawn('W');
    pawn whiteDPawn('W');
    pawn blackEPawn('B');
    pawn blackDPawn('B');

    // Add the white pieces
    board.addPiece(0,0,&whiteARook);
    board.addPiece(0,1,&whiteBKnight);
    board.addPiece(0,2,&whiteCBishop);
    board.addPiece(0,3,&whiteQueen);
    board.addPiece(0,4,&whiteKing);
    board.addPiece(0,5,&whiteFBishop);
    board.addPiece(0,6,&whiteGKnight);
    board.addPiece(0,7,&whiteHRook);

    board.addPiece(1,3,&whiteDPawn);
    board.addPiece(1,4,&whiteEPawn);

    // Add the black pieces
    board.addPiece(7,0,&blackARook);
    board.addPiece(7,1,&blackBKnight);
    board.addPiece(7,2,&blackCBishop);
    board.addPiece(7,3,&blackQueen);
    board.addPiece(7,4,&blackKing);
    board.addPiece(7,5,&blackFBishop);
    board.addPiece(7,6,&blackGKnight);
    board.addPiece(7,7,&blackHRook);

    board.addPiece(6,3,&blackDPawn);
    board.addPiece(6,4,&blackEPawn);
    
    // Check to ensure the board was setup properly
    board.visualiseTextBoard();
    cout << "Please manually ensure the board has been flipped correctly." << endl;
    board.visualiseTextBoard('B');

    return 0;
}