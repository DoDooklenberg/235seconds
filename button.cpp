#include "button.h"

void Button::reloadLabel()
{
    float size;
    if ((shape->getGlobalBounds().size.y / shape->getGlobalBounds().size.x) >= (label.getBounds().size.y / label.getBounds().size.x)) {
        size = (0.85f * label.getSize() * shape->getGlobalBounds().size.x) / label.getBounds().size.x;
    } else {
        size = (0.85f * label.getSize() * shape->getGlobalBounds().size.y) / label.getBounds().size.y;
    }
    label.setSize(size);
    label.setPositionCenter(shape->getGlobalBounds().getCenter());
}

Button::Button(Label label, sf::Shape *shape): label{label}, shape{shape}
{
    reloadLabel();
}

Button::Button(Label label, sf::Vector2f pos, sf::Vector2f size, sf::Color color): label{label}, shape{new sf::RectangleShape{size}}
{
    shape->setPosition(pos);
    shape->setFillColor(color);
    reloadLabel();
}

void Button::render(sf::RenderWindow *window)
{
    window->draw(*shape);
    label.render(window);
}
