#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "UIText.hpp"

using namespace std;
using namespace sf;

// A button to use in any SFML app
class UIButton : public Drawable, public Transformable
{
    public:
        UIText* textComponent;
        RectangleShape* buttonComponent;

    private:
        Color _standardColor;
        Color _inverseColor;

    public:
    // Constructor. Buttons are black with white text, by default
    UIButton(Vector2f position, string text, Vector2f dimensions, Color buttonColor = Color{ 0x454545FF }, int fontSize = 35, Color fontColor = Color{ 0xF5F5F5FF }) {
        // Setup button colors
        _standardColor = buttonColor;
        _inverseColor = fontColor;

        // Create button component (rectangle)
        buttonComponent = new RectangleShape(dimensions);

        buttonComponent->setPosition(position);
        buttonComponent->setFillColor(buttonColor);

        // Create text component
        textComponent = new UIText(position, text, fontSize, fontColor);

        // Center text in button
        const sf::FloatRect bounds(textComponent->element.getLocalBounds());
        const sf::Vector2f box(buttonComponent->getSize());
        textComponent->element.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
    }

    // Returns whether the button is hovered over
    bool isHovered(int x, int y) {
        return ((x > buttonComponent->getPosition().x && x < buttonComponent->getPosition().x + buttonComponent->getSize().x) && 
                (y > buttonComponent->getPosition().y && y < buttonComponent->getPosition().y + buttonComponent->getSize().y));
    }

    // Updates a button's colors depending on whether it is hovered over
    void updateButtonColors(int x, int y) { 
        bool invert = isHovered(x,y);
        
        // If the button is not hovered, color it in the standard fashion
        if (!invert) {
            buttonComponent->setFillColor(_standardColor);
            textComponent->element.setFillColor(_inverseColor);

        // Otherwise, invert its colors
        } else {
            buttonComponent->setFillColor(_inverseColor);   
            textComponent->element.setFillColor(_standardColor);            
        }
    }

    // Draws the button
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // Apply any transformation
        states.transform *= getTransform();

        // Draw the button
        target.draw(*buttonComponent);
        target.draw(*textComponent);
    }
};

#endif
