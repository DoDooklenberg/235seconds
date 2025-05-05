#include <SFML/Graphics.hpp>
#include <string>
#include "label.h"
#include "button.h"
#include "basemodule.h"
#include "drawingmodule.h"
#include "clickermodule.h"

const sf::Font font("font.ttf");

int main();

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
    float uSize = (width + height) / 2;

    Label infoText(font, "Загрузка...", sf::Color::White, uSize * 0.12f);
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
            modules[i] = new DrawingModule(origin, moduleSide, "", font);
            break;
        case 2:
            modules[i] = new ClickerModule(origin, moduleSide, "", font);
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
    std::srand(std::time({}));
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "235seconds", sf::Style::None, sf::State::Fullscreen);
    float width = window->getSize().x;
    float height = window->getSize().y;
    float uSize = (width + height) / 2;
    window->setFramerateLimit(60);
    int m[6], buffer[2];
    bool startGame = false;
    int activeButton = -1;

    sf::RectangleShape* buttons[3]{new sf::RectangleShape{{width * 0.4f, height * 0.1f}},
                                   new sf::RectangleShape{{width * 0.4f, height * 0.1f}},
                                   new sf::RectangleShape{{width * 0.4f, height * 0.1f}}};
    buttons[0]->setPosition({width * 0.3f, height * 0.27f});
    buttons[0]->setFillColor(sf::Color::Transparent);
    buttons[1]->setPosition({width * 0.3f, height * 0.4f});
    buttons[1]->setFillColor(sf::Color::Transparent);
    buttons[2]->setPosition({width * 0.3f, height * 0.53f});
    buttons[2]->setFillColor(sf::Color::Transparent);

    Button startButton{{font, "Начать", sf::Color::White}, {width * 0.55f, height * 0.85f}, {uSize * 0.12f, uSize * 0.06f}, sf::Color(80, 80, 80)},
        exitButton{{font, "Выход", sf::Color::White}, {width * 0.35f, height * 0.85f}, {uSize * 0.12f, uSize * 0.06f}, sf::Color::Magenta},
        easyButton{{font, "Легкий", sf::Color::White}, buttons[0]},
        mediumButton{{font, "Средний", sf::Color::White}, buttons[1]},
        hardButton{{font, "Сложный", sf::Color::White}, buttons[2]};

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf:: Event::Closed>()) {
                window->close();
            } else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (startButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window))) && activeButton != -1) {
                    for (int i = 0; i < (activeButton + 1) * 2; i++) {
                        m[i] = rand() % 1 + 1;
                    }
                    for (int i = 0; i < 60; i++) {
                        buffer[0] = rand() % 6;
                        buffer[1] = m[buffer[0]];
                        m[buffer[0]] = m[i % 6];
                        m[i % 6] = buffer[1];
                    }
                    startGame = true;
                    window->close();
                } else if (exitButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    window->close();
                } else if (easyButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    easyButton.getLabel()->setColor(sf::Color::Magenta);
                    mediumButton.getLabel()->setColor(sf::Color::White);
                    hardButton.getLabel()->setColor(sf::Color::White);
                    activeButton = 0;
                    startButton.getShape()->setFillColor(sf::Color::Magenta);
                } else if (mediumButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    easyButton.getLabel()->setColor(sf::Color::White);
                    mediumButton.getLabel()->setColor(sf::Color::Magenta);
                    hardButton.getLabel()->setColor(sf::Color::White);
                    activeButton = 1;
                    startButton.getShape()->setFillColor(sf::Color::Magenta);
                } else if (hardButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    easyButton.getLabel()->setColor(sf::Color::White);
                    mediumButton.getLabel()->setColor(sf::Color::White);
                    hardButton.getLabel()->setColor(sf::Color::Magenta);
                    activeButton = 2;
                    startButton.getShape()->setFillColor(sf::Color::Magenta);
                }
            }
        }
        window->clear(sf::Color::Black);

        startButton.render(window);
        exitButton.render(window);
        easyButton.render(window);
        mediumButton.render(window);
        hardButton.render(window);

        window->display();
    }
    window->close();
    delete window;

    if (startGame) {
        m[0] = 2;
        game(235, m);
    } else {
        main();
    }
}

int main() { // Это стартовое меню. Пока оно просто ждет нажатие в себя.
    unsigned int width = 640;
    unsigned int height = 360;
    sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode({ width, height }), "235seconds");
    window->setFramerateLimit(60);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            } else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window->setView(sf::View(visibleArea));
            } else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
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
