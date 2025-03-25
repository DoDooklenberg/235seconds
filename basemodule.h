#ifndef BASEMODULE_H
#define BASEMODULE_H

#include <SFML/Graphics.hpp>
#include <string>

class BaseModule // Базовый класс модуля. От него наследованы все модули
{
protected:
    sf::Vector2f origin; // Координаты левого верхнего угла модуля(От него считается где рисовать все внутренние элементы)
    float side; // Длинна стороны модуля(Насколько далеко от origin можно рисовать)
    std::string serial; // Серийный номер, он будет изпользоваться в некоторых головоломках
    bool isDone = false;
    sf::Font font;
public:
    BaseModule(sf::Vector2f newOrigin, float newSide, std::string newSerial, sf::Font newFont); // Конструктор, ничего кроме записи в переменные не делает
    bool isPosInModule(sf::Vector2f pos); // Эта функция будет определять по переданным координатам, принадлежат ли они модулю.
    bool getIsDone();
    virtual void process(sf::RenderWindow* window, int time); // Логика модуля
    virtual void render(sf::RenderWindow* window); // Отрисовка модуля
};

#endif // BASEMODULE_H
