#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
    public:
        // Constructor. Set color of piece
        Knight(char color);

        // Check whether a move is valid
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//KNIGHT_H