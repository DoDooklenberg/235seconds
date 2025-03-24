#include "basemodule.h"
#include <SFML/Graphics.hpp>

BaseModule::BaseModule(sf::Vector2f newStart, sf::Vector2f newEnd, unsigned int newSerial): start{newStart}, end{newEnd}, serial{newSerial} {}

bool BaseModule::isPosInModule(sf::Vector2f pos)
{
    if ((pos.x >= start.x && pos.x <= end.x) && (pos.y >= start.y && pos.y <= end.y)) {
        return true;
    }
    return false;
}

void BaseModule::process(sf::RenderWindow* window, int time)
{
    cirvle.setFillColor(sf::Color::White);
    if (isPosInModule(sf::Vector2f(sf::Mouse::getPosition(*window)))){
        cirvle.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));
    }
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
    window->draw(cirvle);
}
