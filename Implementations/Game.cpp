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

    primary = sf::Color(166, 166, 166);
    secondary = sf::Color::White;
    isPaused = false;
    outlineSize = 2;

    pause.setFont(resources.assets->getFont(arial));
    pause.setString("Pause");
    pause.setFillColor(primary);
    pause.setOutlineThickness(outlineSize);
    pause.setOutlineColor(secondary);

    back.setFont(resources.assets->getFont(arial));
    back.setString("continuar");
    back.setFillColor(primary);
    back.setOutlineThickness(outlineSize);
    back.setOutlineColor(secondary);

    restart.setFont(resources.assets->getFont(arial));
    restart.setString("reiniciar");
    restart.setFillColor(primary);
    restart.setOutlineThickness(outlineSize);
    restart.setOutlineColor(secondary);

    menu.setFont(resources.assets->getFont(arial));
    menu.setString("sair");
    menu.setFillColor(primary);
    menu.setOutlineThickness(outlineSize);
    menu.setOutlineColor(secondary);

    darkOverlay.setSize(static_cast<sf::Vector2f>(resources.window->getSize()));
    darkOverlay.setFillColor(sf::Color(0, 0, 0, 128));

    resize();

    player.init();
}

void Game::handleEvents(sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                if (!isPaused) {
                    player.shoot(heroProjectiles,
                                 resources.window->mapPixelToCoords(sf::Mouse::getPosition(*resources.window)));
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                isPaused = !isPaused;
            }

            break;
        case sf::Event::MouseButtonPressed:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                player.setTargetPosition(resources.window->mapPixelToCoords(sf::Mouse::getPosition(*resources.window)));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (isPaused) {
                    if (back.getGlobalBounds().contains(
                            static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                        isPaused = false;
                        resources.window->setMouseCursor(sf::Cursor());
                    }
                    if (restart.getGlobalBounds().contains(
                            static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                        next = StateType::Restart;
                    }
                    if (menu.getGlobalBounds().contains(
                            static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                        next = StateType::Menu;
                    }
                }
            }

            break;
    }
}

void Game::update(float dt) {
    if (!isPaused) {
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
            (*it)->checkHit(heroProjectiles);
            if ((*it)->isDead()) {
                it = enemies.erase(it);
            } else {
                (*it)->move(player.getPosition(), dt);
                (*it)->rotate(player.getPosition());
                ++it;
            }
        }
    } else {
        if (back.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
            restart.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
            menu.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
            resources.window->setMouseCursor(resources.assets->getCursor(Cursors::hand));
        } else {
            resources.window->setMouseCursor(sf::Cursor());
        }
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

    if (isPaused) {
        resources.window->draw(darkOverlay);
        resources.window->draw(pause);
        resources.window->draw(back);
        resources.window->draw(restart);
        resources.window->draw(menu);
    }

    resources.window->display();
}

void Game::resize() {
    float width = resources.window->getSize().x;
    float height = resources.window->getSize().y;

    pause.setCharacterSize(height / 10);
    pause.setPosition((width - pause.getGlobalBounds().width) / 2, (height - pause.getGlobalBounds().height) / 15);

    back.setCharacterSize(height / 14);
    back.setPosition((width - back.getGlobalBounds().width) / 2, (height - back.getGlobalBounds().height) / 3);

    restart.setCharacterSize(height / 14);
    restart.setPosition((width - restart.getGlobalBounds().width) / 2, (height - restart.getGlobalBounds().height) / 2);

    menu.setCharacterSize(height / 14);
    menu.setPosition((width - menu.getGlobalBounds().width) / 2, (height - menu.getGlobalBounds().height) / 1.5);
}