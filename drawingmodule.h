#ifndef DRAWINGMODULE_H
#define DRAWINGMODULE_H

#include "basemodule.h"

class DrawingModule : public BaseModule
{
public:
    DrawingModule(sf::Vector2f newOrigin, float newSide, std::string newSerial);
    void process(sf::RenderWindow *window, int time) override;
    void render(sf::RenderWindow *window) override;
};

#endif // DRAWINGMODULE_H
