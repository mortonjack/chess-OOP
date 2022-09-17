#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class pawn : public piece {
    public:
        pawn(); // Default constructor (pieces are white by default)
        pawn(char color); // Colored constructor
        bool checkMoveValidity(int oldRank, int oldFile, int newRank, int newFile);
};

#endif//PAWN_H