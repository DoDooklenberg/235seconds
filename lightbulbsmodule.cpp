#include "lightbulbsmodule.h"
#include <cmath>

LightBulbsModule::LightBulbsModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont) : BaseModule(newOrigin, newSide, newSerial, newFont)
{
    isBase = false;

    colors[0] = sf::Color::Red;
    colors[1] = sf::Color::Blue;
    colors[2] = sf::Color::Yellow;
    colors[3] = sf::Color::Green;
    colors[4] = sf::Color::White;
    colors[5] = sf::Color(148, 0, 211);

    float radius = side / 8.0f;
    float padding = side / 15.0f;

    for (int i = 0; i < 6; i++) {
        bulbs[i].setRadius(radius);
        bulbs[i].setFillColor(sf::Color(colors[i].r / 3, colors[i].g / 3, colors[i].b / 3));
        bulbs[i].setOutlineColor(sf::Color::White);
        bulbs[i].setOutlineThickness(1.0f);

        float x = origin.x + padding + (i % 3) * (2 * radius + padding);
        float y = origin.y + padding + (i / 3) * (2 * radius + padding);
        bulbs[i].setPosition(sf::Vector2f(x, y));
    }

    activeBulb = -1;
    bulbTimer.restart();
    isHolding = false;
    holdingBulb = -1;
    holdTimer.restart();
    sequenceStep = 0;
    clickCount = 0;
    clickCooldown.restart();
    solvedCount = 0;
}

void LightBulbsModule::process(sf::RenderWindow *window, int time)
{
    if (isDone || !window)
        return;

    if (activeBulb == -1) {
        if (bulbTimer.getElapsedTime().asSeconds() > 1.5f) {
            activeBulb = rand() % 6;
            bulbs[activeBulb].setFillColor(colors[activeBulb]);
            isHolding = false;
            holdingBulb = -1;
            holdTimer.restart();
            sequenceStep = 0;
            clickCount = 0;
            clickCooldown.restart();
        }
    } else {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePos = window->mapPixelToCoords(mousePosition);
        bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        for (int i = 0; i < 6; i++) {
            sf::Vector2f bulbCenter(
                bulbs[i].getPosition().x + bulbs[i].getRadius(),
                bulbs[i].getPosition().y + bulbs[i].getRadius()
            );

            float distance = std::sqrt(
                std::pow(mousePos.x - bulbCenter.x, 2) +
                std::pow(mousePos.y - bulbCenter.y, 2)
            );

            if (distance <= bulbs[i].getRadius()) {
                if (mousePressed) {
                    if (isHolding && i == holdingBulb) {
                        // Продолжаем удерживать
                    } else if (!isHolding && clickCooldown.getElapsedTime().asSeconds() > 0.2f) {
                        isHolding = true;
                        holdingBulb = i;
                        holdTimer.restart();
                        clickCooldown.restart();

                        switch (activeBulb) {
                            case 0: // Красная -> нажать синюю
                                if (i == 1) {
                                    bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                                    activeBulb = -1;
                                    bulbTimer.restart();
                                    solvedCount++;
                                } else {
                                    mistakes++;
                                }
                                break;

                            case 1: // Синяя -> удерживать жёлтую 3 секунды
                                if (i != 2) {
                                    mistakes++;
                                    bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                                    activeBulb = -1;
                                    bulbTimer.restart();
                                }
                                break;

                            case 2: // Жёлтая -> нажать зелёную, затем белую
                                if (sequenceStep == 0 && i == 3) {
                                    sequenceStep = 1;
                                } else if (sequenceStep == 1 && i == 4) {
                                    bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                                    activeBulb = -1;
                                    bulbTimer.restart();
                                    solvedCount++;
                                } else {
                                    mistakes++;
                                    bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                                    activeBulb = -1;
                                    bulbTimer.restart();
                                }
                                break;

                            case 3: // Зелёная -> нажать фиолетовую дважды
                                if (i == 5) {
                                    clickCount++;
                                    if (clickCount >= 2) {
                                        bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                                        activeBulb = -1;
                                        bulbTimer.restart();
                                        solvedCount++;
                                    }
                                } else {
                                    mistakes++;
                                    bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                                    activeBulb = -1;
                                    bulbTimer.restart();
                                }
                                break;

                            case 4: // Белая -> удерживать зелёную 2 секунды
                                if (i != 3) {
                                    mistakes++;
                                    bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                                    activeBulb = -1;
                                    bulbTimer.restart();
                                }
                                break;

                            case 5: // Фиолетовая -> нажать любую лампочку
                                bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                                activeBulb = -1;
                                bulbTimer.restart();
                                solvedCount++;
                                break;
                        }
                    }
                }
            }
        }

        if (!mousePressed) {
            if (isHolding) {
                isHolding = false;

                if (activeBulb == 1 && holdingBulb == 2) {
                    if (holdTimer.getElapsedTime().asSeconds() >= 3.0f) {
                        bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                        activeBulb = -1;
                        bulbTimer.restart();
                        solvedCount++;
                    } else {
                        mistakes++;
                    }
                } else if (activeBulb == 4 && holdingBulb == 3) {
                    if (holdTimer.getElapsedTime().asSeconds() >= 2.0f) {
                        bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                        activeBulb = -1;
                        bulbTimer.restart();
                        solvedCount++;
                    } else {
                        mistakes++;
                    }
                }
            }

            holdingBulb = -1;
        } else if (isHolding) {
            if (activeBulb == 1 && holdingBulb == 2 && holdTimer.getElapsedTime().asSeconds() >= 3.0f) {
                bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                activeBulb = -1;
                bulbTimer.restart();
                isHolding = false;
                holdingBulb = -1;
                solvedCount++;
            } else if (activeBulb == 4 && holdingBulb == 3 && holdTimer.getElapsedTime().asSeconds() >= 2.0f) {
                bulbs[activeBulb].setFillColor(sf::Color(colors[activeBulb].r / 3, colors[activeBulb].g / 3, colors[activeBulb].b / 3));
                activeBulb = -1;
                bulbTimer.restart();
                isHolding = false;
                holdingBulb = -1;
                solvedCount++;
            }
        }
    }

    if (solvedCount >= 5 || mistakes >= 3) {
        isDone = true;
    }
}

void LightBulbsModule::render(sf::RenderWindow *window)
{
    if (!window)
        return;

    std::array<sf::Vertex, 5> vertices;
    vertices[0].position = sf::Vector2f(origin.x, origin.y);
    vertices[1].position = sf::Vector2f(origin.x + side, origin.y);
    vertices[2].position = sf::Vector2f(origin.x + side, origin.y + side);
    vertices[3].position = sf::Vector2f(origin.x, origin.y + side);
    vertices[4].position = sf::Vector2f(origin.x, origin.y);

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);

    for (int i = 0; i < 6; i++) {
        window->draw(bulbs[i]);
    }
}
