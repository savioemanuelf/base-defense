#include "../Headers/Game.h"

#include <cmath>

void Game::init() {
    switch (resources.heroType) {
        case Heroes::mage:
            resources.assets->addHeroTexture(Heroes::mage, "mage.png");
            break;
        case Heroes::bard:
            resources.assets->addHeroTexture(Heroes::bard, "bard.png");
            break;
    }
    resources.window->setMouseCursor(sf::Cursor());

    player.init();
}

void Game::handleEvents(sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                next = StateType::Menu;
            }

            break;
        case sf::Event::MouseButtonPressed:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                player.setTargetPosition(resources.window->mapPixelToCoords(sf::Mouse::getPosition(*resources.window)));
            }
            break;
    }
}

void Game::update(float dt) {
    sf::Vector2f direction = player.getTargetPosition() - player.getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance > 1.0f) {
        direction /= distance;
        player.walk(direction * dt);
    }

    player.rotate(resources.window->mapPixelToCoords(sf::Mouse::getPosition(*resources.window)));
}

void Game::render() {
    resources.window->clear();
    player.render();
    resources.window->display();
}
