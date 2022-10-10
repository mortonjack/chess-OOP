#include "movenode.h"
#include <cstdlib>

// Constructors
movenode::movenode() {
    _oldFile = -1;
    _newFile = -1;
    _oldRank = -1;
    _newRank = -1;
    _enPassant = false;
    _capturedPiece = nullptr;
    _prevNode = nullptr;
}

movenode::movenode(int oldFile, int oldRank, int newFile, int newRank, 
                    bool enPassant, piece* capturedPiece) {
    _oldFile = oldFile;
    _oldRank = oldRank;
    _newFile = newFile;
    _newRank = newRank;
    _enPassant = enPassant;
    _capturedPiece = capturedPiece;
    _prevNode = nullptr;
}

movenode::movenode(int oldFile, int oldRank, int newFile, int newRank, 
                    bool enPassant, piece* capturedPiece, movenode* prevNode) {
    _oldFile = oldFile;
    _oldRank = oldRank;
    _newFile = newFile;
    _newRank = newRank;
    _enPassant = enPassant;
    _capturedPiece = capturedPiece;
    _prevNode = prevNode;
}

// Add move
void movenode::addMove(int oldFile, int oldRank, int newFile, int newRank,
                    bool enPassant, piece* capturedPiece) {
    movenode* prevMove = new movenode(_oldFile, _oldRank, _newFile, _newRank,
                                    _enPassant, _capturedPiece, _prevNode);
    _prevNode = prevMove;
    _oldFile = oldFile;
    _oldRank = oldRank;
    _newFile = newFile;
    _newRank = newRank;
    _enPassant = enPassant;
    _capturedPiece = capturedPiece;
}

// Access previous node
movenode* movenode::prev() {
    return _prevNode;
}

movenode* movenode::prev(int distance) {
    if (_prevNode == nullptr) {
        return this;
    } else if (distance > 1) {
        return prev()->prev(distance-1);
    } else {
        return prev();
    }
}

// Access information
int movenode::getOldFile() {return _oldFile;}
int movenode::getOldRank() {return _oldRank;}
int movenode::getNewFile() {return _newFile;}
int movenode::getNewRank() {return _newRank;}
piece* movenode::getCapturedPiece() {return _capturedPiece;}
bool movenode::enPassant() {return _enPassant;}

// Reverse 
void movenode::reverseBoard(piece* board[8][8], int moves) {
    // Reverses the input board by [moves] moves
    piece* sourcePiece = board[_newFile][_newRank];
    board[_oldFile][_oldRank] = sourcePiece;

    // Reverse capture
    if (_enPassant) {
        board[_newFile][_newRank] = nullptr;
        board[_newFile][_oldRank] = _capturedPiece;
    } else {
        board[_newFile][_newRank] = _capturedPiece;
    }
    
    // Reverse pieces
    sourcePiece->reverseMove();
    if (_capturedPiece != nullptr) _capturedPiece->reverseMove();

    // Castle 
    if (sourcePiece->getType() == 'k') {
        if (abs(_newFile - _oldFile) == 2) {
            if (_newFile > _oldFile) { // Castling short
                board[7][_oldRank] = board[_newFile-1][_newRank];
                board[_newFile-1][_newRank] = nullptr;
                board[7][_oldRank]->reverseMove();
            } else { // castling long
                board[0][_oldRank] = board[_newFile+1][_newRank];
                board[_newFile+1][_newRank] = nullptr;
                board[0][_oldRank]->reverseMove();
            }
        }
    }

    // Finish reversing this move
    if (moves == 1) return;
    else _prevNode->reverseBoard(board, moves-1);
}

void movenode::unreverseBoard(piece* board[8][8], int moves) {
    // Un-reverses the input board by [moves] moves
    if (moves > 1) _prevNode->unreverseBoard(board, moves-1);

    piece* sourcePiece = board[_oldFile][_oldRank];

    // Make move
    board[_newFile][_newRank] = sourcePiece;
    board[_oldFile][_oldRank] = nullptr;

    // Update pieces
    sourcePiece->move();
    if (_capturedPiece != nullptr) {
        _capturedPiece->capture();
    }

    // En passant
    if (_enPassant) {
        board[_newFile][_oldRank] = nullptr;
    }

    // Castle 
    if (sourcePiece->getType() == 'k') {
        if (abs(_newFile - _oldFile) == 2) {
            if (_newFile > _oldFile) { // Castling short
                board[_newFile-1][_oldRank] = board[7][_oldRank];
                board[7][_oldRank] = nullptr;
                board[_newFile-1][_oldRank]->move();
            } else { // castling long
                board[_newFile+1][_oldFile] = board[7][_oldRank];
                board[7][_oldRank] = nullptr;
                board[_newFile+1][_oldFile]->move();
            }
        }
    }

    return;
}

// Destructor
movenode::~movenode() {
    if (_prevNode != nullptr) {
        delete _prevNode;
    }
}