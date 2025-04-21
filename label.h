#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>
#include <string>

class Label
{
private:
    sf::Font font;
    std::string content;
    sf::Color color;
    int size;
    sf::Vector2f pos;
    void reloadPos();
public:
    Label(sf::Font newFont, std::string string, sf::Color color = sf::Color::Black, int size = 10, sf::Vector2f pos = { 0, 0 });
    void render(sf::RenderWindow* window);
    void setString(std::string string);
    void setPosition(sf::Vector2f newPos);
    void setPositionCenter(sf::Vector2f newPos);
    void setColor(sf::Color newColor);
    void setSize(int newSize);
    int getSize();
    sf::FloatRect getBounds();
};

#endif // LABEL_H
