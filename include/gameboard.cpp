#include "gameboard.h"
#include <iostream>
#include <cstdlib>
using namespace std;

gameboard::gameboard() {
    // initialise empty board
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            this->board[file][rank] = nullptr;
        }
    }
}

void gameboard::removePiece(int file, int rank) {
    // remove piece from the board
    board[file][rank] = nullptr;
}

void gameboard::addPiece(int file, int rank, piece* newPiece) {
    // add piece to the board
    board[file][rank] = newPiece;
}

piece* gameboard::targetWithEnPassant(int oldFile, int oldRank, int newFile, int newRank) {
    // Locate the peice being moved
    piece* sourcePiece = board[oldFile][oldRank];
    piece* targetPiece = board[newFile][newRank];

    // Used to store the difference in rank between where the sourcetarget  pawn moves, and where the pawn is captured
    int rankModifier;

    // If we are moving a white pawn, potential target pawns are ±1 rank up from the source pawn's destination
    if (board[oldFile][oldRank]->getType() == 'p') {
        rankModifier = newRank - oldRank;

    // If we are not moving a pawn, en passant does not apply
    } else {
        return targetPiece;
    }

    // Locate the piece that could be targeted via en passant
    piece* enPassantTarget = board[newFile][newRank+rankModifier];

    // Is the piece being captured via en passant an opposite-colored pawn?
    if (enPassantTarget == nullptr) return targetPiece;
    if (!(enPassantTarget->getType() == 'p')) return targetPiece;
    if (!(enPassantTarget->getColor() != sourcePiece->getColor())) return targetPiece;
    if (!(enPassantTarget->getMoveCount() != 1)) return targetPiece;

    // If so, target that pawn to be captured
    return enPassantTarget;
}

bool gameboard::movePiece(int oldFile, int oldRank, int newFile, int newRank) {
    // Ensure all coordinates are valid
    if (oldRank < 0 || oldRank > 7 || oldFile < 0 || oldFile > 7 ||
        newRank < 0 || newRank > 7 || newFile < 0 || newFile > 7) {
        return false;
    }

    if (board[oldFile][oldRank] != nullptr) { // check a piece exists at oldRank, oldFile
        piece* sourcePiece = board[oldFile][oldRank];
        piece* targetPiece = targetWithEnPassant(oldFile,oldRank, newFile,newRank);

        // Validity Checks
        if (oldRank == newRank && oldFile == newFile) return false; // Ensure that the piece has moved
        if (!(checkPathClear(oldFile,oldRank, newFile,newRank))) return false; // Check if the piece's path is clear

        // If there is not a piece at the new location...
        if (targetPiece == nullptr) {
            // Return false if the move isn't valid
            if (!(sourcePiece->checkMoveValidity(oldFile,oldRank, newFile,newRank))) return false;     

            // Move piece
            addPiece(newFile, newRank, sourcePiece);
            removePiece(oldFile, oldRank);

            // Check if king is in check
            if (isInCheck(sourcePiece->getColor())) {
                // Undo move
                removePiece(newFile, newRank);
                addPiece(oldFile, oldRank, sourcePiece);
                return false;
            } else {
                // increment move counter
                sourcePiece->move();
                // report successful move
                return true;
            }
        // If there is a piece at the new location...
        } else {
            // If the piece is a different color...
            if (sourcePiece->getColor() != targetPiece->getColor()) {
                // Check if the capture is valid
                if (!(sourcePiece->checkCaptureValidity(oldFile,oldRank, newFile,newRank))) return false;

                // Move piece
                addPiece(newFile, newRank, board[oldFile][oldRank]);
                removePiece(oldFile, oldRank);

                // Check if king is in check
                if (isInCheck(sourcePiece->getColor())) {
                    // Undo move
                    addPiece(oldFile, oldRank, sourcePiece);
                    addPiece(newFile, newRank, targetPiece);
                    return false;
                } else {
                    // increment move counter
                    sourcePiece->move();
                    // capture piece
                    targetPiece->capture();
                    // report successful move
                    return true;
                }
            } else { // Piece at destination is the same colour as piece being moved
                return false; // Don't move
                /*
                    IMPLEMENT CASTLE CHECK HERE
                */
            }
        }
    } else { // if no piece exists at oldRank, oldFile
        return false;
    }
}

bool gameboard::checkPathClear(int oldFile, int oldRank, int newFile, int newRank) {
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
            pathClear = board[oldFile + (i+1)*fileIncrement][oldRank + (i+1)*rankIncrement] == nullptr ? pathClear : false;
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
                if (this->board[file][rank] == nullptr) { 
                    cout << ". "; // display empty tile
                } else { // display piece
                    cout << this->board[file][rank]->getName() << " ";
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
                if (this->board[file][rank] == nullptr) {
                    cout << ". "; // display empty tile
                } else { // display piece
                    cout << this->board[file][rank]->getName() << " ";
                }
            }
            cout << rank + 1 << endl; // display rank
        }
        cout << "  A B C D E F G H" << endl; // display file
    }
}

bool gameboard::isInCheck() {return isInCheck('W');}

bool gameboard::isInCheck(char color) {
    // Check if king of color is in check
    int file;
    int rank;
    bool foundKing = false;
    // Find the king
    for (file = 0; file < 8 && !foundKing; file++) {
        for (rank = 0; rank < 8 && !foundKing; rank++) {
            // if there's a piece
            if (board[file][rank] != nullptr) {
                // if its a king of the correct color
                if (board[file][rank]->getColor() == color
                && board[file][rank]->getType() == 'k') {
                    foundKing = true; // will break out of loop
                }
            }
        }
    }
    file--;
    rank--;
    if (!foundKing) return false; // no king exists

    // Check all enemy pieces
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Check if piece exists at location
            if (board[i][j] != nullptr) {
                // Check if piece is enemy
                if (board[i][j]->getColor() != color) {
                    // Check if enemy piece can take king
                    if (board[i][j]->checkCaptureValidity(i,j, file,rank)) {
                        // Check if path is clear to take the king
                        if (checkPathClear(i,j, file,rank)) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    // Not in check
    return false;
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
            if (this->board[file][rank] != nullptr) { 
                // If not nullptr, check if piece is supposed to be here
                success = false;
                for (int i = 0; i < length && !success; i++) {
                    if (file == coords[i*2] && rank == coords[i*2+1]) {
                        success = true;
                    }
                }
                if (!success) {return false;}
            }
        }
    }

    return true;
}