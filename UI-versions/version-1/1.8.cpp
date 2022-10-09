#include <SFML/Graphics.hpp>
#include "Chessboard.hpp"

// Version 1.3: Recolored Chess board with default parameters
int main()
{
    const int boardLength = 512;
    const int boardWidth = 512;

    const int windowLength = boardLength * 5/3;

    // create the window
    sf::RenderWindow window(sf::VideoMode(windowLength, boardWidth), "Chess Board");

    // create the tilemap from the level definition
    Chessboard chessboard;
    if (!chessboard.loadBoard(sf::Vector2u(boardLength/8, boardWidth/8))) return -1;
    if (!chessboard.loadPieces(20)) return -1;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                chessboard.tileClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        // draw the map
        window.clear();
        window.draw(chessboard);
        window.display();
    }

    return 0;
}