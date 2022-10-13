#include "Knight.h"

Knight::Knight(char color): Piece('n',color) {};

bool Knight::checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // Check the Knight is moving 2 tiles in one direction, and 1 tile in the other
    bool valid = ((newRank-oldRank == 2 || newRank-oldRank == -2) && 
                  (newFile-oldFile == 1 || newFile-oldFile == -1))
               ||((newRank-oldRank == 1 || newRank-oldRank == -1) && 
                  (newFile-oldFile == 2 || newFile-oldFile == -2));
    return valid;
}