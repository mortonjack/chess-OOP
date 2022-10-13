#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
    public:
        Bishop(char color); // Colored constructor
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//BISHOP_H