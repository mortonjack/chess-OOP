#include <SFML/Graphics.hpp>
#include "../include/uiboard.hpp"
#include "../include/gameboard.h"
#include "../include/king.h"
#include "../include/bishop.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include "../include/pawn.h"
#include "../include/knight.h"

// UI Test
int main()
{
    // Create empty board
    gameboard gameboard;

    // Create a black and white king
    rook whiteARook;
    rook whiteHRook;
    knight whiteBKnight;
    knight whiteGKnight;
    bishop whiteCBishop;
    bishop whiteFBishop;
    queen whiteQueen;
    king whiteKing;

    rook blackARook('B');
    rook blackHRook('B');
    knight blackBKnight('B');
    knight blackGKnight('B');
    bishop blackCBishop('B');
    bishop blackFBishop('B');
    queen blackQueen('B');
    king blackKing('B');


    gameboard.addPiece(0,0,&whiteARook);
    gameboard.addPiece(1,0,&whiteBKnight);
    gameboard.addPiece(2,0,&whiteCBishop);
    gameboard.addPiece(3,0,&whiteQueen);
    gameboard.addPiece(4,0,&whiteKing);
    gameboard.addPiece(5,0,&whiteFBishop);
    gameboard.addPiece(6,0,&whiteGKnight);
    gameboard.addPiece(7,0,&whiteHRook);

    gameboard.addPiece(0,7,&blackARook);
    gameboard.addPiece(1,7,&blackBKnight);
    gameboard.addPiece(2,7,&blackCBishop);
    gameboard.addPiece(3,7,&blackQueen);
    gameboard.addPiece(4,7,&blackKing);
    gameboard.addPiece(5,7,&blackFBishop);
    gameboard.addPiece(6,7,&blackGKnight);
    gameboard.addPiece(7,7,&blackHRook);
    
    // Board dimensions
    const int boardLength = 512;
    const int boardWidth = 512;

    // The length of the window is 5/3 times the length of the board
    const int windowLength = boardLength * 5/3;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(windowLength, boardWidth), "Chess-OOP");

    // Create the chess board and some pieces with radius 20px
    uiboard uiboard(boardLength,boardWidth);
    uiboard.loadPieces(gameboard.board);

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
            // BROKEN if (event.type == sf::Event::MouseButtonPressed) { uiboard.tileClick(event.mouseButton.x, event.mouseButton.y); }
        }

        // Draw the UI
        window.clear();
        window.draw(uiboard);
        window.display();
    }

    return 0;
}