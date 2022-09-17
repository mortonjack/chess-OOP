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

bool gameboard::movePiece(int oldx, int oldy, int newx, int newy) {
    // Ensure all coordinates are valid
    if (oldx < 0 || oldx > 7 || oldy < 0 || oldy > 7 ||
        newx < 0 || newx > 7 || newy < 0 || newy > 7) {
        return false;
    }

    if (board[oldx][oldy] != nullptr) { // check a piece exists at oldx, oldy
        piece* piece = board[oldx][oldy];

        // Validity Checks
        if (oldx == newx && oldy == newy) return false; 
        if (!(piece->checkMoveValidity(oldx,oldy, newx,newy))) return false;

        // If the proposed move is valid for the piece...
        addPiece(newx,newy,piece); // Add the piece in the target location
        removePiece(oldx,oldy); // Remove the piece from the original location

        // report successful move
        return true;
    } else { // if no piece exists at oldx, oldy
        return false;
    }
}

void gameboard::visualiseTextBoard() {
    cout << "  A B C D E F G H" << endl;
    for (int i = 0; i < 8; i++) {
        cout << i+1 << " ";
        for (int j = 0; j < 8; j++) {
            if (this->board[i][j] == nullptr) {
                cout << ". ";
            } else {
                cout << this->board[i][j]->getName() << " ";
            }
        }
        cout << i+1 << endl;
    }
    cout << "  A B C D E F G H" << endl;
}