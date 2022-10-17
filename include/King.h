#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    public:
        // Constructor. Set color of piece
        King(char color);

        // Check whether a move is valid
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//KING_H