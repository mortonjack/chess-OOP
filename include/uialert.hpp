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
        uitext* titleComponent; 
        uitext* subtitleComponent; 
        uibutton* primaryButton;
        uibutton* secondaryButton;
        RectangleShape* alertComponent;

        uialert(Vector2f position, string titleText, string subtitleText, string primaryButtonText, string secondaryButtonText, Color alertColor = Color{ 0x151515FF }, Color buttonColor = Color{ 0x454545FF }, Color fontColor = Color{ 0xF5F5F5FF }) {
            // Alerts are a hard-coded 480x320px size
            alertComponent = new RectangleShape(Vector2f(480,400));
            alertComponent->setPosition(position);
            alertComponent->setFillColor(alertColor);

            // Create text components
            titleComponent = new uitext(Vector2f(position.x, position.y-140), titleText, 58, fontColor);
            subtitleComponent = new uitext(Vector2f(position.x, position.y-85), subtitleText, 25, fontColor);

            // Center text controls
            const sf::FloatRect titleBounds(titleComponent->element.getLocalBounds());
            const sf::FloatRect subtitleBounds(subtitleComponent->element.getLocalBounds());
            const sf::Vector2f box(alertComponent->getSize());

            titleComponent->element.setOrigin((int)((titleBounds.width - box.x) / 2 + titleBounds.left), ((int)(titleBounds.height - box.y) / 2 + titleBounds.top));
            subtitleComponent->element.setOrigin((int)((subtitleBounds.width - box.x) / 2 + subtitleBounds.left), ((int)(subtitleBounds.height - box.y) / 2 + subtitleBounds.top)); 

            // Create button components
            primaryButton = new uibutton(Vector2f(position.x+25, position.y+400-50-70-70), primaryButtonText, Vector2f(430,70));
            secondaryButton = new uibutton(Vector2f(position.x+25, position.y+400-70-25), secondaryButtonText, Vector2f(430,70));    
        }


    // DRAW FUNCTION
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(*alertComponent);
        target.draw(*titleComponent);
        target.draw(*subtitleComponent);
        target.draw(*primaryButton);
        target.draw(*secondaryButton);
    }
};

#endif