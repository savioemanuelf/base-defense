#include "../Headers/Pause.h"

void Pause::init() {
    int outlineSize = 2;
    primary = sf::Color(166, 166, 166);
    secondary = sf::Color::White;

    pauseTitle.setFont(resources.assets->getFont(arial));
    pauseTitle.setString("Pause");
    pauseTitle.setFillColor(primary);
    pauseTitle.setOutlineThickness(outlineSize);
    pauseTitle.setOutlineColor(secondary);

    backToGame.setFont(resources.assets->getFont(arial));
    backToGame.setString("continuar");
    backToGame.setFillColor(primary);
    backToGame.setOutlineThickness(outlineSize);
    backToGame.setOutlineColor(secondary);

    restartGame.setFont(resources.assets->getFont(arial));
    restartGame.setString("reiniciar");
    restartGame.setFillColor(primary);
    restartGame.setOutlineThickness(outlineSize);
    restartGame.setOutlineColor(secondary);

    backToMenu.setFont(resources.assets->getFont(arial));
    backToMenu.setString("sair");
    backToMenu.setFillColor(primary);
    backToMenu.setOutlineThickness(outlineSize);
    backToMenu.setOutlineColor(secondary);

    darkOverlay.setSize(static_cast<sf::Vector2f>(resources.window->getSize()));
    darkOverlay.setFillColor(sf::Color(0, 0, 0, 128));

    resize();
}

void Pause::handleEvents(sf::Event& event) {
    optionSelected = -1;
    if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (backToGame.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
            optionSelected = 0;
        }
        if (restartGame.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
            optionSelected = 1;
        }
        if (backToMenu.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
            optionSelected = 2;
        }
    }
}

void Pause::update() {
    if (backToGame.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
        restartGame.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
        backToMenu.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
        resources.window->setMouseCursor(resources.assets->getCursor(Cursors::hand));
    } else {
        resources.window->setMouseCursor(sf::Cursor());
    }
}

void Pause::render() {
    resources.window->draw(darkOverlay);
    resources.window->draw(pauseTitle);
    resources.window->draw(backToGame);
    resources.window->draw(restartGame);
    resources.window->draw(backToMenu);
}

void Pause::resize() {
    float width = resources.window->getSize().x;
    float height = resources.window->getSize().y;

    pauseTitle.setCharacterSize(height / 10);
    pauseTitle.setPosition((width - pauseTitle.getGlobalBounds().width) / 2,
                           (height - pauseTitle.getGlobalBounds().height) / 15);

    backToGame.setCharacterSize(height / 14);
    backToGame.setPosition((width - backToGame.getGlobalBounds().width) / 2,
                           (height - backToGame.getGlobalBounds().height) / 3);

    restartGame.setCharacterSize(height / 14);
    restartGame.setPosition((width - restartGame.getGlobalBounds().width) / 2,
                            (height - restartGame.getGlobalBounds().height) / 2);

    backToMenu.setCharacterSize(height / 14);
    backToMenu.setPosition((width - backToMenu.getGlobalBounds().width) / 2,
                           (height - backToMenu.getGlobalBounds().height) / 1.5);
}

int Pause::getSelectedOption() { return optionSelected; }