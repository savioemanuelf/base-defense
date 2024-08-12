#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "Headers/Base.h"
#include "Headers/Enemy.h"
#include "Headers/Heroi.h"
#include "Headers/Menu.h"
#include "Headers/Projectile.h"
#include "Headers/Drop.h"

int main() {
    // Window
    bool isFullscreen = true;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Base Defense", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    // Assets Loading
    sf::Texture projectileTexture;
    if (!projectileTexture.loadFromFile("Assets/Texture/Projectiles/projetil.png")) {
        std::cerr << "Erro ao abrir a textura do projétil" << std::endl;
        return -1;
    }
    sf::Texture lifePotionTexture;
    if(!lifePotionTexture.loadFromFile("Assets/Texture/Drops/life-potion.png")) {
        std::cerr << "Erro ao carregar textura da poção de vida" << std::endl;
        return -1;
    }
    sf::Sprite lifePotionSprite(lifePotionTexture);

    sf::Texture manaPotionTexture;
    if(!manaPotionTexture.loadFromFile("Assets/Texture/Drops/mana-potion.png")) {
        std::cerr << "Erro ao carregar textura da poção de mana" << std::endl;
        return -1;
    }
    sf::Sprite manaPotionSprite(manaPotionTexture);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Assets/Texture/Backgrounds/background.jpg")) {
        std::cerr << "Erro ao abrir a textura de fundo" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Font font;
    if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
        std::cerr << "Erro ao abrir a fonte" << std::endl;
        return -1;
    }
    sf::Cursor cursor;
    if (!cursor.loadFromSystem(sf::Cursor::Hand)) {
        return -1;
    }

    // Menu
    Menu menu(font);

    // Base
    Base base(window);
    base.initializeHealthBar(window);

    // Hero
    Heroi heroi(font);
    std::vector<Projectile> projectiles;
    sf::Vector2f targetPosition = heroi.getPosition();
    heroi.initializeHealthBar(window);
    heroi.initializeAmmoBar(window);

    // Enemy
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Projectile> enemiesProjectiles;

    // Drops
    std::vector<Drop> drops;

    // Clocks
    sf::Clock clock, spawnClock;

    // Event Polling
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                // Window Close
                case sf::Event::Closed:
                    window.close();
                    break;
                // Keyboard Pressed
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        // Escape Key
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        // F11 Key
                        case sf::Keyboard::F11:
                            isFullscreen = !isFullscreen;
                            window.close();
                            if (isFullscreen) {
                                window.create(sf::VideoMode::getDesktopMode(), "Base Defense", sf::Style::Fullscreen);
                            } else {
                                window.create(sf::VideoMode(800, 600), "Base Defense", sf::Style::Default);
                            }
                            window.setFramerateLimit(60);
                            menu.resize(window);
                            break;
                        // Q Key
                        case sf::Keyboard::Q:
                            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            heroi.atirar(projectiles, projectileTexture, mousePosition);
                            break;
                    }
                    break;
                // Mouse Pressed
                case sf::Event::MouseButtonPressed:
                    switch (event.mouseButton.button) {
                        // Left Click
                        case sf::Mouse::Left:
                            // On Play Button
                            if (menu.getPlayBounds().contains(
                                    static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                                menu.setInvisible();
                            }
                            // On Exit Button
                            if (menu.getExitBounds().contains(
                                    static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                                window.close();
                            }
                            break;
                        // Right Click
                        case sf::Mouse::Right:
                            targetPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            break;
                    }
                    break;
            }
        }
        // Update
        if (menu.isVisible()) {
            // Update
            if (menu.getPlayBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ||
                menu.getExitBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                window.setMouseCursor(cursor);
            } else {
                window.setMouseCursor(sf::Cursor());
            }

            // Render
            window.clear();
            menu.draw(window);
            window.display();
        } else {
            window.setMouseCursor(sf::Cursor());

            // Enemy Spawning
            if (spawnClock.getElapsedTime().asSeconds() >= 5) {
                enemies.push_back(std::make_unique<Enemy>());
                spawnClock.restart();
            }

            // Enemy Shooting
            for (auto it = enemies.begin(); it != enemies.end(); it++) {
                if ((*it)->shootTime() >= 4) {
                    sf::Vector2f position = (*it)->getPosition();
                    sf::Vector2f direction =
                        window.mapPixelToCoords(static_cast<sf::Vector2i>(heroi.getPosition())) - position;
                    enemiesProjectiles.emplace_back(projectileTexture, position, direction);
                    (*it)->resetShootTime();
                }
            }
            
            // Enemy Dying
            for (auto it = enemies.begin(); it != enemies.end();) {
                if ((*it)->checkHit(projectiles)) {
                    // Drop items when the enemy dies
                    if (rand() % 2 == 1) { // if rand % 2 == 1, it will drop something
                        if (rand() % 2 == 1) { // if rand % 2 == 1, the drop will be mana, otherwise, it will be life
                            Drop drop(manaPotionSprite, (*it)->getPosition(), &heroi, DropType::manaPotion);
                            drops.push_back(drop);
                        } else {
                            Drop drop(lifePotionSprite, (*it)->getPosition(), &heroi, DropType::lifePotion);
                            drops.push_back(drop);
                        }  
                    }
                    it = enemies.erase(it); // Remove enemy from the list
                } else {
                    (*it)->move(window, heroi.getPosition());
                    ++it;
                }
            }

            // Drop collect and mana Update
            for (auto it = drops.begin(); it != drops.end();) {
                if (it->checkCollision(heroi.getSprite())) {
                    if (it->getDropType() == DropType::manaPotion) {
                        if (heroi.getMunicao() + 5 <= 50) {
                            heroi.setMunicao(heroi.getMunicao() + 5); // Add 5 mana
                        } else {
                            heroi.setMunicao(50);
                        }
                    } else {
                        if (heroi.getHP() < 100) {
                            heroi.setHP(heroi.getHP() + 1); // Add 1 HP
                        }
                    }
                    it = drops.erase(it); // Remove drop from the array
                } else {
                    ++it;
                }
            }

            // Frame Time
            sf::Time deltaTime = clock.restart();
            float dt = deltaTime.asSeconds();

            // Base Health Regen
            base.baseRegen(1);

            //Hero rotate
            sf::Vector2f mousePostion = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            heroi.rotate(mousePostion);

            //Hero Damage Taken
            heroi.dano_tomado(enemiesProjectiles);

            // Hero Moving
            sf::Vector2f direction = targetPosition - heroi.getPosition();
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (distance > 1.0f) {
                direction /= distance;
                heroi.andar(direction * 200.0f * dt);
            }

            // Hero Projectiles Moving
            for (auto& projectile : projectiles) {
                projectile.update(dt);
            }

            //Enemy rotation
            for (auto& enemy : enemies) {
                enemy->rotate(heroi.getPosition());
            }

            // Enemy Projectiles Moving
            for (auto& projectile : enemiesProjectiles) {
                projectile.update(dt);
            }

            // Base Collision
            for (auto it = enemiesProjectiles.begin(); it != enemiesProjectiles.end();) {
                // corrigir para tamanho do projétil (está em 25x25)
                sf::FloatRect enemyProjectileBounds(it->getPosition(), sf::Vector2f(25, 25));
                if (base.checkCollision(it->getPosition(), sf::Vector2f(25, 25))) {
                    base.damage(10);                    // aplicar dano à base
                    it = enemiesProjectiles.erase(it);  // remover projétil da lista
                } else {
                    ++it;
                }
            }

            // Background sprite resize
            sf::Vector2u windowSize = window.getSize();
            backgroundSprite.setScale(
                static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
                static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
            );
            // Render
            window.clear(sf::Color::Black);
            window.draw(backgroundSprite);
            base.showBase(window);
            heroi.draw(window);
            for (auto& projectile : projectiles) {
                projectile.draw(window);
            }
            for (auto& projectile : enemiesProjectiles) {
                projectile.draw(window);
            }
            for (const auto& enemy : enemies) {
                enemy->draw(window);
            }
            for (auto& drop : drops) {
                drop.showDrop(window);
            }
            base.getBaseHealthBar().showBar(window);
            heroi.getBarHealth().showBar(window);
            heroi.getBarAmmo().showBar(window);
            window.display();
        }
    }

    return 0;
}
