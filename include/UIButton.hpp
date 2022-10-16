#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "UIText.hpp"

using namespace std;
using namespace sf;

class UIButton : public Drawable, public Transformable
{
    private:
        Color _standardColor;   // The button's background (body) color
        Color _inverseColor;    // The button's foreground (text) color

        UIText* textComponent;              // The button's text
        RectangleShape* buttonComponent;    // The button's body

    public:
        // Constructor
        UIButton(Vector2f position, string text, Vector2f dimensions, Color buttonColor = Color{ 0x454545FF }, int fontSize = 35, Color fontColor = Color{ 0xF5F5F5FF }) {
            // Setup button colors
            _standardColor = buttonColor;
            _inverseColor = fontColor;

            // Create button body
            buttonComponent = new RectangleShape(dimensions);

            buttonComponent->setPosition(position);
            buttonComponent->setFillColor(buttonColor);

            // Create text component (filled with "Level" to make sure any text is rendered at the same height)
            textComponent = new UIText(position, "Level", fontSize, fontColor);

            // Center text in button
            const sf::FloatRect bounds(textComponent->getElement()->getLocalBounds());
            const sf::Vector2f box(buttonComponent->getSize());
            textComponent->getElement()->setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);

            // Set the button text without modifying its vertical position
            setButtonText(text);
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
                textComponent->getElement()->setFillColor(_inverseColor);

            // Otherwise, invert its colors
            } else {
                buttonComponent->setFillColor(_inverseColor);   
                textComponent->getElement()->setFillColor(_standardColor);         
            }
        }
        
        // Sets the button's text content
        void setButtonText(string text) {
            // Sets the button's text to the passed string
            textComponent->getElement()->setString(text);

            // Center text in button
            const sf::FloatRect bounds(textComponent->getElement()->getLocalBounds());
            const sf::Vector2f box(buttonComponent->getSize());
            textComponent->getElement()->setOrigin((int)((bounds.width - box.x) / 2 + bounds.left), textComponent->getElement()->getOrigin().y);
        }

        // Draws the control
        virtual void draw(RenderTarget& target, RenderStates states) const {
            // Apply any transformation
            states.transform *= getTransform();

            // Draw the button
            target.draw(*buttonComponent);
            target.draw(*textComponent);
        }

        // Destroys the control and all its dynamically-allocated parts
        ~UIButton() {
            delete buttonComponent;
            delete textComponent;
        }
};

#endif
