#include <string>
// #include "player.h"
#include "../include/gameboard.h"


class game{
    public:
        // Add list of pieces, give the pieces to player classes and then add to board
        gameboard* board;

        char colorToMove;

    public:
        game() {
            board = new gameboard();

            colorToMove = 'B';
        }
        
        //start game
        void startGame() {} //!! VERY IMPORTANT: make all the pieces
        void resetGame() {} //!! VERY IMPORTANT: use clearBoard(), then call startGame again

        bool move(int oldFile, int oldRank, int newFile, int newRank) {
            if (board->board[oldFile][oldRank] == nullptr) return false;
            if (board->board[oldFile][oldRank]->getColor() != colorToMove) return false;

            bool successfulMove = board->movePiece(oldFile,oldRank, newFile, newRank);

            if (successfulMove) {
                colorToMove = color2OpponentColor(colorToMove);
                return true;
            }
        }

        char color2OpponentColor(char color) { return color == 'W' ? 'B' : 'W'; }

        //who is winner or if draw
        void displayWin(char winnerColor) {}
        void displayDraw() {}

        
        //destructor
        ~game();

};