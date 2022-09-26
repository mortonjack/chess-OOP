#include "rook.h"

rook::rook(): rook('W') {}; // Pieces are white by default
rook::rook(char color): piece('r',color) {};

bool rook::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // Check if the new move is on the same rank or file.
    bool valid = (oldRank == newRank) || (oldFile == newFile);
    return valid;
}