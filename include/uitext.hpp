#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

class uitext : public Drawable, public Transformable
{
    public:
        Text element;
        Font font;
        string text;

        uitext(string text, Vector2f position, int fontSize = 25, Color color = Color{ 0xF2DBB4FF }) {
            // Load text font
            font.loadFromFile("./assets/Pixeloid.ttf");

            // Set text font
            element.setFont(font);

            // Set color
            element.setColor(color);

            // Set text content
            element.setString(text);

            // Set character size;
            element.setCharacterSize(fontSize);

            // Set text position
            element.setPosition(position);
        }
        

    // DRAW FUNCTION
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(element);
    }
};