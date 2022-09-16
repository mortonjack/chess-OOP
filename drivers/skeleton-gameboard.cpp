#include "../include/piece.h"
#include "../include/gameboard.h"
#include <iostream>
using namespace std;

int main() {
    piece pawn(2, 1, 'p');
    piece rook(0, 7, 'R');

    gameboard board;
    board.addPiece(&pawn);
    board.addPiece(&rook);
    board.visualiseTextBoard();

    return 0;
}