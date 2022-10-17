#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
    public:
        // Constructor. Set color of piece
        Bishop(char color);

        // Check whether a move is valid
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//BISHOP_H