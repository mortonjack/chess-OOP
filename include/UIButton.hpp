#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "UIText.hpp"
using namespace sf;
using namespace std;

class UIButton : public Drawable, public Transformable
{
    public:
        UIText* textComponent;
        RectangleShape* buttonComponent;

        Color standardColor;
        Color inverseColor;

        UIButton(Vector2f position, string text, Vector2f dimensions, Color buttonColor = Color{ 0x454545FF }, int fontSize = 35, Color fontColor = Color{ 0xF5F5F5FF }) {
            // Setup colors
            standardColor = buttonColor;
            inverseColor = fontColor;

            // Create button component
            buttonComponent = new RectangleShape(dimensions);

            buttonComponent->setPosition(position);
            buttonComponent->setFillColor(buttonColor);

            // Create text component
            textComponent = new UIText(position, text, fontSize, fontColor);

            // Center text
            const sf::FloatRect bounds(textComponent->element.getLocalBounds());
            const sf::Vector2f box(buttonComponent->getSize());
            textComponent->element.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
        }

        // Retursn whether the button is hovered over
        bool isHovered(int x, int y) {
            bool hovered = ((x > buttonComponent->getPosition().x && x < buttonComponent->getPosition().x + buttonComponent->getSize().x) && (y > buttonComponent->getPosition().y && y < buttonComponent->getPosition().y + buttonComponent->getSize().y));
            return hovered;
        }

        void updateButtonColors(int x, int y) { 
            bool invert = isHovered(x,y);
            
            if (!invert) {
                buttonComponent->setFillColor(standardColor);
                textComponent->element.setFillColor(inverseColor);
            } else {
                buttonComponent->setFillColor(inverseColor);   
                textComponent->element.setFillColor(standardColor);            
            }
        }

    // DRAW FUNCTION
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(*buttonComponent);
        target.draw(*textComponent);

    }
};

#endif
