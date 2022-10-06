#include "boardnode.h"

boardnode::boardnode(piece* board[8][8]): boardnode(board, nullptr) {}
boardnode::boardnode(piece* board[8][8], boardnode* prevNode): _prevNode(prevNode) {
    _board = new piece**[8];
    for (int i = 0; i < 8; i++) {
        _board[i] = new piece*[8];
        for (int j = 0; j < 8; j++) {
            _board[i][j] = board[i][j];
        }
    }
}
boardnode::boardnode(piece*** board, boardnode* prevNode): _prevNode(prevNode) {
    _board = new piece**[8];
    for (int i = 0; i < 8; i++) {
        _board[i] = new piece*[8];
        for (int j = 0; j < 8; j++) {
            _board[i][j] = board[i][j];
        }
    }
}

piece* boardnode::getPiece(int file, int rank) {
    return _board[file][rank];
}

void boardnode::addBoard(piece* board[8][8]) {
    boardnode* prevBoard = new boardnode(_board, _prevNode);
    _prevNode = prevBoard;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            _board[i][j] = board[i][j];
        }
    }
}

boardnode* boardnode::prev() {
    return _prevNode;
}

boardnode* boardnode::prev(int distance) {
    if (_prevNode == nullptr) {
        return this;
    } else if (distance > 1) {
        return prev()->prev(distance-1);
    } else {
        return prev();
    }
}

boardnode::boardnode(const boardnode &node) {
    _prevNode = node._prevNode;
    _board = new piece**[8];
    for (int i = 0; i < 8; i++) {
        _board[i] = new piece*[8];
        for (int j = 0; j < 8; j++) {
            _board[i][j] = node._board[i][j];
        }
    }
}

boardnode::~boardnode() {
    // Delete this board
    for (int i = 0; i < 8; i++) {
        delete [] _board[i];
    }
    delete [] _board;
}