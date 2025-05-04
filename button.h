#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "label.h"

class Button
{
private:
    Label label;
    sf::Shape* shape;
    float gaps;
public:
    Button(Label label, sf::Shape* shape, float newGaps=0.85f);
    Button(Label label, sf::Vector2f pos, sf::Vector2f size, sf::Color color, float newGaps=0.85f);
    void reloadLabel();
    void render(sf::RenderWindow *window);
    bool isPosIn(sf::Vector2f pos);
    sf::Shape* getShape();
    Label* getLabel();
};

#endif // BUTTON_H
