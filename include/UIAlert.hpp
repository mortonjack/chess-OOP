#ifndef UIALERT_H
#define UIALERT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "UIText.hpp"
#include "UIButton.hpp"
#include "Gameboard.h"
using namespace sf;
using namespace std;

class UIAlert : public Drawable, public Transformable
{
    private:
        RectangleShape* alertComponent; // Alert body

        UIText* titleComponent;         // Title text
        UIText* subtitleComponent;      // Subtitle text

        // Centers the title and subtitle in the alert
        void centerTextControls() {
            const sf::FloatRect titleBounds(titleComponent->element.getLocalBounds());
            const sf::FloatRect subtitleBounds(subtitleComponent->element.getLocalBounds());
            const sf::Vector2f box(alertComponent->getSize());

            titleComponent->element.setOrigin((int)((titleBounds.width - box.x) / 2 + titleBounds.left), ((int)(titleBounds.height - box.y) / 2 + titleBounds.top));
            subtitleComponent->element.setOrigin((int)((subtitleBounds.width - box.x) / 2 + subtitleBounds.left), ((int)(subtitleBounds.height - box.y) / 2 + subtitleBounds.top)); 
        }

    public:
        UIButton* primaryButton;        // Left button
        UIButton* secondaryButton;      // Right button

        // Constructor
        UIAlert(Vector2f position, string primaryButtonText, string secondaryButtonText, string titleText = "", string subtitleText = "",  Color alertColor = Color{ 0x151515FF }, Color buttonColor = Color{ 0x454545FF }, Color fontColor = Color{ 0xF5F5F5FF }) {
            // Alerts are a hard-coded 480x320px size
            alertComponent = new RectangleShape(Vector2f(480,400));
            alertComponent->setPosition(position);
            alertComponent->setFillColor(alertColor);

            // Create text components
            titleComponent = new UIText(Vector2f(position.x, position.y-140), titleText, 58, fontColor);
            subtitleComponent = new UIText(Vector2f(position.x, position.y-85), subtitleText, 25, fontColor);

            // Center text controls
            centerTextControls();

            // Create button components
            primaryButton = new UIButton(Vector2f(position.x+25, position.y+400-50-70-70), primaryButtonText, Vector2f(430,70));
            secondaryButton = new UIButton(Vector2f(position.x+25, position.y+400-70-25), secondaryButtonText, Vector2f(430,70));    
        }

        // Sets the title text to the passed string
        void setTitleText(string text) {
            titleComponent->element.setString(text);
            centerTextControls();     
        }

        // Sets the subtitle text to the passed string 
        void setSubtitleText(string text) {
            subtitleComponent->element.setString(text);
            centerTextControls();
        }

        // Draws the control
        virtual void draw(RenderTarget& target, RenderStates states) const {
            // Apply any transformation
            states.transform *= getTransform();

            // Draw the title, subtitle and buttons
            target.draw(*alertComponent);
            target.draw(*titleComponent);
            target.draw(*subtitleComponent);
            target.draw(*primaryButton);
            target.draw(*secondaryButton);
        }

        // Destroys the control and all its dynamically allocated parts
        ~UIAlert() {
            delete alertComponent;
            delete titleComponent;
            delete subtitleComponent;
            delete primaryButton;
            delete secondaryButton;
        }
};

#endif