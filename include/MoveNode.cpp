#include "MoveNode.h"
#include <cstdlib>

// Constructors
MoveNode::MoveNode() {
    _oldFile = -1;
    _newFile = -1;
    _oldRank = -1;
    _newRank = -1;
    _enPassant = false;
    _capturedPiece = nullptr;
    _prevNode = nullptr;
}

MoveNode::MoveNode(int oldFile, int oldRank, int newFile, int newRank, 
                    bool enPassant, Piece* capturedPiece) {
    _oldFile = oldFile;
    _oldRank = oldRank;
    _newFile = newFile;
    _newRank = newRank;
    _enPassant = enPassant;
    _capturedPiece = capturedPiece;
    _prevNode = nullptr;
}

MoveNode::MoveNode(int oldFile, int oldRank, int newFile, int newRank, 
                    bool enPassant, Piece* capturedPiece, MoveNode* prevNode) {
    _oldFile = oldFile;
    _oldRank = oldRank;
    _newFile = newFile;
    _newRank = newRank;
    _enPassant = enPassant;
    _capturedPiece = capturedPiece;
    _prevNode = prevNode;
}

// Add move
void MoveNode::addMove(int oldFile, int oldRank, int newFile, int newRank,
                    bool enPassant, Piece* capturedPiece) {
    MoveNode* prevMove = new MoveNode(_oldFile, _oldRank, _newFile, _newRank,
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
MoveNode* MoveNode::prev() {
    return _prevNode;
}

MoveNode* MoveNode::prev(int distance) {
    if (_prevNode == nullptr) {
        return this;
    } else if (distance > 1) {
        return prev()->prev(distance-1);
    } else {
        return prev();
    }
}

// Access information
int MoveNode::getOldFile() {return _oldFile;}
int MoveNode::getOldRank() {return _oldRank;}
int MoveNode::getNewFile() {return _newFile;}
int MoveNode::getNewRank() {return _newRank;}
Piece* MoveNode::getCapturedPiece() {return _capturedPiece;}
bool MoveNode::enPassant() {return _enPassant;}

// Reverse 
void MoveNode::reverseBoard(Piece* board[8][8], int moves) {
    // Reverses the input board by [moves] moves
    Piece* sourcePiece = board[_newFile][_newRank];
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

void MoveNode::unreverseBoard(Piece* board[8][8], int moves) {
    // Un-reverses the input board by [moves] moves
    if (moves > 1) _prevNode->unreverseBoard(board, moves-1);
    if (moves == 0) return;

    Piece* sourcePiece = board[_oldFile][_oldRank];

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
MoveNode::~MoveNode() {
    if (_prevNode != nullptr) {
        delete _prevNode;
    }
}