#include "label.h"
#include <SFML/Graphics.hpp>
#include <string>

Label::Label(sf::Font newFont, std::string string, sf::Color newColor, int newSize, sf::Vector2f newPos) : font{newFont}, content{string}, color{newColor}, size{newSize}, pos{newPos}{}

void Label::render(sf::RenderWindow *window)
{
    sf::Text text = sf::Text(font, sf::String::fromUtf8(content.begin(), content.end()), size);
    text.setFillColor(color);
    text.setPosition(pos);
    window->draw(text);
}

void Label::setString(std::string string)
{
    content = string;
}

void Label::setPosition(sf::Vector2f newPos)
{
    pos = newPos;
}

void Label::setPositionCenter(sf::Vector2f newPos)
{
    sf::Text text = sf::Text(font, sf::String::fromUtf8(content.begin(), content.end()), size);
    text.setFillColor(color);
    text.setPosition(pos);
    pos = { newPos.x - text.getLocalBounds().size.x / 2, newPos.y - text.getLocalBounds().size.y / 2 };
}

void Label::setColor(sf::Color newColor)
{
    color = newColor;
}
