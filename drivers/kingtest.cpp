#include "../include/gameboard.h"
#include "../include/king.h"
#include "../include/rook.h"
#include "../include/bishop.h"
#include "../include/knight.h"
#include "kingtest.h"
#include <iostream>
using namespace std;

kingtest::kingtest(): kingtest(1) {}
kingtest::kingtest(int length) {
    this->_failMessage = "King test failed";
    this->_passMessage = "King test succeeded";
}

bool kingtest::movementTest(bool display) {
    // Test king movement
    bool success = true;

    // Create the game board a white king.
    gameboard board;
    king testKing('W');

    // Add the king to the game board
    board.addPiece(3,3,&testKing);
    if (display) board.visualiseTextBoard();

    // Test all valid move directions- move king in a circle
    board.movePiece(3,3, 3,2);
    board.movePiece(3,2, 2,1);
    board.movePiece(2,1, 1,1);
    board.movePiece(1,1, 0,2);
    board.movePiece(0,2, 0,3);
    if (display) board.visualiseTextBoard();
    
    // Run first test
    piece* pieces[1] = {&testKing};
    int coords[2] = {0,3};
    bool test1 = board.testDriver(pieces, coords, 1);

    // Continue to move king
    board.movePiece(0,3, 1,4);
    board.movePiece(1,4, 2,4);
    board.movePiece(2,4, 3,3);
    if (display) board.visualiseTextBoard();
    
    // Run second test
    coords[0] = 3;
    coords[1] = 3;
    bool test2 = board.testDriver(pieces, coords, 1);

    // Test invalid move directions
    board.movePiece(3,3, 1,3);
    board.movePiece(3,3, 2,1);
    board.movePiece(3,3, 5,4);

    // Run third test
    bool test3 = board.testDriver(pieces, coords, 1);
    if (display) board.visualiseTextBoard();

    // Run tests
    if (display) {
        if (test1) {
            cout << "Test passed: King moved halfway around the circle" << endl;
        } else {
            cout << "Test failed: King failed to move halfway around the circle" << endl;
        }

        if (test2) {
            cout << "Test passed: King moved in all 8 directions" << endl;
        } else {
            cout << "Test failed: King failed to move in all 8 directions" << endl;
        }

        if (test3) {
            cout << "Test passed: King didn't make illegal moves" << endl;
        } else {
            cout << "Test failed: King made illegal move" << endl;
        }
    }

    success = test1 && test2 && test3;
    return success;
}

bool kingtest::castleTest(bool display) {
    // Test king castling
    bool success = true;

    // Create the game board a white king.
    gameboard board;

    king whiteKing('W');
    king whiteKingTwo('W');
    king whiteKingThree('W');

    rook whiteARook('W');
    rook whiteHRook('W');
    rook whiteARookTwo('W');
    rook whiteHRookTwo('W');
    rook whiteARookThree('W');
    rook whiteHRookThree('W');

    rook blackRook('B');
    knight blackKnight('B');
    knight whiteKnight('W');

    // Place the pieces
    board.addPiece(4,0, &whiteKing);
    board.addPiece(7,0, &whiteHRook);
    board.addPiece(0,0, &whiteARook);
    board.addPiece(6,0, &whiteKnight);
    if (display) board.visualiseTextBoard();

    // Attempt castle short
    board.movePiece(4,0, 6,0);
    if (display) board.visualiseTextBoard();

    piece* pieces0[] = {&whiteKing, &whiteARook, &whiteHRook, &whiteKnight};
    int coords0[] = {4,0, 0,0, 7,0, 6,0};
    bool test0 = board.testDriver(pieces0, coords0, 4);

    board.removePiece(6, 0);
    if (display) board.visualiseTextBoard();

    // Castle short
    board.movePiece(4,0, 6,0);
    if (display) board.visualiseTextBoard();

    piece* pieces1[] = {&whiteKing, &whiteARook, &whiteHRook};
    int coords1[] = {6,0, 0,0, 5,0};
    bool test1 = board.testDriver(pieces1, coords1, 3);
    

    // Reset the board
    board.clearBoard();

    // Place the pieces
    board.addPiece(4,0, &whiteKingTwo);
    board.addPiece(7,0, &whiteHRookTwo);
    board.addPiece(0,0, &whiteARookTwo);
    board.addPiece(1,0, &blackKnight);
    if (display) board.visualiseTextBoard();

    // Attempt castle long
    bool test2_extra = !board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();
    board.removePiece(1,0);
    if (display) board.visualiseTextBoard();

    // Castle long
    board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();

    piece* pieces2[] = {&whiteKingTwo, &whiteARookTwo, &whiteHRookTwo};
    int coords2[] = {2,0, 3,0, 7,0};
    bool test2 = board.testDriver(pieces2, coords2, 3);


    // Reset the board
    board.clearBoard();

    // Place the pieces
    board.addPiece(4,0, &whiteKingThree);
    board.addPiece(7,0, &whiteHRookThree);
    board.addPiece(0,0, &whiteARookThree);
    board.addPiece(4,7, &blackRook);
    if (display) board.visualiseTextBoard();

    // Try castling long (out of check) and ensure this failed
    board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();

    piece* pieces3[] = {&whiteKingThree, &whiteARookThree, &whiteHRookThree, &blackRook};
    int coords3[] = {4,0, 0,0, 7,0, 4,7};
    bool test3 = board.testDriver(pieces3, coords3, 4);


    // Move the black rook
    board.movePiece(4,7, 3,7);
    if (display) board.visualiseTextBoard();

    // Try castling long (through check) and ensure this failed
    board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();

    int coords4[] = {4,0, 0,0, 7,0, 3,7};
    bool test4 = board.testDriver(pieces3, coords4, 4);


    // Move the black rook
    board.movePiece(3,7, 2,7);
    if (display) board.visualiseTextBoard();

    // Try castling long (into check) and ensure this failed
    board.movePiece(4,0, 2,0);
    if (display) board.visualiseTextBoard();

    int coords5[] = {4,0, 0,0, 7,0, 2,7};
    bool test5 = board.testDriver(pieces3, coords5, 4);


    if (display) {
        if (test0) {
            cout << "Test passed: King doesn't castle through friendly piece" << endl;
        } else {
            cout << "Test failed: King castled through friendly piece" << endl;
        }

        if (test1) {
            cout << "Test passed: King successfully castled short" << endl;
        } else {
            cout << "Test failed: King did not castle short" << endl;
        }

        if (test2_extra) {
            cout << "Test passed: King doesn't castle through enemy piece" << endl;
        } else {
            cout << "Test failed: King castles through enemy piece" << endl;
        }

        if (test2) {
            cout << "Test passed: King successfully castled long" << endl;
        } else {
            cout << "Test failed: King did not castle long" << endl;
        }

        if (test3) {
            cout << "Test passed: King did not castle out of check" << endl;
        } else {
            cout << "Test failed: King castled out of check" << endl;
        }

        if (test4) {
            cout << "Test passed: King did not castle through check" << endl;
        } else {
            cout << "Test failed: King castled through check" << endl;
        }

        if (test5) {
            cout << "Test passed: King did not castle into check" << endl;
        } else {
            cout << "Test failed: King castled into check" << endl;
        }
    }

    success = test0 && test1 && test2_extra && test2 && test3 && test4 && test5;
    return success;
}

bool kingtest::runTests(bool display) {
    bool success = true;
    success = success && this->movementTest(display);
    success = success && this->castleTest(display);
    return success;
}