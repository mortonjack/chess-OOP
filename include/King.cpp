#include "King.h"

King::King(char color): Piece('k',color) {};

bool King::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // check the King isn't moving more than one space
    bool valid = (newRank-oldRank <= 1 && newRank-oldRank >= -1) &&
                 (newFile-oldFile <= 1 && newFile-oldFile >=-1);
    return valid;
}