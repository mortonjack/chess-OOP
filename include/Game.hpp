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
        Gameboard* _gameboard;   // The game's board
        char _colorToMove;       // The color of the player to move
        bool _firstMove;         // Whether it is the first move of the game

    public:
        // Constructor
        Game() { 
            // Create a new game board
            _gameboard = new Gameboard();
            _firstMove = true;
        }

        // Attempt to make a move, returning true is the move is successful and false if it is unsuccessful
        bool move(int oldFile, int oldRank, int newFile, int newRank) {
            // Create a new save state on first move
            if (_firstMove) {
                _gameboard->newSave();
                _firstMove = false;
            }

            // If the player not trying to move a piece, return false
            if (_gameboard->getPiece(oldFile,oldRank) == nullptr) return false;

            // If the piece being moved does not belong to the player-to-move, return false
            if (_gameboard->getPiece(oldFile,oldRank)->getColor() != _colorToMove) return false;

            // Attempt to move, applying all rules of the game logic
            bool successfulMove = _gameboard->movePiece(oldFile,oldRank, newFile, newRank);

            // If the move is successful...
            if (successfulMove) {
                _colorToMove = getOppositeColorToMove(); // Change the player-to-move
                _gameboard->updateSave(); // Update save file
            }

            // Return whether the move was successful
            return successfulMove;
        }

        // Saves the game's state to board.txt and moves.txt
        void saveState() {
            _gameboard->save();
        }

        // Loads the game's state from board.txt and moves.txt
        void loadState() {
            _gameboard->load();
            MoveNode* prevMove = _gameboard->getPrevMove();
            if (prevMove != nullptr) {
                _colorToMove = _gameboard->getPiece(prevMove->getNewFile(), prevMove->getNewRank())->getColor();
                _colorToMove = getOppositeColorToMove();
            } else _colorToMove = 'W';
            _firstMove = true;
        }

        // Return a charcter representing the game's state
        char getGameState() {
            // Winning conidtions
            if (_gameboard->isInCheckmate(_colorToMove))  return 'C';

            // Drawing coniditions
            if (_gameboard->isInStalemate(_colorToMove))  return 'S';
            if (_gameboard->threefoldRepetition())       return '3';
            if (_gameboard->fiftyMoveRule())             return '5';
            if (_gameboard->insufficientMaterial())      return 'I';

            // Otherwise, the game is not over. Return the null character
            return '0';
        }

        // Returns the opposite color to move
        Gameboard* getBoard() {
            return this->_gameboard;
        }

        // Returns the current color-to-move
        char getColorToMove() {
            return _colorToMove;
        }

        // Returns the opposite color to move
        char getOppositeColorToMove() {
            return _colorToMove == 'W' ? 'B' : 'W';
        }

        // Returns this game's game board
        void setupBoard(){
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

        // Destroys the game, going through all past moves to destroy every piece
        ~Game() {
            // Delete pieces
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (_gameboard->getPiece(i, j) != nullptr) {
                        delete _gameboard->getPiece(i, j);
                    }
                }
            }
            // Delete captured/promoted pieces
            MoveNode* node = _gameboard->getPrevMove();
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
            delete _gameboard;
        }

};