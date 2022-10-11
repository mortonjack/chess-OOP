#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class queen : public piece {
    public:
        queen(char color);
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//QUEEN_H