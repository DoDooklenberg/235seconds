#include "drawingpoint.h"
#include <math.h>
#include <string>

DrawingPoint::DrawingPoint(sf::Font newFont, sf::Vector2f pos, float r, int num): font{newFont}, position{pos}, radius{r}, number{num}, label{font, std::to_string(num), sf::Color::White, 20, pos}
{
    point = sf::CircleShape(r);
    point.setPosition(position - sf::Vector2f{r, r});
    line = sf::RectangleShape({0.f, 0.f});
    line.setPosition(position);
}

sf::Vector2f DrawingPoint::getPosition()
{
    return position;
}

void DrawingPoint::setTarget(sf::Vector2f newTarget)
{
    target = newTarget;
    sf::Vector2f tempVec = target - position;
    if (tempVec.length() > radius) {
        line.setSize({tempVec.length(), 1.f});
        line.setRotation(tempVec.angle());
        isActive = true;
    }
}

void DrawingPoint::resetTarget()
{
    isActive = false;
}

void DrawingPoint::setNext(DrawingPoint *newNext)
{
    next = newNext;
    target = next->getPosition();
    sf::Vector2f tempVec = target - position;
    if (tempVec.length() > radius) {
        line.setSize({tempVec.length(), 1.f});
        line.setRotation(tempVec.angle());
        isActive = true;
    } else {
        line.setSize({0.f, 0.f});
        line.setRotation(tempVec.angle());
        isActive = true;
    }
}

DrawingPoint *DrawingPoint::getNext()
{
    return next;
}

bool DrawingPoint::isPrecursor()
{
    return isActive;
}

void DrawingPoint::render(sf::RenderWindow *window)
{
    window->draw(point);
    label.render(window);
    if (isActive)
    {
        window->draw(line);
    }
}
