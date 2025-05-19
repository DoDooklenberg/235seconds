#include "levermodule.h"

void LeverModule::randWin() // случайная победа
{
    if(rand() % 2 == 0)
    {
        ++mistakes;
    }
    else
    {
        isDone = true;
    }
}

void LeverModule::startPosition() // рычаг в верхнем положение
{
    circle.setRadius(side * 0.065f);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition(origin + sf::Vector2(side / 2.0f, side / 4.0f));

    stick.setSize({side * 0.02f, side * 0.3f});
    stick.setOrigin({stick.getSize().x / 2.f, 0.f});
    stick.setPosition(circle.getPosition());
}

bool LeverModule::isPrimeNumber(int num) // проверяет является ли число простым
{
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int LeverModule::serialSum() // сумма цифр серийного номера
{
    int counter = 0;
    for (char num : serial)
    {
        if (isdigit(num))
        {
            counter += int(num - '0');
        }
    }
    return counter;
}

LeverModule::LeverModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont):
    BaseModule(newOrigin, newSide, newSerial, newFont)
{
    startPosition();

    if (rand() % 2 == 0) // случайный цвет рычага
    {
        circle.setFillColor(sf::Color::Red);
    }
    else
    {
        circle.setFillColor(sf::Color::Blue);
    }

    base.setSize({0.2f * side, 0.3f * side}); // крепление рычага
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
        && sf::Mouse::getPosition(* window).x > circle.getPosition().x - circle.getRadius()
        && sf::Mouse::getPosition(* window).x < circle.getPosition().x + circle.getRadius()
        && sf::Mouse::getPosition(* window).y > stick.getPosition().y - circle.getRadius()
        && sf::Mouse::getPosition(* window).y < stick.getPosition().y + stick.getSize().y)
    {
        if (isDone == false && circle.getPosition() == stick.getPosition())
        {
            stick.setPosition(stick.getPosition() + sf::Vector2(0.f, stick.getSize().y)); // рычаг опускается
            circle.setPosition(stick.getPosition() + sf::Vector2(0.f, stick.getSize().y));

            localTime = time;

            auto check{[&](bool expression){if(expression){isDone = true;} else randWin();}};

            char firstNum = serial[0];

            if (isPrimeNumber(serialSum())) // правила нажатия
            {
                if (int(firstNum - '0') % 2 == 0)
                {
                    if (circle.getFillColor() == sf::Color::Blue)
                    {
                        if (serialSum() >= 11)
                        {
                            check(time - 60 * (time / 60) >= 30 && time - 60 * (time / 60) <= 32);
                        }
                        else
                        {
                            check(time - 60 * (time / 60) == 11);
                        }
                    }
                    else
                    {
                        check(time % 2 == 0);
                    }
                }
                else
                {
                    if (circle.getFillColor() == sf::Color::Blue)
                    {
                        check(!(time >= 125 && time <= 179));
                    }
                    else
                    {
                        if (int(firstNum - '0') > 6)
                        {
                            check(time % 10 == 1);
                        }
                        else
                        {
                            check(time == 120);
                        }
                    }
                }
            }
            else
            {
                if (int(firstNum - '0') % 2 == 0)
                {
                    check(time == 17);
                }
                else
                {
                    if (circle.getFillColor() == sf::Color::Red)
                    {
                        check(time % 10 != 0);
                    }
                    else
                    {
                        check(true);
                    }
                }
            }
        }
    }

    if(isDone == false && circle.getPosition() != stick.getPosition()) // рычаг возвращается после нажатия
    {
        if(localTime - time >= 2)
        {
            startPosition();
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
