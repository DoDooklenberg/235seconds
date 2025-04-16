#ifndef DRAWINGPOINT_H
#define DRAWINGPOINT_H

#include <SFML/Graphics.hpp>
#include "label.h"

class DrawingPoint
{
private:
    sf::Vector2f position, target{-1.f, -1.f};
    sf::CircleShape point;
    sf::RectangleShape line;
    sf::Font font;
    DrawingPoint* next = NULL;
    float radius;
    int fakeNumber, realNumber;
    bool isActive{false};
    Label label;
public:
    DrawingPoint(sf::Font newFont, sf::Vector2f pos, float r, int real, int fake);
    sf::Vector2f getPosition();
    void setTarget(sf::Vector2f newTarget);
    void resetTarget();
    void setNext(DrawingPoint* newNext);
    DrawingPoint* getNext();
    bool isPrecursor();
    bool isRight();
    void render(sf::RenderWindow* window);
    int getFakeNumder();
    int getRealNumder();
};

#endif // DRAWINGPOINT_H
