#include "basemodule.h"
#include <SFML/Graphics.hpp>

BaseModule::BaseModule(sf::Vector2f newOrigin, float newSide, unsigned int newSerial): origin{newOrigin}, side{newSide}, serial{newSerial} {}

bool BaseModule::isPosInModule(sf::Vector2f pos)
{
    sf::Vector2f end{origin.x + side, origin.y + side};
    if ((pos.x >= origin.x && pos.x <= end.x) && (pos.y >= origin.y && pos.y <= end.y)) {
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
    sf::Vector2f end{origin.x + side, origin.y + side};
    std::array vertices =
        {
        sf::Vertex{{origin.x, origin.y}},
        sf::Vertex{{end.x, origin.y}},
        sf::Vertex{{end.x, end.y}},
        sf::Vertex{{origin.x, end.y}},
        sf::Vertex{{origin.x, origin.y}},
        };

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);
    window->draw(cirvle);
}
