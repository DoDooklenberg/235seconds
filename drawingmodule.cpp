#include "drawingmodule.h"
#include "drawingpoint.h"


DrawingModule::DrawingModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont):
    BaseModule(newOrigin, newSide, newSerial, newFont), points{DrawingPoint( origin + sf::Vector2f{100, 100}, font, 5.f, 1), DrawingPoint(origin + sf::Vector2f{200, 200}, font, 5.f, 1), DrawingPoint(origin + sf::Vector2f{200, 100}, font, 5.f, 1), DrawingPoint(origin + sf::Vector2f{100, 200}, font, 5.f, 1)}
{}

void DrawingModule::process(sf::RenderWindow *window, int time)
{
    if (isPosInModule(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (currentPoint) {
                points[currentPoint - 1].setTarget(sf::Vector2f(sf::Mouse::getPosition(*window)));
                for (int i = 0; i < 4; i++){
                    if ((points[i].getPosition() - sf::Vector2f(sf::Mouse::getPosition(*window))).lengthSquared() <= 400.f && currentPoint != i + 1 && !points[i].isPrecursor()) {
                        points[currentPoint - 1].setNext(&points[i]);
                        points[currentPoint - 1].setTarget(points[i].getPosition());
                        points[i].setTarget(sf::Vector2f(sf::Mouse::getPosition(*window)));
                        currentPoint = i + 1;
                        break;
                    }
                }
            } else {
                for (int i = 0; i < 4; i++){
                    if ((points[i].getPosition() - sf::Vector2f(sf::Mouse::getPosition(*window))).lengthSquared() <= 400.f) {
                        points[i].setTarget(sf::Vector2f(sf::Mouse::getPosition(*window)));
                        currentPoint = i + 1;
                        break;
                    }
                }
            }
        } else {
            currentPoint = 0;
            for (int i = 0; i < 4; i++){
                points[i].resetTarget();
            }
        }
    } else {
        currentPoint = 0;
        for (int i = 0; i < 4; i++){
            points[i].resetTarget();
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
    for (int i = 0; i < 4; i++){
        points[i].render(window);
    }
}
