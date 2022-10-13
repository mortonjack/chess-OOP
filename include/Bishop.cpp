#include "Bishop.h"

Bishop::Bishop(char color) : Piece('b',color) {};

bool Bishop::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // check the the relative distance moved is equal in both rank and file
    bool valid = (newRank-oldRank) == (newFile-oldFile) || 
              -1*(newRank-oldRank) == (newFile-oldFile);
    return valid;
}