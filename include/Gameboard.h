#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Piece.h"
#include "MoveNode.h"
#include "State.h"

class Gameboard {
    private:
        // Stores location of pieces on the gameboard
        // [i][j] position corresponds to [file][rank]
        Piece* board[8][8];

        // Stores node of the previous move. Changes when reversing board.
        MoveNode* prevMove;

        // Stores original node of the previous move.
        MoveNode* originalPrevMove;

        // Stores game state
        State* _save;

        // Checks if a movement is valid on the whole. Handles validity checks.
        bool validMovement(int oldFile, int oldRank, int newFile, int newRank);

        // Checks the path is clear for a piece to move
        bool checkPathClear(int oldFile, int oldRank, int newFile, int newRank);

        // Called from validMovement, checks a move is valid
        bool validMove(int oldFile, int oldRank, int newFile, int newRank);
        // Called from validMovement, checks a capture is valid
        bool validCapture(int oldFile, int oldRank, int newFile, int newRank);

    public:
        // Constructor. Initialises empty board
        Gameboard();

        // Output board to stdout. Displays from whites POV by default.
        void visualiseTextBoard();
        void visualiseTextBoard(char color);

        // Remove a piece from the board
        void removePiece(int file, int rank);
        // Add a piece to the board
        void addPiece(int file, int rank, Piece* newPiece);
        
        // Clears the board of all pieces. Resets move node. Doesn't reset save
        void clearBoard();

        // Handles request to move a piece
        // from [oldFile][oldRank] to [newFile][newRank]
        bool movePiece(int oldFile, int oldRank, int newFile, int newRank);

        // Access piece at position (file, rank)
        Piece* getPiece(int file, int rank);
        // Access linked list of previous moves
        MoveNode* getPrevMove();

        // Change the target Piece to the Pawn targetted with en passant, if applicable
        Piece* targetWithEnPassant(int oldFile, int oldRank, int newFile, int newRank);
        // Same as above, but works with any input board/movenode
        Piece* targetWithEnPassant(int oldFile, int oldRank, int newFile, int newRank, Piece* board[8][8], MoveNode* node);

        // Checks if the player is trying to castle, and checks if the castle is valid
        bool isCastling(int oldFile, int oldRank, int newFile, int newRank);
        // Castles a piece, assuming its valid
        void castle(int oldFile, int newFile, int rank);

        // Replace kingFile and kingRank with King coordinates (if no King is found, returns -1, -1)
        void getKingCoords(char color, int * kingFile, int * kingRank);

        // Check if tile is being threatened by the opposite colour
        bool isThreatened(char color, int file, int rank);
        // Same as above, assumes a piece exists at this file/rank
        bool isThreatened(int file, int rank);

        // Check if input color is in check
        bool isInCheck(char color);
        // Check if input color can't make a legal move
        bool isInMate(char color);
        // Check if input color is in checkmate
        bool isInCheckmate(char color);
        // Check if input color is in stalemate
        bool isInStalemate(char color);

        // Check for draws

        // Check if the same state has occured three times
        bool threefoldRepetition();
        // Check if no piece has been captured or pawn moves in 50 moves
        bool fiftyMoveRule();
        // Check if there aren't enough pieces to checkmate
        bool insufficientMaterial();

        // For drivers: ensure board is set up correctly
        // Input the amount of pieces (length), an array of length of pieces,
        // and an array twice as long storing {file, rank} position in order
        bool testDriver(Piece* pieces[], int* coords, int length); 

        // Save & Load

        // Allocat _save
        void newSave();
        // Delete _save
        void delSave();
        // Overwrite save
        void save();
        // Update save with most recent move
        void updateSave();
        // Load existing save
        bool load();

        // Previous board states

        // Calculate past move amount
        int getMoveCount();
        // Reverse board by input moves
        void reverseBoard(int moves);
        // Unreverse board by input moves
        void unreverseBoard(int moves);

        // Destructor
        ~Gameboard();
};

#endif//GAMEBOARD_H