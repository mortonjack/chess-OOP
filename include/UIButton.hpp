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

        UIText* _textComponent;              // The button's text
        RectangleShape* _buttonComponent;    // The button's body

    public:
        // Constructor
        UIButton(Vector2f position, string text, Vector2f dimensions, Color buttonColor = Color{ 0x454545FF }, int fontSize = 35, Color fontColor = Color{ 0xF5F5F5FF }) {
            // Setup button colors
            _standardColor = buttonColor;
            _inverseColor = fontColor;

            // Create button body
            _buttonComponent = new RectangleShape(dimensions);

            _buttonComponent->setPosition(position);
            _buttonComponent->setFillColor(buttonColor);

            // Create text component (filled with "Level" to make sure any text is rendered at the same height)
            _textComponent = new UIText(position, "Level", fontSize, fontColor);

            // Center text in button
            const sf::FloatRect bounds(_textComponent->getElement()->getLocalBounds());
            const sf::Vector2f box(_buttonComponent->getSize());
            _textComponent->getElement()->setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);

            // Set the button text without modifying its vertical position
            setButtonText(text);
        }

        // Returns whether the button is hovered over
        bool isHovered(int x, int y) {
            return ((x > _buttonComponent->getPosition().x && x < _buttonComponent->getPosition().x + _buttonComponent->getSize().x) && 
                    (y > _buttonComponent->getPosition().y && y < _buttonComponent->getPosition().y + _buttonComponent->getSize().y));
        }

        // Updates a button's colors depending on whether it is hovered over
        void updateButtonColors(int x, int y) { 
            bool invert = isHovered(x,y);

            // If the button is not hovered, color it in the standard fashion
            if (!invert) {
                _buttonComponent->setFillColor(_standardColor);
                _textComponent->getElement()->setFillColor(_inverseColor);

            // Otherwise, invert its colors
            } else {
                _buttonComponent->setFillColor(_inverseColor);   
                _textComponent->getElement()->setFillColor(_standardColor);         
            }
        }
        
        // Sets the button's text content
        void setButtonText(string text) {
            // Sets the button's text to the passed string
            _textComponent->getElement()->setString(text);

            // Center text in button
            const sf::FloatRect bounds(_textComponent->getElement()->getLocalBounds());
            const sf::Vector2f box(_buttonComponent->getSize());
            _textComponent->getElement()->setOrigin((int)((bounds.width - box.x) / 2 + bounds.left), _textComponent->getElement()->getOrigin().y);
        }

        // Draws the control
        virtual void draw(RenderTarget& target, RenderStates states) const {
            // Apply any transformation
            states.transform *= getTransform();

            // Draw the button
            target.draw(*_buttonComponent);
            target.draw(*_textComponent);
        }

        // Destroys the control and all its dynamically-allocated parts
        ~UIButton() {
            delete _buttonComponent;
            delete _textComponent;
        }
};

#endif
