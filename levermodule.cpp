#include "levermodule.h"


LeverModule::LeverModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont) : BaseModule(newOrigin, newSide, newSerial, newFont)
{

}

void LeverModule::process(sf::RenderWindow *window, int time)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
        && sf::Mouse::getPosition(* window).x > circle.getPosition().x - circle.getRadius() && sf::Mouse::getPosition(* window).x < circle.getPosition().x + circle.getRadius()
        && sf::Mouse::getPosition(* window).y > circle.getPosition().y - circle.getRadius() && sf::Mouse::getPosition(* window).y < stick.getPosition().y + stick.getSize().y)
    {
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(circle.getPosition() + sf::Vector2(0.f, stick.getSize().y + 2.f * circle.getRadius()));
    }
    window->draw(circle);
}

void LeverModule::render(sf::RenderWindow *window)
{
    circle.setRadius(side * 0.08f);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition(origin + sf::Vector2(side / 2.0f, side / 2.0f));
    circle.setFillColor(sf::Color::Red);

    stick.setSize({side * 0.04f, side * 0.3f});
    stick.setOrigin({stick.getSize().x / 2.f, 0.f});
    stick.setPosition(circle.getPosition() + sf::Vector2(0.f, circle.getRadius()));

    window->draw(stick);
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        window->draw(circle);
    }

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
