#include <SFML/Graphics.hpp>
#include <string>
#include "label.h"
#include "button.h"
#include "basemodule.h"
#include "wiresmodule.h"

#include <iostream>

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
    float width = window->getSize().x;
    float height = window->getSize().y;

    Label infoText(font, "Загрузка...", sf::Color::White, 80);
    infoText.setPositionCenter({ width * 0.5f, height * 0.5f });
    window->clear(sf::Color::Black);
    infoText.render(window);
    window->display();

    Label display(font, "00:00", sf::Color::White, 50);
    display.setPositionCenter({ width * 0.05f, height * 0.05f });
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

    BaseModule* modules[6];

    float moduleSide;
    if (width * 2 <= height * 3) {
        moduleSide = 0.3f * width;
    } else {
        moduleSide = 0.45f * height;
    }
    sf::Vector2f origin;
    for (short i = 0; i < 6; i++) {
        origin = {width * 0.5f, height * 0.5f};
        if (i % 2 == 0) {
            origin += {0.f, -moduleSide};
        }
        if (i % 3 == 0) {
            origin += {moduleSide * -1.5f, 0.f};
        } else if (i % 3 == 1) {
            origin += {moduleSide * -0.5f, 0.f};
        } else {
            origin += {moduleSide * 0.5f, 0.f};
        }
        switch (moduleUIDs[i]) {
        case 1:
            modules[i] = new WiresModule(origin, moduleSide, "", font);
            break;
        default:
            modules[i] = new BaseModule(origin, moduleSide, "", font);
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
            modules[i]->process(window, int(time - timer.getElapsedTime().asSeconds()));
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

void startGame() {
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "235seconds", sf::Style::None, sf::State::Fullscreen);
    float width = window->getSize().x;
    float height = window->getSize().y;
    window->setFramerateLimit(60);
    int m[6]{0};

    sf::RectangleShape shape{{100.f, 200.f}};
    shape.setPosition({width * 0.1f, height * 0.1f});
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(4.f);
    shape.setOutlineColor(sf::Color::White);

    Button yesButton = Button({font, "Да!", sf::Color::Green}, &shape);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf:: Event::Closed>()) {
                window->close();
            }
        }
        window->clear(sf::Color::Black);

        if (yesButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
            shape.setOutlineColor(sf::Color(128, 128, 128));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                m[0] = 1;
                window->close();
            }
        } else {
            shape.setOutlineColor(sf::Color::White);
        }

        yesButton.render(window);

        window->display();
    }
    window->close();
    delete window;

    game(235, m);
}

int main() { // Это стартовое меню. Пока оно просто ждет нажатие в себя.
    unsigned int width = 640;
    unsigned int height = 360;
    sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode({ width, height }), "235seconds");
    window->setFramerateLimit(60);

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

        //window->close();

        window->display();
    }
    window->close();
    delete window;

    startGame();

    return 0;
}
