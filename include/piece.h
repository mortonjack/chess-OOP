#ifndef PIECE_H
#define PIECE_H

class piece {
    protected:
        int _x;
        int _y;
        bool _captured;
        char _name;
    public:
        piece();
        piece(int x, int y, char name);
        void move(int x, int y);
        //virtual bool checkMoveValidity(int x, int y) = 0;
        //virtual bool checkTake(int x, int y) = 0;
        //virtual bool checkPathClear(int x, int y) = 0; 
        int getx();
        int gety();
        char getName();
};

#endif//PIECE_H