#include "queen.h"

queen::queen(): queen('W') {}; // Pieces are white by default
queen::queen(char color): piece('q',color) {};

bool queen::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // check the the relative distance moved is equal in both rank and file
    // OR
    // check if the new move is on the same rank or file
    bool valid = ((newRank-oldRank) == (newFile-oldFile) 
                || -1*(newRank-oldRank) == (newFile-oldFile))
                || ((oldRank == newRank) || (oldFile == newFile));
    return valid;
}