#include <string>
// #include "player.h"
#include "../include/Gameboard.h"


class Game{
    private:
    // Add list of pieces, give the pieces to player classes and then add to board
    Gameboard* gameboard;
    char colorToMove = 'W';

    // Convereter between colors
    char color2OpponentColor(char color) { return color == 'W' ? 'B' : 'W'; } 

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

    void setupBoard(){
        Pawn whiteAPawn('W');  gameboard.addPiece(0,1,&whiteAPawn);
        Pawn whiteBPawn('W');  gameboard.addPiece(1,1,&whiteBPawn);
        Pawn whiteCPawn('W');  gameboard.addPiece(2,1,&whiteCPawn);
        Pawn whiteDPawn('W');  gameboard.addPiece(3,1,&whiteDPawn);
        Pawn whiteEPawn('W');  gameboard.addPiece(4,1,&whiteEPawn);
        Pawn whiteFPawn('W');  gameboard.addPiece(5,1,&whiteFPawn);
        Pawn whiteGPawn('W');  gameboard.addPiece(6,1,&whiteGPawn);
        Pawn whiteHPawn('W');  gameboard.addPiece(7,1,&whiteHPawn);

        Pawn blackAPawn('B');  gameboard.addPiece(0,6,&blackAPawn);
        Pawn blackBPawn('B');  gameboard.addPiece(1,6,&blackBPawn);
        Pawn blackCPawn('B');  gameboard.addPiece(2,6,&blackCPawn);
        Pawn blackDPawn('B');  gameboard.addPiece(3,6,&blackDPawn);
        Pawn blackEPawn('B');  gameboard.addPiece(4,6,&blackEPawn);
        Pawn blackFPawn('B');  gameboard.addPiece(5,6,&blackFPawn);
        Pawn blackGPawn('B');  gameboard.addPiece(6,6,&blackGPawn);
        Pawn blackHPawn('B');  gameboard.addPiece(7,6,&blackHPawn);

        Rook whiteARook('W');  gameboard.addPiece(0,0,&whiteARook);
        Knight whiteBKnight('W'); gameboard.addPiece(1,0,&whiteBKnight);
        Bishop whiteCBishop('W'); gameboard.addPiece(2,0,&whiteCBishop);
        Queen whiteDQueen('W'); gameboard.addPiece(3,0,&whiteDQueen);
        King whiteEKing('W'); gameboard.addPiece(4,0,&whiteEKing);
        Bishop whiteFBishop('W'); gameboard.addPiece(5,0,&whiteFBishop);
        Knight whiteGKnight('W'); gameboard.addPiece(6,0,&whiteGKnight);
        Rook whiteHRook('W');  gameboard.addPiece(7,0,&whiteHRook);

        Rook blackARook('B');  gameboard.addPiece(0,7,&blackARook);
        Knight blackBKnight('B'); gameboard.addPiece(1,7,&blackBKnight);
        Bishop blackCBishop('B'); gameboard.addPiece(2,7,&blackCBishop);
        Queen blackDQueen('B'); gameboard.addPiece(3,7,&blackDQueen);
        King blackEKing('B'); gameboard.addPiece(4,7,&blackEKing);
        Bishop blackFBishop('B'); gameboard.addPiece(5,7,&blackFBishop);
        Knight blackGKnight('B'); gameboard.addPiece(6,7,&blackGKnight);
        Rook blackHRook('B');  gameboard.addPiece(7,7,&blackHRook);
    }

    Gameboard* getBoard() {
        return this->gameboard;
    }

    ~Game() {
        delete gameboard;
    }

};