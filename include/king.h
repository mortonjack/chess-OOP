#ifndef KING_H
#define KING_H

#include "piece.h"

class king : public piece {
    public:
        king(); // Default constructor (pieces are white by default)
        king(char color); // Colored constructor
        bool checkMoveValidity(int oldx, int oldy, int newx, int newy);
};

#endif//KING_H