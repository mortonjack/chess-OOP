#include "movenodetest.h"
#include "../include/pawn.h"
#include "../include/king.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include <iostream>
using namespace std;

movenodetest::movenodetest() {
    this->_length = 1;
    this->_failMessage = "Move Node test failed";
    this->_passMessage = "Move Node test succeeded";
    initialiseResults();
}

void movenodetest::visualiseBoard(piece* board[8][8]) {
    cout << "  A B C D E F G H" << endl; // display file
    for (int rank = 7; rank >= 0; rank--) {
        cout << rank + 1 << " "; // display rank
        for (int file = 0; file < 8; file++) {
            if (board[file][rank] == nullptr) {
                cout << ". "; // display empty tile
            } else { // display piece
                cout << board[file][rank]->getName() << " ";
            }
        }
        cout << rank + 1 << endl; // display rank
    }
    cout << "  A B C D E F G H" << endl; // display file
}

bool movenodetest::basicTest(bool display) {
    bool success = false;

    // Initialise empty board
    piece* board[8][8] = {nullptr};

    // Add pieces to board
    queen blackQueen('B');
    queen whiteQueen('W');
    pawn blackPawn('B');
    pawn whitePawn('W');
    king whiteKing('W');
    rook whiteRook('W');

    board[3][6] = &blackPawn;
    board[2][4] = &whitePawn;
    board[0][0] = &whiteQueen;
    board[7][7] = &blackQueen;
    board[7][0] = &whiteRook;
    board[4][0] = &whiteKing;

    if (display) visualiseBoard(board);

    // Move 1: En Passant
    piece* enPassantBoard[8][8];
    copyBoard(board, enPassantBoard);
    board[3][5] = &whitePawn;
    board[2][4] = nullptr;
    board[3][6] = nullptr;
    blackPawn.move();
    movenode node(3,6, 3,4, false, nullptr);
    whitePawn.move();
    blackPawn.capture();
    node.addMove(2,4, 3,5, true, &blackPawn);
    if (display) visualiseBoard(board);

    // Move 2: Castle
    piece* castleBoard[8][8];
    copyBoard(board, castleBoard);
    board[6][0] = &whiteKing;
    board[5][0] = &whiteRook;
    whiteKing.move();
    whiteRook.move();
    board[4][0] = nullptr;
    board[7][0] = nullptr;
    node.addMove(4,0, 6,0, false, nullptr);
    if (display) visualiseBoard(board);

    // Move 3: Queens Take
    piece* queenBoard[8][8];
    copyBoard(board, queenBoard);
    board[0][0] = board[7][7];
    board[7][7] = nullptr;
    blackQueen.move();
    whiteQueen.capture();
    node.addMove(7,7, 0,0, false, &whiteQueen);

    // Save final board
    if (display) visualiseBoard(board);
    piece* finalBoard[8][8];
    copyBoard(board, finalBoard);

    // Test 1: Reverse Queens Take
    node.reverseBoard(board, 1);
    if (display) visualiseBoard(board);
    bool test1 = testBoardEquality(board, queenBoard);
    node.unreverseBoard(board, 1);
    bool test_1 = testBoardEquality(board, finalBoard);

    // Test 2: Reverse Castle
    node.reverseBoard(board, 2);
    if (display) visualiseBoard(board);
    bool test2 = testBoardEquality(board, castleBoard);
    node.unreverseBoard(board, 2);
    bool test_2 = testBoardEquality(board, finalBoard);
    
    // Test 3: Reverse En Passant
    node.reverseBoard(board, 4);
    if (display) visualiseBoard(board);
    bool test3 = testBoardEquality(board, enPassantBoard);
    node.unreverseBoard(board, 4);
    bool test_3 = testBoardEquality(board, finalBoard);

    if (display) {
        if (test1) {
            cout << "Test passed: Reversed queen take" << endl;
        } else {
            cout << "Test failed: Didn't reverse queen take" << endl;
        }

        if (test_1) {
            cout << "Test passed: Unreversed queen take" << endl;
        } else {
            cout << "Test failed: Didn't unreverse queen take" << endl;
        }

        if (test2) {
            cout << "Test passed: Reversed castle" << endl;
        } else {
            cout << "Test failed: Didn't reverse castle" << endl;
        }

        if (test_2) {
            cout << "Test passed: Unreversed castle" << endl;
        } else {
            cout << "Test failed: Didn't unreverse castle" << endl;
        }

        if (test3) {
            cout << "Test passed: Reversed en passant" << endl;
        } else {
            cout << "Test failed: Didn't reverse en passant" << endl;
        }

        if (test_3) {
            cout << "Test passed: Unreversed en passant" << endl;
        } else {
            cout << "Test failed: Didn't unreverse en passant" << endl;
        }
    }

    success = test1 && test_1 && test2 && test_2 && test3 && test_3;
    return success;
}

void movenodetest::copyBoard(piece* copy[8][8], piece* paste[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            paste[i][j] = copy[i][j];
        }
    }
    return;
}

bool movenodetest::testBoardEquality(piece* first[8][8], piece* second[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (first[i][j] != second[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool movenodetest::runTests(bool display) {
    
    _results[0] = basicTest(display && !_results[0]);

    return result();
}