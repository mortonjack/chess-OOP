#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Piece.h"
#include "MoveNode.h"

class Gameboard {
    public:
        Piece* board[8][8]; // Gameboard, stores Piece locations
        MoveNode* prevMove;
    
    public:
        Gameboard(); // initialise empty board
        void visualiseTextBoard();
        void visualiseTextBoard(char color); // print text-based visualisation of the board

        void removePiece(int rank, int file);
        void clearBoard();
        void addPiece(int rank, int file, Piece* newPiece);
        bool movePiece(int oldFile, int oldRank, int newFile, int newRank); // attempt to move a Piece

        // Basic validity checks
        bool checkPathClear(int oldFile, int oldRank, int newFile, int newRank);
        bool validMove(int oldFile, int oldRank, int newFile, int newRank);
        bool validCapture(int oldFile, int oldRank, int newFile, int newRank);
        bool validMovement(int oldFile, int oldRank, int newFile, int newRank);

        // Piece getter
        Piece* getPiece(int file, int rank);
        MoveNode* getPrevMove();

        // Change the target Piece to the Pawn targetted with en passant, if applicable
        Piece* targetWithEnPassant(int oldFile, int oldRank, int newFile, int newRank);
        Piece* targetWithEnPassant(int oldFile, int oldRank, int newFile, int newRank, Piece* board[8][8], MoveNode* node);

        // Checks if the player is trying to perform a valid castle, and handles the castle
        bool isCastling(int oldFile, int oldRank, int newFile, int newRank);
        void castle(int oldFile, int newFile, int rank);

        // Replace kingFile and kingRank with King coordinates (if no King is found, returns -1, -1)
        void getKingCoords(char color, int * kingFile, int * kingRank);

        // Check if tile is being threatened
        bool isThreatened(int file, int rank);
        bool isThreatened(char color, int file, int rank);

        // Check if King is in check
        bool isInCheck(char color);

        // Check if King is in checkmate
        bool isInMate(char color);
        bool isInCheckmate(char color);

        // Check for draws
        bool isInStalemate(char color);
        bool threefoldRepetition();
        bool fiftyMoveRule();

        // For drivers: ensure board is set up correctly
        bool testDriver(Piece* pieces[], int* coords, int length); 
};

#endif//GAMEBOARD_H