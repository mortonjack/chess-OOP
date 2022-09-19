#include "gameboard.h"
#include <iostream>
#include <cstdlib>
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
    // remove piece from the board
    board[rank][file] = nullptr;
}

void gameboard::addPiece(int rank, int file, piece* newPiece) {
    // add piece to the board
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

        if (!(checkPathClear(oldRank,oldFile, newRank,newFile))) return false;

        // If the proposed move is valid for the piece...
        if (board[newRank][newFile] != nullptr) { // If there is a piece at the new location
            board[newRank][newFile]->capture(); //   then capture it
        }
        addPiece(newRank,newFile,piece); // Add the piece in the target location
        removePiece(oldRank,oldFile); // Remove the piece from the original location
        piece->move(); // increment piece's move count

        // report successful move
        return true;
    } else { // if no piece exists at oldRank, oldFile
        return false;
    }
}

bool gameboard::checkPathClear(int oldRank, int oldFile, int newRank, int newFile) {
    bool pathClear = true; // Stores if the path is clear. True by default, but can be falsified by a piece detection.

    // If the path is horizontal, vertical or diagonal (non-knight)...
    if (oldFile == newFile || oldRank == newRank || abs(oldRank - newRank) == abs(oldFile - newFile)) {
        // Determines if we should be searching above (1), below (-1) or at the same rank (0)
        int rankIncrement = 0;
        if (newRank > oldRank) rankIncrement = 1;
        else if (newRank < oldRank) rankIncrement = -1;

        // Determines if we should be searching left (1), right (-1) or on the same file (0)
        int fileIncrement = 0;
        if (newFile > oldFile) fileIncrement = 1;
        else if (newFile < oldFile) fileIncrement = -1;

        // Stores how many squares horizontally, vertically or diagonally to search
        int searchSquares = abs(newRank - oldRank) > abs(newFile - oldFile) ? abs(newRank - oldRank) : abs(newFile - oldFile);

        // Check every sqaure horizontally, vertically or diagonally along the path 
        for (int i = 0; i < searchSquares - 1; i++) {
            pathClear = board[oldRank + (i+1)*rankIncrement][oldFile + (i+1)*fileIncrement] == nullptr ? pathClear : false;
        }
    }
    return pathClear;
}

void gameboard::visualiseTextBoard() { visualiseTextBoard('W'); };

void gameboard::visualiseTextBoard(char color) {
    // display the board as ASCII art in stdout
    if (color == 'B') {
        cout << "  H G F E D C B A" << endl; // display file
        for (int rank = 0; rank < 8; rank++) {
            cout << rank + 1 << " "; // display rank
            for (int file = 7; file >= 0; file--) {
                if (this->board[rank][file] == nullptr) { 
                    cout << ". "; // display empty tile
                } else { // display piece
                    cout << this->board[rank][file]->getName() << " ";
                }
            }
            cout << rank + 1 << endl; // display rank
        }
        cout << "  H G F E D C B A" << endl; // display file
    } else { // display white by default
        cout << "  A B C D E F G H" << endl; // display file
        for (int rank = 7; rank >= 0; rank--) {
            cout << rank + 1 << " "; // display rank
            for (int file = 0; file < 8; file++) {
                if (this->board[rank][file] == nullptr) {
                    cout << ". "; // display empty tile
                } else { // display piece
                    cout << this->board[rank][file]->getName() << " ";
                }
            }
            cout << rank + 1 << endl; // display rank
        }
        cout << "  A B C D E F G H" << endl; // display file
    }
}

bool gameboard::testDriver(piece* pieces[], int* coords, int length) {
    /* 
        Test the board is set up correctly.

        Format: 
        piece* pieces[] = {&piece1, &piece2};
        int coords[] = {0,0, 1,1};
        testDriver(pieces, coords, 2);

        Checks piece1 is located at 0,0, piece2 is located at 1,1
        Then ensures all other points are nullptr
    */

    bool success = true;
    // Check pieces in correct positions:
    for (int i = 0; i < length; i++) {
        if (board[coords[i*2]][coords[i*2+1]] != pieces[i]) {
            success = false;
        }
    }
    if (!success) {return false;}

    // Check rest of board is empty:
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            if (this->board[rank][file] != nullptr) { 
                // If not nullptr, check if piece is supposed to be here
                success = false;
                for (int i = 0; i < length && !success; i++) {
                    if (rank == coords[i*2] && file == coords[i*2+1]) {
                        success = true;
                    }
                }
                if (!success) {return false;}
            }
        }
    }

    return true;
}