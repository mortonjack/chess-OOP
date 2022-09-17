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

bool pawn::checkMoveValidity(int oldx, int oldy, int newx, int newy) {
    bool valid;
    if (this->_color == 'B') {
        valid = (oldy == newy) && (newx-oldx == 1);
    } else { // Uncolored pawns are white by default
        valid = (oldy == newy) && (oldx-newx == 1);
    }
    return valid;
}