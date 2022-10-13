#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
    public:
        Rook(char color);
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//ROOK_H