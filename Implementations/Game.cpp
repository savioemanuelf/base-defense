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
    resources.assets->addProjectileTexture(Projectiles::fireball, "fireball.png");
    resources.assets->addEnemyTexture(Enemies::goblin, "goblin.png");
    resources.window->setMouseCursor(sf::Cursor());

    player.init();
}

void Game::handleEvents(sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                next = StateType::Menu;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                player.shoot(heroProjectiles,
                             resources.window->mapPixelToCoords(sf::Mouse::getPosition(*resources.window)));
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
    if (enemySpawnClock.getElapsedTime().asSeconds() >= 5) {
        enemies.push_back(std::make_unique<Enemy>(resources));
        enemySpawnClock.restart();
    }

    player.walk(dt);
    player.rotate(resources.window->mapPixelToCoords(sf::Mouse::getPosition(*resources.window)));

    for (auto it = heroProjectiles.begin(); it != heroProjectiles.end();) {
        if ((*it)->isOutOfRange()) {
            it = heroProjectiles.erase(it);
        } else {
            (*it)->update(dt);
            ++it;
        }
    }

    for (auto it = enemies.begin(); it != enemies.end();) {
        (*it)->move(player.getPosition(), dt);
        (*it)->rotate(player.getPosition());
        ++it;
    }
}

void Game::render() {
    resources.window->clear();

    player.render();
    for (auto& projectile : heroProjectiles) {
        projectile->render();
    }
    for (auto& enemy : enemies) {
        enemy->render();
    }

    resources.window->display();
}
