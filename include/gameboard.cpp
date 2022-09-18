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

bool gameboard::movePiece(int oldRank, int oldFile, int newRank, int newFile) {
    // Ensure all coordinates are valid
    if (oldRank < 0 || oldRank > 7 || oldFile < 0 || oldFile > 7 ||
        newRank < 0 || newRank > 7 || newFile < 0 || newFile > 7) {
        return false;
    }

    if (board[oldRank][oldFile] != nullptr) { // check a piece exists at oldRank, oldFile
        piece* piece = board[oldRank][oldFile];

        // Validity Checks
        if (oldRank == newRank && oldFile == newFile) return false; 
        if (!(piece->checkMoveValidity(oldRank,oldFile, newRank,newFile))) return false;

        // If the proposed move is valid for the piece...
        addPiece(newRank,newFile,piece); // Add the piece in the target location
        removePiece(oldRank,oldFile); // Remove the piece from the original location

        // report successful move
        return true;
    } else { // if no piece exists at oldRank, oldFile
        return false;
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