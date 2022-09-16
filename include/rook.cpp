
#include "piece.h"
#include "rook.h"

rook::rook(): rook('W') {}; // Peices are white by default

rook::rook(char color) {
    _color = color;
    _name = color == 'W' ? 'R' : 'r'; // If the passed color is not 'W', the piece must be black
}

bool rook::checkMoveValidity(int oldx, int oldy, int newx, int newy) {
    // Check if the new move is on the same rank or file. If so, the move is valid.
    bool valid = (oldx == newx) || (oldy == newy);
    return valid;
}