#include "Rook.h"

Rook::Rook(char color): Piece('r',color) {};

bool Rook::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // Check if the new move is on the same rank or file.
    bool valid = (oldRank == newRank) || (oldFile == newFile);
    return valid;
}