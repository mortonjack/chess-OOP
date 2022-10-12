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
    // Initialise empty movenode
    prevMove = new movenode();
    moveNumber = 1;
}

void gameboard::clearBoard() {
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            removePiece(file,rank);
        }
    }
    delete prevMove;
    prevMove = new movenode();
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
    return targetWithEnPassant(oldFile, oldRank, newFile, newRank, this->board, this->prevMove);
}

piece* gameboard::targetWithEnPassant(int oldFile, int oldRank, int newFile, int newRank, piece* board[8][8], movenode* node) {
    // Locate the peice being moved
    piece* sourcePiece = board[oldFile][oldRank];
    piece* targetPiece = board[newFile][newRank];

    // Used to store the rank of the target pawn
    int captureRank;

    // If we are moving a white pawn, potential target pawns are ±1 rank up from the source pawn's destination
    if (board[oldFile][oldRank]->getType() == 'p') {
        captureRank = oldRank;

    // If we are not moving a pawn, en passant does not apply
    } else {
        return targetPiece;
    }

    // Locate the piece that could be targeted via en passant
    piece* enPassantTarget = board[newFile][captureRank];

    // Is the piece being captured via en passant an opposite-colored pawn?
    if (enPassantTarget == nullptr) return targetPiece;
    if (!(enPassantTarget->getType() == 'p')) return targetPiece;
    if (enPassantTarget->getColor() == sourcePiece->getColor()) return targetPiece;

    // Did the piece move up 2 spots on the previous turn?
    if (!(enPassantTarget->getMoveCount() == 1)) return targetPiece;
    if (!(node->getNewFile() == newFile && node->getNewRank() == oldRank)) return targetPiece;

    // If so, target that pawn to be captured
    return enPassantTarget;
}

bool gameboard::isCastling(int oldFile, int oldRank, int newFile, int newRank) {
    piece* sourcePiece = board[oldFile][oldRank];

    if (!(sourcePiece->getType() == 'k')) return false; // Castling can only happen to kings
    if (!(sourcePiece->getMoveCount() == 0)) return false; // Kings lose castling rights when they move
    if (!((oldRank == newRank) && (newFile == oldFile + 2 || newFile == oldFile - 2))) return false; // Castling only moves the king 2 tiles to the left/right

    // Store properties about the potential castling move
    int rookFile;
    int fileIncrement;

    // If we are castling short... (new file is larger)
    if (newFile > oldFile) {
        rookFile = 7;
        fileIncrement = 1;
    } else {
        rookFile = 0;
        fileIncrement = -1;
    }

    piece* castleRook = board[rookFile][oldRank];

    if (castleRook == nullptr) return false; // Castling must occur between a king and its rook
    if (!(castleRook->getType() == 'r')) return false;
    if (!(castleRook->getColor() == sourcePiece->getColor())) return false; // You cannot castle with an opposite-colored rook
    if (!(castleRook->getMoveCount() == 0)) return false; // Rooks lose castling rights when they move

    if (!(checkPathClear(oldFile, oldRank, rookFile, newRank))) return false; // You cannot castle through peices

    for (int i = 0; i < 3; i++) {
        // You cannot castle into, out of, or through check
        if (isThreatened(sourcePiece->getColor(), oldFile+(i*fileIncrement),oldRank)) return false; 
    }

    // All conditions pass, castling is valid
    return true;
}

void gameboard::castle(int oldFile, int newFile, int rank) {
    // Move the king to its new, castled position
    piece* castleKing = board[oldFile][rank];

    addPiece(newFile,rank,castleKing);
    removePiece(oldFile,rank);

    // Move the rook to its new, castled position
    piece* castleRook;

    // If we are castling short... (new file is larger)
    if (newFile > oldFile) {
        castleRook = board[7][rank];

        addPiece(newFile-1,rank,castleRook);
        removePiece(7,rank);
    } else {
        castleRook = board[0][rank];

        addPiece(newFile+1,rank,castleRook);
        removePiece(0,rank);
    }

    castleKing->move();
    castleRook->move();
}

bool gameboard::validMove(int oldFile, int oldRank, int newFile, int newRank) {
    // Handles validity checking for a move
    // Assumes checks in validMovement have taken place
    piece* sourcePiece = board[oldFile][oldRank];

    // Check castling
    if (isCastling(oldFile, oldRank, newFile, newRank)) return true;

    // Call piece's move validity function
    if (!sourcePiece->checkMoveValidity(oldFile, oldRank, newFile, newRank)) {
        return false;
    }

    // Add & remove piece
    removePiece(oldFile, oldRank);
    addPiece(newFile, newRank, sourcePiece);

    // Check for check
    if (isInCheck(sourcePiece->getColor())) {
        removePiece(newFile, newRank);
        addPiece(oldFile, oldRank, sourcePiece);
        return false;
    }

    // All checks passed. Return true
    removePiece(newFile, newRank);
    addPiece(oldFile, oldRank, sourcePiece);
    return true;
}

