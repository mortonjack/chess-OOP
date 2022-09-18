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

// Tests whether the rank and file system matches the intuition of ranks and files
int main() {
    // Create the game board
    gameboard board;

    // Create kings
    king whiteKing = king();
    king blackKing = king('B');

    // Create queens
    queen whiteQueen = queen();
    queen blackQueen = queen('B');

    // Create bishops
    bishop whiteCBishop = bishop();
    bishop whiteFBishop = bishop();
    bishop blackCBishop = bishop('B');
    bishop blackFBishop = bishop('B');

    // Create knights
    knight whiteBKnight = knight();
    knight whiteGKnight = knight();
    knight blackBKnight = knight('B');
    knight blackGKnight = knight('B');

    // Create rooks
    rook whiteARook = rook();
    rook whiteHRook = rook();
    rook blackARook = rook('B');
    rook blackHRook = rook('B');

    // Create e-file and d-file pawns
    pawn whiteEPawn = pawn();
    pawn whiteDPawn = pawn();
    pawn blackEPawn = pawn('B');
    pawn blackDPawn = pawn('B');

    // Add the white pieces
    board.addPiece(7,0,&whiteARook);
    board.addPiece(7,1,&whiteBKnight);
    board.addPiece(7,2,&whiteCBishop);
    board.addPiece(7,3,&whiteQueen);
    board.addPiece(7,4,&whiteKing);
    board.addPiece(7,5,&whiteFBishop);
    board.addPiece(7,6,&whiteGKnight);
    board.addPiece(7,7,&whiteHRook);

    board.addPiece(6,3,&whiteDPawn);
    board.addPiece(6,4,&whiteEPawn);

    // Add the black pieces
    board.addPiece(0,0,&blackARook);
    board.addPiece(0,1,&blackBKnight);
    board.addPiece(0,2,&blackCBishop);
    board.addPiece(0,3,&blackQueen);
    board.addPiece(0,4,&blackKing);
    board.addPiece(0,5,&blackFBishop);
    board.addPiece(0,6,&blackGKnight);
    board.addPiece(0,7,&blackHRook);

    board.addPiece(1,3,&blackDPawn);
    board.addPiece(1,4,&blackEPawn);
    
    // Check to ensure the board was setup properly
    board.visualiseTextBoard();
    board.visualiseTextBoard('B');

    return 0;
}