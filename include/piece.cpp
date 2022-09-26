#include "piece.h"
#include <cctype>

piece::piece(): piece('x','W') {}
piece::piece(char type, char color) {
    this->_type = type; 
    this->_color = color; 

    this->_name = _color != 'B' ? tolower(type) : toupper(type);

    this->_captured = false; 
    this->_moveCount = 1; 
          
                                    }
bool piece::checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank) { return checkMoveValidity(oldFile, oldRank, newFile, newRank); }
void piece::capture() {this->_captured = true;}
bool piece::captured() {return this->_captured;}
char piece::getName() {return this->_name;}
char piece::getType() {return this->_type;}
char piece::getColor() {return this->_color;}
void piece::move() {_moveCount++;}