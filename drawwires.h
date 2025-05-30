#ifndef DRAWWIRES_H
#define DRAWWIRES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "basemodule.h"

class DrawWires
{
public:
    DrawWires(sf::Vector2f pos_1, sf::Vector2f pos_2, sf::Color color, bool wireIsCut, bool isCorrect);
    sf::Vector2f pos_1;
    sf::Vector2f pos_2;
    sf::Color color;
    bool wireIsCut = 0;
    bool isCorrect = 0;
private:

};

#endif // DRAWWIRES_H
