#include "State.h"

State::State() {
    // Set save file
    file = "./build/save.txt";
    
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
    // Set save file
    file = "./build/save.txt";
}

void loadCurrentBoard() {

}

void loadPrevMoves() {

}

void saveState() {
    // Step One: Clear File

    // Step One: Save Board
    saveBoard();
    
    // Step Two: Save Moves
    saveMoves();
}