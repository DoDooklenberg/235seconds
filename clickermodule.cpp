#include "clickermodule.h"
#include <iostream>

ClickerModule::ClickerModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont) :
    BaseModule(newOrigin, newSide, newSerial, newFont),
    mainButton{Label(font, "ЖМИ", sf::Color::Red), origin+sf::Vector2f(side*0.25f, side*0.4f), sf::Vector2f(side*0.5f,side*0.2f), sf::Color::White},
    confirmButton{Label(font, "ПОДТВЕРДИТЬ", sf::Color::Red), origin+sf::Vector2f(side*0.3f, side*0.65f), sf::Vector2f(side*0.4f,side*0.1f), sf::Color::White},
    displayCount{font,"0", sf::Color::White, int(side*0.1f)}

{
    displayCount.setPositionCenter(origin+sf::Vector2f(side*0.5f, side*0.1f));
    setCorrectClickAmount();


}
void ClickerModule::setCorrectClickAmount()
{
    int lettersCount = 0;
    int numbersCount = 0;
    int numSum = 0;
    int lCount = 0;
    int dCount = 0;

    for (char ch : serial) {
        if (isdigit(ch)) {
            numbersCount++;
            numSum += int(ch - '0');
        }
        else {lettersCount++;}

        if (ch == 'L') {lCount++;}
        else if (ch == 'D') {dCount++;}
        }

    correctClickAmount = ((numSum * lettersCount) + (lCount * dCount * numbersCount) + 10) % 100;
    std::cout << correctClickAmount << std::endl;
}

void ClickerModule::process(sf::RenderWindow *window, int time)
{
    if (mainButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        mainButton.getLabel()->setColor(sf::Color::Green);
        if (!isMousePressedLastFrame) {
            count++;
            displayCount.setString(std::to_string(count));
            isMousePressedLastFrame = true;
        }

    }
    else{
        mainButton.getLabel()->setColor(sf::Color::Red);
        isMousePressedLastFrame = false;
    }

    if (confirmButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        confirmButton.getLabel()->setColor(sf::Color::Green);
        if (!isMousePressedLastFrame) {
            if (count == correctClickAmount) {
                isDone = true;
                isMousePressedLastFrame = true;
            }
            else {
                mistakes++;
                count = 0;
                isMousePressedLastFrame = true;
            }
        }
    }
    else{
       confirmButton.getLabel()->setColor(sf::Color::Red);
//        isMousePressedLastFrame = false;
    }
}

void ClickerModule::render(sf::RenderWindow *window)
{
    mainButton.render(window);
    confirmButton.render(window);
    std::array vertices =
        {
         sf::Vertex{{origin.x, origin.y}},
         sf::Vertex{{origin.x + side, origin.y}},
         sf::Vertex{{origin.x + side, origin.y + side}},
         sf::Vertex{{origin.x, origin.y + side}},
         sf::Vertex{{origin.x, origin.y}},
         };

    window->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);

    displayCount.render(window);
}
