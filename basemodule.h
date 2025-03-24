#ifndef BASEMODULE_H
#define BASEMODULE_H

#include <SFML/Graphics.hpp>

class BaseModule
{
private:
    sf::CircleShape cirvle{10.f};
protected:
    sf::Vector2f start;
    sf::Vector2f end;
    unsigned int serial;
public:
    BaseModule(sf::Vector2f newStart, sf::Vector2f newEnd, unsigned int newSerial);
    bool isPosInModule(sf::Vector2f pos);
    virtual void process(sf::RenderWindow* window, int time);
    virtual void render(sf::RenderWindow* window);
};

#endif // BASEMODULE_H
