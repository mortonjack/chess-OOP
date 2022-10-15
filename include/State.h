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
        Piece* currentBoard[8][8];
        MoveNode* _prevMove;
        fstream _file;

        // Piece Methods
        Piece* makePiece(string pieceStr);
        string storePiece(Piece* piece);

        // Update Board
        void updateBoard(Piece* board[8][8]);

        // Load from file
        void loadCurrentBoard();
        void loadPrevMoves();

        // Save to file
        void saveBoard();
        void saveMove(MoveNode* node);
        void saveAllMoves(MoveNode* node);

    public:
        // Constructors
        State();
        State(Piece* board[8][8], MoveNode* prevMove);

        // Save to file
        void saveState();
        void saveState(Piece* board[8][8]);

        // Load 
        void loadGame(Piece* board[8][8], MoveNode** node);
};

#endif//STATE_H