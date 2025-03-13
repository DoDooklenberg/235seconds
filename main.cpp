#include <SFML/Graphics.hpp>

void game(int time, int modules[6]) {
    sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "235seconds", sf::Style::None, sf::State::Fullscreen);
    window->setVerticalSyncEnabled(true);
    float width = window->getSize().x;
    float height = window->getSize().y;

    sf::Font font("font.ttf");
    sf::Text display(font);
    display.setCharacterSize(50);
    display.setFillColor(sf::Color::White);
    display.setPosition({ width * 0.1f, height * 0.05f });

    sf::Clock timer;
    timer.stop();
    std::wstring minutes, seconds;
    if (time % 60 < 10) {
        seconds = L"0" + std::to_wstring(time % 60);
    } else {
        seconds = std::to_wstring(time % 60);
    }
    if (time / 60 < 10) {
        minutes = L"0" + std::to_wstring(time / 60);
    } else {
        minutes = std::to_wstring(time / 60);
    }
    display.setString(minutes + L":" + seconds);

    sf::VertexArray module(sf::PrimitiveType::Lines, 2);
    module[0].position = sf::Vector2f(width * 0.15f, height * 0.1f);
    module[1].position = sf::Vector2f(width * 0.15f, height * 0.4f);

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
        window->draw(display);
        window->draw(module);

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

        window->draw(display);
        window->draw(module);


        if (seconds != std::to_wstring(int(time - timer.getElapsedTime().asSeconds()) % 60)) {
            if (int(time - timer.getElapsedTime().asSeconds()) % 60 < 10) {
                seconds = L"0" + std::to_wstring(int(time - timer.getElapsedTime().asSeconds()) % 60);
            } else {
                seconds = std::to_wstring(int(time - timer.getElapsedTime().asSeconds()) % 60);
            }
            if (int(time - timer.getElapsedTime().asSeconds()) / 60 < 10) {
                minutes = L"0" + std::to_wstring(int(time - timer.getElapsedTime().asSeconds()) / 60);
            } else {
                minutes = std::to_wstring(int(time - timer.getElapsedTime().asSeconds()) / 60);
            }
            display.setString(minutes + L":" + seconds);
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

int main() {
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

        window->display();
    }
    window->close();
    delete window;

    startGame();

    return 0;
}
