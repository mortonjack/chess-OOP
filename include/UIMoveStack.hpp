#ifndef UIMOVESTACK_H
#define UIMOVESTACK_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "UIText.hpp"
#include "Gameboard.h"
using namespace sf;
using namespace std;

class UIMoveStack : public Drawable, public Transformable
{
    public:
        UIText* textComponent;

        int moveCapacity;
        int pastMoves = 0;
        vector<string> moveHistory;

        UIMoveStack(int capacity, Vector2f position) {
            textComponent = new UIText(position, "");
            moveCapacity = capacity;
        }

        UIMoveStack(int capacity, Vector2f position, int fontSize, Color fontColor) {
            textComponent = new UIText(position, "", fontSize, fontColor);
            moveCapacity = capacity;
        }

        
    void updateMovesDisplayed(Gameboard* board) {
        MoveNode* move = board->prevMove;

        int file = move->getNewFile();
        int rank = move->getNewRank();
        char pieceType = board->board[file][rank]->getType();

        string moveString = pieceType2String(pieceType) + file2String(file) + rank2String(rank);

        // If our move histroy is overflowing, remove the first element
        if(moveHistory.size() > moveCapacity) {
            moveHistory.erase(moveHistory.begin());
            moveHistory.erase(moveHistory.begin() + 1);
            pastMoves++;
        }
        moveHistory.push_back(moveString);

        textComponent->element.setString("");
        int moveNumber = 1;

        for (int i = 0; i < moveHistory.size(); i += 2) {
            string whiteMove;
            string blackMove;

            if (i == moveHistory.size() - 1) {
                whiteMove = moveHistory[i];
                blackMove = "";
            } else {
                whiteMove = moveHistory[i];
                blackMove = moveHistory[i+1];
            }
            
            string moveString = to_string(moveNumber+pastMoves) + ". " + whiteMove + " " + blackMove + "\n";
            string newString = textComponent->element.getString().toAnsiString() + moveString;
            
            textComponent->element.setString(newString);

            moveNumber++;
        }
    }

    string rank2String(int rank) { return to_string(rank + 1); }

    string file2String(int file) { return string(1,file+97); }

    string pieceType2String(char type) { return (type == 'p') ? "" : string(1,toupper(type)); }


    // DRAW FUNCTION
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(*textComponent);
    }
};

#endif