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
public:
    DrawingModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont);
    void genertePoints();
    void process(sf::RenderWindow *window, int time);
    void render(sf::RenderWindow *window);
};

#endif // DRAWINGMODULE_H
