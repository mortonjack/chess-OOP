#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class rook : public piece {
    public:
        rook(char color);
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//ROOK_H