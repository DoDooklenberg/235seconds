#include <SFML/Graphics.hpp>
#include <string>
#include "label.h"
#include "button.h"
#include "basemodule.h"
#include "drawingmodule.h"
#include <iostream>
#include "particlesystem.h"

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

void lose(int neutralized) {} // Заглушка

void game(int time, int moduleUIDs[6], int maxMistakes) {
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

    Label display(font, "00:00", sf::Color::White, height * 0.08f);
    display.setPositionCenter({ width * 0.5f, height * 0.95f });
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

    char symbols[37]  = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string serial;
    for (int i = 0; i<3; i++) {
        serial += symbols[rand()%(10)];
    }
    for (int i = 0; i<9; i++) {
        serial += symbols[rand()%(37)];
    }
    Label LSerial(font, serial, sf::Color::White, height * 0.08f);
    LSerial.setPositionCenter({width * 0.5f, height * 0.05f});

    BaseModule* modules[6];

    float moduleSide;
    if (width * 0.8f * 2 <= height * 0.8f * 3) {
        moduleSide = 0.34f * width * 0.8f;
    } else {
        moduleSide = 0.51f * height * 0.8f;
    }
    sf::RectangleShape statuses[6]{sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide))};
    int mistakesCount[6]{0};
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
        statuses[i].setPosition(origin);
        statuses[i].setFillColor(sf::Color::Transparent);
        switch (moduleUIDs[i]) {
        case 1:
            modules[i] = new DrawingModule(origin + sf::Vector2f(moduleSide * 0.01f, moduleSide * 0.01f), moduleSide * 0.98f, serial, font);
            break;
        default:
            modules[i] = new BaseModule(origin + sf::Vector2f(moduleSide * 0.01f, moduleSide * 0.01f), moduleSide * 0.98f, serial, font);
            break;
        }
    }
    origin = {width * 0.5f, height * 0.5f};
    std::array border =
        {
         sf::Vertex{{origin.x - moduleSide * 1.51f, origin.y - moduleSide * 1.01f}},
         sf::Vertex{{origin.x + moduleSide * 1.51f, origin.y - moduleSide * 1.01f}},
         sf::Vertex{{origin.x + moduleSide * 1.51f, origin.y + moduleSide * 1.01f}},
         sf::Vertex{{origin.x - moduleSide * 1.51f, origin.y + moduleSide * 1.01f}},
         sf::Vertex{{origin.x  - moduleSide * 1.51f, origin.y - moduleSide * 1.01f}},
         };

    sf::CircleShape mistakes[maxMistakes];
    int amtMistakes = 0;

    for (short i = 0; i < maxMistakes; i++) {
        mistakes[i] = sf::CircleShape(width * 0.04f);
        mistakes[i].setFillColor(sf::Color::Transparent);
        mistakes[i].setOutlineColor(sf::Color::White);
        mistakes[i].setOutlineThickness(1.f);
        mistakes[i].setPosition({width * 0.91f, height * 0.1f + width * 0.1f * i});
    }

    timer.restart();
    bool wining = false;
    int neutralizedCount = 0;

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

        if (neutralizedCount == 6) {
            wining = true;
            window->close();
        }

        if (time - timer.getElapsedTime().asSeconds() <= 0 || amtMistakes > maxMistakes) {
            window->close();
        }

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

        amtMistakes = 0;
        neutralizedCount = 0;
        for (short i = 0; i < 6; i++) {
            modules[i]->process(window, int(time - timer.getElapsedTime().asSeconds()));
            amtMistakes += modules[i]->getMistakes();
            if (modules[i]->getIsDone()) {
                neutralizedCount++;
                if (!modules[i]->getIsBase()) {
                    statuses[i].setFillColor(sf::Color(0, 255, 0, 128));
                }
            } else if (modules[i]->getMistakes() != mistakesCount[i]) {
                mistakesCount[i] = modules[i]->getMistakes();
                statuses[i].setFillColor(sf::Color(255, 0, 0, 230));
            } else {
                statuses[i].setFillColor(sf::Color(255, 0, 0, std::make_unsigned_t<int>(statuses[i].getFillColor().a * 0.999f)));
            }
        }

        for (short i = 0; i < 6; i++) {
            modules[i]->render(window);
            window->draw(statuses[i]);
            if (i < maxMistakes) {
                if (i < amtMistakes) {
                    mistakes[i].setFillColor(sf::Color::Red);
                }
                window->draw(mistakes[i]);
            }
        }
        display.render(window);
        LSerial.render(window);
        window->draw(border.data(), border.size(), sf::PrimitiveType::LineStrip);

        window->display();
    }
    window->close();
    delete window;
    if (wining) {
        win(time - timer.getElapsedTime().asSeconds());
    } else {
        lose(neutralizedCount);
    }
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

    ParticleSystem particles(7000);

    sf::Clock clock;

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
        exitButton{{font, "Назад", sf::Color::White}, {width * 0.35f, height * 0.85f}, {uSize * 0.12f, uSize * 0.06f}, sf::Color::Magenta},
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
                    int haveModule[6]{0};
                    for (int i = 0; i < (activeButton + 1) * 2; i++) {
                        int currentModule = rand() % 1 + 1;
                        /*while (haveModule[currentModule]) {
                            currentModule = rand() % 1 + 1;
                        }*/ // TODO раскомментить когда модулей будет 6
                        haveModule[currentModule] = 1;
                        m[i] = currentModule;
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

        sf::Vector2i mouse = sf::Mouse::getPosition(*window);
        particles.setEmitter(window->mapPixelToCoords(mouse));

        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        window->clear(sf::Color::Black);

        startButton.render(window);
        exitButton.render(window);
        easyButton.render(window);
        mediumButton.render(window);
        hardButton.render(window);
        window->draw(particles);

        window->display();
    }
    window->close();
    delete window;

    if (startGame) {
        game(235, m, (activeButton - 2) * -1);
    } else {
        main();
    }
}

