#ifndef LEVERMODULE_H
#define LEVERMODULE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "basemodule.h"

class LeverModule : public BaseModule
{
private:
    int localTime; //для возвращения рычага
    void randWin(); // игорок случайно выполняет модуль или нет
    void startPosition(); // задается начальное положение рычага
    bool isPrimeNumber(int num); // проверяет является ли число простым
    int serialSum(); // возвращает сумму цифр серийного номера
    sf::RectangleShape base;
    sf::RectangleShape base2;
    sf::CircleShape circle;
    sf::RectangleShape stick;
    sf::SoundBuffer LeverSoundBuffer;
    sf::Sound LeverFlip;
public:
    LeverModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void process(sf::RenderWindow *window, int time);
    void render(sf::RenderWindow *window);
};

#endif // LEVERMODULE_H
