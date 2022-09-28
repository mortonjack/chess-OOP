#include "gameboard.h"
#include "pawn.h"
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

bool gameboard::movePiece(int oldFile, int oldRank, int newFile, int newRank) {
    // Ensure all coordinates are valid
    if (oldRank < 0 || oldRank > 7 || oldFile < 0 || oldFile > 7 ||
        newRank < 0 || newRank > 7 || newFile < 0 || newFile > 7) {
        return false;
    }

    if (board[oldFile][oldRank] != nullptr) { // check a piece exists at oldRank, oldFile
        piece* piece = board[oldFile][oldRank];

        // Validity Checks
        if (oldRank == newRank && oldFile == newFile) return false; // Ensure that the piece has moved
        if (!(checkPathClear(oldFile,oldRank, newFile,newRank))) return false; // Check if the piece's path is clear

        // If there is not a piece at the new location...
        if (board[newFile][newRank] == nullptr) {
            if (!(piece->checkMoveValidity(oldFile,oldRank, newFile,newRank))) return false; // Check if the move is valid
            // Move piece
            addPiece(newFile, newRank, piece);
            removePiece(oldFile, oldRank);
            // Check if king is in check
            if (isInCheck(piece->getColor())) {
                // Undo move
                removePiece(newFile, newRank);
                addPiece(oldFile, oldRank, piece);
                return false;
            } else {
                // increment move counter
                piece->move();
                // report successful move
                return true;
            }
        // If there is a piece at the new location...
        } else {
            // If the piece is a different color...
            if (board[newFile][newRank]->getColor() != board[oldFile][oldRank]->getColor()) {
                // Check if the capture is valid
                if (!(piece->checkCaptureValidity(oldFile,oldRank, newFile,newRank))) return false;
                
                // store pointer to piece at desination
                piece = board[newFile][newRank];

                // Move piece
                addPiece(newFile, newRank, board[oldFile][oldRank]);
                removePiece(oldFile, oldRank);

                // Check if king is in check
                if (isInCheck(board[newFile][newRank]->getColor())) {
                    // Undo move
                    addPiece(oldFile, oldRank, board[newFile][newRank]);
                    addPiece(newFile, newRank, piece);
                    return false;
                } else {
                    // increment move counter
                    board[newFile][newRank]->move();
                    // capture piece
                    piece->capture();
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

void gameboard::getKingCoords(char color, int * kingFile, int * kingRank) {
    // Replace kingFile and kingRank with king coordinates
    // if no king is found, replaces each with -1
    // format: void getKingCoords(char color, int* kingFile, int* kingRank);

    // Find the king
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // if there's a piece
            if (board[i][j] != nullptr) {
                // if its a king of the correct color
                if (board[i][j]->getColor() == color && board[i][j]->getType() == 'k') {
                    *kingFile = i;
                    *kingRank = j;
                    return;
                }
            }
        }
    }

    // No king could be found
    *kingFile = -1;
    *kingRank = -1;
    return;
}

bool gameboard::isThreatened(int file, int rank) {
    // Only use this input if there is a piece at this position.
    return (isThreatened(board[file][rank]->getColor(), file, rank));
}

bool gameboard::isThreatened(char color, int file, int rank) {
    // Returns true if the tile is being threatened
    // Input color is the color of the piece
    
    // Check all enemy pieces
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Ensure [i][j] isn't current position
            if (i != file || j != rank) {
                // Check if piece exists at location
                if (board[i][j] != nullptr) {
                    // Check if piece is enemy
                    if (board[i][j]->getColor() != color) {
                        // Check if enemy piece can take at this tile
                        if (board[i][j]->checkCaptureValidity(i,j, file,rank)) {
                            // Check if path is clear to take at this tile
                            if (checkPathClear(i,j, file,rank)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    // No enemy piece threatens this tile
    return false;
}

bool gameboard::isInCheck() {return isInCheck('W');}

bool gameboard::isInCheck(char color) {
    // Check if king of color is in check
    int file;
    int rank;

    // Find the king
    getKingCoords(color, &file, &rank);
    if (file == -1 || rank == -1) return false; // no king exists

    // Check if enemy piece is threatening the king
    return isThreatened(color, file, rank);
}

bool gameboard::isInCheckmate() {return isInCheckmate('W');} 

bool gameboard::isInCheckmate(char color) {
    /*
     * Returns true if color is in checkmate
     * otherwise returns false
     * 
     * STEPS:
     * 
     * 1. Ask if king is in check
     * 2. Remove king from board
     * 3. Look for a free tile around the king which isn’t under attack
     * 4. Add king back to board
     * 5. Add generic piece to all points on the board (except kings location & places with the king’s pieces) and see if king is out of check
     * 6. Find a piece which can move there
     * 7. Remove & add piece there
     * 8. Ask if king in check
     */

    // Step 1: Ask if king is in check
    if (!isInCheck(color)) return false;
    bool canEscape = false;

    // Step 2: Remove king from board
    int file;
    int rank;
    getKingCoords(color, &file, &rank);
    if (file == -1 || rank == -1) return false; // no king exists
    piece* theKing = board[file][rank];
    removePiece(file, rank);

    // Step 3: Look for a free tile around the king which isn't under attack
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Make sure within bounds of the gameboard
            if (!(file+i < 0 || file+i > 7 || rank+j < 0 || rank+j > 7)) {
                // Ensure king can move to this position
                if (board[file+i][rank+j] == nullptr || 
                    board[file+i][rank+j]->getColor() != color) {
                    // If this tile isn't threatened, king can escape check
                    if (!isThreatened(color, file+i, rank+j)) canEscape = true;
                }
            }
        }
    }

    // Step 4: Add king back to board
    addPiece(file, rank, theKing);
    if (canEscape) return false;

    // Step 5: Add generic piece to all points on the board and see if king is in check
    pawn somePawn(color);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Check friendly piece doesn't already exist there
            if (board[i][j] == nullptr || board[i][j]->getColor() != color) {
                // Save current piece
                piece* currentPiece = board[i][j];
                // Add generic piece to this location
                addPiece(i, j, &somePawn);
                // See if king is out of check
                if (!isInCheck(color)) {
                    // Step 6: Find a piece which can move here
                    for (int f = 0; f < 8 && !canEscape; f++) {
                        for (int r = 0; r < 8 && !canEscape; r++) {
                            if (board[f][r] != nullptr) {
                                // Check piece is friendly
                                canEscape = board[f][r]->getColor() == color;
                                if (currentPiece == nullptr) {
                                    // Check if piece can move to i, j
                                    canEscape = canEscape && 
                                    board[f][r]->checkMoveValidity(f,r, i,j);
                                } else {
                                    // Check if piece can capture existing piece at i, j
                                    canEscape = canEscape &&
                                    board[f][r]->checkCaptureValidity(f,r, i,j);
                                }
                                // Check path clear
                                canEscape = canEscape && checkPathClear(f,r, i,j);
                            }

                            // Step 7: Remove & add piece there
                            if (canEscape) {
                                addPiece(i, j, board[f][r]);
                                removePiece(f, r);
                                // Step 8: Ask if king in check
                                if (isInCheck(color)) {
                                    canEscape = false;
                                }
                                // Add piece back
                                addPiece(f,r, board[i][j]);
                                removePiece(i, j);
                            }
                        }
                    }
                }
                // Put existing piece back
                addPiece(i, j, currentPiece);
                if (canEscape) return false;
            }
        }
    }

    // No way out of check (return true)
    return true;
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