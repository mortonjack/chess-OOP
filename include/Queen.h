#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
    public:
        Queen(char color);
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//QUEEN_H