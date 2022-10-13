#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
    public:
        Knight(char color); 
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//KNIGHT_H