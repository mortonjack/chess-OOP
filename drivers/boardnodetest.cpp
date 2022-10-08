#include "boardnodetest.h"
#include "../include/pawn.h"
#include "../include/king.h"
#include "../include/queen.h"
#include <iostream>
using namespace std;

boardnodetest::boardnodetest() {
    this->_length = 1;
    this->_failMessage = "Board Node test failed";
    this->_passMessage = "Board Node test succeeded";
    initialiseResults();
}

void boardnodetest::visualiseBoard(boardnode node) {
    cout << "  A B C D E F G H" << endl; // display file
    for (int rank = 7; rank >= 0; rank--) {
        cout << rank + 1 << " "; // display rank
        for (int file = 0; file < 8; file++) {
            if (node.getPiece(file, rank) == nullptr) {
                cout << ". "; // display empty tile
            } else { // display piece
                cout << node.getPiece(file, rank)->getName() << " ";
            }
        }
        cout << rank + 1 << endl; // display rank
    }
    cout << "  A B C D E F G H" << endl; // display file
}

void boardnodetest::visualiseBoard(piece* board[8][8]) {
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

bool boardnodetest::basicTest(bool display) {
    // Basic test for the class
    // Ensuring all methods work
    bool success = false;

    // Initialise pieces
    king blackKing('B');
    king whiteKing('W');
    pawn blackPawn('B');
    pawn whitePawn('W');
    queen blackQueen('B');
    queen whiteQueen('W');

    // Create fake board 'cos its private in the gameboard class
    piece* board[8][8];
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            board[file][rank] = nullptr;
        }
    }

    // Sprinkle in a few pieces
    board[7][3] = &blackKing;
    board[0][3] = &whiteKing;
    board[5][2] = &blackQueen;
    board[3][6] = &whiteQueen;
    board[6][1] = &blackPawn;
    board[3][2] = &whitePawn;

    if (display) visualiseBoard(board);
    boardnode prevBoard(board);
    if (display) visualiseBoard(prevBoard);

    // The first test is that this doesn't segfault

    // Add board to the list
    board[5][2] = nullptr;
    board[1][7] = &blackQueen;
    prevBoard.addBoard(board);
    if (display) visualiseBoard(prevBoard);
    if (display) visualiseBoard(*(prevBoard.prev()));

    bool test1 = prevBoard.getPiece(1, 7) == &blackQueen;
    bool test2 = prevBoard.prev()->getPiece(1, 7) == nullptr;

    // Move white queen to black's position
    board[3][6] = nullptr;
    board[1][7] = &whiteQueen;
    prevBoard.addBoard(board);
    if (display) visualiseBoard(prevBoard);

    // Move black pawn to queen's position
    board[6][1] = nullptr;
    board[1][7] = &blackPawn;
    prevBoard.addBoard(board);
    if (display) visualiseBoard(prevBoard);
    if (display) visualiseBoard(*(prevBoard.prev(8)));

    bool test3 = prevBoard.getPiece(1, 7) == &blackPawn;
    bool test4 = prevBoard.prev(6)->getPiece(1, 7) == nullptr;
    bool test5 = prevBoard.prev(2)->getPiece(1, 7) == &blackQueen;
    bool test6 = prevBoard.prev(1)->getPiece(1, 7) == &whiteQueen;
    
    if (display) {
        if (test1) {
            cout << "Test passed: New node added to linked list" << endl;
        } else {
            cout << "Test failed: New node not added to linked list" << endl;
        }

        if (test2) {
            cout << "Test passed: Original node intact" << endl;
        } else {
            cout << "Test failed: Original node not intact" << endl;
        }

        if (test3) {
            cout << "Test passed: Four nodes added to linked list" << endl;
        } else {
            cout << "Test failed: Four nodes not added to linked list" << endl;
        }

        if (test4) {
            cout << "Test passed: Linked list search stops at original node" << endl;
        } else {
            cout << "Test failed: Linked list search doesn't go to original node" << endl;
        }

        if (test5) {
            cout << "Test passed: 2nd previous node accessible" << endl;
        } else {
            cout << "Test failed: 2nd previous node inaccessible" << endl;
        }

        if (test6) {
            cout << "Test passed: Previous node accessible" << endl;
        } else {
            cout << "Test failed: Previous node inaccessible" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6;
    return success;
}

bool boardnodetest::runTests(bool display) {
    bool success = true;

    success = success && basicTest(display);

    return success;
}