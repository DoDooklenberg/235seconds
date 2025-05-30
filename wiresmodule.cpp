#include "wiresmodule.h"
#include "basemodule.h"
#include <vector>
#include <SFML/Audio.hpp>

WiresModule::WiresModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont):
    BaseModule(newOrigin, newSide, newSerial, newFont), WireSoundBuffer("WireCut.wav"), WireCut(WireSoundBuffer)
{
    generateWires();
    setCorrectWires();
}

void WiresModule::setCorrectWires()
{

    switch (amountOfWires) {
    //при двух проводах правильный провод зависит от остатка от деления на 2 суммы всех цифр серийника. 0 - 1-ый провод, 1 - 2-ой провод
    //но если кол-во цифр серийника больше 5 - то провода меняются местами
    case 2: {
        int sum = 0;
        int cnt = 0;
        for (char ch : serial) {
                if (isdigit(ch)) {
                    cnt++;
                }
        }
        if (cnt > 5) {
            for (char ch : serial) {
                    if (isdigit(ch)) {
                        sum += int(ch - '0');
                    }
                }
            if (sum % 2 == 1) {Wires.at(0).isCorrect = true;}
            else {Wires.at(1).isCorrect = true;}
        }
        else {
        for (char ch : serial) {
                if (isdigit(ch)) {
                    sum += int(ch - '0');
                }
            }
        Wires.at(sum % 2).isCorrect = true;
        }
        break;
    }
    //при трёх проводах - находится по формуле: остакток от деления на 3 от (количество букв серийеика) * 2 + (количество цифр серийника) * 3
    // + (сумма кодов цвета проводов: красный - 0, жёлтый - 31, зелёный - 1,синий - 52, бирюзоый - 13)
    // 0 - первый провод, 1 - второй, 2 - третий
    case 3: {
        int lettersCount = 0;
        int numbersCount = 0;
        int colorCodeSum = 0;

        for (char ch : serial) {
                if (isdigit(ch)) {numbersCount++;}
                else {lettersCount++;}
            }
        for (int i = 0; i < 3; i++) {
            if (Wires.at(i).color == sf::Color::Red) {colorCodeSum += 0;}
            if (Wires.at(i).color == sf::Color::Yellow) {colorCodeSum += 31;}
            if (Wires.at(i).color == sf::Color::Green) {colorCodeSum += 1;}
            if (Wires.at(i).color == sf::Color::Blue) {colorCodeSum += 52;}
            if (Wires.at(i).color == sf::Color::Cyan) {colorCodeSum += 13;}
        }
        Wires.at((lettersCount * 2 + numbersCount * 3 + colorCodeSum) % 3).isCorrect = true;
        break;
    }
    //при четырёх проводах читать ниже
    case 4: {
        int maxSum = 0;
        int curSum = 0;
        sf::Color mostUsedColor;

        for (int i = 0; i < amountOfWires; i++) {
            for (int j = 0; j < amountOfWires; j++) {
                if (Wires.at(i).color == Wires.at(j).color) {
                    curSum++;
                }
        }
            if (curSum >= maxSum) {
                mostUsedColor = Wires.at(i).color;
                maxSum = curSum;
            }
            curSum = 0;
        }

        switch (maxSum) {
        //при четырёх разных проводах - резать первый и четвёртый
        case 1:
            Wires.at(0).isCorrect = true;
            Wires.at(3).isCorrect = true;
            break;
        //при двух одинакоых проводах - резать два разного цвета,
        //если две пары по два цвета - резать два провода чей цвет встречается НЕ последним (а ловко я это придумал)
        case 2:
            for (int i = 0; i < 4; i++) {
                if (Wires.at(i).color != mostUsedColor) {
                    Wires.at(i).isCorrect = true;
                }
            }
            break;
        //при трёх проводах одинакового цвета - резать первый провод самого часто-встречающегося цвета и последний
        case 3:
            for (int i = 0; i < 4; i++) {
                if (Wires.at(i).color == mostUsedColor) {
                    Wires.at(i).isCorrect = true;
                    i++;
                }
            }
            break;
        //при четырёх проводах одинакогового цвета - резать третий и второй
        case 4:
            Wires.at(1).isCorrect = true;
            Wires.at(2).isCorrect = true;
            break;
        }
        break;
    }
    default:
        break;
    }

}
sf::Color WiresModule::getRandomColor()
{
    int wireColor = rand() % 5;
    switch (wireColor) {
    case 0:
        return sf::Color::Red;
        break;
    case 1:
        return sf::Color::Yellow;
        break;
    case 2:
        return sf::Color::Green;
        break;
    case 3:
        return sf::Color::Blue;
        break;
    case 4:
        return sf::Color::Cyan;
        break;
    default:
        return sf::Color::White;
        break;
    }
}



