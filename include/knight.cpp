#include "knight.h"

knight::knight(): knight('W') {}; // Pieces are white by default

knight::knight(char color) {
    _color = color;

    switch (color) {
        case 'W':
            _name = 'N';
            break;

        case 'B':
            _name = 'n';
            break;

        default:
            // Uncolored knights are white by default
            _name = 'K';
            break;
    }
}

bool knight::checkMoveValidity(int oldx, int oldy, int newx, int newy) {
    // check the absolute value of the relative movement in the x or y direction is 1,
    // and the absolute value of the relative movement in the other direction is 2.
    bool valid = ((newx-oldx == 2 || newx-oldx == -2) && (newy-oldy == 1 || newy-oldy == -1))
               ||((newx-oldx == 1 || newx-oldx == -1) && (newy-oldy == 2 || newy-oldy == -2));
    return valid;
}