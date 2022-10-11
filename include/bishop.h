#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece {
    public:
        bishop(char color); // Colored constructor
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//BISHOP_H