bool gameboard::validCapture(int oldFile, int oldRank, int newFile, int newRank) {
    // Handles validity checking for a capture
    // Assumes checks in validMovement have taken place
    piece* sourcePiece = board[oldFile][oldRank];
    piece* targetPiece = targetWithEnPassant(oldFile, oldRank, newFile, newRank);
    bool enPassant = targetPiece != board[newFile][newRank];

    if (sourcePiece->getColor() == targetPiece->getColor()) return false;

    // Call piece's capture validity function
    if (!sourcePiece->checkCaptureValidity(oldFile, oldRank, newFile, newRank)) {
        return false;
    }

    // Add & remove piece
    removePiece(oldFile, oldRank);
    if (enPassant) removePiece(newFile, oldRank);
    addPiece(newFile, newRank, sourcePiece);

    // Check for check
    if (isInCheck(sourcePiece->getColor())) {
        removePiece(newFile, newRank);
        addPiece(oldFile, oldRank, sourcePiece);
        if (enPassant) {
            addPiece(newFile, oldRank, targetPiece);
        } else {
            addPiece(newFile, newRank, targetPiece);
        }
        return false;
    }

    // All checks passed. Return true
    removePiece(newFile, newRank);
    addPiece(oldFile, oldRank, sourcePiece);
    if (enPassant) {
        addPiece(newFile, oldRank, targetPiece);
    } else {
        addPiece(newFile, newRank, targetPiece);
    }
    return true;
}

bool gameboard::validMovement(int oldFile, int oldRank, int newFile, int newRank) {
    // Checks if a proposed movement is valid

    // Ensure all coordinates are valid
    if (oldRank < 0 || oldRank > 7 || oldFile < 0 || oldFile > 7 ||
        newRank < 0 || newRank > 7 || newFile < 0 || newFile > 7) {
        return false;
    }

    piece* sourcePiece = board[oldFile][oldRank];

    // Check if piece exists
    if (sourcePiece == nullptr) return false;

    piece* targetPiece = targetWithEnPassant(oldFile, oldRank, newFile, newRank);

    // Ensure the piece isn't moving to its current location
    if (oldRank == newRank && oldFile == newFile) return false;

    // Check if the piece's path is clear
    if (!(checkPathClear(oldFile,oldRank, newFile,newRank))) return false;

    // Check if capturing a piece
    if (targetPiece == nullptr) {
        return validMove(oldFile, oldRank, newFile, newRank);
    } else {
        return validCapture(oldFile, oldRank, newFile, newRank);
    }
}

bool gameboard::movePiece(int oldFile, int oldRank, int newFile, int newRank) {
    // Check validity of move
    if (!validMovement(oldFile, oldRank, newFile, newRank)) return false;

    // Check castle
    if (isCastling(oldFile, oldRank, newFile, newRank)) {
        castle(oldFile, newFile, newRank);
        prevMove->addMove(oldFile, oldRank, newFile, newRank, false, nullptr);
        return true;
    }

    // Store pieces
    piece* sourcePiece = board[oldFile][oldRank];
    piece* targetPiece = targetWithEnPassant(oldFile, oldRank, newFile, newRank);
    bool enPassant = targetPiece != board[newFile][newRank];

    // Check en passant
    if (enPassant) {
        removePiece(newFile, oldRank);
    }

    // Capture
    if (targetPiece != nullptr) {
        targetPiece->capture();
    }

    // Move
    sourcePiece->move();
    removePiece(oldFile, oldRank);
    addPiece(newFile, newRank, sourcePiece);

    // Report successful move
    prevMove->addMove(oldFile, oldRank, newFile, newRank, enPassant, targetPiece);
    moveNumber++;
    return true;
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

bool gameboard::isInMate(char color) {
    // Cycles through all friendly pieces
    for (int f = 0; f < 8; f++) {
        for (int r = 0; r < 8; r++) {
            if (board[f][r] != nullptr && board[f][r]->getColor() == color) {
                // Looks for any potential move
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        // Check move validity
                        if (validMovement(f,r, i,j)) return false;
                    }
                }
            }
        }
    }
    return true;
}

bool gameboard::isInCheckmate(char color) {
    // Checks if a colour is in checkmate
    // No legal moves, in check

    if (!isInCheck(color)) return false;
    return isInMate(color);
}

