#include "rook.h"

rook::rook(): rook('W') {}; // Pieces are white by default

rook::rook(char color) {
    _color = color;

    switch (color) {
        case 'W':
            _name = 'R';
            break;

        case 'B':
            _name = 'r';
            break;

        default:
            // Uncolored rooks are white by default
            _name = 'R';
            break;
    }
}

bool rook::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // Check if the new move is on the same rank or file.
    bool valid = (oldRank == newRank) || (oldFile == newFile);
    return valid;
}