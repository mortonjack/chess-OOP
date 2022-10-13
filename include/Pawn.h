#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
    public:
        Pawn(char color);
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
        bool checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//PAWN_H