bool gameboard::isInStalemate(char color) {
    // Checks if a colour is in stalemate
    // No legal moves, not in check

    if (isInCheck(color)) return false;
    return isInMate(color);
}

bool gameboard::threefoldRepetition() {
    // Checks if the same board state has existed three times
    bool possibleThreefold = true;
    movenode* node = prevMove;
    bool sameState;
    int stateCount = 1;
    int oldPieceCount = 0;
    int pieceCount = 0;
    int depth = 0;
    bool blackLongCastle = isCastling(4,7,2,7);
    bool blackShortCastle = isCastling(4,7,6,7);
    bool whiteLongCastle = isCastling(4,0,2,0);
    bool whiteShortCastle = isCastling(4,0,6,0);

    // Copy state of current board
    piece* oldBoard[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            oldBoard[i][j] = board[i][j];
            if (board[i][j] != nullptr) pieceCount++;
        }
    }

    while (possibleThreefold) {
        sameState = true;
        oldPieceCount = 0;

        // Are there more moves to reverse?
        if (node->prev(2)->prev() == nullptr) {
            possibleThreefold = false;
            prevMove->unreverseBoard(oldBoard, depth);
            return false;
        }
        node->reverseBoard(oldBoard, 2);
        depth += 2;
        node = prevMove->prev(depth);

        // Check if all pieces are in the same state
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                
                // Check if pieces are in the same position
                if (oldBoard[i][j] != board[i][j]) sameState = false;

                // Check if piece existed at this location
                if (oldBoard[i][j] != nullptr) {
                    
                    // Increment piece counter
                    oldPieceCount++;

                    // Check if pawn moved up
                    if (oldBoard[i][j] != board[i][j]) {
                        if (oldBoard[i][j]->getType() == 'p') {
                            possibleThreefold = false;
                            prevMove->unreverseBoard(oldBoard, depth);
                            return false;
                        }
                    }

                    // En Passant Check
                    if (targetWithEnPassant(i,j, i+1,j+1, oldBoard, node) != oldBoard[i+1][j+1]
                    || targetWithEnPassant(i,j, i-1,j+1, oldBoard, node) != oldBoard[i-1][j+1]
                    || targetWithEnPassant(i,j, i-1,j-1, oldBoard, node) != oldBoard[i-1][j-1]
                    || targetWithEnPassant(i,j, i+1,j-1, oldBoard, node) != oldBoard[i+1][j-1]) {
                        possibleThreefold = false;
                        prevMove->unreverseBoard(oldBoard, depth);
                        return false;
                    }

                    // Castle Check
                    if (blackLongCastle != isCastling(4,7,2,7)
                    || blackShortCastle != isCastling(4,7,6,7)
                    || whiteLongCastle != isCastling(4,0,2,0)
                    || whiteShortCastle != isCastling(4,0,6,0)) {
                        possibleThreefold = false;
                        prevMove->unreverseBoard(oldBoard, depth);
                        return false;
                    }
                }
            }
        }

        // Check if piece was captured
        if (oldPieceCount != pieceCount) {
            possibleThreefold = false;
            prevMove->unreverseBoard(oldBoard, depth);
            return false;
        }

        // Incremement state count
        if (sameState) {
            stateCount++;
        }

        // Check if same board hass occured 3 times
        if (stateCount == 3) {
            prevMove->unreverseBoard(oldBoard, depth);
            return true;
        }
    }

    // Threefold not possible
    return false;
}

bool gameboard::fiftyMoveRule() {
    // Returns true if each player has made 50 moves without
    // capturing a piece or moving up a pawn

    // Check if fifty moves have passed
    movenode* node = prevMove->prev(99);
    if (node->prev() == nullptr) {return false;}

    // Initialise variables
    piece* oldBoard[8][8];
    int pieceCount = 0;
    int oldPieceCount = 0;
    bool pawnMove = false;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            oldBoard[i][j] = board[i][j];
        }
    }

    // Reverse board to old state
    prevMove->reverseBoard(oldBoard, 99);

    // Check if a piece has been captured or a pawn has moved up
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Increment move count
            if (oldBoard[i][j] != nullptr) {
                oldPieceCount++;
            }
            // Increment move count
            if (board[i][j] != nullptr) {
                pieceCount++;

                // See if pawn has moved up
                if (board[i][j]->getType() == 'p') {
                    if (board[i][j] != oldBoard[i][j]) {
                        pawnMove = true;
                    }
                }
            }
        }
    }

    // Bring board back to current state
    prevMove->unreverseBoard(oldBoard, 99);

    // Check if pawn moved up or piece was captured
    return !(pawnMove || pieceCount < oldPieceCount);
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