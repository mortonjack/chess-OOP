#include <string>
#include "../include/Gameboard.h"


class Game{
    private:
    // Add list of pieces, give the pieces to player classes and then add to board
    Gameboard* gameboard;
    char colorToMove;

    // Convereter between colors
    char color2OpponentColor(char color) { return color == 'W' ? 'B' : 'W'; } 

    public:
    // Constructor
    Game() {
        // Create a new game board
        gameboard = new Gameboard();

        // To start, it is white-to-move
        colorToMove = 'W';
    }
    

    // Attempt to make a move, returning true is the move is successful and false if it is unsuccessful
    bool move(int oldFile, int oldRank, int newFile, int newRank) {
        // If the player not trying to move a piece, return false
        if (gameboard->getPiece(oldFile,oldRank) == nullptr) return false;

        // If the piece being moved does not belong to the player-to-move, return false
        if (gameboard->getPiece(oldFile,oldRank)->getColor() != colorToMove) return false;

        // Attempt to move, applying all rules of the game logic
        bool successfulMove = gameboard->movePiece(oldFile,oldRank, newFile, newRank);

        // If the move is successful...
        if (successfulMove) {
            colorToMove = color2OpponentColor(colorToMove); // Change the player-to-move
        }

        // Return whether the move was successful
        return successfulMove;
    }

    void saveState() {
        /* 
        To be added.
        */
    }

    void loadState() {
        /* 
        To be added.
        */
    }

    char getGameState() {
        // Winning conidtions
        if (gameboard->isInCheckmate(colorToMove))  return 'C';

        // Drawing coniditions
        if (gameboard->isInStalemate(colorToMove)) return 'S';
        if (gameboard->threefoldRepetition())       return '3';
        if (gameboard->fiftyMoveRule())             return '5';

        // Otherwise, the game is not over. Return the null character
        return '0';
    }

    char getColorToMove() {
        return colorToMove;
    }

    char getOppositeColorToMove() {
        return color2OpponentColor(colorToMove);
    }


    // Returns this game's game board
    Gameboard* getBoard() {
        return this->gameboard;
    }

    // Destructor
    ~Game() {
        delete gameboard;
    }

};