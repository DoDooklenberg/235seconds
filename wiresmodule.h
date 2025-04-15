#ifndef WIRESMODULE_H
#define WIRESMODULE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "basemodule.h"


class WiresModule : public BaseModule {
public:
    WiresModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void process(sf::RenderWindow *window, int time);
    void render(sf::RenderWindow *window);
    bool WiresPosCheck(sf::Vector2f pos);
    bool wireIsCut = 0;
};

#endif // WIRESMODULE_H
