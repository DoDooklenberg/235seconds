#include "button.h"

void Button::reloadLabel()
{
    float size;
    if ((shape->getGlobalBounds().size.y / shape->getGlobalBounds().size.x) >= (label.getBounds().size.y / label.getBounds().size.x)) {
        size = (gaps * label.getSize() * shape->getGlobalBounds().size.x) / label.getBounds().size.x;
    } else {
        size = (gaps * label.getSize() * shape->getGlobalBounds().size.y) / label.getBounds().size.y;
    }
    label.setSize(size);
    label.setPositionCenter(shape->getGlobalBounds().getCenter());
}

Button::Button(Label label, sf::Shape *shape, float newGaps): label{label}, shape{shape}
{
    if (newGaps < 0.f || newGaps > 1.f) throw std::invalid_argument("Gaps must be in the range from 0 to 1. Переменная gaps может принимать значения только от 0 до 1.)");
    gaps = newGaps;
    reloadLabel();
}

Button::Button(Label label, sf::Vector2f pos, sf::Vector2f size, sf::Color color, float newGaps): label{label}, shape{new sf::RectangleShape{size}}
{
    if (newGaps < 0.f || newGaps > 1.f) throw std::invalid_argument("Gaps must be in the range from 0 to 1. Переменная gaps может принимать значения только от 0 до 1.)");
    gaps = newGaps;
    shape->setPosition(pos);
    shape->setFillColor(color);
    reloadLabel();
}

void Button::render(sf::RenderWindow *window)
{
    window->draw(*shape);
    label.render(window);
}

bool Button::isPosIn(sf::Vector2f pos)
{
    if (shape->getGlobalBounds().position.x <= pos.x &&
        shape->getGlobalBounds().position.x + shape->getGlobalBounds().size.x >= pos.x &&
        shape->getGlobalBounds().position.y <= pos.y &&
        shape->getGlobalBounds().position.y + shape->getGlobalBounds().size.y >= pos.y) {
        return true;
    }
    return false;
}
