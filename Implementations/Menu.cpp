#include "../Headers/Menu.h"

void Menu::init() {
    primary = sf::Color(166, 166, 166);
    secondary = sf::Color::White;
    outlineSize = 2;
    // Title
    title.setFont(resources.assets->getFont(arial));
    title.setString("Base Defense");
    title.setFillColor(primary);
    title.setOutlineThickness(outlineSize);
    title.setOutlineColor(secondary);
    // Play
    play.setFont(resources.assets->getFont(arial));
    play.setString("Jogar");
    play.setFillColor(primary);
    play.setOutlineThickness(outlineSize);
    play.setOutlineColor(secondary);
    // Settings
    settings.setFont(resources.assets->getFont(arial));
    settings.setString("Opcoes");
    settings.setFillColor(primary);
    settings.setOutlineThickness(outlineSize);
    settings.setOutlineColor(secondary);
    // Exit
    exit.setFont(resources.assets->getFont(arial));
    exit.setString("Sair");
    exit.setFillColor(primary);
    exit.setOutlineThickness(outlineSize);
    exit.setOutlineColor(secondary);

    resize();
}

void Menu::handleEvents(sf::Event& event) {
    switch (event.type) {
        case sf::Event::MouseButtonPressed:
            switch (event.mouseButton.button) {
                case sf::Mouse::Left:
                    if (play.getGlobalBounds().contains(
                            static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                        next = StateType::Game;
                    }
                    if (settings.getGlobalBounds().contains(
                            static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                        next = StateType::Settings;
                    }
                    if (exit.getGlobalBounds().contains(
                            static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                        resources.window->close();
                    }
                    break;
            }
            break;
    }
}

void Menu::update(float dt) {
    if (play.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
        settings.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
        exit.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
        resources.window->setMouseCursor(resources.assets->getCursor(Cursors::hand));
    } else {
        resources.window->setMouseCursor(sf::Cursor());
    }
}

void Menu::render() {
    resources.window->clear();
    resources.window->draw(title);
    resources.window->draw(play);
    resources.window->draw(settings);
    resources.window->draw(exit);
    resources.window->display();
}

void Menu::resize() {
    float width = resources.window->getSize().x;
    float height = resources.window->getSize().y;

    title.setCharacterSize(height / 10);
    title.setPosition((width - title.getGlobalBounds().width) / 2, (height - title.getGlobalBounds().height) / 15);

    play.setCharacterSize(height / 14);
    play.setPosition((width - play.getGlobalBounds().width) / 2, (height - play.getGlobalBounds().height) / 3);

    settings.setCharacterSize(height / 14);
    settings.setPosition((width - settings.getGlobalBounds().width) / 2,
                         (height - settings.getGlobalBounds().height) / 2);

    exit.setCharacterSize(height / 14);
    exit.setPosition((width - exit.getGlobalBounds().width) / 2, (height - exit.getGlobalBounds().height) / 1.5);
}