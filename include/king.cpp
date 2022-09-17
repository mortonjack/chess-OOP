#include "king.h"

king::king(): king('W') {}; // Pieces are white by default

king::king(char color) {
    _color = color;

    switch (color) {
        case 'W':
            _name = 'K';
            break;

        case 'B':
            _name = 'k';
            break;

        default:
            // Uncolored kings are white by default
            _name = 'K';
            break;
    }
}

bool king::checkMoveValidity(int oldx, int oldy, int newx, int newy) {
    // check the king isn't moving more than one space
    bool valid = (newx-oldx <= 1 && newx-oldx >= -1) &&
                 (newy-oldy <= 1 && newy-oldy >=-1);
    return valid;
}