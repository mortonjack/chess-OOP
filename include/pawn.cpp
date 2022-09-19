#include "pawn.h"

pawn::pawn(): pawn('W') {}; // Pieces are white by default

pawn::pawn(char color) {
    _color = color;

    switch (color) {
        case 'W':
            _name = 'P';
            break;

        case 'B':
            _name = 'p';
            break;

        default:
            // Uncolored pawns are white by default
            _name = 'P';
            break;
    }
}

bool pawn::checkMoveValidity(int oldRank, int oldFile, int newRank, int newFile) {
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