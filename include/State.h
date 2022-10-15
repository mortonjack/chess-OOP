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
using std::ofstream;
using std::string;

class State {
    private:
        Piece* currentBoard[8][8];
        MoveNode* _prevMove;
        ofstream _file;

        // Piece Methods
        Piece* makePiece(string pieceStr);
        string storePiece(Piece* piece);
    public:
        // Constructors
        State();
        State(Piece* board[8][8], MoveNode* prevMove);

        // Load from file
        void loadCurrentBoard();
        void loadPrevMoves();

        // Save to file
        void saveState();
        void saveBoard();
        void saveMoves();
};

#endif//STATE_H