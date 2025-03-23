#include <SFML/Graphics.hpp>
#include <string>
#include "label.h"
#include "basemodule.h"

const sf::Font font("font.ttf");

void win(int time) {
    unsigned int width = 1280;
    unsigned int height = 720;
    sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode({ width, height }), "Winning window",sf::Style::None);
    window->setFramerateLimit(60);
    sf::sleep(sf::milliseconds(200));

    Label message(font, "Вы выжили!", sf::Color::White, 100);
    message.setPositionCenter({width * 0.5f, height * 0.5f});

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf:: Event::Closed>()) {
                window->close();
            }  else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
                {
                    window->close();
                }
            }
        }
        window->clear(sf::Color::Black);

        message.render(window);

        window->display();
    }
    window->close();
    delete window;
};

void game(int time, int moduleUIDs[6]) {
    sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "235seconds", sf::Style::None, sf::State::Fullscreen);
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);
    float width = window->getSize().x;
    float height = window->getSize().y;

    Label infoText(font, "Загрузка...", sf::Color::White, 80);
    infoText.setPositionCenter({ width * 0.5f, height * 0.5f });
    window->clear(sf::Color::Black);
    infoText.render(window);
    window->display();

    Label display(font, "00:00", sf::Color::White, 50);
    display.setPositionCenter({ width * 0.1f, height * 0.05f });
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

    sf::Clock timer;
    timer.stop();

    unsigned int moduleSide;
    BaseModule* modules[6];
    for (short i = 0; i < 6; i++) {
        if (moduleUIDs[i]) {
            // TODO Добавить нужные модули
        } else {
            modules[i] = new BaseModule({i*150.f, i*150.f}, {(i + 1)*150.f, (i + 1)*150.f}, 10);
        }
    }

    infoText.setString("Нажмите enter чтобы начать.");
    infoText.setPositionCenter({ width * 0.5f, height * 0.5f });

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf:: Event::Closed>()) {
                window->close();
            }
        }
        window->clear(sf::Color::Black);

        infoText.render(window);

        window->display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            break;
        }
    }

    timer.restart();

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf:: Event::Closed>()) {
                window->close();
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
                {
                    window->close();
                }
            }
        }
        window->clear(sf::Color::Black);

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
        for (short i = 0; i < 6; i++) {
            modules[i]->process(int(time - timer.getElapsedTime().asSeconds()));
        }

        for (short i = 0; i < 6; i++) {
            modules[i]->render(window);
        }
        display.render(window);

        window->display();
    }
    window->close();
    delete window;
}

void startGame() { // Это будет меню выбора сложности. Оно будет выбирать модули и время для игры.
    int m[6]{0};
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

        window->close();

        window->display();
    }
    window->close();
    delete window;

    startGame();

    return 0;
}
