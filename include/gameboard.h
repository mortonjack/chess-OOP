#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "piece.h"

class gameboard {
    protected:
        piece * board[8][8]; // gameboard, stores piece locations
    public:
        gameboard(); // initialise empty board
        void visualiseTextBoard(); // print text-based visualisation of the board
        void removePiece(int x, int y);
        void addPiece(piece* newPiece);
};

#endif//GAMEBOARD_H