#include "../include/gameboard.h"
#include "../include/king.h"
#include "../include/bishop.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include "../include/pawn.h"
#include "../include/knight.h"
#include "drawtest.h"
#include <iostream>
using namespace std;

drawtest::drawtest() {
    this->_length = 5;
    this->_failMessage = "Draw test failed";
    this->_passMessage = "Draw test succeeded";
    initialiseResults();
}


bool drawtest::stalemateTest(bool display) {
    // Tests the stalemate function
    // Stalemate occurs when a player 
    // cannot make a legal move on their turn
    bool success = false;

    // Initialise objects
    gameboard board;
    king whiteKing('W');
    king blackKing('B');
    queen whiteQueen('W');

    // Set up board
    board.addPiece(0,7, &blackKing);
    board.addPiece(1,5, &whiteKing);
    board.addPiece(7,6, &whiteQueen);

    // Test 1: Not in stalemate
    if (display) board.visualiseTextBoard();
    bool test1 = !board.isInStalemate('B');

    // Test 2: In stalemate when queen moves to C7
    board.movePiece(7,6, 2,6);
    if (display) board.visualiseTextBoard();
    bool test2 = board.isInStalemate('B');

    // Test 3: White not also in stalemate
    bool test3 = !board.isInStalemate('W');

    // Test 4: Not in stalemate whilst in check
    board.movePiece(2,6, 1,6);
    bool test4 = !board.isInStalemate('B') && board.isInCheckmate('B');
    if (display) board.visualiseTextBoard();

    if (display) {
        if (test1) {
            cout << "Test passed: Not in stalemate" << endl;
        } else {
            cout << "Test failed: Stalemate" << endl;
        }

        if (test2) {
            cout << "Test passed: Stalemate" << endl;
        } else {
            cout << "Test failed: Not in stalemate" << endl;
        }

        if (test3) {
            cout << "Test passed: White not in stalemate" << endl;
        } else {
            cout << "Test failed: White in stalemate" << endl;
        }

        if (test4) {
            cout << "Test passed: Not in stalemate (checkmate)" << endl;
        } else {
            cout << "Test failed: Stalemate" << endl;
        }
    }

    success = test1 && test2 && test3 && test4;
    return success;
}

