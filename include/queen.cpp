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

bool queen::checkMoveValidity(int oldRank, int oldFile, int newRank, int newFile) {
    // check the the relative distance moved is equal in both rank and file
    // OR
    // check if the new move is on the same rank or file
    bool valid = ((newRank-oldRank) == (newFile-oldFile) 
                || -1*(newRank-oldRank) == (newFile-oldFile))
                || ((oldRank == newRank) || (oldFile == newFile));
    return valid;
}