#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece {
    public:
        bishop(); // Default constructor (pieces are white by default)
        bishop(char color); // Colored constructor
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//BISHOP_H