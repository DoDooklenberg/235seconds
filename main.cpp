#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "label.h"
#include "button.h"
#include "basemodule.h"
#include "drawingmodule.h"
#include "lightbulbsmodule.h"
#include "wiresmodule.h"
#include "particlesystem.h"
#include "levermodule.h"
#include "clickermodule.h"
#include "shifrmodule.h"

const sf::Font font("font.ttf");
sf::Music music;

int main();

void win(int time) {
    unsigned int width = unsigned(sf::VideoMode::getFullscreenModes()[0].size.x * 0.67);
    unsigned int height = unsigned(sf::VideoMode::getFullscreenModes()[0].size.y * 0.67);
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Winning window", sf::Style::None);
    window->setFramerateLimit(60);

    Label message(font, "Вы выжили!", sf::Color::White, width / 15);
    message.setPositionCenter({ width * 0.5f, height * 0.5f });

    std::string timeStr = "Время: ";
    if (time / 60 < 10) {
        timeStr += "0" + std::to_string(time / 60) + ":";
    }
    else {
        timeStr += std::to_string(time / 60) + ":";
    }
    if (time % 60 < 10) {
        timeStr += "0" + std::to_string(time % 60);
    }
    else {
        timeStr += std::to_string(time % 60);
    }

    Label timeLabel(font, timeStr, sf::Color::White, width / 40);
    timeLabel.setPositionCenter({ width * 0.5f, height * 0.35f });

    Button exitButton(Label(font, "Выход", sf::Color::White),
        sf::Vector2f(width * 0.1f, height * 0.85f),
        sf::Vector2f(width * 0.15f, height * 0.1f),
        sf::Color::Magenta);

    Button playAgainButton(Label(font, "Играть ещё раз", sf::Color::White),
        sf::Vector2f(width * 0.75f, height * 0.85f),
        sf::Vector2f(width * 0.15f, height * 0.1f),
        sf::Color::Magenta);

    sf::SoundBuffer clickBuf("click.wav");
    sf::Sound click(clickBuf);
    click.setVolume(20.f);

    bool playAgain = false;

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
                    window->close();
                }
            }
            else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (exitButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    click.play();
                    window->close();
                }
                else if (playAgainButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    click.play();
                    window->close();
                    playAgain = true;
                }
            }
        }
        window->clear(sf::Color::Black);

        message.render(window);
        timeLabel.render(window);
        exitButton.render(window);
        playAgainButton.render(window);

        window->display();
    }
    window->close();
    delete window;

    if (playAgain) {
        main();
    }
}

void lose(int neutralized, int difficulty) {
    unsigned int width = unsigned(sf::VideoMode::getFullscreenModes()[0].size.x * 0.67);
    unsigned int height = unsigned(sf::VideoMode::getFullscreenModes()[0].size.y * 0.67);
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Winning window", sf::Style::None);
    window->setFramerateLimit(60);

    Label message(font, "Вы проиграли!", sf::Color::White, width / 15);
    message.setPositionCenter({ width * 0.5f, height * 0.5f });


    int totalModules = (difficulty == 0) ? 2 : (difficulty == 1) ? 4 : 6;


    std::string modulesStr = "Нейтрализовано модулей: " + std::to_string(neutralized - (6 - totalModules)) + " из " + std::to_string(totalModules);
    Label modulesLabel(font, modulesStr, sf::Color::White, width / 40);
    modulesLabel.setPositionCenter({ width * 0.5f, height * 0.65f });

    Button exitButton(Label(font, "Выход", sf::Color::White),
        sf::Vector2f(width * 0.1f, height * 0.85f),
        sf::Vector2f(width * 0.15f, height * 0.1f),
        sf::Color::Magenta);

    Button playAgainButton(Label(font, "Играть ещё раз", sf::Color::White),
        sf::Vector2f(width * 0.75f, height * 0.85f),
        sf::Vector2f(width * 0.15f, height * 0.1f),
        sf::Color::Magenta);

    sf::SoundBuffer clickBuf("click.wav");
    sf::Sound click(clickBuf);
    click.setVolume(20.f);

    bool playAgain = false;

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
                    window->close();
                }
            }
            else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (exitButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    click.play();
                    window->close();
                }
                else if (playAgainButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    click.play();
                    window->close();
                    playAgain = true;
                }
            }
        }
        window->clear(sf::Color::Black);

        message.render(window);
        modulesLabel.render(window);
        exitButton.render(window);
        playAgainButton.render(window);

        window->display();
    }
    window->close();
    delete window;

    if (playAgain) {
        main();
    }
}

