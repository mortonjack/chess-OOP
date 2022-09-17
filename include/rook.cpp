
#include "piece.h"
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

bool rook::checkMoveValidity(int oldx, int oldy, int newx, int newy) {
    // Check if the new move is on the same rank or file. If so, the move is valid.
    bool valid = (oldx == newx) || (oldy == newy);
    return valid;
}