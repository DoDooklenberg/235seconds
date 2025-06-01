#ifndef SHIFRMODULE_H
#define SHIFRMODULE_H

#include "basemodule.h"
#include "button.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "label.h"
#include <map>

class ShifrModule : public BaseModule
{
public:
    ShifrModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void process(sf::RenderWindow* window, int time) override;
    void render(sf::RenderWindow* window) override;
private:
    void generateWords();
    bool justPressed = false;
    Button code;
    Button buttons[6], agree;
    sf::SoundBuffer clickBuf;
    sf::Sound click;
    std::string words[12]{"ДОМ", "КОТ", "ПИР", "ЛУК", "СЫТ", "БАК", "ВЕС", "ЖАР", "ГУБ", "ЧАС", "ЩУК", "ФЕН"};
    std::string letters[3][12]{
        {"Щ", "Г", "В", "Ч", "К", "Б", "Ж", "Ф", "П", "Л", "С", "Д"},
        {"У", "А", "Е", "Ы", "О", "И", "А", "У", "Е", "О", "У", "А"},
        {"С", "К", "Б", "Т", "Р", "Н", "М", "К", "Т", "С", "Р", "К"}};
    int currentLet[6]{0, 0, 0, 0, 0, 0}, correctWords[2]{0, 0};
    std::map<std::string, std::string> morseCode{
        {"Щ", ". _ . _ _"},
        {"И", "_ . . _ _"},
        {"Л", ". . . _ _"},
        {"С", "_ _ _ . _"},
        {"Р", ". _ _ . _"},
        {"Б", "_ . _ . _"},
        {"Ж", ". . _ . _"},
        {"Г", "_ _ . . _"},
        {"У", ". _ . . _"},
        {"О", "_ . . . _"},
        {"Ы", ". . . . _"},
        {"В", "_ _ _ _ ."},
        {"Ф", ". _ _ _ ."},
        {"А", "_ . _ _ ."},
        {"М", ". . _ _ ."},
        {"К", "_ _ . _ ."},
        {"Д", ". _ . _ ."},
        {"Е", "_ . . _ ."},
        {"П", ". . . _ ."},
        {"Т", "_ _ _ . ."},
        {"Ч", ". _ _ . ."},
        {"Н", "_ . _ . ."}
    };
};

#endif // SHIFRMODULE_H
