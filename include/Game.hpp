#include <string>
// #include "player.h"
#include "../include/Gameboard.h"


class Game{
    public:
        // Add list of pieces, give the pieces to player classes and then add to board
        Gameboard* gameboard;

        int moveNumber;
        char colorToMove = 'W';

    public:
        Game() {
            // Create a new game board
            gameboard = new Gameboard();
        }
        
        void startGame() {} //!! VERY IMPORTANT: make all the pieces
        void resetGame() {} //!! VERY IMPORTANT: use clearBoard(), then call startGame again

        // Attempt to make a move, returning true is the move is successful and false if it is unsuccessful
        bool move(int oldFile, int oldRank, int newFile, int newRank) {
            // If the player not trying to move a piece, return false
            if (gameboard->board[oldFile][oldRank] == nullptr) return false;

            // If the piece being moved does not belong to the player-to-move, return false
            if (gameboard->board[oldFile][oldRank]->getColor() != colorToMove) return false;

            // Attempt to move, applying all rules of the game logic
            bool successfulMove = gameboard->movePiece(oldFile,oldRank, newFile, newRank);

            // If the move is successful...
            if (successfulMove) {
                colorToMove = color2OpponentColor(colorToMove); // Change the player-to-move
                if (colorToMove == 'B') moveNumber++;
            }

            // Return whether the move was successful
            return successfulMove;
        }

        char color2OpponentColor(char color) { return color == 'W' ? 'B' : 'W'; }

        //who is winner or if draw
        void displayWin(char winnerColor) {}
        void displayDraw() {}

        
        //destructor
        ~Game();

};