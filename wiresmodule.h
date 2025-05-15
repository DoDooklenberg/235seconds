#ifndef WIRESMODULE_H
#define WIRESMODULE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "basemodule.h"
#include "drawwires.h"


class WiresModule : public BaseModule {
private:
    std::vector<DrawWires> Wires;
public:
    int mouseOnWire = 0;
    WiresModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void generateWires();
    void setWireColors();
    void process(sf::RenderWindow *window, int time);
    void render(sf::RenderWindow *window);
    bool WiresPosCheck(sf::Vector2f pos);
    int amountOfWires;


};

#endif // WIRESMODULE_H
