#ifndef LIGHTBULBSMODULE_H
#define LIGHTBULBSMODULE_H

#include "basemodule.h"
#include <array>

class LightBulbsModule : public BaseModule
{
private:
    sf::CircleShape bulbs[6];
    sf::Color colors[6];
    int activeBulb;
    sf::Clock bulbTimer;
    bool isHolding;
    int holdingBulb;
    sf::Clock holdTimer;
    int sequenceStep;
    int clickCount;
    sf::Clock clickCooldown;
    int solvedCount;

public:
    LightBulbsModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void process(sf::RenderWindow* window, int time) override;
    void render(sf::RenderWindow* window) override;
};

#endif
