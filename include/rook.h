#ifndef ROOK_H
#define ROOH_H

#include "piece.h"

class rook : public piece {
    public:
        rook(); // Default constructor (pieces are white by default)
        rook(char color); // Colored constructor
        bool checkMoveValidity(int oldRank, int oldFile, int newRank, int newFile);
};

#endif