bool drawtest::threefoldTest(bool display) {
    // Tests the threefold repetition function
    // Threefold repetition occurs when the same
    // board state occurs 3 turns in a row
    bool success = false;

    // Initialise objects
    gameboard board;
    rook whiteARook('W');
    rook blackARook('B');
    rook whiteHRook('W');
    rook blackHRook('B');
    king whiteKing('W');
    king blackKing('B');
    pawn whitePawn('W');
    pawn blackPawn('B');

    // Set up board
    board.addPiece(4,0, &whiteKing);
    board.addPiece(4,7, &blackKing);
    board.addPiece(0,0, &whiteARook);
    board.addPiece(0,7, &blackARook);
    board.addPiece(7,0, &whiteHRook);
    board.addPiece(7,7, &blackHRook);
    board.addPiece(2,1, &whitePawn);
    board.addPiece(3,6, &blackPawn);

    // Test 1: Returns false when less than 6 moves
    bool test1 = !board.threefoldRepetition();
    if (display) board.visualiseTextBoard();

    // Test 2: Returns false after same state 3 times, except castling no longer possible
    board.movePiece(0,0, 1,0);
    board.movePiece(7,7, 6,7);
    if (display) board.visualiseTextBoard();
    board.movePiece(1,0, 0,0);
    board.movePiece(6,7, 7,7);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,0, 1,0);
    board.movePiece(7,7, 6,7);
    board.movePiece(1,0, 0,0);
    board.movePiece(6,7, 7,7);
    bool test2 = !board.threefoldRepetition();

    // Test 3: Returns true after (truly) same state 3 times
    board.movePiece(0,0, 1,0);
    board.movePiece(7,7, 6,7);
    if (display) board.visualiseTextBoard();
    board.movePiece(1,0, 0,0);
    board.movePiece(6,7, 7,7);
    bool test3 = board.threefoldRepetition();
    if (display) board.visualiseTextBoard();

    // Test 4: Returns false after moving pawns up
    board.movePiece(2,1, 2,3);
    bool test4 = !board.threefoldRepetition();
    board.movePiece(7,7, 7,6);
    board.movePiece(2,3, 2,4);
    if (display) board.visualiseTextBoard();

    // Test 5-6: Doesn't count if en passant possible on first turn
    board.movePiece(3,6, 3,4);
    if (display) board.visualiseTextBoard();

    board.movePiece(0,0, 0,1);
    board.movePiece(7,6, 7,7);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,1, 0,0);
    board.movePiece(7,7, 7,6);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,0, 0,1);
    board.movePiece(7,6, 7,7);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,1, 0,0);
    board.movePiece(7,7, 7,6);
    if (display) board.visualiseTextBoard();
    bool test5 = !board.threefoldRepetition();
    
    board.movePiece(0,0, 0,1);
    board.movePiece(7,6, 7,7);
    board.movePiece(0,1, 0,0);
    board.movePiece(7,7, 7,6);

    bool test6 = board.threefoldRepetition();

    // Test 7: Doesn't count if both castles aren't possible (king move)
    board.movePiece(4,0, 4,1);
    if (display) board.visualiseTextBoard();
    board.movePiece(7,6, 7,7);
    board.movePiece(4,1, 4,0);
    if (display) board.visualiseTextBoard();
    board.movePiece(7,7, 7,6);
    bool test7 = !board.threefoldRepetition();

    // Test 8: Counts if moves aren't in a row
    board.movePiece(0,0, 0,1);
    board.movePiece(7,6, 7,7);
    board.movePiece(0,1, 0,0);
    board.movePiece(7,7, 7,6);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,0, 0,2);
    board.movePiece(7,6, 7,5);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,2, 0,1);
    board.movePiece(7,5, 7,7);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,1, 0,0);
    board.movePiece(7,7, 7,6);
    if (display) board.visualiseTextBoard();
    bool test8 = board.threefoldRepetition();

    // Test 9: Doesn't count if opponent's king moves
    board.movePiece(4,7, 4,6);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,0, 0,1);
    board.movePiece(4,6, 4,7);
    if (display) board.visualiseTextBoard();
    board.movePiece(0,1, 0,0);
    bool test9 = !board.threefoldRepetition();

    if (display) {
        cout << "Threefold repetition function results:" << endl;

        if (test1) {
            cout << "Test passed: Returns false when < 6 moves" << endl;
        } else {
            cout << "Test failed: Returns true when < 6 moves" << endl;
        }

        if (test2) {
            cout << "Test passed: Returns false when castling no longer possible" << endl;
        } else {
            cout << "Test failed: Returns true when castling no longer possible" << endl;
        }

        if (test3) {
            cout << "Test passed: Returns true after same state 3 times" << endl;
        } else {
            cout << "Test failed: Returns false after same state 3 times" << endl;
        }

        if (test4) {
            cout << "Test passed: Returns false after pawns move up" << endl;
        } else {
            cout << "Test failed: Returns true after pawns move up" << endl;
        }

        if (test5) {
            cout << "Test passed: Returns false if en passant possible in first state" << endl;
        } else {
            cout << "Test failed: Returns true if en passant possible in first state" << endl;
        }

        if (test6) {
            cout << "Test passed: Returns true if pawns next to each other 4 turns in a row" << endl;
        } else {
            cout << "Test failed: Returns false if pawns next to each other 4 turns in a row" << endl;
        }

        if (test7) {
            cout << "Test passed: Doesn't count if 2nd castle stops being possible" << endl;
        } else {
            cout << "Test failed: Still counts if 2nd castle stops being possible" << endl;
        }

        if (test8) {
            cout << "Test passed: Counts if moves aren't all in a row" << endl;
        } else {
            cout << "Test failed: Doesn't count if moves aren't all in a row" << endl;
        }

        if (test9) {
            cout << "Test passed: Doesn't count if opponent's king moves (2nd castle not possible)" << endl;
        } else {
            cout << "Test failed: Still counts if opponent's king moves (2nd castle not possible)" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8 && test9;
    return success;
}

bool drawtest::fiftyMoveTest(bool display) {
    // Tests the fifty move function
    // Returns true if each player has moved 50 times
    // Without capturing a piece or moving a pawn
    bool success = false;

    // Initialise objects
    gameboard board;
    pawn whitePawn('W');
    pawn blackPawn('B');
    queen whiteQueen('W');
    queen blackQueen('B');

    // Place pieces
    board.addPiece(3,0, &blackQueen);
    board.addPiece(7,1, &whitePawn);
    board.addPiece(7,6, &blackPawn);
    board.addPiece(0,7, &whiteQueen);

    // Test 1: Fails when no moves made
    if (display) board.visualiseTextBoard();
    bool test1 = !board.fiftyMoveRule();

    // Test 2: Fails when 99 moves made
    board.movePiece(3,0, 0,3);
    if (display) board.visualiseTextBoard();
    for (int i = 1; i < 50; i++) {
        board.movePiece(0,3, 3,0);
        board.movePiece(3,0, 0,3);
    }
    bool test2 = !board.fiftyMoveRule();

    // Test 3: Succeeds when 100 moves made
    board.movePiece(0,3, 3,0);
    if (display) board.visualiseTextBoard();
    bool test3 = board.fiftyMoveRule();

    // Test 4: Fails when pawn moved
    board.movePiece(7,1, 7,3);
    if (display) board.visualiseTextBoard();
    bool test4 = !board.fiftyMoveRule();

    // Test 5: Succeeds after 100 moves
    for (int i = 0; i < 50; i++) {
        board.movePiece(0,7, 0,3);
        board.movePiece(0,3, 0,7);
    }
    board.movePiece(0,7, 0,3);
    if (display) board.visualiseTextBoard();
    bool test5 = board.fiftyMoveRule();

    // Test 6: Fails after capture
    board.movePiece(0,3, 3,0);
    if (display) board.visualiseTextBoard();
    bool test6 = !board.fiftyMoveRule();

    // Display results
    if (display) {
        if (test1) {
            cout << "Test passed: False when no moves made" << endl;
        } else {
            cout << "Test failed: True when no moves made" << endl;
        }

        if (test2) {
            cout << "Test passed: False when 99 moves made" << endl;
        } else {
            cout << "Test failed: True when 99 moves made" << endl;
        }

        if (test3) {
            cout << "Test passed: True when 100 moves made" << endl;
        } else {
            cout << "Test failed: False when 100 moves made" << endl;
        }

        if (test4) {
            cout << "Test passed: False when pawn moved" << endl;
        } else {
            cout << "Test failed: True when pawn moved" << endl;
        }

        if (test5) {
            cout << "Test passed: True when 100 moves made" << endl;
        } else {
            cout << "Test failed: False when 100 moves made" << endl;
        }

        if (test6) {
            cout << "Test passed: False when queen captured" << endl;
        } else {
            cout << "Test failed: True when queen captured" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6;
    return success;
}

bool drawtest::mutualTest(bool display) {
    // If both players mutually agree to draw,
    // the game will result in a draw
    bool success = true;

    return success;
}

bool drawtest::deadTest(bool display) {
    // If no player can legally checkmate the opponent's king,
    // the game automatically ends in a draw
    bool success = true;

    return success;
}

bool drawtest::runTests(bool display) {

    _results[0] = stalemateTest(display && !_results[0]);
    _results[1] = threefoldTest(display && !_results[1]);
    _results[2] = fiftyMoveTest(display && !_results[2]);
    _results[3] = mutualTest(display && !_results[3]);
    _results[4] = deadTest(display && !_results[4]);

    return result();
}