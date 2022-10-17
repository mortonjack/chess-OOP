#ifndef STATE_H
#define STATE_H

#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "MoveNode.h"
#include <fstream>
#include <string>
using std::fstream;
using std::string;

class State {
    private:
        // Stores a copy of the current board
        Piece* currentBoard[8][8];
        // Stores a pointer to the previous move
        MoveNode* _prevMove;
        // An object to interact with files
        fstream _file;

        // Create a piece based off input string information
        Piece* makePiece(string pieceStr);
        // Create string to store data about a piece
        string storePiece(Piece* piece);

        // Update the copy of the board
        void updateBoard(Piece* board[8][8]);

        // Load currentBoard from file
        void loadCurrentBoard();
        // Load _prevMove from file
        void loadPrevMoves();

        // Save board to file (overwrite save)
        void saveBoard();
        // Save most recent move to file
        void saveMove(MoveNode* node);
        // Save all moves to file (overwrite save)
        void saveAllMoves(MoveNode* node);

    public:
        // Constructors

        // Load information from file
        State();
        // Take information from input
        State(Piece* board[8][8], MoveNode* prevMove);

        // Save to file

        // Overwrite existing save
        void saveState();
        // Update existing save
        void saveState(Piece* board[8][8]);

        // Load currentBoard and _prevMove to input board & node
        void loadGame(Piece* board[8][8], MoveNode** node);
};

#endif//STATE_H