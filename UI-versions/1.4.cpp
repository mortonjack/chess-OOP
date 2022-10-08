#include <SFML/Graphics.hpp>
#include "Chessboard.hpp"

// Version 1.3: Recolored Chess board with default parameters
int main()
{
    const int windowLength = 512;
    const int windowWidth = 512;

    // create the window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowWidth), "Chess Board");

    const int boardLength = 8;

    // create the tilemap from the level definition
    Chessboard chessboard;
    if (!chessboard.load(sf::Vector2u(windowLength/boardLength, windowWidth/boardLength))) return -1;

    int ballRank = 6;
    int ballFile = 1;

    int ballRadius = 20;

    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ballRadius,ballRadius);

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
                // up key is pressed: move our character
                ballRank--;
            }
        }

        // draw the map
        window.clear();
        window.draw(chessboard);

        ball.setPosition(chessboard.rankFile2Vector(ballFile,ballRank));
        window.draw(ball);
        window.display();
    }

    return 0;
}