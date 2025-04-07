#include "drawingmodule.h"


DrawingModule::DrawingModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont):
    BaseModule(newOrigin, newSide, newSerial, newFont)
{
    genertePoints();
}

void DrawingModule::genertePoints()
{
    std::srand(std::time({}));
    amt = 10 + rand() % 11;
    int j = 0;
    for (int i = 0; i < amt; i++){
        sf::Vector2f pointPos = origin + sf::Vector2f{side * 0.9f * 0.01f * (rand() % 100) + side * 0.05f, side * 0.9f * 0.01f * (rand() % 100) + side * 0.05f};
        if (points.empty()){
            points.push_back(DrawingPoint(font, pointPos, 5.f, i + 1));
            continue;
        }
        j = 0;
        while (1){
            if ((points.at(j).getPosition() - pointPos).lengthSquared() <= 5000.f) {
                pointPos = origin + sf::Vector2f{side * 0.8f * 0.01f * (rand() % 100) + side * 0.1f, side * 0.9f * 0.01f * (rand() % 100) + side * 0.05f};
                j = 0;
            } else {
                j++;
                if (j >= points.size()) {
                    break;
                }
            }
        }
        points.push_back(DrawingPoint(font, pointPos, 5.f, i + 1));
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        currentPoint = 0;
        points.clear();
        amt = 0;
        genertePoints();
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
