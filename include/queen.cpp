#include "queen.h"

queen::queen(): queen('W') {}; // Pieces are white by default

queen::queen(char color) {
    _color = color;

    switch (color) {
        case 'W':
            _name = 'Q';
            break;

        case 'B':
            _name = 'q';
            break;

        default:
            // Uncolored queens are white by default
            _name = 'Q';
            break;
    }
}

bool queen::checkMoveValidity(int oldx, int oldy, int newx, int newy) {
    // check the absolute value of the relative movement in the x direction is
    // equal to the absolute value of the relative movement in the y direction
    // OR
    // check if the new move is on the same rank or file
    bool valid = ((newx-oldx) == (newy-oldy) || -1*(newx-oldx) == (newy-oldy))
                || ((oldx == newx) || (oldy == newy));
    return valid;
}