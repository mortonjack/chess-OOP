#include "piece.h"

void piece::move(int x, int y) {
    this->_x = x;
    this->_y = y;
}


int piece::getx() {return this->_x;}
int piece::gety() {return this->_y;}