int main() { // Это стартовое меню.

    sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "235seconds", sf::Style::None, sf::State::Fullscreen);
    window->setFramerateLimit(60);

    unsigned int width = window->getSize().x;
    unsigned int height = window->getSize().y;

    bool ifPlay = false;

    Label gameName (font, "235 seconds", sf::Color::White, height * 0.1f);
    gameName.setPositionCenter(sf::Vector2f(width * 0.5f, height * 0.06f));

    Button playButton(Label(font, "Играть", sf::Color::White), sf::Vector2f(0.f, 0.f), sf::Vector2f(width * 0.1f, height * 0.1f), sf::Color::Magenta);
    playButton.getShape()->setOrigin(playButton.getShape()->getGeometricCenter());
    playButton.getShape()->setPosition({width * 0.5f, height * 0.7f});
    playButton.reloadLabel();

    Button exitButton(Label(font, "Выход", sf::Color::White), sf::Vector2f(0.f, 0.f),sf::Vector2f(width * 0.1f, height * 0.1f), sf::Color::Magenta);
    exitButton.getShape()->setOrigin(playButton.getShape()->getGeometricCenter());
    exitButton.getShape()->setPosition({width * 0.5f, height * 0.85f});
    exitButton.reloadLabel();

    Label instruction(font, "Инструкция", sf::Color::White, height * 0.05f);
    instruction.setPositionCenter(sf::Vector2f(width * 0.5f, height * 0.2f));

    sf::RectangleShape QrBase({height * 0.3f, height * 0.3f});
    QrBase.setOrigin(QrBase.getGeometricCenter());
    QrBase.setPosition(sf::Vector2f(width * 0.5f, height * 0.4f));

    ParticleSystem particles(7000);

    sf::Clock clock;

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
                return 0;
            }
            else if (playButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                ifPlay = true;
                window->close();
            }
            else if (exitButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                window->close();
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(*window);
        particles.setEmitter(window->mapPixelToCoords(mouse));

        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        window->clear(sf::Color::Black);

        gameName.render(window);
        playButton.render(window);
        exitButton.render(window);
        instruction.render(window);
        window->draw(particles);
        window->draw(QrBase);

        window->display();
    }
    window->close();
    delete window;

    if (ifPlay)
    {
        startGame();
    }
    return 0;
}
