#include "State.h"
using std::ofstream;

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