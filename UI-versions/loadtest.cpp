#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/UIBoard.hpp"
#include "../include/Gameboard.h"
#include "../include/King.h"
#include "../include/Bishop.h"
#include "../include/Rook.h"
#include "../include/Queen.h"
#include "../include/Pawn.h"
#include "../include/Knight.h"

// UI Test
int main()
{
    // Create empty board
    Gameboard sourceBoard;

    // Create a black and white King
    Rook whiteARook;
    Rook whiteHRook;
    Knight whiteBKnight;
    Knight whiteGKnight;
    Bishop whiteCBishop;
    Bishop whiteFBishop;
    Queen whiteQueen;
    King whiteKing;

    Pawn whiteDPawn;
    Pawn whiteEPawn;

    Rook blackARook('B');
    Rook blackHRook('B');
    Knight blackBKnight('B');
    Knight blackGKnight('B');
    Bishop blackCBishop('B');
    Bishop blackFBishop('B');
    Queen blackQueen('B');
    King blackKing('B');

    Pawn blackDPawn('B');
    Pawn blackEPawn('B');

    sourceBoard.addPiece(0,0,&whiteARook);
    sourceBoard.addPiece(1,0,&whiteBKnight);
    sourceBoard.addPiece(2,0,&whiteCBishop);
    sourceBoard.addPiece(3,0,&whiteQueen);
    sourceBoard.addPiece(4,0,&whiteKing);
    sourceBoard.addPiece(5,0,&whiteFBishop);
    sourceBoard.addPiece(6,0,&whiteGKnight);
    sourceBoard.addPiece(7,0,&whiteHRook);

    sourceBoard.addPiece(3,1,&whiteDPawn);
    sourceBoard.addPiece(4,1,&whiteEPawn);

    sourceBoard.addPiece(0,7,&blackARook);
    sourceBoard.addPiece(1,7,&blackBKnight);
    sourceBoard.addPiece(2,7,&blackCBishop);
    sourceBoard.addPiece(3,7,&blackQueen);
    sourceBoard.addPiece(4,7,&blackKing);
    sourceBoard.addPiece(5,7,&blackFBishop);
    sourceBoard.addPiece(6,7,&blackGKnight);
    sourceBoard.addPiece(7,7,&blackHRook);
    
    sourceBoard.addPiece(3,6,&blackDPawn);
    sourceBoard.addPiece(4,6,&blackEPawn);

    // Board dimensions
    const int boardLength = 768;
    const int boardWidth = 768;

    // The length of the window is 5/3 times the length of the board
    const int windowLength = boardLength * 5/3;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(windowLength, boardWidth), "Chess-OOP");

    // Create the chess board and some pieces with radius 20px
    UIBoard UIBoard(boardLength,boardWidth);
 
    UIBoard.loadPieces(sourceBoard.board);

    // Run the main loop
    while (window.isOpen())
    {
        // Handle window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // If we want to close this window, destroy it
            if(event.type == sf::Event::Closed) { window.close(); }

            // Handle the appropriate behavior for clicking a tile
            if (event.type == sf::Event::MouseButtonPressed) {
                if (UIBoard.tileClick(event.mouseButton.x, event.mouseButton.y)) {
                    int oldFile = UIBoard.getSourceCoords().x;
                    int oldRank = UIBoard.getSourceCoords().y;

                    int newFile = UIBoard.getTargetCoords().x;
                    int newRank = UIBoard.getTargetCoords().y;

                    sourceBoard.movePiece(oldFile,oldRank, newFile, newRank);
                    UIBoard.loadPieces(sourceBoard.board);
                }
            }
        }

        // Draw the UI
        window.clear();
        window.draw(UIBoard);
        window.display();
    }

    return 0;
}