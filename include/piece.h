#ifndef PIECE_H
#define PIECE_H

class piece {
    protected:
        bool _captured;
        char _name;
        char _color;
        int _moveCount;
    public:
        piece();
        piece(char name, char color);
        void capture();
        bool captured();
        virtual bool checkMoveValidity(int oldFile, int oldRank, int newFile, int newRank) = 0;
        char getName();
        char getColor();
        void move();
};

#endif//PIECE_H