void game(int time, int moduleUIDs[6], int maxMistakes) {
    int difficulty = (maxMistakes == 2) ? 0 : (maxMistakes == 1) ? 1 : 2;
    music.stop();
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "235seconds", sf::Style::None, sf::State::Fullscreen);
    window->setVerticalSyncEnabled(true);
    float width = window->getSize().x;
    float height = window->getSize().y;
    float uSize = (width + height) / 2;

    sf::SoundBuffer beepBuf("beep.wav"), boomBuf("boom.wav"), winBuf("win.wav"), errorBuf("error.wav"), doneBuf("done.wav");
    sf::Sound beep(beepBuf), boom(boomBuf), winSound(winBuf), error(errorBuf), done(doneBuf);
    error.setVolume(10.f);

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
    }
    else {
        seconds = std::to_string(time % 60);
    }
    if (time / 60 < 10) {
        minutes = "0" + std::to_string(time / 60);
    }
    else {
        minutes = std::to_string(time / 60);
    }
    display.setString(minutes + ":" + seconds);

    sf::Clock timer;

    char symbols[37] = "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ";
    std::string serial;
    for (int i = 0; i < 3; i++) {
        serial += symbols[rand() % (10)];
    }
    for (int i = 0; i < 9; i++) {
        serial += symbols[rand() % (37)];
    }
    Label LSerial(font, serial, sf::Color::White, height * 0.08f);
    LSerial.setPositionCenter({ width * 0.5f, height * 0.05f });

    BaseModule* modules[6];

    float moduleSide;
    if (width * 0.8f * 2 <= height * 0.8f * 3) {
        moduleSide = 0.34f * width * 0.8f;
    }
    else {
        moduleSide = 0.51f * height * 0.8f;
    }
    sf::RectangleShape statuses[6]{ sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)),
                                   sf::RectangleShape(sf::Vector2f(moduleSide, moduleSide)) };
    int mistakesCount[6]{ 0 };
    sf::Vector2f origin;
    for (short i = 0; i < 6; i++) {
        origin = { width * 0.5f, height * 0.5f };
        if (i % 2 == 0) {
            origin += {0.f, -moduleSide};
        }
        if (i % 3 == 0) {
            origin += {moduleSide * -1.5f, 0.f};
        }
        else if (i % 3 == 1) {
            origin += {moduleSide * -0.5f, 0.f};
        }
        else {
            origin += {moduleSide * 0.5f, 0.f};
        }
        statuses[i].setPosition(origin);
        statuses[i].setFillColor(sf::Color::Transparent);
        switch (moduleUIDs[i]) {
        case 1:
            modules[i] = new DrawingModule(origin + sf::Vector2f(moduleSide * 0.01f, moduleSide * 0.01f), moduleSide * 0.98f, serial, font);
            break;
        case 2:
            modules[i] = new WiresModule(origin + sf::Vector2f(moduleSide * 0.01f, moduleSide * 0.01f), moduleSide * 0.98f, serial, font);
            break;
        case 3:
            modules[i] = new LeverModule(origin + sf::Vector2f(moduleSide * 0.01f, moduleSide * 0.01f), moduleSide * 0.98f, serial, font);
            break;
        case 4:
            modules[i] = new LightBulbsModule(origin + sf::Vector2f(moduleSide * 0.01f, moduleSide * 0.01f), moduleSide * 0.98f, serial, font);
            break;
        case 5:
            modules[i] = new ClickerModule(origin + sf::Vector2f(moduleSide * 0.01f, moduleSide * 0.01f), moduleSide * 0.98f, serial, font);
            break;
        case 6:
            modules[i] = new ShifrModule(origin + sf::Vector2f(moduleSide * 0.01f, moduleSide * 0.01f), moduleSide * 0.98f, serial, font);
            break;
        default:
            modules[i] = new BaseModule(origin + sf::Vector2f(moduleSide * 0.01f, moduleSide * 0.01f), moduleSide * 0.98f, serial, font);
            break;
        }
    }
    origin = { width * 0.5f, height * 0.5f };
    std::array border =
        {
         sf::Vertex{{origin.x - moduleSide * 1.51f, origin.y - moduleSide * 1.01f}},
         sf::Vertex{{origin.x + moduleSide * 1.51f, origin.y - moduleSide * 1.01f}},
         sf::Vertex{{origin.x + moduleSide * 1.51f, origin.y + moduleSide * 1.01f}},
         sf::Vertex{{origin.x - moduleSide * 1.51f, origin.y + moduleSide * 1.01f}},
         sf::Vertex{{origin.x  - moduleSide * 1.51f, origin.y - moduleSide * 1.01f}},
         };
    std::vector<sf::CircleShape> mistakes;
    int amtMistakes = 0;

    for (short i = 0; i < maxMistakes; i++) {
        mistakes.push_back(sf::CircleShape(width * 0.035f));
        mistakes.at(i).setFillColor(sf::Color::Transparent);
        mistakes.at(i).setOutlineColor(sf::Color::White);
        mistakes.at(i).setOutlineThickness(1.f);
        mistakes.at(i).setPosition({ width * 0.92f, height * 0.1f + width * 0.1f * i });
    }

    timer.restart();
    bool wining = false;
    int neutralizedCount = 0;

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
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

        if (time - timer.getElapsedTime().asSeconds() < 30) {
            display.setColor(sf::Color::Red);
        }
        if (time - timer.getElapsedTime().asSeconds() < 10) {
            beep.play();
        }

        if (seconds != std::to_string(int(time - timer.getElapsedTime().asSeconds()) % 60) && seconds != "0" + std::to_string(int(time - timer.getElapsedTime().asSeconds()) % 60)) {
            beep.play();
            if (int(time - timer.getElapsedTime().asSeconds()) % 60 < 10) {
                seconds = "0" + std::to_string(int(time - timer.getElapsedTime().asSeconds()) % 60);
            }
            else {
                seconds = std::to_string(int(time - timer.getElapsedTime().asSeconds()) % 60);
            }
            if (int(time - timer.getElapsedTime().asSeconds()) / 60 < 10) {
                minutes = "0" + std::to_string(int(time - timer.getElapsedTime().asSeconds()) / 60);
            }
            else {
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
            }
            else if (modules[i]->getMistakes() != mistakesCount[i]) {
                mistakesCount[i] = modules[i]->getMistakes();
                error.play();
                statuses[i].setFillColor(sf::Color(255, 0, 0, 230));
            }
            else {
                statuses[i].setFillColor(sf::Color(255, 0, 0, std::make_unsigned_t<int>(statuses[i].getFillColor().a * 0.99f)));
            }
        }

        for (short i = 0; i < 6; i++) {
            modules[i]->render(window);
            window->draw(statuses[i]);
            if (i < maxMistakes) {
                if (i < amtMistakes) {
                    mistakes.at(i).setFillColor(sf::Color::Red);
                }
                window->draw(mistakes.at(i));
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
        winSound.play();
        win(time - timer.getElapsedTime().asSeconds());
    }
    else {
        boom.play();
        lose(neutralizedCount, difficulty);
    }
}

