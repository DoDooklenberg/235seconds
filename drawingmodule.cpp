#include "drawingmodule.h"


DrawingModule::DrawingModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont):
    BaseModule(newOrigin, newSide, newSerial, newFont)
{
    amt = 16;
    for (int i = 0; i < amt; i++){
        points.push_back(DrawingPoint(newFont, origin + sf::Vector2f{i * 30.f, i * 30.f}, 5.f, i + 1));
    }
}

void DrawingModule::process(sf::RenderWindow *window, int time)
{
    if (isPosInModule(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (currentPoint) {
                points.at(currentPoint - 1).setTarget(sf::Vector2f(sf::Mouse::getPosition(*window)));
                for (int i = 0; i < amt; i++){
                    if ((points.at(i).getPosition() - sf::Vector2f(sf::Mouse::getPosition(*window))).lengthSquared() <= 300.f && currentPoint != i + 1 && !points.at(i).isPrecursor()) {
                        points.at(currentPoint - 1).setNext(&points.at(i));
                        points.at(i).setTarget(sf::Vector2f(sf::Mouse::getPosition(*window)));
                        currentPoint = i + 1;
                        break;
                    }
                }
            } else {
                for (int i = 0; i < amt; i++){
                    if ((points.at(i).getPosition() - sf::Vector2f(sf::Mouse::getPosition(*window))).lengthSquared() <= 400.f) {
                        points.at(i).setTarget(sf::Vector2f(sf::Mouse::getPosition(*window)));
                        currentPoint = i + 1;
                        break;
                    }
                }
            }
        } else {
            currentPoint = 0;
            for (int i = 0; i < amt; i++){
                points.at(i).resetTarget();
            }
        }
    } else {
        currentPoint = 0;
        for (int i = 0; i < amt; i++){
            points.at(i).resetTarget();
        }
    }
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
    for (int i = 0; i < amt; i++){
        points.at(i).render(window);
    }
}
