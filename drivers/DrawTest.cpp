#include "../include/Gameboard.h"
#include "../include/King.h"
#include "../include/Bishop.h"
#include "../include/Rook.h"
#include "../include/Queen.h"
#include "../include/Pawn.h"
#include "../include/Knight.h"
#include "DrawTest.h"
#include <iostream>
using namespace std;

DrawTest::DrawTest() {
    this->_length = 4;
    this->_failMessage = "Draw test failed";
    this->_passMessage = "Draw test succeeded";
    initialiseResults();
}


bool DrawTest::stalemateTest(bool display) {
    // Tests the stalemate function
    // Stalemate occurs when a player 
    // cannot make a legal move on their turn
    bool success = false;

    // Initialise objects
    Gameboard board;
    King whiteKing('W');
    King blackKing('B');
    Queen whiteQueen('W');

    // Set up board
    board.addPiece(0,7, &blackKing);
    board.addPiece(1,5, &whiteKing);
    board.addPiece(7,6, &whiteQueen);

    // Test 1: Not in stalemate
    if (display) board.visualiseTextBoard();
    bool test1 = !board.isInStalemate('B');

    // Test 2: In stalemate when Queen moves to C7
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

bool DrawTest::threefoldTest(bool display) {
    // Tests the threefold repetition function
    // Threefold repetition occurs when the same
    // board state occurs 3 turns in a row
    bool success = false;

    // Initialise objects
    Gameboard board;
    Rook whiteARook('W');
    Rook blackARook('B');
    Rook whiteHRook('W');
    Rook blackHRook('B');
    King whiteKing('W');
    King blackKing('B');
    Pawn whitePawn('W');
    Pawn blackPawn('B');

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

    // Test 7: Doesn't count if both castles aren't possible (King move)
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

    // Test 9: Doesn't count if opponent's King moves
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
            cout << "Test passed: Doesn't count if opponent's King moves (2nd castle not possible)" << endl;
        } else {
            cout << "Test failed: Still counts if opponent's King moves (2nd castle not possible)" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8 && test9;
    return success;
}

bool DrawTest::fiftyMoveTest(bool display) {
    // Tests the fifty move function
    // Returns true if each player has moved 50 times
    // Without capturing a Piece or moving a Pawn
    bool success = false;

    // Initialise objects
    Gameboard board;
    Pawn whitePawn('W');
    Pawn blackPawn('B');
    Queen whiteQueen('W');
    Queen blackQueen('B');

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

    // Test 4: Fails when Pawn moved
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
            cout << "Test passed: False when Pawn moved" << endl;
        } else {
            cout << "Test failed: True when Pawn moved" << endl;
        }

        if (test5) {
            cout << "Test passed: True when 100 moves made" << endl;
        } else {
            cout << "Test failed: False when 100 moves made" << endl;
        }

        if (test6) {
            cout << "Test passed: False when Queen captured" << endl;
        } else {
            cout << "Test failed: True when Queen captured" << endl;
        }
    }

    success = test1 && test2 && test3 && test4 && test5 && test6;
    return success;
}

bool DrawTest::insufficientTest(bool display) {
    // Tests the insuffient material function
    // Returns true if some player has enough pieces
    // to force checkmate
    bool success = false;

    // Initialise objects
    Gameboard board;
    King whiteKing('W');
    King blackKing('B');
    Knight whiteKnightOne('W');
    Knight whiteKnightTwo('W');
    Bishop whiteBishopOne('W');
    Bishop whiteBishopTwo('W');
    Pawn whitePawn('W');
    Knight blackKnightOne('B');

    // Place pieces
    board.addPiece(0,0,&whiteKing);
    board.addPiece(7,0,&blackKing);

    // Make sure it is insufficient material, when there are just two kings
    if (display) board.visualiseTextBoard();
    bool test1 = board.insufficientMaterial();

    // Place single knight
    board.addPiece(0,2,&whiteKnightOne);

    // Make sure the material is still insufficient
    if (display) board.visualiseTextBoard();
    bool test2 = board.insufficientMaterial();

    // Place the other knight
    board.addPiece(0,3,&whiteKnightOne);

    // Make sure the material is no longer insufficient
    if (display) board.visualiseTextBoard();
    bool test3 = !board.insufficientMaterial();

    // Remove a knight, replace with a bishop
    board.removePiece(0,2);
    board.addPiece(0,2,&whiteBishopOne);

    // Make sure that material is still sufficient
    if (display) board.visualiseTextBoard();
    bool test4 = !board.insufficientMaterial();

    // Remove the other knight, replace with a bishop
    board.removePiece(0,3);
    board.addPiece(0,3,&whiteBishopTwo);

    // Make sure that material is still sufficient
    if (display) board.visualiseTextBoard();
    bool test5 = !board.insufficientMaterial();

    // Remove a bishop
    board.removePiece(0,3);

    // Make sure that material is no longer sufficient
    if (display) board.visualiseTextBoard();
    bool test6 = board.insufficientMaterial();

    // Add an opposite-colored knight
    board.addPiece(0,4,&blackKnightOne);

    // Make sure that material is still insufficient
    if (display) board.visualiseTextBoard();
    bool test7 = board.insufficientMaterial();

    // Add a pawn
    board.addPiece(7,7,&whitePawn);

    // Make sure that material is no longer insufficient
    if (display) board.visualiseTextBoard();
    bool test8 = !board.insufficientMaterial();

    // Display results
    if (display) {
        if (test1) {
            cout << "Test passed: True with two kings" << endl;
        } else {
            cout << "Test failed: False with two kings" << endl;
        }

        if (test2) {
            cout << "Test passed: True with lone knight" << endl;
        } else {
            cout << "Test failed: False with lone knight" << endl;
        }

        if (test3) {
            cout << "Test passed: False with two knights" << endl;
        } else {
            cout << "Test failed: True with two knights" << endl;
        }

        if (test4) {
            cout << "Test passed: False with a knight and bishop" << endl;
        } else {
            cout << "Test failed: True with a knight and bishop" << endl;
        }

        if (test5) {
            cout << "Test passed: False with two bishops" << endl;
        } else {
            cout << "Test failed: True with two bishops" << endl;
        }

        if (test6) {
            cout << "Test passed: True with lone bishop" << endl;
        } else {
            cout << "Test failed: False with lone bishop" << endl;
        }

        if (test7) {
            cout << "Test passed: True with opposite-colored pieces" << endl;
        } else {
            cout << "Test failed: False with opposite-colored pieces" << endl;
        }

        if (test8) {
            cout << "Test passed: False with pawn" << endl;
        } else {
            cout << "Test failed: True with pawn" << endl;
        }
    }

    return success = test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8;
}

bool DrawTest::runTests(bool display) {

    _results[0] = stalemateTest(display && !_results[0]);
    _results[1] = threefoldTest(display && !_results[1]);
    _results[2] = fiftyMoveTest(display && !_results[2]);
    _results[3] = insufficientTest(display && !_results[3]);

    return result();
}