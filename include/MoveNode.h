#ifndef MOVENODE_H
#define MOVENODE_H

#include "Piece.h"

class MoveNode {
    /* LINKED LIST */
    private:
        // Stores move information
        int _oldFile;
        int _oldRank;
        int _newFile;
        int _newRank;

        // Stores the captured piece
        Piece* _capturedPiece;

        // Stores the promoted piece
        Piece* _promotedPiece;

        // Did this move take by en passant?
        bool _enPassant;

        // Stores a pointer to the previous node
        MoveNode* _prevNode;

    public:
    
        // Constructors
        MoveNode();
        MoveNode(int oldFile, int oldRank, int newFile, int newRank, 
                bool enPassant, Piece* promotedPiece, Piece* capturedPiece);
        MoveNode(int oldFile, int oldRank, int newFile, int newRank, 
                bool enPassant, Piece* promotedPiece, Piece* capturedPiece, MoveNode*);

        // Add move to list
        void addMove(int oldFile, int oldRank, int newFile, int newRank, 
                bool enPassant, Piece* promotedPiece, Piece* capturedPiece);

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
        Piece* getPromotedPiece();

        // Reverse the input board by input moves
        void reverseBoard(Piece* board[8][8], int moves);
        // Undo the above function
        void unreverseBoard(Piece* board[8][8], int moves);

        // Destructor
        ~MoveNode();
};

#endif//MOVENODE_H