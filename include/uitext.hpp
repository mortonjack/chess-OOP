#ifndef UITEXT_H
#define UITEXT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
using namespace sf;
using namespace std;

class uitext : public Drawable, public Transformable
{
    public:
        Text element;
        Font font;
        string text;

        uitext(): uitext(Vector2f(0,0), "") {}

        uitext(Vector2f position, string text, int fontSize = 35, Color fontColor = Color{ 0xF5f5f5FF }) {
            // Load text font
            font.loadFromFile("./assets/Pixeloid-Mono.ttf");

            // Set text font
            element.setFont(font);

            // Set color
            element.setFillColor(fontColor);

            // Set text content
            element.setString(text);

            // Set character size;
            element.setCharacterSize(fontSize);

            // Set text position (rounded to the nearest pixel)
            element.setPosition((int)position.x,(int)(position.y));
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

#endif