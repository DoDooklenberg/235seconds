#include "shifrmodule.h"

ShifrModule::ShifrModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont) :
    BaseModule(newOrigin, newSide, newSerial, newFont),
    buttons{Button(Label(font, ".", sf::Color::White), origin + sf::Vector2f(side * 0.1f + side * 0.3f * 0, side * 0.3f), sf::Vector2f(side * 0.2f, side * 0.2f), sf::Color::Magenta),
            Button(Label(font, ".", sf::Color::White), origin + sf::Vector2f(side * 0.1f + side * 0.3f * 1, side * 0.3f), sf::Vector2f(side * 0.2f, side * 0.2f), sf::Color::Magenta),
            Button(Label(font, ".", sf::Color::White), origin + sf::Vector2f(side * 0.1f + side * 0.3f * 2, side * 0.3f), sf::Vector2f(side * 0.2f, side * 0.2f), sf::Color::Magenta),
            Button(Label(font, ".", sf::Color::White), origin + sf::Vector2f(side * 0.1f + side * 0.3f * 0, side * 0.6f), sf::Vector2f(side * 0.2f, side * 0.2f), sf::Color::Magenta),
            Button(Label(font, ".", sf::Color::White), origin + sf::Vector2f(side * 0.1f + side * 0.3f * 1, side * 0.6f), sf::Vector2f(side * 0.2f, side * 0.2f), sf::Color::Magenta),
            Button(Label(font, ".", sf::Color::White), origin + sf::Vector2f(side * 0.1f + side * 0.3f * 2, side * 0.6f), sf::Vector2f(side * 0.2f, side * 0.2f), sf::Color::Magenta)},
    agree{Label(font, "Проверить", sf::Color::White), origin, sf::Vector2f(side * 0.5, side * 0.1), sf::Color::Magenta},
    code{Label(font, "", sf::Color::White), origin, sf::Vector2f(side * 0.9, side * 0.1), sf::Color::Black}
{
    agree.getShape()->setOrigin(agree.getShape()->getGeometricCenter());
    agree.getShape()->setPosition(origin + sf::Vector2f(side * 0.5f, side * 0.9));
    agree.reloadLabel();
    for (int i = 0; i < 6; i++) {
        currentLet[i] = rand() % 12;
    }
    generateWords();
}

void ShifrModule::process(sf::RenderWindow *window, int time)
{
    if (!isDone) {
        if (isPosInModule(sf::Vector2f(sf::Mouse::getPosition(*window))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (!justPressed) {
                for (int i = 0; i < 6; i++) {
                    if (buttons[i].isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                        currentLet[i] += 1;
                        currentLet[i] %= 12;
                        buttons[i].getLabel()->setString(letters[i % 3][currentLet[i]]);
                        buttons[i].reloadLabel();
                    }
                }
                if (agree.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    for (int i = 0; i < 6; i++) {
                        if (i % 3 == 1) {
                            if (words[correctWords[(i + 1) % 2]].substr((i % 3) * 2, ((i % 3) + 1) * 2).substr(0, 2) != letters[i % 3][currentLet[i]]) {
                                mistakes++;
                                generateWords();
                                break;
                            }
                        } else {
                            if (words[correctWords[i % 2]].substr((i % 3) * 2, ((i % 3) + 1) * 2).substr(0, 2) != letters[i % 3][currentLet[i]]) {
                                mistakes++;
                                generateWords();
                                break;
                            }
                        }
                        if (i == 5) {
                            isDone = true;
                        }
                    }
                }
            }
            justPressed = true;
        } else {
            justPressed = false;
        }
    }
}

void ShifrModule::render(sf::RenderWindow *window)
{
    std::array vertices =
        {
         sf::Vertex{{origin.x, origin.y}},
         sf::Vertex{{origin.x + side, origin.y}},
         sf::Vertex{{origin.x + side, origin.y + side}},
         sf::Vertex{{origin.x, origin.y + side}},
         sf::Vertex{{origin.x, origin.y}},
         };

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);

    for (int i = 0; i < 6; i++) {
        buttons[i].render(window);
    }
    agree.render(window);
    code.render(window);
}

void ShifrModule::generateWords()
{
    correctWords[0] = rand() % 12;
    correctWords[1] = rand() % 12;
    std::string morse{""};
    for (int i = 0; i < 6; i++) {
        if (i == 3) {
            morse.append("\n");
        }
        morse.append(" ");
        if (i % 3 == 1) {
            morse.append(morseCode[words[correctWords[(i + 1) % 2]].substr((i % 3) * 2, ((i % 3) + 1) * 2).substr(0, 2)]);
            continue;
        }
        morse.append(morseCode[words[correctWords[i % 2]].substr((i % 3) * 2, ((i % 3) + 1) * 2).substr(0, 2)]);
    }
    code = Button(Label(font, morse, sf::Color::White), origin, sf::Vector2f(side * 0.9, side * 0.15), sf::Color::Black);
    code.getShape()->setOrigin(code.getShape()->getGeometricCenter());
    code.getShape()->setPosition(origin + sf::Vector2f(side * 0.5f, side * 0.15));
    code.reloadLabel();
}
