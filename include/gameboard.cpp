#include "gameboard.h"
#include <iostream>
using namespace std;

gameboard::gameboard() {
    // initialise empty board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            this->board[i][j] = nullptr;
        }
    }
}

void gameboard::removePiece(int x, int y) {
    board[x][y] = nullptr;
}

void gameboard::addPiece(int x, int y, piece* newPiece) {
    board[x][y] = newPiece;
}

void gameboard::movePiece(int oldx, int oldy, int newx, int newy) {
    if (board[oldx][oldy] != nullptr) { // check a piece exists at oldx, oldy
        piece* piece = board[oldx][oldy];
        bool validMove = true;

        if (!(piece->checkMoveValidity(oldx,oldy, newx,newy))) validMove = false;
        if (oldx == newx && oldy == newy) validMove = false;

        if (validMove) { // If the proposed move is valid for the piece...
            addPiece(newx,newy,piece); // Add the piece in the target location
            removePiece(oldx,oldy); // Remove the piece from the original location
        } else {
            // Do nothing (error message?)
        }
    }
}

void gameboard::visualiseTextBoard() {
    cout << "  A B C D E F G H" << endl;
    for (int i = 0; i < 8; i++) {
        cout << i << " ";
        for (int j = 0; j < 8; j++) {
            if (this->board[i][j] == nullptr) {
                cout << ". ";
            } else {
                cout << this->board[i][j]->getName() << " ";
            }
        }
        cout << i << endl;
    }
    cout << "  A B C D E F G H" << endl;
}