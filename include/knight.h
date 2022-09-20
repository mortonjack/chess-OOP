#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class knight : public piece {
    public:
        knight(); // Default constructor (pieces are white by default)
        knight(char color); // Colored constructor
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//KNIGHT_H