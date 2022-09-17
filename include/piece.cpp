#include "piece.h"

piece::piece(): piece('x','W') {};
piece::piece(char name, char color) : _name(name), _color(color) {};

char piece::getName() {return this->_name;}