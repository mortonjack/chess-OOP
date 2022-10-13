#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    public:
        King(char color); // Colored constructor
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//KING_H