#ifndef LEVERMODULE_H
#define LEVERMODULE_H

#include <SFML/Graphics.hpp>
#include "basemodule.h"

class LeverModule : public BaseModule
{
private:
    sf::Clock ss;
    int c = 0;
    void randwin(); // игорок случайно выполняет модуль или нет
    void startposition(); // задается начальное положение рычага
    sf::RectangleShape base;
    sf::RectangleShape base2;
    sf::CircleShape circle;
    sf::RectangleShape stick;
public:
    LeverModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void process(sf::RenderWindow *window, int time);
    void render(sf::RenderWindow *window);
};

#endif // LEVERMODULE_H
