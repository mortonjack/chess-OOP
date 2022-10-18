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
        RenderWindow* _window;           // The app's main window

        Game* _game;                     // The app's game logic

        UIBoard* _uiBoard;               // The visual board, and its pieces
        
        UIText* _whiteText;              // Text indicating white's name
        UIText* _blackText;              // Text indicating black's name
        UIText* _matchText;              // Text indicating the matchup between players

        UIMoveStack* _moveStack;         // Text storing the players' past moves

        UIButton* _saveButton;           // The button to save the game
        UIButton* _loadButton;           // The button to load the game
        UIButton* _drawButton;           // The button to offer a draw
        UIButton* _resignButton;         // The button to resign

        UIAlert* _alert;                 // The alert pop-up that appears when the game is over

        bool _drawOffered = false;       // Whether a draw has been offered
        bool _resignOffered = false;     // Whether a resignation has been offered
        bool _isAlertDisplayed = false;  // Whether the alert is displayed

    public:
        // Constructor
        UI() {
            // Create a new instance of the game logic
            _game = new Game();

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

            const int WINDOW_LENGTH = 1200; // Length of _window
            const int WINDOW_HEIGHT = BOARD_HEIGHT + 4*PADDING + 2*TEXT_HEIGHT; // Height of window

            const int CONTROL_LENGTH = WINDOW_LENGTH - 3*PADDING - BOARD_LENGTH;                    // Length of non-board UI
            const int GUTTER_HEIGHT = 2*PADDING + TEXT_HEIGHT;                                      // Height above/below board
            const int MOVES_HEIGHT = WINDOW_HEIGHT - 4*PADDING - 4*BUTTON_HEIGHT - 2*GUTTER_HEIGHT; // Height of the move stack

            const int TOP_TEXT_Y = PADDING - 5;                                 // Y position of white player name
            const int BOTTOM_TEXT_Y = GUTTER_HEIGHT + BOARD_HEIGHT + PADDING;   // Y position of black player name
            const int CONTROL_X = PADDING*2 + BOARD_LENGTH;                     // X position of non-board UI

            const Vector2f BUTTON_DIMENSIONS = Vector2f(CONTROL_LENGTH,BUTTON_HEIGHT); // Dimensions of UIButton

            // Create each control with the desired position, text and dimensions
            _window = new RenderWindow(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Chess-OOP", Style::Close);

            _uiBoard = new UIBoard(BOARD_LENGTH,BOARD_HEIGHT,Vector2i(PADDING,GUTTER_HEIGHT));

            _whiteText = new UIText(Vector2f(PADDING,BOTTOM_TEXT_Y),"White");
            _blackText = new UIText(Vector2f(PADDING,TOP_TEXT_Y),"Black");
            _matchText = new UIText(Vector2f(CONTROL_X,TOP_TEXT_Y),"White vs. Black");

            _moveStack = new UIMoveStack(Vector2f(CONTROL_X,GUTTER_HEIGHT),10);

            _saveButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT),"Save",BUTTON_DIMENSIONS);
            _loadButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*1),"Load",BUTTON_DIMENSIONS);
            _drawButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*2),"Offer Draw",BUTTON_DIMENSIONS);
            _resignButton = new UIButton(Vector2f(CONTROL_X,GUTTER_HEIGHT+PADDING+MOVES_HEIGHT+(BUTTON_HEIGHT+PADDING)*3),"Resign",BUTTON_DIMENSIONS);

            _alert = new UIAlert(Vector2f(PADDING+80,GUTTER_HEIGHT+120), "Play Again", "Quit");

            // Set the app's icon
            Image image = Image();
            image.loadFromFile("./assets/logo.png");
            _window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        }

        // Operates the Game's functionality
        void run() {
            // Setup the UI's controls
            setupControls();

            // Setup the game's logic
            _game->setupBoard();
            _uiBoard->loadPieces(_game->getBoard());

            // While the app is open...
            while (_window->isOpen())
            {
                // Handle _window events
                sf::Event event;
                while (_window->pollEvent(event))
                {
                    // If we want to close this window, destroy it
                    if(event.type == sf::Event::Closed) { _window->close(); }

                    // If we clicked on the window...
                    if (event.type == sf::Event::MouseButtonPressed) {
                        // Store the co-ordinates of the click
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;

                        // If there is currently no active _alert, and the mouse is hovering over the game board...
                        if (_isAlertDisplayed == false && _uiBoard->isHovered(x,y) == true) {
                            // Check if we are making a move (true) or selecting a piece (false)
                            bool makeMove = _uiBoard->tileClick(x,y);

                            // If we are making a move...
                            if(makeMove) {
                                // Find the source/target rank/file of this move
                                int oldFile = _uiBoard->getSourceCoords().x;
                                int oldRank = _uiBoard->getSourceCoords().y;

                                int newFile = _uiBoard->getTargetCoords().x;
                                int newRank = _uiBoard->getTargetCoords().y;

                                // Attempt to make the move, and store whether it is successful
                                bool successfulMove = _game->move(oldFile,oldRank, newFile, newRank);
                                
                                // If this move is valid...
                                if (successfulMove) {
                                    // Reload the board and text storing past moves
                                    _uiBoard->loadPieces(_game->getBoard());
                                    _moveStack->updateMovesDisplayed(_game->getBoard());

                                    // If the game has ended, display an _alert to show this
                                    if (_game->getGameState() != '0') { displayAlert(_game->getGameState(), _game->getOppositeColorToMove()); }

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
            if (!_isAlertDisplayed) {
                
                // Load command
                if (_loadButton->isHovered(x,y)) {
                    // Create a new game
                    delete _game;
                    _game = new Game();
                    // Load state from file
                    _game->loadState();
                    // Refresh display
                    _uiBoard->loadPieces(_game->getBoard());
                    _moveStack->updateAllMoves(_game->getBoard());
                }

                if (_drawButton->isHovered(x,y))   { drawButtonClick(); }    // Draw command
                if (_resignButton->isHovered(x,y)) { displayAlert('R',_game->getOppositeColorToMove()); }  // Resign command
            } else {
                if (_alert->getPrimaryButton()->isHovered(x,y)) { resetControls(); }   // Primary button command (play again) 
                if (_alert->getSecondaryButton()->isHovered(x,y)) { _window->close(); } // Secondary button command (quit)
            }
        }

        // Reset the draw button's state to its default, unclicked value
        void resetButtonStates() {
            _drawButton->setButtonText("Offer Draw");
            _drawOffered = false;
        }

        // If the draw button has is clicked, offer a draw. If it is clicked again, accept the draw
        void drawButtonClick() {
            if (!_drawOffered) {
                _drawButton->setButtonText("Accept Draw");
                _drawOffered = true;
            } else {
                displayAlert('A',_game->getOppositeColorToMove()); 
                resetButtonStates();
            }
        }

        // Is a button currently hovered? If so, invert its colors
        void updateButtonColors(int x, int y) {
            _saveButton->updateButtonColors(x,y);
            _loadButton->updateButtonColors(x,y);
            _drawButton->updateButtonColors(x,y);
            _resignButton->updateButtonColors(x,y);

            _alert->getPrimaryButton()->updateButtonColors(x,y);
            _alert->getSecondaryButton()->updateButtonColors(x,y);
        }

        // Resets the UI: including the gameboard, draw button and past moves display
        void resetControls() {
            delete _game;
            _game = new Game();
            _game->setupBoard();
            _uiBoard->loadPieces(_game->getBoard());
            _moveStack->resetMoveStack();
            resetButtonStates();
            _isAlertDisplayed = false; 
        }

        // Displays the alert control, with its appropriate message, depending on how the game ended
        void displayAlert(char stateCode, char playerColor) {
            switch (stateCode) {
                // If a player is checkmated...
                case 'C':
                    _alert->setTitleText(color2WinnerString(playerColor));
                    _alert->setSubtitleText("By checkmate");
                    break;

                // If a player resigns...
                case 'R':
                    _alert->setTitleText(color2WinnerString(playerColor));
                    _alert->setSubtitleText("By resignation");
                    break;

                // If a player is stalemated...
                case 'S':
                    _alert->setTitleText("Draw");
                    _alert->setSubtitleText("By stalemate");
                    break;

                // If three-fold repetition occurs...
                case '3':
                    _alert->setTitleText("Draw");
                    _alert->setSubtitleText("By threefold repetition");
                    break;

                // If the 50-move rule is invoked...
                case '5':
                    _alert->setTitleText("Draw");
                    _alert->setSubtitleText("By the 50-move rule");
                    break;

                // If the players agree to a draw...
                case 'A':
                    _alert->setTitleText("Draw");
                    _alert->setSubtitleText("By agreement");
                    break;

                // If there is insufficient material to checkmate...
                case 'I':
                    _alert->setTitleText("Draw");
                    _alert->setSubtitleText("By insufficient material");
                    break;
            }

            // Display the UI's alert
            _isAlertDisplayed = true;
        }

        // Converts from a player color into a string, describing who has won
        string color2WinnerString(char color) {
            return color == 'W' ? "White Wins" : "Black Wins";
        }

        // Draws the UIs controls
        void drawControls() {
            // Make the UI a dark grey
            _window->clear(Color{ 0x151515FF });

            // Draw the board
            _window->draw(*_uiBoard);

            // Draw the player names and matchup text
            _window->draw(*_whiteText);
            _window->draw(*_blackText);
            _window->draw(*_matchText);

            // Draw the move-tracking text
            _window->draw(*_moveStack);

            // Draw the buttons
            _window->draw(*_saveButton);
            _window->draw(*_loadButton);
            _window->draw(*_drawButton);
            _window->draw(*_resignButton);

            // If a player has won, display the nessecary _alert
            if (_isAlertDisplayed) _window->draw(*_alert);

            // Update the window
            _window->display();
        }

        // Destructor
        ~UI() {
            delete _window;

            delete _game;

            delete _uiBoard;
            
            delete _whiteText;
            delete _blackText;
            delete _matchText;

            delete _moveStack;

            delete _saveButton;
            delete _loadButton;
            delete _drawButton;
            delete _resignButton;

            delete _alert;
    }
};