void startGame() {
    std::srand(std::time({}));
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "235seconds", sf::Style::None, sf::State::Fullscreen);
    float width = window->getSize().x;
    float height = window->getSize().y;
    float uSize = (width + height) / 2;
    window->setFramerateLimit(60);
    int m[6]{ 0 }, buffer[2]{ 0 };

    sf::SoundBuffer clickBuf("click.wav");
    sf::Sound click(clickBuf);
    click.setVolume(20.f);

    ParticleSystem particles(7000);

    sf::Clock clock;

    bool startGame = false;
    int activeButton = -1;

    sf::RectangleShape* buttons[3]{ new sf::RectangleShape{{width * 0.4f, height * 0.1f}},
                                   new sf::RectangleShape{{width * 0.4f, height * 0.1f}},
                                   new sf::RectangleShape{{width * 0.4f, height * 0.1f}} };
    buttons[0]->setPosition({ width * 0.3f, height * 0.27f });
    buttons[0]->setFillColor(sf::Color::Transparent);
    buttons[1]->setPosition({ width * 0.3f, height * 0.4f });
    buttons[1]->setFillColor(sf::Color::Transparent);
    buttons[2]->setPosition({ width * 0.3f, height * 0.53f });
    buttons[2]->setFillColor(sf::Color::Transparent);

    Button startButton{ {font, "Начать", sf::Color::White}, {width * 0.55f, height * 0.85f}, {uSize * 0.12f, uSize * 0.06f}, sf::Color(80, 80, 80) },
        exitButton{ {font, "Назад", sf::Color::White}, {width * 0.35f, height * 0.85f}, {uSize * 0.12f, uSize * 0.06f}, sf::Color::Magenta },
        easyButton{ {font, "Легкий", sf::Color::White}, buttons[0] },
        mediumButton{ {font, "Средний", sf::Color::White}, buttons[1] },
        hardButton{ {font, "Сложный", sf::Color::White}, buttons[2] };

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (startButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window))) && activeButton != -1) {
                    click.play();
                    int haveModule[6]{ 0 };
                    int totalModules = (activeButton == 0) ? 2 : (activeButton == 1) ? 4 : 6;
                    for (int i = 0; i < totalModules; i++) {
                        int currentModule = rand() % 6;
                        while (haveModule[currentModule]) {
                            currentModule = rand() % 6;
                        }
                        haveModule[currentModule] = 1;
                        m[i] = currentModule + 1;
                    }
                    for (int i = totalModules; i < 6; i++) {
                        m[i] = 0;
                    }
                    for (int i = 0; i < 60; i++) {
                        buffer[0] = rand() % 6;
                        buffer[1] = m[buffer[0]];
                        m[buffer[0]] = m[i % 6];
                        m[i % 6] = buffer[1];
                    }
                    startGame = true;
                    window->close();
                }
                else if (exitButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    click.play();
                    window->close();
                }
                else if (easyButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    click.play();
                    easyButton.getLabel()->setColor(sf::Color::Magenta);
                    mediumButton.getLabel()->setColor(sf::Color::White);
                    hardButton.getLabel()->setColor(sf::Color::White);
                    activeButton = 0;
                    startButton.getShape()->setFillColor(sf::Color::Magenta);
                }
                else if (mediumButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    click.play();
                    easyButton.getLabel()->setColor(sf::Color::White);
                    mediumButton.getLabel()->setColor(sf::Color::Magenta);
                    hardButton.getLabel()->setColor(sf::Color::White);
                    activeButton = 1;
                    startButton.getShape()->setFillColor(sf::Color::Magenta);
                }
                else if (hardButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
                    click.play();
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
    }
    else {
        main();
    }
}

