#ifndef PIECE_H
#define PIECE_H

class piece {
    protected:
        bool _captured;
        char _color;
        char _name;
    public:
        piece();
        piece(char name, char color);
        virtual bool checkMoveValidity(int oldx, int oldy, int newx, int newy) = 0;
        char getName();
};

#endif//PIECE_H