void WiresModule::generateWires()
{
    amountOfWires = rand()%3+2;
    int step = 0;
    for (int i = 0; i < amountOfWires; i++) {
        Wires.push_back(DrawWires(origin + sf::Vector2f(side/3, 30 + side/3 + step),
        sf::Vector2f(side/3, 15.f), getRandomColor(), false, false));
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

    if (isDone == false) {

            if (WiresPosCheck(sf::Vector2f(sf::Mouse::getPosition()))) {
                if (Wires.at(mouseOnWire).wireIsCut == false) {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                        WireCut.play();
                        Wires.at(mouseOnWire).wireIsCut = true;
                            if (Wires.at(mouseOnWire).isCorrect == true) {
                                correctWireCut++;
                            }
                            else {
                                mistakes++;
                            }
                    }
                }
            }
    }

    switch (amountOfWires) {
    case 2:
        if (correctWireCut == 1) {
            isDone = 1;
        }
        break;
    case 3:
        if (correctWireCut == 1){
            isDone = 1;
        }
        break;
    case 4:
        if (correctWireCut == 2) {
            isDone = 1;
        }
        break;
    default:
        isDone = 1;
        break;
    }


}

void WiresModule::render(sf::RenderWindow *window)
{

    std::array vertices =
        {
        sf::Vertex{{origin.x, origin.y}, sf::Color::White},
        sf::Vertex{{origin.x + side, origin.y}, sf::Color::White},
        sf::Vertex{{origin.x + side, origin.y + side}, sf::Color::White},
        sf::Vertex{{origin.x, origin.y + side}, sf::Color::White},
        sf::Vertex{{origin.x, origin.y}, sf::Color::White},
        };

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);

    sf::Texture wireTexture_0_cut("WireSprite_1_cut.png"), wireTexture_0("WireSprite_1.png"),
    wireTexture_1_cut("WireSprite_2_cut.png"), wireTexture_1("WireSprite_2.png"),
    wireTexture_2_cut("WireSprite_3_cut.png"), wireTexture_2("WireSprite_3.png"),
    wireTexture_3_cut("WireSprite_3_cut.png"), wireTexture_3("WireSprite_3.png"),
    wireTexture_4_cut("WireSprite_4_cut.png"), wireTexture_4("WireSprite_4.png");

    sf::Texture backPlateTexture("BackPlate.png"), frontPlateTexture("FrontPlate.png");


    sf::RectangleShape backPlate({side / 3, side / 3});
    backPlate.setPosition({origin.x + side / 3, origin.y + side / 3});
    backPlate.setTexture(&backPlateTexture);
    window->draw(backPlate);




        if (amountOfWires >= 1) {
            sf::RectangleShape wire_0(Wires.at(0).pos_2);
            wire_0.setPosition(Wires.at(0).pos_1);

            if (Wires.at(0).wireIsCut) {
                wire_0.setTexture(&wireTexture_0_cut);
            }
            else {
                wire_0.setTexture(&wireTexture_0);
            }
            wire_0.setFillColor(Wires.at(0).color);
            window->draw(wire_0);
            if (amountOfWires >= 2) {
                sf::RectangleShape wire_1(Wires.at(1).pos_2);
                wire_1.setPosition(Wires.at(1).pos_1);

                if (Wires.at(1).wireIsCut) {
                    wire_1.setTexture(&wireTexture_1_cut);
                }
                else {
                    wire_1.setTexture(&wireTexture_1);
                }
                wire_1.setFillColor(Wires.at(1).color);
                window->draw(wire_1);

                    if (amountOfWires >= 3) {
                        sf::RectangleShape wire_2(Wires.at(2).pos_2);
                        wire_2.setPosition(Wires.at(2).pos_1);

                        if (Wires.at(2).wireIsCut) {
                            wire_2.setTexture(&wireTexture_2_cut);
                        }
                        else {
                            wire_2.setTexture(&wireTexture_2);
                        }
                        wire_2.setFillColor(Wires.at(2).color);
                        window->draw(wire_2);

                        if (amountOfWires >= 4) {
                            sf::RectangleShape wire_3(Wires.at(3).pos_2);
                            wire_3.setPosition(Wires.at(3).pos_1);
                            if (Wires.at(3).wireIsCut) {
                                wire_3.setTexture(&wireTexture_3_cut);
                            }
                            else {
                                wire_3.setTexture(&wireTexture_3);
                            }
                            wire_3.setFillColor(Wires.at(3).color);
                            window->draw(wire_3);
                        }
                    }
            }
        }

        sf::RectangleShape frontPlate({side / 3, side / 3});
        backPlate.setPosition({origin.x + side / 3, origin.y + side / 3});
        backPlate.setTexture(&frontPlateTexture);
        window->draw(backPlate);




}
