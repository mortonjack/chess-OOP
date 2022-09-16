#ifndef ROOK_H
#define ROOH_H

#include "piece.h"

class rook : public piece {
    public:
        rook();
        rook(char color);
        bool checkMoveValidity(int oldx, int oldy, int newx, int newy);
};

#endif