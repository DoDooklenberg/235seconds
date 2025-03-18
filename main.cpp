#include <SFML/Graphics.hpp>
#include "label.h"
#include <string>

void game(int time, int modules[6]) {
    sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "235seconds", sf::Style::None, sf::State::Fullscreen);
    window->setVerticalSyncEnabled(true);
    float width = window->getSize().x;
    float height = window->getSize().y;

    sf::Font font("font.ttf");

    Label infoText(font, "Загрузка...", sf::Color::White, 80);
    infoText.setPositionCenter({ width * 0.5f, height * 0.5f });

    window->clear(sf::Color::Black);
    infoText.render(window);
    window->display();

    for (int i = 0; i >= 0; i++){
        i++;
    }
    for (int i = 0; i >= 0; i++){
        i++;
    }
    for (int i = 0; i >= 0; i++){
        i++;
    }

    Label display(font, "00:00", sf::Color::White, 50);
    display.setPositionCenter({ width * 0.1f, height * 0.05f });

    sf::Clock timer;
    timer.stop();
    std::string minutes, seconds;
    if (time % 60 < 10) {
        seconds = "0" + std::to_string(time % 60);
    } else {
        seconds = std::to_string(time % 60);
    }
    if (time / 60 < 10) {
        minutes = "0" + std::to_string(time / 60);
    } else {
        minutes = std::to_string(time / 60);
    }
    display.setString(minutes + ":" + seconds);

    infoText.setString("Нажмите enter чтобы начать.");
    infoText.setPositionCenter({ width * 0.5f, height * 0.5f });
    bool playing = false;

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf:: Event::Closed>()) {
                window->close();
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::Enter)
                {
                    playing = true;
                }
            }
        }
        window->clear(sf::Color::Black);
        infoText.render(window);

        if (playing) {
            break;
        }

        window->display();
    }

    timer.start();

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf:: Event::Closed>()) {
                window->close();
            }
        }
        window->clear(sf::Color::Black);

        display.render(window);

        if (seconds != std::to_string(int(time - timer.getElapsedTime().asSeconds()) % 60)) {
            if (int(time - timer.getElapsedTime().asSeconds()) % 60 < 10) {
                seconds = "0" + std::to_string(int(time - timer.getElapsedTime().asSeconds()) % 60);
            } else {
                seconds = std::to_string(int(time - timer.getElapsedTime().asSeconds()) % 60);
            }
            if (int(time - timer.getElapsedTime().asSeconds()) / 60 < 10) {
                minutes = "0" + std::to_string(int(time - timer.getElapsedTime().asSeconds()) / 60);
            } else {
                minutes = std::to_string(int(time - timer.getElapsedTime().asSeconds()) / 60);
            }
            display.setString(minutes + ":" + seconds);
        }

        window->display();
    }
    window->close();
    delete window;
}

void startGame() { // Это будет меню выбора сложности. Оно будет выбирать модули и время для игры.
    int m[6]{1};
    game(235, m);
}

int main() { // Это стартовое меню. Пока оно просто ждет нажатие в себя.
    unsigned int width = 640;
    unsigned int height = 360;
    sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode({ width, height }), "235seconds");
    window->setFramerateLimit(60);
    sf::sleep(sf::milliseconds(200));

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf:: Event::Closed>()) {
                window->close();
            } else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window->setView(sf::View(visibleArea));
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                window->close();
            }
        }
        window->clear(sf::Color::White);

        window->display();
    }
    window->close();
    delete window;

    startGame();

    return 0;
}
