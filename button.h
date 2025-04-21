#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "label.h"

class Button
{
private:
    Label label;
    sf::Shape* shape;
    void reloadLabel();
public:
    Button(Label label, sf::Shape* shape);
    Button(Label label, sf::Vector2f pos, sf::Vector2f size, sf::Color color);
    void render(sf::RenderWindow *window);
};

#endif // BUTTON_H
