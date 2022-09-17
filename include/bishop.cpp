#include "bishop.h"

bishop::bishop(): bishop('W') {}; // Pieces are white by default

bishop::bishop(char color) {
    _color = color;

    switch (color) {
        case 'W':
            _name = 'B';
            break;

        case 'B':
            _name = 'b';
            break;

        default:
            // Uncolored bishops are white by default
            _name = 'B';
            break;
    }
}

bool bishop::checkMoveValidity(int oldx, int oldy, int newx, int newy) {
    // check the absolute value of the relative movement in the x direction is
    // equal to the absolute value of the relative movement in the y direction
    bool valid = ((newx-oldx) == (newy-oldy) || -1*(newx-oldx) == (newy-oldy));
    return valid;
}