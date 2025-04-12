#include "drawingmodule.h"


DrawingModule::DrawingModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont):
    BaseModule(newOrigin, newSide, newSerial, newFont)
{
    genertePoints();
}

void DrawingModule::genertePoints()
{
    std::srand(std::time({})); //TODO Вынести рандом в окно выбора сложности
    currentPoint = 0;
    points.clear();
    amt = 12 + rand() % 3;
    int j = 0;
    for (int i = 0; i < amt; i++){
        sf::Vector2f pointPos = origin + sf::Vector2f{side * 0.8f * 0.01f * (rand() % 100) + side * 0.1f, side * 0.8f * 0.01f * (rand() % 100) + side * 0.1f};
        if (points.empty()){
            points.push_back(DrawingPoint(font, pointPos, side * 0.01f, i + 1, getFakeNumber(i + 1)));
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
        points.push_back(DrawingPoint(font, pointPos, side * 0.01f, i + 1, getFakeNumber(i + 1)));
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

int DrawingModule::getFakeNumber(int real) // Боже какой ужас, но как переписать это более читаемо я хз
{
    /*
     * 1 -> 6, но если остаток от деления количества точек на 3 равен 0 или 1, то 4.
     * 2 -> 9, но если остаток от деления количества точек на 3 равен 2 или 0, то 10.
     * 3 -> 5, но если остаток от деления количества точек на 3 равен 1 или 2, то 1.
     * 4 -> 3, но если остаток от деления количества точек на 3 равен 1 или 2, то 8.
     * 5 -> 4, но если остаток от деления количества точек на 3 равен 0 или 1, то 2.
     * 6 -> 11, но если остаток от деления количества точек на 3 равен 2 или 0, то 9.
     * 7 -> 12, но если остаток от деления количества точек на 3 равен 0 или 1, то 6.
     * 8 -> 14, но если остаток от деления количества точек на 3 равен 0 или 1, то 12.
     * 9 -> 3, но если остаток от деления количества точек на 3 равен 2 или 0, то 13.
     * 10 -> 1, но если остаток от деления количества точек на 3 равен 1 или 2, то 5.
     * 11 -> 2, но если остаток от деления количества точек на 3 равен 0 или 1, то 7.
     * 12 -> 10, но если остаток от деления количества точек на 3 равен 2 или 0, то 11.
     * 13 -> 8, но если остаток от деления количества точек на 3 равен 2, то 7.
     * 14 -> 3.
     */
    if (amt == 12) {
        switch (real) {
        case 4:
            return 1;
            break;
        case 9:
            return 2;
            break;
        case 1:
            return 3;
            break;
        case 8:
            return 4;
            break;
        case 2:
            return 5;
            break;
        case 11:
            return 6;
            break;
        case 6:
            return 7;
            break;
        case 12:
            return 8;
            break;
        case 3:
            return 9;
            break;
        case 5:
            return 10;
            break;
        case 7:
            return 11;
            break;
        case 10:
            return 12;
            break;
        default:
            return 0;
            break;
        }
    } else if (amt == 13) {
        switch (real) {
        case 4:
            return 1;
            break;
        case 10:
            return 2;
            break;
        case 5:
            return 3;
            break;
        case 3:
            return 4;
            break;
        case 2:
            return 5;
            break;
        case 9:
            return 6;
            break;
        case 6:
            return 7;
            break;
        case 12:
            return 8;
            break;
        case 13:
            return 9;
            break;
        case 1:
            return 10;
            break;
        case 7:
            return 11;
            break;
        case 11:
            return 12;
            break;
        case 8:
            return 13;
            break;
        default:
            return 0;
            break;
        }
    } else {
        switch (real) {
        case 6:
            return 1;
            break;
        case 10:
            return 2;
            break;
        case 1:
            return 3;
            break;
        case 8:
            return 4;
            break;
        case 4:
            return 5;
            break;
        case 9:
            return 6;
            break;
        case 12:
            return 7;
            break;
        case 14:
            return 8;
            break;
        case 13:
            return 9;
            break;
        case 5:
            return 10;
            break;
        case 2:
            return 11;
            break;
        case 11:
            return 12;
            break;
        case 7:
            return 13;
            break;
        case 3:
            return 14;
            break;
        default:
            return 0;
            break;
        }
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
