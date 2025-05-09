#include "levermodule.h"



LeverModule::LeverModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont) : BaseModule(newOrigin, newSide, newSerial, newFont)
{

}

void LeverModule::process(sf::RenderWindow *window, int time)
{

}

void LeverModule::render(sf::RenderWindow *window)
{
    std::array vertices =
        {
         sf::Vertex{{origin.x, origin.y}},
         sf::Vertex{{origin.x + side, origin.y}},
         sf::Vertex{{origin.x + side, origin.y + side}},
         sf::Vertex{{origin.x, origin.y + side}},
         sf::Vertex{{origin.x, origin.y}},
         };

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);
}
