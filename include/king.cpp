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

bool king::checkMoveValidity(int oldRank, int oldFile, int newRank, int newFile) {
    // check the king isn't moving more than one space
    bool valid = (newRank-oldRank <= 1 && newRank-oldRank >= -1) &&
                 (newFile-oldFile <= 1 && newFile-oldFile >=-1);
    return valid;
}