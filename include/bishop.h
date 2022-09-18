#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece {
    public:
        bishop(); // Default constructor (pieces are white by default)
        bishop(char color); // Colored constructor
        bool checkMoveValidity(int oldRank, int oldFile, int newRank, int newFile);
};

#endif//BISHOP_H