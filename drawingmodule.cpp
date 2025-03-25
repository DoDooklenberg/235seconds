#include "drawingmodule.h"


DrawingModule::DrawingModule(sf::Vector2f newOrigin, float newSide, std::string newSerial): BaseModule(newOrigin, newSide, newSerial){}

void DrawingModule::process(sf::RenderWindow* window, int time) {

}

void DrawingModule::render(sf::RenderWindow *window)
{
    std::array vertices =
        {
         sf::Vertex{{origin.x, origin.y}, sf::Color::Blue},
         sf::Vertex{{origin.x + side, origin.y}, sf::Color::Blue},
         sf::Vertex{{origin.x + side, origin.y + side}, sf::Color::Blue},
         sf::Vertex{{origin.x, origin.y + side}, sf::Color::Blue},
         sf::Vertex{{origin.x, origin.y}, sf::Color::Blue},
         };

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);
}
