#include "wiresmodule.h"
#include <iostream>
#include "basemodule.h"

WiresModule::WiresModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont):
    BaseModule(newOrigin, newSide, newSerial, newFont) {}

bool WiresModule::WiresPosCheck(sf::Vector2f pos)
{
    if ((pos.x >= origin.x + side/2 && pos.x <= origin.x + side/2 + 50.f) && (pos.y >= origin.y + side/2 && pos.y <= origin.y + side/2 + 50.f)) {
        return true;
    }
    return false;
}
void WiresModule::process(sf::RenderWindow *window, int time)
{
    if (wireIsCut == false) {
        if (WiresPosCheck(sf::Vector2f(sf::Mouse::getPosition()))) {
                const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
                window->setMouseCursor(cursor);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                wireIsCut = true;
                const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
                window->setMouseCursor(cursor);
            }
        }
        else {
            const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
            window->setMouseCursor(cursor);
        }
    }


}

void WiresModule::render(sf::RenderWindow *window)
{

    std::array vertices =
        {
        sf::Vertex{{origin.x, origin.y}, sf::Color::Red},
        sf::Vertex{{origin.x + side, origin.y}, sf::Color::Red},
        sf::Vertex{{origin.x + side, origin.y + side}, sf::Color::Red},
        sf::Vertex{{origin.x, origin.y + side}, sf::Color::Red},
        sf::Vertex{{origin.x, origin.y}, sf::Color::Red},
        };

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);

    sf::RectangleShape rectangle({50.f, 50.f});
    rectangle.setPosition(origin + sf::Vector2f{side*0.5f, side*0.5f});
    if (wireIsCut == true) {
        rectangle.setFillColor(sf::Color::Blue);
    }
    else {
        rectangle.setFillColor(sf::Color::Red);
    }
    window->draw(rectangle);
}
