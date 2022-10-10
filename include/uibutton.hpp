#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "uitext.hpp"
using namespace sf;
using namespace std;

class uibutton : public Drawable, public Transformable
{
    public:
        uitext* textComponent;
        RectangleShape buttonComponent;

        uibutton(Vector2f position, string text, Vector2f dimensions): uibutton(position, text, dimensions, Color{ 0x454545FF }, 35, Color{ 0xF2DBB4FF }) {}

        uibutton(Vector2f position, string text, Vector2f dimensions, Color buttonColor, int fontSize, Color fontColor) {
            textComponent = new uitext(position, text, fontSize, fontColor);

            buttonComponent.setSize(dimensions);
            buttonComponent.setFillColor(buttonColor);
            buttonComponent.setPosition(position);

            const sf::FloatRect bounds(textComponent->element.getLocalBounds());
            const sf::Vector2f box(buttonComponent.getSize());
            textComponent->element.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
        }

    // DRAW FUNCTION
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(buttonComponent);
        target.draw(*textComponent);

    }
};

#endif
