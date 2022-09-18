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

bool bishop::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // check the the relative distance moved is equal in both rank and file
    bool valid = (newRank-oldRank) == (newFile-oldFile) || 
              -1*(newRank-oldRank) == (newFile-oldFile);
    return valid;
}