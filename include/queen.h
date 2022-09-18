#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class queen : public piece {
    public:
        queen(); // Default constructor (pieces are white by default)
        queen(char color); // Colored constructor
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//QUEEN_H