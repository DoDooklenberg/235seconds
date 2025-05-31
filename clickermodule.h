#ifndef CLICKERMODULE_H
#define CLICKERMODULE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include "basemodule.h"
#include "label.h"
#include <string>

class ClickerModule : public BaseModule
{
public:
    ClickerModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void process(sf::RenderWindow* window, int time); // Логика модуля
    void render(sf::RenderWindow* window); // Отрисовка модуля
private:
    void setCorrectClickAmount();
    unsigned int correctClickAmount;
    Button mainButton;
    Button confirmButton;
    unsigned int count = 0;
    Label displayCount;
    sf::SoundBuffer clickBuf;
    sf::Sound click;
    bool isMousePressedLastFrame = false;
    bool isMousePressedLastFrame_2 = false;

};

#endif // CLICKERMODULE_H
