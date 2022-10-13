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

// A stack of chess moves, to be used in the game
class UIMoveStack : public Drawable, public Transformable
{
    public:
        UIText* textComponent;

    private:
        int _moveCapacity;
        int _pastMoves = 0;
        vector<string> _moveHistory;

    public:
    // Constructor
    UIMoveStack(Vector2f position, int capacity, int fontSize = 35, Color fontColor = Color{ 0xF5F5F5FF }) {
        // Create the text for the move stack
        textComponent = new UIText(position, "", fontSize, fontColor);

        // Store the number of moves this stack can hold
        _moveCapacity = capacity;
    }

        
    void updateMovesDisplayed(Gameboard* gameboard) {
        // Get the rank, file and piece type of the most recent move
        MoveNode* move = gameboard->prevMove;

        int file = move->getNewFile();
        int rank = move->getNewRank();
        char pieceType = gameboard->getPiece(file, rank)->getType();

        // Create a string describing the move recent move
        string moveString = pieceType2String(pieceType) + file2String(file) + rank2String(rank);

        // If our move histroy is overflowing, remove the first element
        if(_moveHistory.size() > _moveCapacity) {
            _moveHistory.erase(_moveHistory.begin());
            _moveHistory.erase(_moveHistory.begin() + 1);
            _pastMoves++;
        }

        // Add the most recent move to our move histroy
        _moveHistory.push_back(moveString);

        // Reset text stack and move number counter
        textComponent->element.setString("");
        int moveNumber = 1;

        // For each pair of moves
        for (int i = 0; i < _moveHistory.size(); i += 2) {
            // Determine the move made by white and black, making the black move blank if it has not been made yet
            string whiteMove;
            string blackMove;

            if (i == _moveHistory.size() - 1) {
                whiteMove = _moveHistory[i];
                blackMove = "";
            } else {
                whiteMove = _moveHistory[i];
                blackMove = _moveHistory[i+1];
            }
            
            // Create a string describing the most recent move pair
            string moveString = to_string(moveNumber+_pastMoves) + ". " + whiteMove + " " + blackMove + "\n";
            string newString = textComponent->element.getString().toAnsiString() + moveString;
            
            // Update the move stack string
            textComponent->element.setString(newString);

            // Increment the move number being counted
            moveNumber++;
        }
    }

    private:
    // Converts from a rank's array number to its string value
    string rank2String(int rank) { return to_string(rank + 1); }

    // Converts from a file's string to its string value
    string file2String(int file) { return string(1,file+97); }

    // Converts from a piece's type to its string value
    string pieceType2String(char type) { return (type == 'p') ? "" : string(1,toupper(type)); }

    public:

    // Draws the UI move stack
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(*textComponent);
    }
};

#endif