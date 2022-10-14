
#include <SFML/Graphics.hpp>

#include "Game.hpp"

#include "UIBoard.hpp"
#include "UIText.hpp"
#include "UIButton.hpp"
#include "UIMoveStack.hpp"
#include "UIAlert.hpp"

#include "Gameboard.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "Pawn.h"
#include "Knight.h"

class UI {
    private:
        RenderWindow* window;

        Game* game;

        UIBoard* uiBoard;
        
        UIText* whiteText;
        UIText* blackText;
        UIText* matchText;

        UIMoveStack* movesText;

        UIButton* saveButton;
        UIButton* loadButton;
        UIButton* drawButton;
        UIButton* resignButton;

        UIAlert* alert;

        bool isAlertDisplayed = false;

    public:
    UI() {
        game = new Game();
        setupControls();
        run();
    }

    // Sets up the controls on the UI
    void setupControls() {
        const int PADDING = 25;  // Space between each element

        const int TEXT_HEIGHT = 40; // Height of UIText
        const int BUTTON_HEIGHT = 70; // Height of UIButton

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

        const Vector2f BUTTON_DIMENSIONS = Vector2f(CONTROL_LENGTH,BUTTON_HEIGHT); // Dimensions of UIButton


        window = new RenderWindow(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Chess-OOP");

        uiBoard = new UIBoard(BOARD_LENGTH,BOARD_HEIGHT,Vector2i(PADDING,GUTTER_HEIGHT));

        whiteText = new UIText(Vector2f(PADDING,TOP_TEXT_Y),"White");
        blackText = new UIText(Vector2f(PADDING,BOTTOM_TEXT_Y),"Black");
        matchText = new UIText(Vector2f(CONTROL_X,TOP_TEXT_Y),"White vs. Black");

        movesText = new UIMoveStack(Vector2f(CONTROL_X,GUTTER_HEIGHT),10);

        saveButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT),"Save",BUTTON_DIMENSIONS);
        loadButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*1),"Load",BUTTON_DIMENSIONS);
        drawButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*2),"Offer Draw",BUTTON_DIMENSIONS);
        resignButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*3),"Resign",BUTTON_DIMENSIONS);

        alert = new UIAlert(Vector2f(PADDING+80,GUTTER_HEIGHT+120), "White wins!", "By checkmate", "Play Again","Quit");
    }

    // Manages the Game's functionality
    void run() {
        game->setupBoard();
        uiBoard->loadPieces(game->getBoard());

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
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;

                    bool makeMove = uiBoard->tileClick(x,y);
                    if(makeMove) {
                        int oldFile = uiBoard->getSourceCoords().x;
                        int oldRank = uiBoard->getSourceCoords().y;

                        int newFile = uiBoard->getTargetCoords().x;
                        int newRank = uiBoard->getTargetCoords().y;

                        bool successfulMove = game->move(oldFile,oldRank, newFile, newRank);
                        
                        if (successfulMove) {
                            uiBoard->loadPieces(game->getBoard());
                            movesText->updateMovesDisplayed(game->getBoard());
                        }
                    }

                    /* Button commands

                    saveButton->isHovered(event.mouseButton.x, event.mouseButton.y) { Game->saveState(); }
                    loadButton->isHovered(event.mouseButton.x, event.mouseButton.y) { Game->loadState(); }
                    drawButton->isHovered(event.mouseButton.x, event.mouseButton.y) { Game->displayDraw(); }
                    resignButton->isHovered(event.mouseButton.x, event.mouseButton.y) { Game->displayWin(Game->oppositeColor); }

                    */

                   // If the Game alert is displayed...

                }

                if (event.type == sf::Event::MouseMoved) {
                    updateButtonStates(event);
                }

            }

            drawControls();
        }
    }

    void displayWin() {
        
    }

    void updateButtonStates(sf::Event event) {
        saveButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);
        loadButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);
        drawButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);
        resignButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);

        alert->primaryButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);
        alert->secondaryButton->updateButtonColors(event.mouseMove.x, event.mouseMove.y);

        if (isAlertDisplayed) {
            if (alert->secondaryButton->isHovered(event.mouseMove.x,event.mouseMove.y)) { window->close(); }
        }
    }

    void drawControls() {
        // Make the UI a dark grey
        window->clear(Color{ 0x151515FF });

        // Draw the board
        window->draw(*uiBoard);

        // Draw the player names and matchup text
        window->draw(*whiteText);
        window->draw(*blackText);
        window->draw(*matchText);

        // Draw the move-tracking text
        window->draw(*movesText);

        // Draw the buttons
        window->draw(*saveButton);
        window->draw(*loadButton);
        window->draw(*drawButton);
        window->draw(*resignButton);

        // If a player has won, display the nessecary alert
        if (isAlertDisplayed) window->draw(*alert);

        // Update the window
        window->display();
    }
};
