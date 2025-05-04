#include "label.h"
#include <string>

void Label::reloadPos()
{
    sf::Text text = sf::Text(font, sf::String::fromUtf8(content.begin(), content.end()), size);
    text.setPosition(pos);
    pos = pos - (text.getGlobalBounds().position - pos);
    /*
     * При задании позиции текста по факту текст чуть сдвинут от задаваемых координат,
     * причем сдвинут по разному для каждого шрифта. Костыль, но по-другому не работает.
     */
}

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
    reloadPos();
}

void Label::setPositionCenter(sf::Vector2f newPos)
{
    sf::Text text = sf::Text(font, sf::String::fromUtf8(content.begin(), content.end()), size);
    text.setFillColor(color);
    text.setPosition(pos);
    pos = { newPos.x - text.getGlobalBounds().size.x / 2, newPos.y - text.getGlobalBounds().size.y / 2 };
    reloadPos();
}

void Label::setColor(sf::Color newColor)
{
    color = newColor;
}

void Label::setSize(int newSize)
{
    size = newSize;
}

sf::FloatRect Label::getBounds()
{
    return sf::Text(font, sf::String::fromUtf8(content.begin(), content.end()), size).getGlobalBounds();
}

int Label::getSize()
{
    return sf::Text(font, sf::String::fromUtf8(content.begin(), content.end()), size).getCharacterSize();
}
