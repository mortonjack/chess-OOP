#include "piece.h"

piece::piece(): piece('x','W') {}
piece::piece(char name, char color) : _captured(false), _name(name), _color(color) {}

void piece::capture() {this->_captured = true;}
bool piece::captured() {return this->_captured;}
char piece::getName() {return this->_name;}