#ifndef UIALERT_H
#define UIALERT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "uitext.hpp"
#include "uibutton.hpp"
#include "gameboard.h"
using namespace sf;
using namespace std;

class uialert : public Drawable, public Transformable
{
    public:
        // Color constants
        uitext* textComponent; 
        uibutton* primaryButton;
        uibutton* secondaryButton;
        RectangleShape* alertComponent;

        uialert(Vector2f position, string message, string primaryButtonText, string secondaryButtonText): uialert(position, message, primaryButtonText, secondaryButtonText, Color{ 0xD50000FF }, Color{ 0x454545FF }, 35, Color{ 0xF5F5F5FF }) {}

        uialert(Vector2f position, string message, string primaryButtonText, string secondaryButtonText, Color alertColor, Color buttonColor, int fontSize, Color fontColor) {
            // Alerts are a hard-coded 480x320px size
            alertComponent = new RectangleShape(Vector2f(480,320));
            alertComponent->setPosition(position);
            alertComponent->setFillColor(alertColor);

            // Create text component
            textComponent = new uitext(position, message, fontSize, fontColor);

            // Center text
            const sf::FloatRect bounds(textComponent->element.getLocalBounds());
            const sf::Vector2f box(alertComponent->getSize());
            textComponent->element.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
        }


    // DRAW FUNCTION
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(*alertComponent);
        target.draw(*textComponent);
    }
};

#endif