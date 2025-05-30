#include "clickermodule.h"

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

    for (char ch : serial) {
        if (isdigit(ch)) {
            numbersCount++;
            numSum += int(ch - '0');
        }
        else {lettersCount++;}

        }

    correctClickAmount = ((numSum * lettersCount) + numbersCount * 5) % 100;
}

void ClickerModule::process(sf::RenderWindow *window, int time)
{
    if (!isDone) {
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
            if (!isMousePressedLastFrame_2) {
                if (count == correctClickAmount) {
                    isDone = true;
                }
                else {
                    mistakes++;
                    count = 0;
                    displayCount.setString(std::to_string(count));
                }
                isMousePressedLastFrame_2 = true;
            }
        }
        else{
           confirmButton.getLabel()->setColor(sf::Color::Red);
           isMousePressedLastFrame_2 = false;
        }
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
