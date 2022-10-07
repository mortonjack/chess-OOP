#ifndef BOARDNODE_H
#define BOARDNODE_H

#include "piece.h"

class boardnode {
    /* LINKED LIST
     * Stores a piece* array representing the board
     * and a pointer to another boardnode
     */
    private:
        piece*** _board;
        boardnode* _prevNode;
    public:
        // Constructors
        boardnode(piece* board[8][8]);
        boardnode(piece* board[8][8], boardnode* prevNode);
        boardnode(piece*** board, boardnode* prevNode);
        // Access piece information
        piece* getPiece(int file, int rank);
        // Add board to list
        void addBoard(piece* board[8][8]);
        // Access previous node
        boardnode* prev();
        boardnode* prev(int distance);
        // Copy constructor
        boardnode(const boardnode &node);
        // Destructor
        ~boardnode();
};

#endif//BOARDNODE_H