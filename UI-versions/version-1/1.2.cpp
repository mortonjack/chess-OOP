#include <SFML/Graphics.hpp>
#include "Chessboard.hpp"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(512, 512), "Chess Board");

    // create the tilemap from the level definition
    Chessboard chessboard;
    if (!chessboard.load(sf::Vector2u(64, 64), 8, 8))
        return -1;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();
        window.draw(chessboard);
        window.display();
    }

    return 0;
}