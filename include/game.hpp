#include <string>
// #include "player.h"
#include "../include/gameboard.h"


class game{
    public:
        // Add list of pieces, give the pieces to player classes and then add to board
        gameboard* board;

    public:
        game() {
            board = new gameboard();
        }
        
        //start game
        void startGame() {} //!! VERY IMPORTANT: make all the pieces
        void resetGame() {} //!! VERY IMPORTANT: use clearBoard(), then call startGame again

        //who is winner or if draw
        void displayWin(char winnerColor) {}
        void displayDraw() {}

        
        //destructor
        ~game();

};