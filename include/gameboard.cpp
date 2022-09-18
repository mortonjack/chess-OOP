#include "gameboard.h"
#include <iostream>
using namespace std;

gameboard::gameboard() {
    // initialise empty board
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            this->board[rank][file] = nullptr;
        }
    }
}

void gameboard::removePiece(int rank, int file) {
    board[rank][file] = nullptr;
}

void gameboard::addPiece(int rank, int file, piece* newPiece) {
    board[rank][file] = newPiece;
}

void gameboard::movePiece(int oldx, int oldy, int newx, int newy) {
    if (!(board[oldx][oldy] == nullptr)) {
        piece* piece = board[oldx][oldy];

        if (piece->checkMoveValidity(oldx,oldy, newx,newy)) { // If the proposed move is valid for the piece...
            addPiece(newx,newy,piece); // Add the piece in the target location
            removePiece(oldx,oldy); // Remove the piece from the original location
        } else {
            // Do nothing (error message?)
        }
    }
}

void gameboard::visualiseTextBoard() {visualiseTextBoard('W');};

void gameboard::visualiseTextBoard(char color) {
    if (color == 'B') {
        cout << "  H G F E D C B A" << endl;
        for (int rank = 0; rank < 8; rank++) {
            cout << rank + 1 << " ";
            for (int file = 7; file >= 0; file--) {
                if (this->board[rank][file] == nullptr) {
                    cout << ". ";
                } else {
                    cout << this->board[rank][file]->getName() << " ";
                }
            }
            cout << rank + 1 << endl;
        }
        cout << "  H G F E D C B A" << endl;
    } else {
        cout << "  A B C D E F G H" << endl;
        for (int rank = 7; rank >= 0; rank--) {
            cout << rank + 1 << " ";
            for (int file = 0; file < 8; file++) {
                if (this->board[rank][file] == nullptr) {
                    cout << ". ";
                } else {
                    cout << this->board[rank][file]->getName() << " ";
                }
            }
            cout << rank + 1 << endl;
        }
        cout << "  A B C D E F G H" << endl;
    }
}