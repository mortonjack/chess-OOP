#include "king.h"

king::king(char color): piece('k',color) {};

bool king::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // check the king isn't moving more than one space
    bool valid = (newRank-oldRank <= 1 && newRank-oldRank >= -1) &&
                 (newFile-oldFile <= 1 && newFile-oldFile >=-1);
    return valid;
}