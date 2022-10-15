#ifndef UITEXT_H
#define UITEXT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

class UIText : public Drawable, public Transformable
{
    private:
        Font _font;  // The text's font

    public:
        Text element; // The text element storing the text

        // Default constructor
        UIText(): UIText(Vector2f(0,0), "") {}

        // Constructor
        UIText(Vector2f position, string text, int fontSize = 35, Color fontColor = Color{ 0xF5f5f5FF }) {
            // Load and text font
            _font.loadFromFile("./assets/Pixeloid-Mono.ttf");
            element.setFont(_font);

            // Set color
            element.setFillColor(fontColor);

            // Set text content
            element.setString(text);

            // Set font size;
            element.setCharacterSize(fontSize);

            // Set text position (rounded to the nearest pixel)
            element.setPosition((int)position.x,(int)(position.y));
        }
            
        // Draws the text
        virtual void draw(RenderTarget& target, RenderStates states) const
        {
            // Apply any transformation
            states.transform *= getTransform();

            // Draw the text
            target.draw(element);
        }
};

#endif