#include <SFML/Graphics.hpp>
#include "../include/UIBoard.hpp"
#include "../include/Gameboard.h"

// UI Test
int main()
{
    // Board dimensions
    const int boardLength = 512;
    const int boardWidth = 512;

    // The length of the window is 5/3 times the length of the board
    const int windowLength = boardLength * 5/3;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(windowLength, boardWidth), "Chess-OOP");

    // Create the chess board and some pieces with radius 20px
    UIBoard board(boardLength,boardWidth);

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
            if (event.type == sf::Event::MouseButtonPressed) { board.tileClick(event.mouseButton.x, event.mouseButton.y); }
        }

        // Draw the UI
        window.clear();
        window.draw(board);
        window.display();
    }

    return 0;
}