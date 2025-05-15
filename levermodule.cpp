#include "levermodule.h"


void LeverModule::randwin()
{
    //if(arc4random() % 2 == 0)
    if(c % 2 == 0)
    {
        mistakes += 1;
    }
    else
    {
        isDone = true;
    }
}

void LeverModule::startposition()
{
    circle.setRadius(side * 0.065f);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition(origin + sf::Vector2(side / 2.0f, side / 4.0f));

    stick.setSize({side * 0.02f, side * 0.3f});
    stick.setOrigin({stick.getSize().x / 2.f, 0.f});
    stick.setPosition(circle.getPosition());
}

LeverModule::LeverModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont) : BaseModule(newOrigin, newSide, newSerial, newFont)
{
    startposition();

    base.setSize({0.2f * side, 0.3f * side});
    base.setOrigin(base.getGeometricCenter());
    base.setPosition(origin + sf::Vector2(side / 2.0f, side / 4.0f + stick.getSize().y));
    base.setFillColor(sf::Color::Black);
    base.setOutlineThickness(side * 0.01f);

    base2.setSize({0.05f * side, 0.07f * side});
    base2.setOrigin(base2.getGeometricCenter());
    base2.setPosition(base.getPosition());
}

void LeverModule::process(sf::RenderWindow *window, int time)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) // рычаг нажат
        && sf::Mouse::getPosition(* window).x > circle.getPosition().x - circle.getRadius() && sf::Mouse::getPosition(* window).x < circle.getPosition().x + circle.getRadius()
        && sf::Mouse::getPosition(* window).y > stick.getPosition().y - circle.getRadius() && sf::Mouse::getPosition(* window).y < stick.getPosition().y + stick.getSize().y)
    {
        if (isDone == false && circle.getPosition() == stick.getPosition()) // рычаг опускается
        {
                stick.setPosition(stick.getPosition() + sf::Vector2(0.f, stick.getSize().y));
                circle.setPosition(stick.getPosition() + sf::Vector2(0.f, stick.getSize().y));
                randwin();
        }
    }
    if(isDone == false && circle.getPosition() != stick.getPosition()) // рычаг возвращается после нажатия
    {
        if(!ss.isRunning())
        {
            ss.start();
        }
        if(ss.getElapsedTime().asSeconds() < 1.83f && ss.getElapsedTime().asSeconds() > 1.8f)
        {
            startposition();
            ss.reset();
        }
    }
}

void LeverModule::render(sf::RenderWindow *window)
{
    window->draw(base);
    window->draw(base2);
    window->draw(stick);
    window->draw(circle);

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
