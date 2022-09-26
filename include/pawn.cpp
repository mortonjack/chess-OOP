#include "pawn.h"

pawn::pawn(): pawn('W') {}; // Pieces are white by default
pawn::pawn(char color): piece('p',color) {};

bool pawn::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    bool valid;
    // check pawns are moving up one space
    if (this->_color == 'B') {
        valid = (oldFile == newFile) && (oldRank-newRank == 1 
        || (this->_moveCount == 1 && oldRank-newRank == 2)); // can move 2 places first move
    } else { // Uncolored pawns are white by default
        valid = (oldFile == newFile) && (newRank-oldRank == 1 
        || (this->_moveCount == 1 && newRank-oldRank == 2)); // can move 2 places first move
    }
    return valid;
}