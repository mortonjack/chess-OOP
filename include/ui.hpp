
#include <SFML/Graphics.hpp>

#include "game.hpp"

#include "uiboard.hpp"
#include "uitext.hpp"
#include "uibutton.hpp"
#include "uimovestack.hpp"

#include "gameboard.h"
#include "king.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "pawn.h"
#include "knight.h"

class ui {
    public:
        RenderWindow* window;

        game* userGame;

        uiboard* userBoard;
        
        uitext* whiteText;
        uitext* blackText;
        uitext* matchText;

        uimovestack* movesText;

        uibutton* saveButton;
        uibutton* loadButton;
        uibutton* drawButton;
        uibutton* resignButton;


    ui() {
        userGame = new game();
        setupControls();
        run();
    }

    // Sets up the controls on the UI
    void setupControls() {
        const int PADDING = 25;  // Space between each element

        const int TEXT_HEIGHT = 40; // Height of uitext
        const int BUTTON_HEIGHT = 70; // Height of uibutton

        const int BOARD_LENGTH = 640; // Length of board
        const int BOARD_HEIGHT = 640; // Height of board

        const int WINDOW_LENGTH = 1200; // Length of window
        const int WINDOW_HEIGHT = BOARD_HEIGHT + 4*PADDING + 2*TEXT_HEIGHT; // Height of window

        const int CONTROL_LENGTH = WINDOW_LENGTH - 3*PADDING - BOARD_LENGTH;                    // Length of non-board UI
        const int GUTTER_HEIGHT = 2*PADDING + TEXT_HEIGHT;                                      // Height above/below board
        const int MOVES_HEIGHT = WINDOW_HEIGHT - 4*PADDING - 4*BUTTON_HEIGHT - 2*GUTTER_HEIGHT; // Height of uimovesstack

        const int TOP_TEXT_Y = PADDING - 5;                                 // Y position of white player name
        const int BOTTOM_TEXT_Y = GUTTER_HEIGHT + BOARD_HEIGHT + PADDING;   // Y position of black player name

        const int CONTROL_X = PADDING*2 + BOARD_LENGTH;                     // X position of non-board UI

        const Vector2f BUTTON_DIMENSIONS = Vector2f(CONTROL_LENGTH,BUTTON_HEIGHT); // Dimensions of uibutton


        window = new RenderWindow(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Chess-OOP");

        userBoard = new uiboard(BOARD_LENGTH,BOARD_HEIGHT,Vector2i(PADDING,GUTTER_HEIGHT));

        whiteText = new uitext(Vector2f(PADDING,TOP_TEXT_Y),"White");
        blackText = new uitext(Vector2f(PADDING,BOTTOM_TEXT_Y),"Black");
        matchText = new uitext(Vector2f(CONTROL_X,TOP_TEXT_Y),"White vs. Black");

        movesText = new uimovestack(10, Vector2f(CONTROL_X,GUTTER_HEIGHT));

        saveButton = new uibutton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT),"Save",BUTTON_DIMENSIONS);
        loadButton = new uibutton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*1),"Load",BUTTON_DIMENSIONS);
        drawButton = new uibutton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*2),"Offer Draw",BUTTON_DIMENSIONS);
        resignButton = new uibutton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*3),"Resign",BUTTON_DIMENSIONS);
    }

    // Manages the game's functionality
    void run() {
        king whiteKing('W');
        rook whiteRook('W');
        
        userGame->board->addPiece(0,0, &whiteKing);
        userGame->board->addPiece(7,0, &whiteRook);

        userBoard->loadPieces(userGame->board->board);

        while (window->isOpen())
        {
            // Handle window events
            sf::Event event;
            while (window->pollEvent(event))
            {
                // If we want to close this window, destroy it
                if(event.type == sf::Event::Closed) { window->close(); }

                // Handle the appropriate behavior for clicking a tile
                if (event.type == sf::Event::MouseButtonPressed) {
                    bool makeMove = userBoard->tileClick(event.mouseButton.x, event.mouseButton.y);
                    if(makeMove) {
                        int oldFile = userBoard->getSourceCoords().x;
                        int oldRank = userBoard->getSourceCoords().y;

                        int newFile = userBoard->getTargetCoords().x;
                        int newRank = userBoard->getTargetCoords().y;

                        bool successfulMove = userGame->board->movePiece(oldFile,oldRank, newFile, newRank);
                        
                        if (successfulMove) {
                            userBoard->loadPieces(userGame->board->board);
                            movesText->updateMovesDisplayed(userGame->board);

                            /* Checks for game ending 

                            if (userGame->board->isInCheckmate(game->colorToMove)) { game->displayWin(game->oppositeColor); }
                            if (userGame->board->isInStalemate) { game->displayDraw(); }

                            */
                        }
                    }

                    /* Button commands

                    saveButton->isHovered(event.mouseButton.x, event.mouseButton.y) { game->saveState(); }
                    loadButton->isHovered(event.mouseButton.x, event.mouseButton.y) { game->loadState(); }
                    drawButton->isHovered(event.mouseButton.x, event.mouseButton.y) { game->displayDraw(); }
                    resignButton->isHovered(event.mouseButton.x, event.mouseButton.y) { game->displayWin(game->oppositeColor); }

                    */

                }

                if (event.type == sf::Event::MouseMoved) {
                    saveButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);
                    loadButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);
                    drawButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);
                    resignButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);
                }

            }

            // Draw the UI
            window->clear(Color{ 0x151515FF });
            window->draw(*userBoard);
            window->draw(*whiteText);
            window->draw(*blackText);
            window->draw(*matchText);
            window->draw(*saveButton);
            window->draw(*loadButton);
            window->draw(*drawButton);
            window->draw(*resignButton);
            window->draw(*movesText);
            window->display();
        }
    }
};