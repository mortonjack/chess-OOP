#ifndef ROOK_H
#define ROOH_H

#include "piece.h"

class rook : public piece {
    public:
        rook(); // Default constructor (rooks are white by default)
        rook(char color); // Colored constructor
        bool checkMoveValidity(int oldx, int oldy, int newx, int newy);
};

#endif