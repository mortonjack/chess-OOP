#ifndef PIECE_H
#define PIECE_H

class piece {
    protected:
        bool _captured;
        char _name;
        char _color;
    public:
        piece();
        piece(char name, char color);
        void capture();
        bool captured();
        virtual bool checkMoveValidity(int oldRank, int oldFile, int newRank, int newFile) = 0;
        char getName();
};

#endif//PIECE_H