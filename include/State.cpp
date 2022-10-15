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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            currentBoard[i][j] = board[i][j];
        }
    }
    // Copy prev move
    _prevMove = prevMove;

    // Clear file
    _file.open("./build/save.txt", ofstream::trunc);
    _file.close();
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
    string returnStr = "";
    returnStr += piece->getType();
    returnStr += ", ";
    // Calculate move count
    int moveCount = piece->getMoveCount();
    string moveString = "";
    while (moveCount > 0) {
        moveString += (char)(moveCount % 10) + '0';
        moveCount -= moveCount % 10;
        moveCount /= 10;
    }
    while (!moveString.empty()) {
        returnStr += moveString.back();
        moveString.pop_back();
    }

    returnStr += ", ";
    returnStr += piece->getColor();
    return returnStr;
}

void State::loadCurrentBoard() {

}

void State::loadPrevMoves() {

}

void State::saveState() {
    // Step One: Create Object
    _file.open("./build/save.txt", ofstream::app);
    _file << "Test";

    // Step One: Save Board
    saveBoard();
    
    // Step Two: Save Moves
    saveMoves();
}


void State::saveBoard() {

}

void State::saveMoves() {

}