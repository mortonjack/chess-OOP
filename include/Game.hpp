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
        Gameboard* _gameboard;  // The game's board
        char _colorToMove;      // The color of the player-to-move

    public:
        // Empty constructor
        Game() { }

        // Attempt to make a move, returning true is the move is successful and false if it is unsuccessful
        bool move(int oldFile, int oldRank, int newFile, int newRank) {
            // If the player not trying to move a piece, return false
            if (_gameboard->getPiece(oldFile,oldRank) == nullptr) return false;

            // If the piece being moved does not belong to the player-to-move, return false
            if (_gameboard->getPiece(oldFile,oldRank)->getColor() != _colorToMove) return false;

            // Attempt to move, applying all rules of the game logic
            bool successfulMove = _gameboard->movePiece(oldFile,oldRank, newFile, newRank);

            // If the move is successful...
            if (successfulMove) {
                _colorToMove = getOppositeColorToMove(); // Change the player-to-move
            }

            // Return whether the move was successful
            return successfulMove;
        }

        // Creates a new gameboard and sets it up with all of the pieces in the appropraite position
        void setupBoard(){
            // Create a new game board
            _gameboard = new Gameboard();

            // To start, it is white-to-move
            _colorToMove = 'W';

            // Add pieces to the game board
            Pawn* whiteAPawn = new Pawn('W');       _gameboard->addPiece(0,1,whiteAPawn);
            Pawn* whiteBPawn = new Pawn('W');       _gameboard->addPiece(1,1,whiteBPawn);
            Pawn* whiteCPawn = new Pawn('W');       _gameboard->addPiece(2,1,whiteCPawn);
            Pawn* whiteDPawn = new Pawn('W');       _gameboard->addPiece(3,1,whiteDPawn);
            Pawn* whiteEPawn = new Pawn('W');       _gameboard->addPiece(4,1,whiteEPawn);
            Pawn* whiteFPawn = new Pawn('W');       _gameboard->addPiece(5,1,whiteFPawn);
            Pawn* whiteGPawn = new Pawn('W');       _gameboard->addPiece(6,1,whiteGPawn);
            Pawn* whiteHPawn = new Pawn('W');       _gameboard->addPiece(7,1,whiteHPawn);

            Pawn* blackAPawn = new Pawn('B');       _gameboard->addPiece(0,6,blackAPawn);
            Pawn* blackBPawn = new Pawn('B');       _gameboard->addPiece(1,6,blackBPawn);
            Pawn* blackCPawn = new Pawn('B');       _gameboard->addPiece(2,6,blackCPawn);
            Pawn* blackDPawn = new Pawn('B');       _gameboard->addPiece(3,6,blackDPawn);
            Pawn* blackEPawn = new Pawn('B');       _gameboard->addPiece(4,6,blackEPawn);
            Pawn* blackFPawn = new Pawn('B');       _gameboard->addPiece(5,6,blackFPawn);
            Pawn* blackGPawn = new Pawn('B');       _gameboard->addPiece(6,6,blackGPawn);
            Pawn* blackHPawn = new Pawn('B');       _gameboard->addPiece(7,6,blackHPawn);

            Rook* whiteARook = new Rook('W');       _gameboard->addPiece(0,0,whiteARook);
            Knight* whiteBKnight = new Knight('W'); _gameboard->addPiece(1,0,whiteBKnight);
            Bishop* whiteCBishop = new Bishop('W'); _gameboard->addPiece(2,0,whiteCBishop);
            Queen* whiteDQueen = new Queen('W');    _gameboard->addPiece(3,0,whiteDQueen);
            King* whiteEKing = new King('W');       _gameboard->addPiece(4,0,whiteEKing);
            Bishop* whiteFBishop = new Bishop('W'); _gameboard->addPiece(5,0,whiteFBishop);
            Knight* whiteGKnight = new Knight('W'); _gameboard->addPiece(6,0,whiteGKnight);
            Rook* whiteHRook = new Rook('W');       _gameboard->addPiece(7,0,whiteHRook);

            Rook* blackARook = new Rook('B');       _gameboard->addPiece(0,7,blackARook);
            Knight* blackBKnight = new Knight('B'); _gameboard->addPiece(1,7,blackBKnight);
            Bishop* blackCBishop = new Bishop('B'); _gameboard->addPiece(2,7,blackCBishop);
            Queen* blackDQueen = new Queen('B');    _gameboard->addPiece(3,7,blackDQueen);
            King* blackEKing = new King('B');       _gameboard->addPiece(4,7,blackEKing);
            Bishop* blackFBishop = new Bishop('B'); _gameboard->addPiece(5,7,blackFBishop);
            Knight* blackGKnight = new Knight('B'); _gameboard->addPiece(6,7,blackGKnight);
            Rook* blackHRook = new Rook('B');       _gameboard->addPiece(7,7,blackHRook);
        }

        // Loads the game from its most recent state
        void loadState() {
            /* 
            To be added.
            */
        }

        // Returns this game's board
        Gameboard* getBoard() { return this->_gameboard; }

        // Returns a code indicating whehter the game has ended, and how this has occured
        char getGameState() {
            // Winning conidtions
            if (_gameboard->isInCheckmate(_colorToMove))  return 'C';

            // Drawing coniditions
            if (_gameboard->isInStalemate(_colorToMove)) return 'S';
            if (_gameboard->threefoldRepetition())       return '3';
            if (_gameboard->fiftyMoveRule())             return '5';

            // Otherwise, the game is not over. Return zero.
            return '0';
        }

        // Returns the color of the player-to-move
        char getColorToMove() { return _colorToMove; }

        // Returns the color of theplayer that isn't-to-move
        char getOppositeColorToMove() { return _colorToMove == 'W' ? 'B' : 'W'; }

        // Destructor
        ~Game() {
            delete _gameboard;
        }
};