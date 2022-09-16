#include "piece.h"

piece::piece() {_name = 'x';}
piece::piece(int x, int y, char name) : _x(x), _y(y), _name(name) {};

void piece::move(int x, int y) {
    this->_x = x;
    this->_y = y;
} 

int piece::getx() {return this->_x;}
int piece::gety() {return this->_y;}
char piece::getName() {return this->_name;}