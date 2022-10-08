#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Movement Test");
    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                // left key is pressed: move our character
                ball.move(-5,0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                // right key is pressed: move our character
                ball.move(5,0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                // up key is pressed: move our character
                ball.move(0,-5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                // down key is pressed: move our character
                ball.move(0,5);
            }
        }

        window.clear();
        window.draw(ball);
        window.display();
    }

    return 0;
}