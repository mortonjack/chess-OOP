#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece {
    public:
        bishop(); // Default constructor (pieces are white by default)
        bishop(char color); // Colored constructor
        bool checkMoveValidity(int oldx, int oldy, int newx, int newy);
};

#endif//BISHOP_H