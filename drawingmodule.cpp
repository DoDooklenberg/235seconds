#include "drawingmodule.h"
#include <iostream>


DrawingModule::DrawingModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont):
    BaseModule(newOrigin, newSide, newSerial, newFont)
{
    genertePoints();
}

void DrawingModule::genertePoints()
{
    auto getFakeNumber = [=](int real){if (amt == 12) {return numbers_12[real];} else if (amt == 13) {return numbers_13[real];} else {return numbers_14[real];} };
    /*
     * Я переписал логику ложной точки на лямбду, ура. Понятнее не стало, но по крайне мере это не так страшно выглядит.
     * Точка с номером 2 обозначена как 10, но если остаток от деления кол-ва точек на 3 равен 0, то как 9
     * Точка с номером 3 обозначена как 1, но если остаток от деления кол-ва точек на 3 равен 1, то как 5
     * Точка с номером 4 обозначена как 8, но если остаток от деления кол-ва точек на 3 равен 1, то как 3
     * Точка с номером 5 обозначена как 2, но если остаток от деления кол-ва точек на 3 равен 2, то как 4
     * Точка с номером 6 обозначена как 9, но если остаток от деления кол-ва точек на 3 равен 0, то как 11
     * Точка с номером 7 обозначена как 6, но если остаток от деления кол-ва точек на 3 равен 2, то как 12
     * Точка с номером 8 обозначена как 12, но если остаток от деления кол-ва точек на 3 равен 2, то как 14
     * Точка с номером 9 обозначена как 13, но если остаток от деления кол-ва точек на 3 равен 0, то как 3
     * Точка с номером 10 обозначена как 5, но если остаток от деления кол-ва точек на 3 равен 1, то как 1
     * Точка с номером 11 обозначена как 7, но если остаток от деления кол-ва точек на 3 равен 2, то как 2
     * Точка с номером 12 обозначена как 11, но если остаток от деления кол-ва точек на 3 равен 0, то как 10
     * Точка с номером 13 обозначена как 8, но если остаток от деления кол-ва точек на 3 равен 2, то как 7
     * Точка с номером 14 обозначена как 3, но если остаток от деления кол-ва точек на 3 равен 1, то как 4
     */
    currentPoint = 0;
    points.clear();
    amt = 12 + rand() % 3;
    int j = 0;
    for (int i = 0; i < amt; i++){
        sf::Vector2f pointPos = origin + sf::Vector2f{side * 0.8f * 0.01f * (rand() % 100) + side * 0.1f, side * 0.8f * 0.01f * (rand() % 100) + side * 0.1f};
        if (points.empty()){
            points.push_back(DrawingPoint(font, pointPos, side * 0.01f, i + 1, getFakeNumber(i)));
            continue;
        }
        j = 0;
        while (1){
            if ((points.at(j).getPosition() - pointPos).length() <= side * 0.1f) {
                pointPos = origin + sf::Vector2f{side * 0.8f * 0.01f * (rand() % 100) + side * 0.1f, side * 0.8f * 0.01f * (rand() % 100) + side * 0.1f};
                j = 0;
            } else {
                j++;
                if (j >= points.size()) {
                    break;
                }
            }
        }
        points.push_back(DrawingPoint(font, pointPos, side * 0.01f, i + 1, getFakeNumber(i)));
    }
}

bool DrawingModule::checkWin()
{
    bool isAllRight = true;
    for (int i = 0; i < amt; i++){
        if (!points.at(i).isPrecursor()) {
            return false;
        } else if (!points.at(i).isRight() && ((i + 1) != amt)) {
            isAllRight = false;
        }
    }
    if (isAllRight) {
        return true;
    } else {
        mistakes++;
        genertePoints();
        return false;
    }
}

void DrawingModule::process(sf::RenderWindow *window, int time)
{
    if (!isDone) {
        if (isPosInModule(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if (currentPoint) {
                    points.at(currentPoint - 1).setTarget(sf::Vector2f(sf::Mouse::getPosition(*window)));
                    for (int i = 0; i < amt; i++){
                        if ((points.at(i).getPosition() - sf::Vector2f(sf::Mouse::getPosition(*window))).length() <= side * 0.035f && currentPoint != i + 1 && !points.at(i).isPrecursor()) {
                            points.at(currentPoint - 1).setNext(&points.at(i));
                            points.at(i).setTarget(sf::Vector2f(sf::Mouse::getPosition(*window)));
                            currentPoint = i + 1;
                            break;
                        }
                    }
                } else {
                    for (int i = 0; i < amt; i++){
                        if ((points.at(i).getPosition() - sf::Vector2f(sf::Mouse::getPosition(*window))).length() <= side * 0.035f) {
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
        if (checkWin()) {
            for (int i = 0; i < amt; i++){
                if (points.at(i).getNext() == NULL) {
                    points.at(i).resetTarget();
                    break;
                }
            }
            isDone = true;
        }
    }
}

void DrawingModule::render(sf::RenderWindow *window)
{
    std::array vertices =
        {
         sf::Vertex{{origin.x + side * 0.01f, origin.y + side * 0.01f}},
         sf::Vertex{{origin.x + side * 0.99f, origin.y + side * 0.01f}},
         sf::Vertex{{origin.x + side * 0.99f, origin.y + side * 0.99f}},
         sf::Vertex{{origin.x + side * 0.01f, origin.y + side * 0.99f}},
         sf::Vertex{{origin.x + side * 0.01f, origin.y + side * 0.01f}},
         };

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);
    for (int i = 0; i < amt; i++){
        points.at(i).render(window);
    }
}
