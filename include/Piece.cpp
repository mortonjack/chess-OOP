#include "Piece.h"
#include <cctype>

// Constructor
Piece::Piece(char type, char color) {
    this->_type = type; 
    this->_color = color; 

    this->_name = _color != 'B' ? toupper(type) : tolower(type);

    this->_captured = false; 
    this->_moveCount = 0; 
}

// Validity test
bool Piece::checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank) {
    // Capture validity is the same as move validity by default 
    return checkMoveValidity(oldFile, oldRank, newFile, newRank);
}

// Capture
void Piece::capture() {this->_captured = true;}
bool Piece::captured() {return this->_captured;}

// Get info
char Piece::getName() {return this->_name;}
char Piece::getType() {return this->_type;}
char Piece::getColor() {return this->_color;}
int Piece::getMoveCount() {return this->_moveCount;}

// Update info
void Piece::move() {_moveCount++;}
void Piece::reverseMove() {
    if (captured()) {
        this->_captured = false;
    } else {
        this->_moveCount--;
    }
    return;
}
void Piece::reset() {
    _captured = false;
    _moveCount = 0;
}
void Piece::swapColor() {
    this->_color = _color == 'W' ? 'B' : 'W';
}