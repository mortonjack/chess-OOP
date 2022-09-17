#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class knight : public piece {
    public:
        knight(); // Default constructor (pieces are white by default)
        knight(char color); // Colored constructor
        bool checkMoveValidity(int oldRank, int oldFile, int newRank, int newFile);
};

#endif//KNIGHT_H