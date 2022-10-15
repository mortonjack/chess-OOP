#include "State.h"
using std::ofstream;
using std::string;

#include <iostream>
using std::cout; using std::endl;

State::State() {
    // Load board from save file
    loadCurrentBoard();
    loadPrevMoves();
}

State::State(Piece* board[8][8], MoveNode* prevMove) {
    // Copy board pieces
    updateBoard(board);

    // Copy prev move
    _prevMove = prevMove;

    // Clear files
    _file.open("./build/board.txt", ofstream::trunc);
    _file.close();
    _file.open("./build/moves.txt", ofstream::trunc);
    _file.close();
}

void State::updateBoard(Piece* board[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            currentBoard[i][j] = board[i][j];
        }
    }
}


Piece* State::makePiece(string pieceStr) {
    /* 
     * Takes "pieceType, moveCount, color" as input
     * Also returns nullptr if string is empty
     * Creates & returns dynamically allocated
     */

    // Initialise vars
    Piece* piece = nullptr;
    bool typeRead = false;
    char pieceType = '\0';
    bool movesCounted = false;
    int moveCount = 0;
    char pieceColour = '\0';

    // Iterate through string
    for (int i = 0; i < (int)pieceStr.length(); i++) {
        if (pieceStr[i] != ' ') {
            if (!typeRead) { // Get piece type
                if (pieceStr[i] != ',') pieceType = pieceStr[i];
                else typeRead = true;
            } else if (!movesCounted) { // Get moves counted
                if (pieceStr[i] == ',') movesCounted = true;
                else {
                    moveCount *= 10;
                    moveCount += (int)pieceStr[i] - '0';
                }
            } else if (pieceColour == '\0') { // Get colour
                pieceColour = pieceStr[i];
            }
        }
    }

    // Construct piece
    switch(pieceType) {
        case 'r':
            piece = new Rook(pieceColour);
            break;
        case 'b':
            piece = new Bishop(pieceColour);
            break;
        case 'n':
            piece = new Knight(pieceColour);
            break;
        case 'k':
            piece = new King(pieceColour);
            break;
        case 'q':
            piece = new Queen(pieceColour);
            break;
        case 'p':
            piece = new Pawn(pieceColour);
            break;
    }

    // Make moves
    for (int i = 0; i < moveCount; i++) {
        piece->move();
    }

    return piece;
}

string State::storePiece(Piece* piece) {
    // Store a piece as a string
    string returnStr = "";
    if (piece == nullptr) return returnStr;

    // Get piece type
    returnStr += piece->getType();
    returnStr += ", ";

    // Calculate move count
    int moveCount = piece->getMoveCount();
    string moveString = "";
    if (moveCount == 0) moveString += '0';

    while (moveCount > 0) {
        // Get each multiple of 10
        moveString += (char)(moveCount % 10) + '0';
        moveCount -= moveCount % 10;
        moveCount /= 10;
    }

    while (!moveString.empty()) {
        // Reverse string
        returnStr += moveString.back();
        moveString.pop_back();
    }

    // Store color
    returnStr += ", ";
    returnStr += piece->getColor();
    return returnStr;
}

void State::loadCurrentBoard() {

}

void State::loadPrevMoves() {

}

void State::saveState() {
    // Step One: Save Board
    saveBoard();

    // Step Two: Save Moves
    _file.open("./build/moves.txt", ofstream::trunc);
    _file.close();
    saveAllMoves(_prevMove);
}

void State::saveState(Piece* board[8][8]) {
    // Step One: Save Board
    updateBoard(board);
    saveBoard();
    
    // Step Two: Save Previous Move
    saveMove(_prevMove);
}


void State::saveBoard() {
    // Save board (re-write board save)

    // Clear board save file
    _file.open("./build/board.txt", ofstream::trunc);
    _file.close();

    // Open file
    _file.open("./build/board.txt", ofstream::app);
    
    // Write to file
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            _file << "{"; // begin piece
            
            _file << storePiece(currentBoard[file][rank]);

            _file << "} "; // end piece
        }
        _file << "\n"; // new line
    }
}

void State::saveAllMoves(MoveNode* node) {
    // Save all moves (re-write moves save)

    // Recursively call function until the final node
    if (node->prev() == nullptr) {
        return;
    } else {
        saveAllMoves(node->prev());
    }

    // Save this node
    saveMove(node);

    return;
}

void State::saveMove(MoveNode* node) {
    // Save the most recent move
    char enPassant = node->enPassant() ? 'T' : 'F';

    // Open Moves Save
    _file.open("./build/moves.txt", ofstream::app);
    
    // Append Most Recent Move
    _file << "{";
    _file << node->getOldFile() << ", " << node->getOldRank() << ", ";
    _file << node->getNewFile() << ", " << node->getNewRank() << ", ";
    _file << '{' << storePiece(node->getCapturedPiece()) << "}, ";
    _file << enPassant << ", {" << "}}\n";

    // Close file
    _file.close();
}