#ifndef MOVENODE_H
#define MOVENODE_H

#include "Piece.h"

class MoveNode {
    /* LINKED LIST */
    private:
        int _oldFile;
        int _oldRank;
        int _newFile;
        int _newRank;
        Piece* _capturedPiece;
        bool _enPassant;
        bool _promote;
        MoveNode* _prevNode;
    public:
        // Constructors
        MoveNode();
        MoveNode(int oldFile, int oldRank, int newFile, int newRank, 
                bool enPassant, bool promote, Piece* capturedPiece);
        MoveNode(int oldFile, int oldRank, int newFile, int newRank, 
                bool enPassant, bool promote, Piece* capturedPiece, MoveNode*);

        // Add move to list
        void addMove(int oldFile, int oldRank, int newFile, int newRank, 
                bool enPassant, bool promote, Piece* capturedPiece);

        // Access previous node
        MoveNode* prev();
        MoveNode* prev(int distance);

        // Access information
        int getOldFile();
        int getOldRank();
        int getNewFile();
        int getNewRank();
        Piece* getCapturedPiece();
        bool enPassant();
        bool promoted();

        // Reverse
        void reverseBoard(Piece* board[8][8], int moves);
        void unreverseBoard(Piece* board[8][8], int moves);

        // Destructor
        ~MoveNode();
};

#endif//MOVENODE_H