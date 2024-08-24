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
    resources.assets->addBackgroundTexture(Backgrounds::rocks, "background-rocks.jpg");
    resources.assets->addDropTexture(Drops::ammo, "mana-potion.png");
    resources.assets->addDropTexture(Drops::life, "life-potion.png");
    resources.assets->addBaseTexture(Bases::intact, "base.png");
    resources.assets->addBaseTexture(Bases::destroyed, "destroyed-base.png");
    resources.window->setMouseCursor(sf::Cursor());

    sf::Texture* backgroundTexture = &resources.assets->getBackgroundTexture(Backgrounds::rocks);

    background.setTexture(*backgroundTexture);
    background.setScale(1, 1);

    isPaused = false;
    endGame = false;
    victory = false;

    player.init();
    base.init();

    switch (resources.difficult) {
        case Difficulties::easy:
            // player settings
            player.setHp(100);
            player.setAmmo(50);
            player.setSpeed(200);
            // base settings
            base.setHp(100);
            base.setRegenCooldown(1);
            // enemy settings
            enemyCooldown = 5;
            enemySpeed = 130;
            // drop settings
            dropCooldown = 8;
            droppedLifeAmount = 3;
            droppedAmmoAmount = 5;
            // game settings
            enemiesToKill = 15;
            break;
        case Difficulties::normal:
            // player settings
            player.setHp(100);
            player.setAmmo(50);
            player.setSpeed(200);
            // base settings
            base.setHp(100);
            base.setRegenCooldown(3);
            // enemy settings
            enemyCooldown = 3.5;
            enemySpeed = 120;
            // drop settings
            dropCooldown = 8;
            droppedLifeAmount = 2;
            droppedAmmoAmount = 3;
            // game settings
            enemiesToKill = 25;
            break;
        case Difficulties::hard:
            // player settings
            player.setHp(50);
            player.setAmmo(30);
            player.setSpeed(200);
            // base settings
            base.setHp(50);
            base.setRegenCooldown(5);
            // enemy settings
            enemyCooldown = 2.5;
            enemySpeed = 110;
            // drop settings
            dropCooldown = 8;
            droppedLifeAmount = 1;
            droppedAmmoAmount = 2;
            // game settings
            enemiesToKill = 50;
            break;
    }

    gameHud.init(player.getHP(), player.getAmmo(), base.getHP());
}

void Game::handleEvents(sf::Event& event) {
    if (endGame) {
        gameover.handleEvents(event);
        switch (gameover.getSelectedOption()) {
            case 0:
                next = StateType::Restart;
                break;
            case 1:
                next = StateType::Menu;
                break;
        }
    } else if (victory) {
        gamewin.handleEvents(event);
        switch (gamewin.getSelectedOption()) {
            case 0:
                next = StateType::Menu;
                break;
        }
    } else {
        if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            isPaused = !isPaused;
        }
        if (isPaused) {
            pauseMenu.handleEvents(event);
            switch (pauseMenu.getSelectedOption()) {
                case 0:
                    isPaused = !isPaused;
                    break;
                case 1:
                    next = StateType::Restart;
                    break;
                case 2:
                    next = StateType::Menu;
                    break;
            }
        } else {
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                player.shoot(heroProjectiles,
                             resources.window->mapPixelToCoords(sf::Mouse::getPosition(*resources.window)));
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    player.setTargetPosition(
                        resources.window->mapPixelToCoords(sf::Mouse::getPosition(*resources.window)));
                }
            }
        }
    }
}

void Game::update(float dt) {
    if (isPaused) {
        pauseMenu.update();
    } else if (endGame) {
        gameover.update();
    } else if (victory) {
        gamewin.update();
    } else {
        if (enemySpawnClock.getElapsedTime().asSeconds() >= enemyCooldown) {
            enemies.push_back(std::make_unique<Enemy>(resources));
            enemies.back()->setSpeed(enemySpeed);
            enemySpawnClock.restart();
        }

        if (!base.isDestroyed()) {
            base.update();
        } else {
            endGame = true;
        }

        if (!player.isDead()) {
            player.walk(dt);
            player.rotate(resources.window->mapPixelToCoords(sf::Mouse::getPosition(*resources.window)));
            player.checkHit(enemiesProjectiles);
        }

        for (auto it = drops.begin(); it != drops.end();) {
            if ((*it)->getHitbox().intersects(player.getHitbox())) {
                if ((*it)->getType() == Drops::life) {
                    player.increaseHP(droppedLifeAmount);
                } else {
                    player.increaseAmmo(droppedAmmoAmount);
                }
                it = drops.erase(it);
            } else if ((*it)->getDespawnTime() >= dropCooldown) {
                it = drops.erase(it);
            } else {
                it++;
            }
        }

        for (auto it = enemiesProjectiles.begin(); it != enemiesProjectiles.end();) {
            if ((*it)->isOutOfRange()) {
                it = enemiesProjectiles.erase(it);
            } else {
                (*it)->update(dt);
                ++it;
            }
        }

        for (auto it = heroProjectiles.begin(); it != heroProjectiles.end();) {
            if ((*it)->isOutOfRange()) {
                it = heroProjectiles.erase(it);
            } else {
                (*it)->update(dt);
                ++it;
            }
        }

        for (auto it = enemies.begin(); it != enemies.end();) {
            if ((*it)->isDead()) {
                if (rand() % 2 == 1) {
                    if (rand() % 2 == 1) {
                        drops.push_back(std::make_unique<Drop>(resources, Drops::ammo, (*it)->getPosition()));
                    } else {
                        drops.push_back(std::make_unique<Drop>(resources, Drops::life, (*it)->getPosition()));
                    }
                }
                it = enemies.erase(it);
                killCount += 1;
            } else {
                if (player.isDead()) {
                    (*it)->move(base.getPosition(), dt);
                    (*it)->rotate(base.getPosition());
                    (*it)->shoot(enemiesProjectiles, base.getPosition());
                } else {
                    (*it)->move(player.getPosition(), dt);
                    (*it)->rotate(player.getPosition());
                    (*it)->shoot(enemiesProjectiles, player.getPosition());
                }
                (*it)->checkHit(heroProjectiles);
                (*it)->checkHit(enemiesProjectiles);
                ++it;
            }
        }

        base.checkHit(enemiesProjectiles);

        gameHud.setHeroLife(player.getHP());
        gameHud.setHeroAmmo(player.getAmmo());
        gameHud.setBaseLife(base.getHP());

        if (killCount == enemiesToKill) {
            victory = true;
        }
    }
}

void Game::render() {
    resources.window->clear();

    resources.window->draw(background);

    for (auto& drop : drops) {
        drop->render();
    }

    base.render();
    player.render();

    for (auto& projectile : heroProjectiles) {
        projectile->render();
    }
    for (auto& projectile : enemiesProjectiles) {
        projectile->render();
    }
    for (auto& enemy : enemies) {
        enemy->render();
    }

    gameHud.render();

    if (isPaused) {
        pauseMenu.render();
    }
    if (endGame) {
        gameover.render();
    }
    if (victory) {
        gamewin.render();
    }

    resources.window->display();
}