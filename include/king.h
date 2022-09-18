#ifndef KING_H
#define KING_H

#include "piece.h"

class king : public piece {
    public:
        king(); // Default constructor (pieces are white by default)
        king(char color); // Colored constructor
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//KING_H