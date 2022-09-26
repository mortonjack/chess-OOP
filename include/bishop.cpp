#include "bishop.h"

bishop::bishop(): bishop('W') {}; // Pieces are white by default
bishop::bishop(char color) : piece('b',color) {};

bool bishop::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // check the the relative distance moved is equal in both rank and file
    bool valid = (newRank-oldRank) == (newFile-oldFile) || 
              -1*(newRank-oldRank) == (newFile-oldFile);
    return valid;
}