#include <string>
// #include "player.h"
#include "../include/Gameboard.h"


class Game{
    public:
        // Add list of pieces, give the pieces to player classes and then add to board
        Gameboard* gameboard;

        char colorToMove = 'W';

    public:
        Game() {
            gameboard = new Gameboard();
        }
        
        //start Game
        void startGame() {} //!! VERY IMPORTANT: make all the pieces
        void resetGame() {} //!! VERY IMPORTANT: use clearBoard(), then call startGame again

        bool move(int oldFile, int oldRank, int newFile, int newRank) {
            if (gameboard->board[oldFile][oldRank] == nullptr) return false;
            if (gameboard->board[oldFile][oldRank]->getColor() != colorToMove) return false;

            bool successfulMove = gameboard->movePiece(oldFile,oldRank, newFile, newRank);

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
        ~Game();

};