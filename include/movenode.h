#ifndef MOVENODE_H
#define MOVENODE_H

#include "piece.h"

class movenode {
    /* LINKED LIST */
    private:
        int _oldFile;
        int _oldRank;
        int _newFile;
        int _newRank;
        piece* _capturedPiece;
        bool _enPassant;
        movenode* _prevNode;
    public:
        // Constructors
        movenode(int oldFile, int oldRank, int newFile, int newRank, 
                bool enPassant, piece* capturedPiece);
        movenode(int oldFile, int oldRank, int newFile, int newRank, 
                bool enPassant, piece* capturedPiece, movenode*);

        // Access previous node
        movenode* prev();
        movenode* prev(int distance);

        // Access information
        int getOldFile();
        int getOldRank();
        int getNewFile();
        int getNewRank();
        piece* getCapturedPiece();
        bool enPassant();

        // Reverse
        void reverseBoard(piece* board[8][8], int moves);
        void unreverseBoard(piece* board[8][8], int moves);

        // Add move to list
        void addMove(int oldFile, int oldRank, int newFile, int newRank, 
                bool enPassant, piece* capturedPiece);

        // Copy piece
        piece* copyPiece(piece* pieceToCopy);

        // Destructor
        ~movenode();
};

#endif//MOVENODE_H