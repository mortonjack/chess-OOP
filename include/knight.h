#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class knight : public piece {
    public:
        knight(); // Default constructor (pieces are white by default)
        knight(char color); // Colored constructor
        bool checkMoveValidity(int oldx, int oldy, int newx, int newy);
};

#endif//KNIGHT_H