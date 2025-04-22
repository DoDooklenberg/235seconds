#include "wiresmodule.h"
#include <iostream>
#include "basemodule.h"
#include <vector>
#include <iostream>

WiresModule::WiresModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont):
    BaseModule(newOrigin, newSide, newSerial, newFont)
{
    generateWires();
}


void WiresModule::generateWires()
{
    std::srand(std::time({}));
    amountOfWires = rand()%4 + 1;
    int step = 0;
    for (int i = 0; i < amountOfWires; i++) {
        Wires.push_back(DrawWires(origin + sf::Vector2f(side/3, side/(amountOfWires + 1) + step), sf::Vector2f(side/3, 15.f), sf::Color::White, false));
        step += 30;
    }

}


bool WiresModule::WiresPosCheck(sf::Vector2f cursor)
{
    for (mouseOnWire = 0; mouseOnWire < amountOfWires; mouseOnWire++) {
        if ((cursor.x >= Wires.at(mouseOnWire).pos_1.x && cursor.x <= Wires.at(mouseOnWire).pos_1.x + Wires.at(mouseOnWire).pos_2.x)
           && (cursor.y >= Wires.at(mouseOnWire).pos_1.y && cursor.y <= Wires.at(mouseOnWire).pos_1.y + Wires.at(mouseOnWire).pos_2.y)) {
            return true;

        }
    }
    mouseOnWire = 0;
    return false;
}
void WiresModule::process(sf::RenderWindow *window, int time)
{
    const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
    window->setMouseCursor(cursor);
    std::cout << mouseOnWire;

        if (WiresPosCheck(sf::Vector2f(sf::Mouse::getPosition()))) {
            if (Wires.at(mouseOnWire).wireIsCut == false) {
                const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
                window->setMouseCursor(cursor);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Wires.at(mouseOnWire).wireIsCut = true;
                }
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


    //это я у вадима научился такие свитч-кейсы делать, потом изменю
    switch (amountOfWires) {
    case 1: {
        sf::RectangleShape wire_1(Wires.at(0).pos_2);
        wire_1.setPosition(Wires.at(0).pos_1);
        if (Wires.at(0).wireIsCut == true) {wire_1.setFillColor(sf::Color::Black);}
        window->draw(wire_1);
        break;
    }
    case 2: {
        sf::RectangleShape wire_1(Wires.at(0).pos_2);
        wire_1.setPosition(Wires.at(0).pos_1);
        window->draw(wire_1);
        sf::RectangleShape wire_2(Wires.at(1).pos_2);
        wire_2.setPosition(Wires.at(1).pos_1);
        window->draw(wire_2);
        break;
    }
    case 3: {
        sf::RectangleShape wire_1(Wires.at(0).pos_2);
        wire_1.setPosition(Wires.at(0).pos_1);
        window->draw(wire_1);
        sf::RectangleShape wire_2(Wires.at(1).pos_2);
        wire_2.setPosition(Wires.at(1).pos_1);
        window->draw(wire_2);
        sf::RectangleShape wire_3(Wires.at(2).pos_2);
        wire_3.setPosition(Wires.at(2).pos_1);
        window->draw(wire_3);
        break;
    }
    case 4: {
        sf::RectangleShape wire_1(Wires.at(0).pos_2);
        wire_1.setPosition(Wires.at(0).pos_1);
        window->draw(wire_1);
        sf::RectangleShape wire_2(Wires.at(1).pos_2);
        wire_2.setPosition(Wires.at(1).pos_1);
        window->draw(wire_2);
        sf::RectangleShape wire_3(Wires.at(2).pos_2);
        wire_3.setPosition(Wires.at(2).pos_1);
        window->draw(wire_3);
        sf::RectangleShape wire_4(Wires.at(3).pos_2);
        wire_4.setPosition(Wires.at(3).pos_1);
        window->draw(wire_4);
        break;
    }
    deafault:
        break;
    }



}
