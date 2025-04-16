#ifndef DRAWINGMODULE_H
#define DRAWINGMODULE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "basemodule.h"
#include "drawingpoint.h"

class DrawingModule : public BaseModule
{
private:
    std::vector<DrawingPoint> points;
    int currentPoint = 0, amt;
    int numbers_12[12]{4, 9, 1, 8, 2, 11, 6, 12, 3, 5, 7, 10},
        numbers_13[13]{4, 10, 5, 3, 2, 9, 6, 12, 13, 1, 7, 11, 8},
        numbers_14[14]{6, 10, 1, 8, 4, 9, 12, 14, 13, 5, 2, 11, 7, 3};
public:
    DrawingModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void genertePoints();
    bool checkWin();
    void process(sf::RenderWindow *window, int time);
    void render(sf::RenderWindow *window);
};

#endif // DRAWINGMODULE_H
