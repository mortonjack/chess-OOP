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
        virtual bool checkMoveValidity(int oldRank, int oldFile, int newRank, int newFile) = 0;
        char getName();
};

#endif//PIECE_H