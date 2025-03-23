#include "basemodule.h"
#include <SFML/Graphics.hpp>

BaseModule::BaseModule(sf::Vector2f newStart, sf::Vector2f newEnd, unsigned int newSerial): start{newStart}, end{newEnd}, serial{newSerial} {}

void BaseModule::process(int time)
{

}

void BaseModule::render(sf::RenderWindow *window)
{
    std::array vertices =
        {
        sf::Vertex{{start.x, start.y}},
        sf::Vertex{{end.x, start.y}},
        sf::Vertex{{end.x, end.y}},
        sf::Vertex{{start.x, end.y}},
        sf::Vertex{{start.x, start.y}},
        };

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);
}
