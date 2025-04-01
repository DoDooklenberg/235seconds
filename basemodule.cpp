#include "basemodule.h"

BaseModule::BaseModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont): origin{newOrigin}, side{newSide}, serial{newSerial}, font{newFont} {}// Простой конструктор

bool BaseModule::isPosInModule(sf::Vector2f pos) // Определение попадания координат в модуль
{
    /*
     * Например, если пользователь кликает мышкой, на клик реагирует только тот модуль, в котором сейчас курсор.
    */
    if ((pos.x >= origin.x && pos.x <= origin.x + side) && (pos.y >= origin.y && pos.y <= origin.y + side)) {
        return true;
    }
    return false;
}

int BaseModule::getMistakes()
{
    return mistakes;
}

bool BaseModule::getIsDone()
{
    return isDone;
}

void BaseModule::process(sf::RenderWindow* window, int time) {}

void BaseModule::render(sf::RenderWindow *window)
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
