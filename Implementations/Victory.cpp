#include "../Headers/Victory.h"

void Victory::init() {
    // assets
    int outlineSize = 2;
    primary = sf::Color(166, 166, 166);
    secondary = sf::Color::White;

    // you win settings
    youWin.setFont(resources.assets->getFont(arial));
    youWin.setString("Voce Ganhou!!!!");
    youWin.setFillColor(primary);
    youWin.setOutlineThickness(outlineSize);
    youWin.setOutlineColor(secondary);

    // back to menu settings
    backToMenu.setFont(resources.assets->getFont(arial));
    backToMenu.setString("voltar pro menu");
    backToMenu.setFillColor(primary);
    backToMenu.setOutlineThickness(outlineSize);
    backToMenu.setOutlineColor(secondary);

    // dark overlay settings
    darkOverlay.setSize(static_cast<sf::Vector2f>(resources.window->getSize()));
    darkOverlay.setFillColor(sf::Color(0, 0, 0, 128));

    resize();
}

void Victory::handleEvents(sf::Event& event) {
    optionSelected = -1;
    if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (backToMenu.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
            optionSelected = 0;
        }
    }
}

void Victory::update() {
    // change mouse cursor
    if (backToMenu.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
        resources.window->setMouseCursor(resources.assets->getCursor(Cursors::hand));
    } else {
        resources.window->setMouseCursor(sf::Cursor());
    }
}

void Victory::render() {
    resources.window->draw(darkOverlay);
    resources.window->draw(youWin);
    resources.window->draw(backToMenu);
}

void Victory::resize() {
    float width = resources.window->getSize().x;
    float height = resources.window->getSize().y;

    youWin.setCharacterSize(height / 10);
    youWin.setPosition((width - youWin.getGlobalBounds().width) / 2, (height - youWin.getGlobalBounds().height) / 15);

    backToMenu.setCharacterSize(height / 14);
    backToMenu.setPosition((width - backToMenu.getGlobalBounds().width) / 2,
                           (height - backToMenu.getGlobalBounds().height) / 2);
}

int Victory::getSelectedOption() { return optionSelected; }
