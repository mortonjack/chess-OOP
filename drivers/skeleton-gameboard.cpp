#include "../include/piece.h"
#include <iostream>
using namespace std;

int main() {
    piece dummyPiece;
    dummyPiece.move(3, 3);
    cout << "X: " << dummyPiece.getx() << "\nY: " << dummyPiece.gety() << endl;
    dummyPiece.move(4, 4);
    cout << "X: " << dummyPiece.getx() << "\nY: " << dummyPiece.gety() << endl;
    return 0;
}