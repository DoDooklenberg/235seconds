#ifndef DRAWINGPOINT_H
#define DRAWINGPOINT_H

#include <SFML/Graphics.hpp>

class DrawingPoint
{
private:
    sf::Vector2f position, target{-1.f, -1.f};
    sf::CircleShape point;
    sf::RectangleShape line;
    sf::Font font;
    DrawingPoint* next = NULL;
    float radius;
    int number;
    bool isActive{false};
public:
    DrawingPoint(sf::Vector2f pos, sf::Font newFont, float r, int num);
    sf::Vector2f getPosition();
    void setTarget(sf::Vector2f newTarget);
    void resetTarget();
    void setNext(DrawingPoint* newNext);
    DrawingPoint* getNext();
    bool isPrecursor();
    void render(sf::RenderWindow* window);
};

#endif // DRAWINGPOINT_H
