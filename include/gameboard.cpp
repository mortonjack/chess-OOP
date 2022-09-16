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

void gameboard::addPiece(piece* newPiece) {
    board[newPiece->getx()][newPiece->gety()] = newPiece;
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