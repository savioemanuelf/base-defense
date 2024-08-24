#include "../Headers/Gameover.h"

void Gameover::init() {
    int outlineSize = 2;
    primary = sf::Color(166, 166, 166);
    secondary = sf::Color::White;

    youLose.setFont(resources.assets->getFont(arial));
    youLose.setString("Voce Perdeu!");
    youLose.setFillColor(primary);
    youLose.setOutlineThickness(outlineSize);
    youLose.setOutlineColor(secondary);

    playAgain.setFont(resources.assets->getFont(arial));
    playAgain.setString("jogar novamente");
    playAgain.setFillColor(primary);
    playAgain.setOutlineThickness(outlineSize);
    playAgain.setOutlineColor(secondary);

    backToMenu.setFont(resources.assets->getFont(arial));
    backToMenu.setString("voltar pro menu");
    backToMenu.setFillColor(primary);
    backToMenu.setOutlineThickness(outlineSize);
    backToMenu.setOutlineColor(secondary);

    darkOverlay.setSize(static_cast<sf::Vector2f>(resources.window->getSize()));
    darkOverlay.setFillColor(sf::Color(0, 0, 0, 128));

    resize();
}

void Gameover::handleEvents(sf::Event& event) {
    optionSelected = -1;
    if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (playAgain.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
            optionSelected = 0;
        }
        if (backToMenu.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
            optionSelected = 1;
        }
    }
}

void Gameover::update() {
    if (playAgain.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
        backToMenu.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
        resources.window->setMouseCursor(resources.assets->getCursor(Cursors::hand));
    } else {
        resources.window->setMouseCursor(sf::Cursor());
    }
}

void Gameover::render() {
    resources.window->draw(darkOverlay);
    resources.window->draw(youLose);
    resources.window->draw(playAgain);
    resources.window->draw(backToMenu);
}

void Gameover::resize() {
    float width = resources.window->getSize().x;
    float height = resources.window->getSize().y;

    youLose.setCharacterSize(height / 10);
    youLose.setPosition((width - youLose.getGlobalBounds().width) / 2,
                        (height - youLose.getGlobalBounds().height) / 15);

    playAgain.setCharacterSize(height / 14);
    playAgain.setPosition((width - playAgain.getGlobalBounds().width) / 2,
                          (height - playAgain.getGlobalBounds().height) / 3);

    backToMenu.setCharacterSize(height / 14);
    backToMenu.setPosition((width - backToMenu.getGlobalBounds().width) / 2,
                           (height - backToMenu.getGlobalBounds().height) / 1.5);
}

int Gameover::getSelectedOption() { return optionSelected; }
