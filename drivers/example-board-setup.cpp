#include "../include/Piece.h"
#include "../include/Gameboard.h"
#include "../include/King.h"
#include "../include/Queen.h"
#include "../include/Rook.h"
#include "../include/Bishop.h"
#include "../include/Knight.h"
#include "../include/Pawn.h"
#include <iostream>
using namespace std;

// This currently has no Makefile
// because we neglected this test
// and never use it.
// but its still here if we want it.

// Tests whether the rank and file system matches the intuition of ranks and files
int main() {
    // Create the Game board
    Gameboard board;

    // Create kings
    King whiteKing('W');
    King blackKing('B');

    // Create queens
    Queen whiteQueen('W');
    Queen blackQueen('B');

    // Create bishops
    Bishop whiteCBishop('W');
    Bishop whiteFBishop('W');
    Bishop blackCBishop('B');
    Bishop blackFBishop('B');

    // Create knights
    Knight whiteBKnight('W');
    Knight whiteGKnight('W');
    Knight blackBKnight('B');
    Knight blackGKnight('B');

    // Create rooks
    Rook whiteARook('W');
    Rook whiteHRook('W');
    Rook blackARook('B');
    Rook blackHRook('B');

    // Create e-file and d-file pawns
    Pawn whiteEPawn('W');
    Pawn whiteDPawn('W');
    Pawn blackEPawn('B');
    Pawn blackDPawn('B');

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