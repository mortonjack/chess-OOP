#ifndef PIECE_H
#define PIECE_H

class piece {
    protected:
        bool _captured;
        char _name;
        char _type;
        char _color;
        int _moveCount;
    public:
        piece();
        piece(char name, char color);
        void capture();
        bool captured();
        virtual bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) = 0;
        virtual bool checkCaptureValidity(int oldFile, int oldRank, int newFile, int newRank); // A piece's valid captures is the same as their valid moves, by default
        char getName();
        char getType();
        char getColor();
        int getMoveCount();
        void move();
};

#endif//PIECE_H