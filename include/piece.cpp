#include "piece.h"
#include <cctype>

piece::piece(): piece('x','W') {}
piece::piece(char type, char color) {
    this->_type = type; 
    this->_color = color; 

    this->_name = _color != 'B' ? toupper(type) : tolower(type);

    this->_captured = false; 
    this->_moveCount = 0; 
}

bool piece::checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank) { return checkMoveValidity(oldFile, oldRank, newFile, newRank); }
void piece::capture() {this->_captured = true;}
bool piece::captured() {return this->_captured;}
char piece::getName() {return this->_name;}
char piece::getType() {return this->_type;}
char piece::getColor() {return this->_color;}
int piece::getMoveCount() {return this->_moveCount;}
void piece::move() {_moveCount++;}
void piece::reverseMove() {
    if (captured()) {
        this->_captured = false;
    } else {
        this->_moveCount--;
    }
    return;
}
void piece::reset() {
    _captured = false;
    _moveCount = 0;
}