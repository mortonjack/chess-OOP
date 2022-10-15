#include "SaveTest.h"
#include "../include/Game.hpp"
#include <iostream>
using std::cout;
using std::endl;

SaveTest::SaveTest() {
    this->_length = 2;
    this->_failMessage = "Save test failed";
    this->_passMessage = "Save test succeeded";
    initialiseResults();
}

bool SaveTest::testBoard(Piece* board1[8][8], Piece* board2[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Piece exists
            if (board1[i][j] != nullptr || board2[i][j] != nullptr) {
                // Both boards have existing piece
                if (board1[i][j] == nullptr || board2[i][j] == nullptr) return false;
                // Both pieces are of same type & colour
                if (board1[i][j]->getName() != board2[i][j]->getName()) return false;
                // Both pieces have same move count
                if (board1[i][j]->getMoveCount() != board2[i][j]->getMoveCount()) return false;
            }
        }
    }
    return true;
}

bool SaveTest::testMoveNode(MoveNode* node1, MoveNode* node2) {
    if (node1 == node2) return true;
    if (node1 == nullptr || node2 == nullptr) return false;

    while (node1->prev() != nullptr && node2->prev() != nullptr) {
        // Check positions
        if (node1->getOldFile() != node2->getOldFile()) return false;
        if (node1->getOldRank() != node2->getOldRank()) return false;
        if (node1->getNewFile() != node2->getNewFile()) return false;
        if (node1->getNewRank() != node2->getNewRank()) return false;

        // Check captured piece
        if (node1->getCapturedPiece() != nullptr || node2->getCapturedPiece() != nullptr) {
            if (node1->getCapturedPiece() == nullptr || node2->getCapturedPiece() == nullptr) return false;
            if (node1->getCapturedPiece()->getName() != node2->getCapturedPiece()->getName()) return false;
            if (node1->getCapturedPiece()->getMoveCount() != node2->getCapturedPiece()->getMoveCount()) return false;
        }

        // Check en passant
        if (node1->enPassant() != node2->enPassant()) return false;
        
        // Check promoted
        if (node1->promoted() != node2->promoted()) return false;

        node1 = node1->prev();
        node2 = node2->prev();
    }

    // Both nodes end here
    if (node1->prev() != node2->prev()) return false;

    return true;
}

bool SaveTest::directTest(bool display) {
    bool success = false;

    // Initialise objects
    Gameboard board;
    Pawn whitePawnOne('W');
    Pawn whitePawnTwo('W');
    Pawn blackPawn('B');
    Rook blackRook('B');
    King blackKing('B');
    King whiteKing('W');

    // Place pieces
    board.addPiece(5,6, &whitePawnOne);
    board.addPiece(6,1, &whitePawnTwo);
    board.addPiece(3,6, &blackPawn);
    board.addPiece(7,7, &blackKing);
    board.addPiece(0,7, &blackRook);
    board.addPiece(3,0, &whiteKing);
    if (display) board.visualiseTextBoard();

    // Make moves
    board.movePiece(3,6, 3,5);
    board.movePiece(5,6, 5,7);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,7, 5,7);
    board.movePiece(6,1, 6,3);
    board.movePiece(3,5, 3,4);
    if (display) board.visualiseTextBoard();

    // Save game state
    Piece* currBoard[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            currBoard[i][j] = board.getPiece(i, j);
        }
    }
    State save(currBoard, board.getPrevMove());
    save.saveState();

    // Tests 1 & 2: Load game state from state object
    Piece* board1[8][8];
    MoveNode* moveHistory1 = nullptr;
    save.loadGame(board1, &moveHistory1);
    bool test1 = testBoard(currBoard, board1);
    bool test2 = testMoveNode(board.getPrevMove(), moveHistory1);

    success = test1 && test2;
    return success;
}

bool SaveTest::gameTest(bool display) {
    // Tests game.hpp saves/loads correctly
    bool success = true;

    return success;
}

bool SaveTest::runTests(bool display) {
    _results[0] = directTest(display && !_results[0]);
    _results[1] = gameTest(display && !_results[1]);

    return result();
}