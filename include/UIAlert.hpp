#ifndef UIALERT_H
#define UIALERT_H

#include <SFML/Graphics.hpp>
#include <string>

#include "UIText.hpp"
#include "UIButton.hpp"
#include "Gameboard.h"

using namespace sf;
using namespace std;

class UIAlert : public Drawable, public Transformable
{
    private:
        RectangleShape* _alertComponent; // Alert body

        UIText* _titleComponent;         // Title text
        UIText* _subtitleComponent;      // Subtitle text

        // Centers the title and subtitle in the alert
        void centerTextControls() {
            const sf::FloatRect titleBounds(_titleComponent->element.getLocalBounds());
            const sf::FloatRect subtitleBounds(_subtitleComponent->element.getLocalBounds());
            const sf::Vector2f box(_alertComponent->getSize());

            _titleComponent->element.setOrigin((int)((titleBounds.width - box.x) / 2 + titleBounds.left), ((int)(titleBounds.height - box.y) / 2 + titleBounds.top));
            _subtitleComponent->element.setOrigin((int)((subtitleBounds.width - box.x) / 2 + subtitleBounds.left), ((int)(subtitleBounds.height - box.y) / 2 + subtitleBounds.top)); 
        }

        UIButton* primaryButton;        // Left button
        UIButton* secondaryButton;      // Right button

    public:

        // Constructor
        UIAlert(Vector2f position, string primaryButtonText, string secondaryButtonText, string titleText = "", string subtitleText = "",  Color alertColor = Color{ 0x151515FF }, Color buttonColor = Color{ 0x454545FF }, Color fontColor = Color{ 0xF5F5F5FF }) {
            // Alerts are a hard-coded 480x320px size
            _alertComponent = new RectangleShape(Vector2f(480,400));
            _alertComponent->setPosition(position);
            _alertComponent->setFillColor(alertColor);

            // Create text components
            _titleComponent = new UIText(Vector2f(position.x, position.y-140), titleText, 58, fontColor);
            _subtitleComponent = new UIText(Vector2f(position.x, position.y-85), subtitleText, 25, fontColor);

            // Center text controls
            centerTextControls();

            // Create button components
            primaryButton = new UIButton(Vector2f(position.x+25, position.y+400-50-70-70), primaryButtonText, Vector2f(430,70));
            secondaryButton = new UIButton(Vector2f(position.x+25, position.y+400-70-25), secondaryButtonText, Vector2f(430,70));    
        }

        // Access buttons
        UIButton* getPrimaryButton() {
            return primaryButton;
        }
        UIButton* getSecondaryButton() {
            return secondaryButton;
        }

        // Sets the title text to the passed string
        void setTitleText(string text) {
            _titleComponent->element.setString(text);
            centerTextControls();     
        }

        // Sets the subtitle text to the passed string 
        void setSubtitleText(string text) {
            _subtitleComponent->element.setString(text);
            centerTextControls();
        }

        // Draws the control
        virtual void draw(RenderTarget& target, RenderStates states) const {
            // Apply any transformation
            states.transform *= getTransform();

            // Draw the title, subtitle and buttons
            target.draw(*_alertComponent);
            target.draw(*_titleComponent);
            target.draw(*_subtitleComponent);
            target.draw(*primaryButton);
            target.draw(*secondaryButton);
        }

        // Destroys the control and all its dynamically allocated parts
        ~UIAlert() {
            delete _alertComponent;
            delete _titleComponent;
            delete _subtitleComponent;
            delete primaryButton;
            delete secondaryButton;
        }
};

#endif