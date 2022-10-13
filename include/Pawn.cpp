#include "Pawn.h"

Pawn::Pawn(char color): Piece('p',color) {};

bool Pawn::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    bool valid;
    // check pawns are moving up one space
    if (this->_color == 'B') {
        valid = (oldFile == newFile) && (oldRank-newRank == 1 
        || (this->_moveCount == 0 && oldRank-newRank == 2)); // can move 2 places first move
    } else { // Uncolored pawns are white by default
        valid = (oldFile == newFile) && (newRank-oldRank == 1 
        || (this->_moveCount == 0 && newRank-oldRank == 2)); // can move 2 places first move
    }
    return valid;
}

bool Pawn::checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank) {
    bool valid;
    
    // Check pawns are moving diagonally left or diagonally right
    if (this->_color == 'B') {
        valid = (newRank == oldRank - 1) && ((newFile == oldFile + 1) || (newFile == oldFile - 1));
    } else { // Uncolored pawns are white by default
        valid = (newRank == oldRank + 1) && ((newFile == oldFile + 1) || (newFile == oldFile - 1));
    }


    return valid;
}