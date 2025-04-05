#ifndef CLICKERMODULE_H
#define CLICKERMODULE_H

#include <SFML/Graphics.hpp>
#include "basemodule.h"


class ClickerModule : public BaseModule
{
public:
    ClickerModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
};

#endif // CLICKERMODULE_H
