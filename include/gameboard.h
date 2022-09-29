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
        bool movePiece(int oldFile, int oldRank, int newFile, int newRank); // attempt to move a piece
        bool checkPathClear(int oldFile, int oldRank, int newFile, int newRank);

        // Replace kingFile and kingRank with king coordinates (if no king is found, returns -1, -1)
        void getKingCoords(char color, int * kingFile, int * kingRank);

        // Check if tile is being threatened
        bool isThreatened(int file, int rank);
        bool isThreatened(char color, int file, int rank);

        // Check if king is in check
        bool isInCheck();
        bool isInCheck(char color);

        // Check if king is in checkmate
        bool isInCheckmate();
        bool isInCheckmate(char color);

        // For drivers: ensure board is set up correctly
        bool testDriver(piece* pieces[], int* coords, int length); 
};

#endif//GAMEBOARD_H