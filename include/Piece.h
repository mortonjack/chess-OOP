#ifndef PIECE_H
#define PIECE_H

class Piece {
    protected:
        // Stores capture status
        bool _captured;

        // Stores piece name based off color and type
        // White pieces are upper-case, black lower-case
        // Used for text displays, and saving/loading
        char _name;

        // Stores piece type
        char _type;

        // Stores piece color
        char _color;

        // Stores move count
        int _moveCount;

    public:
        // Constructor
        Piece(char type, char color);

        // Mark piece as captured
        void capture();
        // Returns true if piece is captured
        bool captured();

        // Returns true if piece could move from
        // oldFile, oldRank to newFile, newRank on an empty borad
        virtual bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) = 0;
        // Returns true if a piece at oldFile, oldRank 
        // could capture a piece at newFile, newRank
        // on an otherwise empty board
        // By default, this is the same as checkMoveValidity
        virtual bool checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank); 

        // Returns info about the piece
        char getName(); // returns _name
        char getType(); // returns _type
        char getColor(); // returns _color
        int getMoveCount(); // returns _moveCount

        // Update info aboout the piece

        // increments _moveCount by 1
        void move(); 

        // If a piece is captured, set it as uncaptured.
        // otherwise, decrement _moveCount by 1
        void reverseMove();

        // Sets _captured to true and _moveCount to 0
        void reset();

        // Swaps the colour of the piece
        void swapColor();

        // Sets the piece move count to input number
        void setMoveCount(int moves);

        // Virtual Destructor
        virtual ~Piece() = default;
};

#endif//PIECE_H