int main() {
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "235seconds", sf::Style::None, sf::State::Fullscreen);
    window->setFramerateLimit(60);

    unsigned int width = window->getSize().x;
    unsigned int height = window->getSize().y;
    if (!bool(music.getStatus())) {
        music = sf::Music("music.wav");
        music.setVolume(35.f);
        music.setLooping(true);
        music.play();
    }
    sf::SoundBuffer clickBuf("click.wav");
    sf::Sound click(clickBuf);
    click.setVolume(20.f);

    bool ifPlay = true;

    Label gameName(font, "235 seconds", sf::Color::White, height * 0.1f);
    gameName.setPositionCenter(sf::Vector2f(width * 0.5f, height * 0.06f));

    Button playButton(Label(font, "Играть", sf::Color::White), sf::Vector2f(0.f, 0.f), sf::Vector2f(width * 0.1f, height * 0.1f), sf::Color::Magenta);
    playButton.getShape()->setOrigin(playButton.getShape()->getGeometricCenter());
    playButton.getShape()->setPosition({ width * 0.5f, height * 0.7f });
    playButton.reloadLabel();

    Button exitButton(Label(font, "Выход", sf::Color::White), sf::Vector2f(0.f, 0.f), sf::Vector2f(width * 0.1f, height * 0.1f), sf::Color::Magenta);
    exitButton.getShape()->setOrigin(playButton.getShape()->getGeometricCenter());
    exitButton.getShape()->setPosition({ width * 0.5f, height * 0.85f });
    exitButton.reloadLabel();

    Label instruction(font, "Инструкция", sf::Color::White, height * 0.05f);
    instruction.setPositionCenter(sf::Vector2f(width * 0.5f, height * 0.2f));

    sf::Texture qrImage("qr.png", false, sf::IntRect({ 0, 0 }, { 462, 462 }));
    sf::Sprite qr(qrImage);
    qr.setTextureRect(sf::IntRect({ 0, 0 }, { 462, 462 }));
    qr.setScale(sf::Vector2f(height * 0.3f / 462.f, height * 0.3f / 462.f));
    qr.setOrigin(qr.getLocalBounds().getCenter());
    qr.setPosition(sf::Vector2f(width * 0.5f, height * 0.4f));

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
                click.play();
                window->close();
            }
            else if (exitButton.isPosIn(sf::Vector2f(sf::Mouse::getPosition(*window))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                click.play();
                ifPlay = false;
            }
            else if (!ifPlay) {
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
        window->draw(qr);

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
