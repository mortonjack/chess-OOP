
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/UIBoard.hpp"
#include "../include/UIText.hpp"
#include "../include/UIButton.hpp"
#include "../include/UIMoveStack.hpp"
#include "../include/Gameboard.h"
#include "../include/King.h"
#include "../include/Bishop.h"
#include "../include/Rook.h"
#include "../include/Queen.h"
#include "../include/Pawn.h"
#include "../include/Knight.h"

using namespace sf;

// UI Test
int main()
{
    // Create empty board
    Gameboard sourceBoard;

    // GAME BOARD SETUP

    // Create a black and white King
    Rook whiteARook('W');
    Rook whiteHRook('W');
    Knight whiteBKnight('W');
    Knight whiteGKnight('W');
    Bishop whiteCBishop('W');
    Bishop whiteFBishop('W');
    Queen whiteQueen('W');
    King whiteKing('W');

    Pawn whiteDPawn('W');
    Pawn whiteEPawn('W');

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

    // UI CONSTANTS

    // Core Constants
    const int PADDING = 25;

    const int TEXT_HEIGHT = 40;
    const int BUTTON_HEIGHT = 70;

    // Board dimensions
    const int BOARD_LENGTH = 640;
    const int BOARD_HEIGHT = 640;

    // Window dimensions
    const int WINDOW_LENGTH = 1200;
    const int WINDOW_HEIGHT = BOARD_HEIGHT + 4*PADDING + 2*TEXT_HEIGHT;

    // Space next to board
    const int CONTROL_LENGTH = WINDOW_LENGTH - 3*PADDING - BOARD_LENGTH;

    // Space above / below board
    const int GUTTER_HEIGHT = 2*PADDING + TEXT_HEIGHT;

    // Remaining space in the control panel after the buttons are made
    const int MOVES_HEIGHT = WINDOW_HEIGHT - 4*PADDING - 4*BUTTON_HEIGHT - 2*GUTTER_HEIGHT;

    // Recurring positons
    const int TOP_TEXT_Y = PADDING - 5;
    const int BOTTOM_TEXT_Y = GUTTER_HEIGHT + BOARD_HEIGHT + PADDING;

    const int CONTROL_X = PADDING*2 + BOARD_LENGTH;

    const Vector2f BUTTON_DIMENSIONS = Vector2f(CONTROL_LENGTH,BUTTON_HEIGHT);


    // UI ELEMENTS

    // Create the window
    RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Chess-OOP");

    // Create the chess board and some pieces with radius 20px
    UIBoard UIBoard(BOARD_LENGTH,BOARD_HEIGHT,Vector2i(PADDING,GUTTER_HEIGHT));

    UIText whiteName(Vector2f(PADDING,TOP_TEXT_Y),"White");
    UIText blackName(Vector2f(PADDING,BOTTOM_TEXT_Y),"Black");

    UIText matchTitle(Vector2f(CONTROL_X,TOP_TEXT_Y),"White vs. Black");

    UIMoveStack movesText(10, Vector2f(CONTROL_X,GUTTER_HEIGHT));

    UIButton saveButton  (Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT),"Save",BUTTON_DIMENSIONS);
    UIButton loadButton  (Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*1),"Load",BUTTON_DIMENSIONS);
    UIButton drawButton  (Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*2),"Offer Draw",BUTTON_DIMENSIONS);
    UIButton resignButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*3),"Resign",BUTTON_DIMENSIONS);

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

                    movesText.updateMovesDisplayed(&sourceBoard);

                    if (saveButton.isHovered(event.mouseButton.x, event.mouseButton.y)) {} // Execute save function }
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                saveButton.updateButtonColors(event.mouseMove.x, event.mouseMove.y);
                loadButton.updateButtonColors(event.mouseMove.x, event.mouseMove.y);
                drawButton.updateButtonColors(event.mouseMove.x, event.mouseMove.y);
                resignButton.updateButtonColors(event.mouseMove.x, event.mouseMove.y);
            }

        }

        // Draw the UI
        window.clear(Color{ 0x151515FF });
        window.draw(UIBoard);
        window.draw(whiteName);
        window.draw(blackName);
        window.draw(matchTitle);
        window.draw(saveButton);
        window.draw(loadButton);
        window.draw(drawButton);
        window.draw(resignButton);
        window.draw(movesText);
        window.display();
    }

    return 0;
}