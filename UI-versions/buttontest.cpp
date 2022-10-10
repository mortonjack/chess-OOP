#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/uiboard.hpp"
#include "../include/gameboard.h"
#include "../include/king.h"
#include "../include/bishop.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include "../include/pawn.h"
#include "../include/knight.h"

using namespace sf;

// UI Test
int main()
{
    // Create empty board
    gameboard sourceBoard;

    // Create a black and white king
    rook whiteARook;
    rook whiteHRook;
    knight whiteBKnight;
    knight whiteGKnight;
    bishop whiteCBishop;
    bishop whiteFBishop;
    queen whiteQueen;
    king whiteKing;

    pawn whiteDPawn;
    pawn whiteEPawn;

    rook blackARook('B');
    rook blackHRook('B');
    knight blackBKnight('B');
    knight blackGKnight('B');
    bishop blackCBishop('B');
    bishop blackFBishop('B');
    queen blackQueen('B');
    king blackKing('B');

    pawn blackDPawn('B');
    pawn blackEPawn('B');

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
    const int boardLength = 640;
    const int boardHeight = 640;

    // Window dimentions
    const int windowLength = 1200;
    const int windowHeight = 900;
    
    const int gutterSpace = (windowHeight - boardHeight)/2;
    const int padding = 20;

    // UI dimentions
    const int uiLength = windowLength - boardLength - padding*2;



    // Create the window
    RenderWindow window(sf::VideoMode(windowLength, windowHeight), "Chess-OOP");

    // Create the chess board and some pieces with radius 20px
    uiboard uiboard(boardLength,boardHeight,Vector2i(padding,gutterSpace));

    sf::Text text;

    sf::Font font;
    if (!font.loadFromFile("./assets/Roboto-Black.ttf")) { return -1; }

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("White");


    // set the string to display
    text.setPosition(Vector2f(padding,gutterSpace/2 - padding));


    // set the character size
    text.setCharacterSize(60); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    uiboard.loadPieces(sourceBoard.board);

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
                if (uiboard.tileClick(event.mouseButton.x, event.mouseButton.y)) {
                    int oldFile = uiboard.getSourceCoords().x;
                    int oldRank = uiboard.getSourceCoords().y;

                    int newFile = uiboard.getTargetCoords().x;
                    int newRank = uiboard.getTargetCoords().y;

                    sourceBoard.movePiece(oldFile,oldRank, newFile, newRank);
                    uiboard.loadPieces(sourceBoard.board);
                }
            }
        }

        // Draw the UI
        window.clear();
        window.draw(uiboard);
        window.draw(text);
        window.display();
    }

    return 0;
}