#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
    public:
        // Constructor. Set color of piece
        Rook(char color);

        // Check whether a move is valid
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//ROOK_H