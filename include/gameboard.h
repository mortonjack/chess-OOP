#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "piece.h"
#include "movenode.h"

class gameboard {
    protected:
        piece* board[8][8]; // gameboard, stores piece locations
        movenode* prevMove;
    public:
        gameboard(); // initialise empty board
        void visualiseTextBoard();
        void visualiseTextBoard(char color); // print text-based visualisation of the board

        void removePiece(int rank, int file);
        void clearBoard();
        void addPiece(int rank, int file, piece* newPiece);
        bool movePiece(int oldFile, int oldRank, int newFile, int newRank); // attempt to move a piece

        // Basic validity checks
        bool checkPathClear(int oldFile, int oldRank, int newFile, int newRank);
        bool validMove(int oldFile, int oldRank, int newFile, int newRank);
        bool validCapture(int oldFile, int oldRank, int newFile, int newRank);
        bool validMovement(int oldFile, int oldRank, int newFile, int newRank);

        // Change the target piece to the pawn targetted with en passant, if applicable
        piece* targetWithEnPassant(int oldFile, int oldRank, int newFile, int newRank);

        // Checks if the player is trying to perform a valid castle, and handles the castle
        bool isCastling(int oldFile, int oldRank, int newFile, int newRank);
        void castle(int oldFile, int newFile, int rank);

        // Replace kingFile and kingRank with king coordinates (if no king is found, returns -1, -1)
        void getKingCoords(char color, int * kingFile, int * kingRank);

        // Check if tile is being threatened
        bool isThreatened(int file, int rank);
        bool isThreatened(char color, int file, int rank);

        // Check if king is in check
        bool isInCheck(char color);

        // Check if king is in checkmate
        bool isInMate(char color);
        bool isInCheckmate(char color);

        // Check for draws
        bool isInStalemate(char color);
        bool threefoldRepetition();

        // For drivers: ensure board is set up correctly
        bool testDriver(piece* pieces[], int* coords, int length); 
};

#endif//GAMEBOARD_H