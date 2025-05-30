#ifndef WIRESMODULE_H
#define WIRESMODULE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "basemodule.h"
#include "drawwires.h"
#include <SFML/Audio.hpp>


class WiresModule : public BaseModule {
private:
    std::vector<DrawWires> Wires;
    sf::Color getRandomColor();
    void setCorrectWires();
    int correctWireCut = 0;
    void generateWires();
    void setWireColors();
    bool WiresPosCheck(sf::Vector2f pos);
    int amountOfWires;
    sf::SoundBuffer WireSoundBuffer;
    sf::Sound WireCut;
    sf::Texture wireTexture_0_cut, wireTexture_0,
        wireTexture_1_cut, wireTexture_1,
        wireTexture_2_cut, wireTexture_2,
        wireTexture_3_cut, wireTexture_3,
        wireTexture_4_cut, wireTexture_4,
        backPlateTexture, frontPlateTexture;
public:
    int mouseOnWire = 0;
    WiresModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void process(sf::RenderWindow *window, int time);
    void render(sf::RenderWindow *window);
};

#endif // WIRESMODULE_H
