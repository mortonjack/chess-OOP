#include <string>
#include "../include/Gameboard.h"
#include "../include/Bishop.h"
#include "../include/Rook.h"
#include "../include/Knight.h"
#include "../include/Pawn.h"
#include "../include/King.h"
#include "../include/Queen.h"

class Game{
    private:
    // Add list of pieces, give the pieces to player classes and then add to board
    Gameboard* gameboard;
    char colorToMove;

    // Convereter between colors
    char color2OpponentColor(char color) { return color == 'W' ? 'B' : 'W'; } 

    // Detect first move
    bool firstMove;

    public:
    // Constructor
    Game() { 
        // Create a new game board
        gameboard = new Gameboard();
        firstMove = true;
    }

    // Attempt to make a move, returning true is the move is successful and false if it is unsuccessful
    bool move(int oldFile, int oldRank, int newFile, int newRank) {
        // Create a new save state on first move
        if (firstMove) {
            gameboard->newSave();
            firstMove = false;
        }

        // If the player not trying to move a piece, return false
        if (gameboard->getPiece(oldFile,oldRank) == nullptr) return false;

        // If the piece being moved does not belong to the player-to-move, return false
        if (gameboard->getPiece(oldFile,oldRank)->getColor() != colorToMove) return false;

        // Attempt to move, applying all rules of the game logic
        bool successfulMove = gameboard->movePiece(oldFile,oldRank, newFile, newRank);

        // If the move is successful...
        if (successfulMove) {
            colorToMove = color2OpponentColor(colorToMove); // Change the player-to-move
            gameboard->updateSave(); // Update save file
        }

        // Return whether the move was successful
        return successfulMove;
    }

    void saveState() {
        gameboard->save();
    }

    void loadState() {
        gameboard->load();
        MoveNode* prevMove = gameboard->getPrevMove();
        if (prevMove != nullptr) {
            colorToMove = gameboard->getPiece(prevMove->getNewFile(), prevMove->getNewRank())->getColor();
            colorToMove = color2OpponentColor(colorToMove);
        } else colorToMove = 'W';
        firstMove = true;
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
    void setupBoard(){
        // To start, it is white-to-move
        colorToMove = 'W';

        // Add pieces to the game board
        Pawn* whiteAPawn = new Pawn('W');       gameboard->addPiece(0,1,whiteAPawn);
        Pawn* whiteBPawn = new Pawn('W');       gameboard->addPiece(1,1,whiteBPawn);
        Pawn* whiteCPawn = new Pawn('W');       gameboard->addPiece(2,1,whiteCPawn);
        Pawn* whiteDPawn = new Pawn('W');       gameboard->addPiece(3,1,whiteDPawn);
        Pawn* whiteEPawn = new Pawn('W');       gameboard->addPiece(4,1,whiteEPawn);
        Pawn* whiteFPawn = new Pawn('W');       gameboard->addPiece(5,1,whiteFPawn);
        Pawn* whiteGPawn = new Pawn('W');       gameboard->addPiece(6,1,whiteGPawn);
        Pawn* whiteHPawn = new Pawn('W');       gameboard->addPiece(7,1,whiteHPawn);

        Pawn* blackAPawn = new Pawn('B');       gameboard->addPiece(0,6,blackAPawn);
        Pawn* blackBPawn = new Pawn('B');       gameboard->addPiece(1,6,blackBPawn);
        Pawn* blackCPawn = new Pawn('B');       gameboard->addPiece(2,6,blackCPawn);
        Pawn* blackDPawn = new Pawn('B');       gameboard->addPiece(3,6,blackDPawn);
        Pawn* blackEPawn = new Pawn('B');       gameboard->addPiece(4,6,blackEPawn);
        Pawn* blackFPawn = new Pawn('B');       gameboard->addPiece(5,6,blackFPawn);
        Pawn* blackGPawn = new Pawn('B');       gameboard->addPiece(6,6,blackGPawn);
        Pawn* blackHPawn = new Pawn('B');       gameboard->addPiece(7,6,blackHPawn);

        Rook* whiteARook = new Rook('W');       gameboard->addPiece(0,0,whiteARook);
        Knight* whiteBKnight = new Knight('W'); gameboard->addPiece(1,0,whiteBKnight);
        Bishop* whiteCBishop = new Bishop('W'); gameboard->addPiece(2,0,whiteCBishop);
        Queen* whiteDQueen = new Queen('W');    gameboard->addPiece(3,0,whiteDQueen);
        King* whiteEKing = new King('W');       gameboard->addPiece(4,0,whiteEKing);
        Bishop* whiteFBishop = new Bishop('W'); gameboard->addPiece(5,0,whiteFBishop);
        Knight* whiteGKnight = new Knight('W'); gameboard->addPiece(6,0,whiteGKnight);
        Rook* whiteHRook = new Rook('W');       gameboard->addPiece(7,0,whiteHRook);

        Rook* blackARook = new Rook('B');       gameboard->addPiece(0,7,blackARook);
        Knight* blackBKnight = new Knight('B'); gameboard->addPiece(1,7,blackBKnight);
        Bishop* blackCBishop = new Bishop('B'); gameboard->addPiece(2,7,blackCBishop);
        Queen* blackDQueen = new Queen('B');    gameboard->addPiece(3,7,blackDQueen);
        King* blackEKing = new King('B');       gameboard->addPiece(4,7,blackEKing);
        Bishop* blackFBishop = new Bishop('B'); gameboard->addPiece(5,7,blackFBishop);
        Knight* blackGKnight = new Knight('B'); gameboard->addPiece(6,7,blackGKnight);
        Rook* blackHRook = new Rook('B');       gameboard->addPiece(7,7,blackHRook);
    }

    Gameboard* getBoard() {
        return this->gameboard;
    }

    // Destructor
    ~Game() {
        // Delete pieces
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (gameboard->getPiece(i, j) != nullptr) {
                    delete gameboard->getPiece(i, j);
                }
            }
        }
        // Delete captured/promoted pieces
        MoveNode* node = gameboard->getPrevMove();
        while (node->prev() != nullptr) {
        // Delete captured piece
        if (node->getCapturedPiece() != nullptr) {
            delete node->getCapturedPiece();
        }
        // Delete promoted piece
        if (node->getPromotedPiece() != nullptr) {
            delete node->getPromotedPiece();
        }

        // Next node
        node = node->prev();
    }

        // Delete gameboard
        delete gameboard;
    }

};