#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class pawn : public piece {
    public:
        pawn(char color);
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
        bool checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//PAWN_H