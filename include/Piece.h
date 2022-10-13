#ifndef PIECE_H
#define PIECE_H

class Piece {
    protected:
        bool _captured;
        char _name;
        char _type;
        char _color;
        int _moveCount;
    public:
        // Constructor
        Piece(char type, char color);

        // Capture
        void capture();
        bool captured();

        // Validity checks
        virtual bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) = 0;
        virtual bool checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank); 

        // Get info
        char getName();
        char getType();
        char getColor();
        int getMoveCount();

        // Update info
        void move();
        void reverseMove();
        void reset();
        void swapColor();
};

#endif//PIECE_H