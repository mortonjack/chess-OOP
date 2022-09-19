#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "piece.h"

class gameboard {
    protected:
        piece* board[8][8]; // gameboard, stores piece locations
    public:
        gameboard(); // initialise empty board
        void visualiseTextBoard();
        void visualiseTextBoard(char color); // print text-based visualisation of the board
        void removePiece(int rank, int file);
        void addPiece(int rank, int file, piece* newPiece);
        bool movePiece(int oldRank, int oldFile, int newRank, int newFile); // attempt to move a piece
        bool checkPathClear(int oldRank, int oldFile, int newRank, int newFile);
        bool testDriver(piece* pieces[], int* coords, int length); // For test drivers: ensure board is set up correctly
};

#endif//GAMEBOARD_H