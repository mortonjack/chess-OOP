#ifndef PIECE_H
#define PIECE_H

class piece {
    protected:
        int _x;
        int _y;
        bool _captured;
        char _name;
    public:
        void move(int x, int y);
        /*virtual bool checkMoveValidity(int x, int y) = 0; /* checks if this piece 
        can move to this place.Doesn’t check for things like check, 
        another piece in the way, etc. */
        /*virtual bool checkTake(int x, int y) = 0; /* checks if moving would take a 
        piece */
        /*virtual bool checkPathClear(int x, int y) = 0; /* checks if path is clear */
        int getx();
        int gety();
};

#endif//PIECE_H