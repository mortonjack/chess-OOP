#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Movement Test");

    // create a new vertex
    sf::Vertex vertex;

    // set its position
    vertex.position = sf::Vector2f(100.f, 100.f);

    // set its color
    vertex.color = sf::Color::Red;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.display();
    }

    return 0;
}