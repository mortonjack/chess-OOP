#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
    public:
        // Constructor. Set color of piece
        Pawn(char color);

        // Check whether a move is valid
        bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank);

        // Check whether a piece can be captured
        bool checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank);
};

#endif//PAWN_H