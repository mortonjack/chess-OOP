#include "knight.h"

knight::knight(): knight('W') {}; // Pieces are white by default

knight::knight(char color) {
    _color = color;
    _type = 'n';

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

bool knight::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // Check the knight is moving 2 tiles in one direction, and 1 tile in the other
    bool valid = ((newRank-oldRank == 2 || newRank-oldRank == -2) && 
                  (newFile-oldFile == 1 || newFile-oldFile == -1))
               ||((newRank-oldRank == 1 || newRank-oldRank == -1) && 
                  (newFile-oldFile == 2 || newFile-oldFile == -2));
    return valid;
}