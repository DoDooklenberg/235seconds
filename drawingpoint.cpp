#include "drawingpoint.h"
#include <math.h>

DrawingPoint::DrawingPoint(sf::Vector2f pos, sf::Font newFont, float r, int num): position{pos}, font{newFont}, radius{r}, number{num}
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
    if (isActive)
    {
        window->draw(line);
    }
}
