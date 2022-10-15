
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

        UIMoveStack* moveStack;

        UIButton* saveButton;
        UIButton* loadButton;
        UIButton* drawButton;
        UIButton* resignButton;

        UIAlert* alert;

        bool isAlertDisplayed = false;

        bool drawOffered = false;
        bool resignOffered = false;

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

        whiteText = new UIText(Vector2f(PADDING,BOTTOM_TEXT_Y),"White");
        blackText = new UIText(Vector2f(PADDING,TOP_TEXT_Y),"Black");
        matchText = new UIText(Vector2f(CONTROL_X,TOP_TEXT_Y),"White vs. Black");

        moveStack = new UIMoveStack(Vector2f(CONTROL_X,GUTTER_HEIGHT),10);

        saveButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT),"Save",BUTTON_DIMENSIONS);
        loadButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*1),"Load",BUTTON_DIMENSIONS);
        drawButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*2),"Offer Draw",BUTTON_DIMENSIONS);
        resignButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*3),"Resign",BUTTON_DIMENSIONS);

        alert = new UIAlert(Vector2f(PADDING+80,GUTTER_HEIGHT+120), "Play Again", "Quit");

        // Set window icon
        Image image = Image();
        image.loadFromFile("./assets/logo.png");
        window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
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

                // Handle the appropriate behavior for clicking
                if (event.type == sf::Event::MouseButtonPressed) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;

                    // If there is currently no active alert, and the mouse is hovering over the game board...
                    if (isAlertDisplayed == false && uiBoard->isHovered(x,y) == true) {
                        // Check if we are making a move (true) or selecting a piece (false)
                        bool makeMove = uiBoard->tileClick(x,y);

                        // If we are making a move...
                        if(makeMove) {
                            // Find the source/target rank/file of this move
                            int oldFile = uiBoard->getSourceCoords().x;
                            int oldRank = uiBoard->getSourceCoords().y;

                            int newFile = uiBoard->getTargetCoords().x;
                            int newRank = uiBoard->getTargetCoords().y;

                            bool successfulMove = game->move(oldFile,oldRank, newFile, newRank);
                            
                            // If this move is valid...
                            if (successfulMove) {
                                // Reload the board and text stroing past moves
                                uiBoard->loadPieces(game->getBoard());
                                moveStack->updateMovesDisplayed(game->getBoard());

                                // If the game has ended, display an alert to show this
                                if (game->getGameState() != '0') { displayAlert(game->getGameState(), game->getOppositeColorToMove()); }

                                // Reset the draw button, if it was not accepted
                                resetButtonStates();
                            }
                        }
                    }

                    // Listen out for button commands
                    runButtonCommands(x,y);

                }

                // Handle the appropriate behavior for moving the mouse
                if (event.type == sf::Event::MouseMoved) {
                    int x = event.mouseMove.x;
                    int y = event.mouseMove.y;

                    updateButtonColors(x,y);
                }

            }

            drawControls();
        }
    }

    // Is a button currently hovered? If so, we run its command
    void runButtonCommands(int x, int y) {
        if (!isAlertDisplayed) {
            if (loadButton->isHovered(x,y))   { game->loadState(); }                        // Load command
            if (drawButton->isHovered(x,y))   { drawButtonClick(); }                        // Draw command
            if (resignButton->isHovered(x,y)) { resignButtonClick(); } // Resign command
        } else {
            if (alert->primaryButton->isHovered(x,y)) { resetControls(); } // Primary button command (play again) 
            if (alert->secondaryButton->isHovered(x,y)) { window->close(); } // Secondary button command (quit)
        }
    }

    void resetButtonStates() {
        drawButton->setButtonText("Offer Draw");
        resignButton->setButtonText("Resign");
        drawOffered = false;
        resignOffered = false;
    }

    void drawButtonClick() {
        if (!drawOffered) {
            drawButton->setButtonText("Accept Draw");
            drawOffered = true;
        } else {
            displayAlert('A',game->getOppositeColorToMove()); 
            resetButtonStates();
        }
    }

    void resignButtonClick() {
        if (!resignOffered) {
            resignButton->setButtonText("Accept Resignation");
            resignOffered = true;
        } else {
            displayAlert('R',game->getColorToMove()); 
            resetButtonStates();
        }
    }

    // Is a button currently hovered? If so, invert its colors
    void updateButtonColors(int x, int y) {
        saveButton->updateButtonColors(x,y);
        loadButton->updateButtonColors(x,y);
        drawButton->updateButtonColors(x,y);
        resignButton->updateButtonColors(x,y);

        alert->primaryButton->updateButtonColors(x,y);
        alert->secondaryButton->updateButtonColors(x,y);
    }

    // Resets the UI: including the gameboard, material/time advantage/disadvantage and past moves display
    void resetControls() {
        game->setupBoard();
        uiBoard->loadPieces(game->getBoard());
        moveStack->resetMoveStack();
        isAlertDisplayed = false; 
    }


    // Displays the alert control, with its appropriate message
    void displayAlert(char stateCode, char playerColor) {
        switch (stateCode) {
            case 'C':
                alert->setTitleText(color2WinnerString(playerColor));
                alert->setSubtitleText("By checkmate");
                break;

            case 'R':
                alert->setTitleText(color2WinnerString(playerColor));
                alert->setSubtitleText("By resignation");
                break;

            case 'S':
                alert->setTitleText("Draw");
                alert->setSubtitleText("By stalemate");
                break;

            case '3':
                alert->setTitleText("Draw");
                alert->setSubtitleText("By threefold repetition");
                break;

            case '5':
                alert->setTitleText("Draw");
                alert->setSubtitleText("By the 50-move rule");
                break;

            case 'A':
                alert->setTitleText("Draw");
                alert->setSubtitleText("By agreement");
                break;
        }

        isAlertDisplayed = true;
    }

    // Converts from a player color into a string, describing who has won
    string color2WinnerString(char color) {
        return color == 'W' ? "White Wins" : "Black Wins";
    }

    // Draws the UIs controls
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
        window->draw(*moveStack);

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
