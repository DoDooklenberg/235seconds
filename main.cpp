#include <SFML/Graphics.hpp>

int main() {
    unsigned int width = 640;
    unsigned int height = 360;
    sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode({ width, height }), "240seconds");
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf:: Event::Closed>()) {
                window->close();
            }
        }
        window->clear();

        window->display();
    }
    window->close();
    delete window;
return 0;
}
