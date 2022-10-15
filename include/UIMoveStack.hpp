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
    private:
        int _moveCapacity;              // The number of moves storable in the move stack
        vector<string> _moveHistory;    // The past moves stores in the move stack
        int _pastMoves = 0;             // The number of past moves in the UI stack

        // Converts a gameboard to a string describing its most recent move (in PGN form)
        string gameboard2MoveString(Gameboard* gameboard) {
            // Get the rank, file and piece type of the most recent move
            MoveNode* move = gameboard->getPrevMove();

            // The move string
            string moveString;

            // Derive attibutes of the most recent move
            int oldFile = move->getOldFile();
            int newFile = move->getNewFile();
            int newRank = move->getNewRank();
            char pieceType = gameboard->getPiece(newFile, newRank)->getType();
            pieceType = move->promoted() ? 'p' : pieceType;

            // If a king moved > 1 tile left (we castled short...)
            if (pieceType == 'k' && (newFile - oldFile) > 1) {
                moveString += "O-O";                                        // Append short-castle symbol
            // If a king moved > 1 tile right (we castled) long...
            } else if (pieceType == 'k' && (newFile - oldFile) < -1) {
                moveString += "O-O-O";                                      // Append long-castle symbol
            // Otherwise...
            } else {
                moveString += pieceType2String(pieceType);                  // Append piece type
                if (move->getCapturedPiece() != nullptr) moveString += 'x'; // Append capture symbol (if applicable)
                moveString += file2String(newFile) + rank2String(newRank);  // Append target coordinates
                if (move->promoted()) moveString += "=Q";                   // Append promotion (if appliable)
            }

            if (gameboard->isInMate('W') || gameboard->isInMate('B')) moveString += '#'; // Append mate symbol (if applicable)
            else if (gameboard->isInCheck('W') || gameboard->isInCheck('B')) moveString += '+'; // Otherwise, append check symbol (if applicable)

            return moveString;
        }

        // Converts from a rank's array number to its string value
        string rank2String(int rank) { return to_string(rank + 1); }

        // Converts from a file's string to its string value
        string file2String(int file) { return string(1,file+97); }

        // Converts from a piece's type to its string value
        string pieceType2String(char type) { return (type == 'p') ? "" : string(1,toupper(type)); }
        
    public:
        UIText* textComponent; // The text element of the move stack

        // Constructor
        UIMoveStack(Vector2f position, int capacity, int fontSize = 35, Color fontColor = Color{ 0xF5F5F5FF }) {
            // Create the text for the move stack
            textComponent = new UIText(position, "", fontSize, fontColor);

            // Store the number of moves that stack can hold
            _moveCapacity = capacity;
        }
    
        // Updates the moves displayed with the most recent one
        void updateMovesDisplayed(Gameboard* gameboard) {
            // Get the string describing the most recent move
            string moveString = gameboard2MoveString(gameboard);

            // If our move history is overflowing, remove the first element
            if((int)_moveHistory.size() > _moveCapacity) {
                _moveHistory.erase(_moveHistory.begin());
                _moveHistory.erase(_moveHistory.begin() + 1);
                _pastMoves++;
            }

            // Add the most recent move to our move histroy
            _moveHistory.push_back(moveString);

            // Reset text stack and move number counter
            textComponent->element.setString("");
            int moveNumber = 1;

            // For each pair of moves...
            for (int i = 0; i < (int)_moveHistory.size(); i += 2) {
                // Determine the move made by white and black, making the black move blank if it has not been made yet
                string whiteMove;
                string blackMove;

                if (i == (int)_moveHistory.size() - 1) {
                    whiteMove = _moveHistory[i];
                    blackMove = "";
                } else {
                    whiteMove = _moveHistory[i];
                    blackMove = _moveHistory[i+1];
                }
                
                // Create a string describing the most recent move pair
                string moveString = to_string(moveNumber+_pastMoves) + ". " + whiteMove + " " + blackMove + "\n";
                
                // Append this string to the move stack
                string newString = textComponent->element.getString().toAnsiString() + moveString;
                textComponent->element.setString(newString);

                // Increment the move number being counted
                moveNumber++;
            }
        }

        // Clears and resets the move stack
        void resetMoveStack() {
            textComponent->element.setString("");
            _moveHistory.clear();
            _pastMoves = 0;
        }

        // Draws the control
        virtual void draw(RenderTarget& target, RenderStates states) const {
            // Apply any transformation
            states.transform *= getTransform();

            // Draw the text
            target.draw(*textComponent);
        }

        // Destroys the control and all its dynamically allocated parts
        ~UIMoveStack() {
            delete textComponent;
        }
};

#endif