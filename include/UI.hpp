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
        RenderWindow* window;           // The app's main window

        Game* game;                     // The app's game logic

        UIBoard* uiBoard;               // The visual board, and its pieces
        
        UIText* whiteText;              // Text indicating white's name
        UIText* blackText;              // Text indicating black's name
        UIText* matchText;              // Text indicating the matchup between players

        UIMoveStack* moveStack;         // Text storing the players' past moves

        UIButton* saveButton;           // The button to save the game
        UIButton* loadButton;           // The button to load the game
        UIButton* drawButton;           // The button to offer a draw
        UIButton* resignButton;         // The button to resign

        UIAlert* alert;                 // The alert pop-up that appears when the game is over

        bool drawOffered = false;       // Whether a draw has been offered
        bool resignOffered = false;     // Whether a resignation has been offered
        bool isAlertDisplayed = false;  // Whether the alert is displayed

    public:
        // Constructor
        UI() {
            // Create a new instance of the game logic
            game = new Game();

            // Set up the game's controls and begin handing its interaction logic
            run();
        }

        // Sets up the controls on the UI
        void setupControls() {
            // Create position constants
            const int PADDING = 25;  // Space between each element

            const int TEXT_HEIGHT = 40; // Height of UIText
            const int BUTTON_HEIGHT = 70; // Height of UIButton

            const int BOARD_LENGTH = 640; // Length of board
            const int BOARD_HEIGHT = 640; // Height of board

            const int WINDOW_LENGTH = 1200; // Length of window
            const int WINDOW_HEIGHT = BOARD_HEIGHT + 4*PADDING + 2*TEXT_HEIGHT; // Height of window

            const int CONTROL_LENGTH = WINDOW_LENGTH - 3*PADDING - BOARD_LENGTH;                    // Length of non-board UI
            const int GUTTER_HEIGHT = 2*PADDING + TEXT_HEIGHT;                                      // Height above/below board
            const int MOVES_HEIGHT = WINDOW_HEIGHT - 4*PADDING - 4*BUTTON_HEIGHT - 2*GUTTER_HEIGHT; // Height of the move stack

            const int TOP_TEXT_Y = PADDING - 5;                                 // Y position of white player name
            const int BOTTOM_TEXT_Y = GUTTER_HEIGHT + BOARD_HEIGHT + PADDING;   // Y position of black player name
            const int CONTROL_X = PADDING*2 + BOARD_LENGTH;                     // X position of non-board UI

            const Vector2f BUTTON_DIMENSIONS = Vector2f(CONTROL_LENGTH,BUTTON_HEIGHT); // Dimensions of UIButton

            // Create each control with the desired position, text and dimensions
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

            // Set the app's icon
            Image image = Image();
            image.loadFromFile("./assets/logo.png");
            window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        }

        // Operates the Game's functionality
        void run() {
            // Setup the UI's controls
            setupControls();

            // Setup the game's logic
            game->setupBoard();
            uiBoard->loadPieces(game->getBoard());

            // While the app is open...
            while (window->isOpen())
            {
                // Handle window events
                sf::Event event;
                while (window->pollEvent(event))
                {
                    // If we want to close this window, destroy it
                    if(event.type == sf::Event::Closed) { window->close(); }

                    // If we clicked on the window...
                    if (event.type == sf::Event::MouseButtonPressed) {
                        // Store the co-ordinates of the click
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

                                // Attempt to make the move, and store whether it is successful
                                bool successfulMove = game->move(oldFile,oldRank, newFile, newRank);
                                
                                // If this move is valid...
                                if (successfulMove) {
                                    // Reload the board and text storing past moves
                                    uiBoard->loadPieces(game->getBoard());
                                    moveStack->updateMovesDisplayed(game->getBoard());

                                    // If the game has ended, display an alert to show this
                                    if (game->getGameState() != '0') { displayAlert(game->getGameState(), game->getOppositeColorToMove()); }

                                    // Reset the draw and resign buttons, since they were not accepted
                                    resetButtonStates();
                                }
                            }
                        }

                        // Listen out for button commands
                        runButtonCommands(x,y);

                    }

                    // If the mouse is moved...
                    if (event.type == sf::Event::MouseMoved) {
                        // Store the co-ordinates of the mouse
                        int x = event.mouseMove.x;
                        int y = event.mouseMove.y;

                        // Handle the roll-over logic
                        updateButtonColors(x,y);
                    }

                }

                // Draw up the controls
                drawControls();
            }
        }

        // Is a button currently hovered? If so, we run its command
        void runButtonCommands(int x, int y) {
            if (!isAlertDisplayed) {
                // Load command
                if (loadButton->isHovered(x,y)) {
                    delete game;
                    game = new Game();
                    game->loadState();
                    uiBoard->loadPieces(game->getBoard());
                    moveStack->updateAllMoves(game->getBoard());
                }
                if (drawButton->isHovered(x,y))   { drawButtonClick(); }    // Draw command
                if (resignButton->isHovered(x,y)) { displayAlert('R',game->getOppositeColorToMove()); }  // Resign command
            } else {
                if (alert->getPrimaryButton()->isHovered(x,y)) { resetControls(); }   // Primary button command (play again) 
                if (alert->getSecondaryButton()->isHovered(x,y)) { window->close(); } // Secondary button command (quit)
            }
        }

        // Reset the draw button's state to its default, unclicked value
        void resetButtonStates() {
            drawButton->setButtonText("Offer Draw");
            drawOffered = false;
        }

        // If the draw button has is clicked, offer a draw. If it is clicked again, accept the draw
        void drawButtonClick() {
            if (!drawOffered) {
                drawButton->setButtonText("Accept Draw");
                drawOffered = true;
            } else {
                displayAlert('A',game->getOppositeColorToMove()); 
                resetButtonStates();
            }
        }

        // Is a button currently hovered? If so, invert its colors
        void updateButtonColors(int x, int y) {
            saveButton->updateButtonColors(x,y);
            loadButton->updateButtonColors(x,y);
            drawButton->updateButtonColors(x,y);
            resignButton->updateButtonColors(x,y);

            alert->getPrimaryButton()->updateButtonColors(x,y);
            alert->getSecondaryButton()->updateButtonColors(x,y);
        }

        // Resets the UI: including the gameboard, draw button and past moves display
        void resetControls() {
            delete game;
            game = new Game();
            game->setupBoard();
            uiBoard->loadPieces(game->getBoard());
            moveStack->resetMoveStack();
            resetButtonStates();
            isAlertDisplayed = false; 
        }

        // Displays the alert control, with its appropriate message, depending on how the game ended
        void displayAlert(char stateCode, char playerColor) {
            switch (stateCode) {
                // If a player is checkmated...
                case 'C':
                    alert->setTitleText(color2WinnerString(playerColor));
                    alert->setSubtitleText("By checkmate");
                    break;

                // If a player resigns...
                case 'R':
                    alert->setTitleText(color2WinnerString(playerColor));
                    alert->setSubtitleText("By resignation");
                    break;

                // If a player is stalemated...
                case 'S':
                    alert->setTitleText("Draw");
                    alert->setSubtitleText("By stalemate");
                    break;

                // If three-fold repetition occurs...
                case '3':
                    alert->setTitleText("Draw");
                    alert->setSubtitleText("By threefold repetition");
                    break;

                // If the 50-move rule is invoked...
                case '5':
                    alert->setTitleText("Draw");
                    alert->setSubtitleText("By the 50-move rule");
                    break;

                // If the players agree to a draw...
                case 'A':
                    alert->setTitleText("Draw");
                    alert->setSubtitleText("By agreement");
                    break;

                // If there is insufficient material to checkmate...
                case 'I':
                    alert->setTitleText("Draw");
                    alert->setSubtitleText("By insufficient material");
                    break;
            }

            // Display the UI's alert
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

        // Destructor
        ~UI() {
        delete window;

        delete game;

        delete uiBoard;
        
        delete whiteText;
        delete blackText;
        delete matchText;

        delete moveStack;

        delete saveButton;
        delete loadButton;
        delete drawButton;
        delete resignButton;

        delete alert;
    }
};