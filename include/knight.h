#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class knight : public piece {
    public:
        knight(char color); 
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//KNIGHT_H