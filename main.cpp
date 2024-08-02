#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "Headers/Base.h"
#include "Headers/Enemy.h"
#include "Headers/Heroi.h"
#include "Headers/Menu.h"
#include "Headers/Projectile.h"

int main() {
    bool isFullscreen = true;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Hero Game", sf::Style::Fullscreen);

    Heroi heroi;
    Base base(window);

    sf::Texture projectileTexture;
    if (!projectileTexture.loadFromFile("Assets/Texture/projetil.png")) {
        std::cerr << "Erro ao abrir a textura do projétil" << std::endl;
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf")) {
        std::cerr << "Erro ao abrir a fonte" << std::endl;
        return -1;
    }

    // Menu
    Menu menu(font);

    float heroiSpeed = 200.0f;
    sf::Vector2f targetPosition = heroi.getPosition();
    std::vector<Projectile> projectiles;

    // INIMIGOS DESATIVADOS POR ENQUANTO
    // std::vector<std::unique_ptr<Enemy>> enemies;

    // Hand Cursor
    sf::Cursor cursor;
    if (!cursor.loadFromSystem(sf::Cursor::Hand)) {
        return -1;
    }

    sf::Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(12);
    hpText.setFillColor(sf::Color::Red);

    sf::Text ammoText;
    ammoText.setFont(font);
    ammoText.setCharacterSize(12);
    ammoText.setFillColor(sf::Color::White);

    sf::Clock clock;

    // INIMIGOS DESATIVADOS POR ENQUANTO
    // sf::Clock spawnClock;

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
                                window.create(sf::VideoMode::getDesktopMode(), "Hero Game ", sf::Style::Fullscreen);
                            } else {
                                window.create(sf::VideoMode(800, 600), "Hero Game", sf::Style::Default);
                            }
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
                    base.updateWindowSize(window);
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
            // INIMIGOS DESATIVADOS POR ENQUANTO
            // if (spawnClock.getElapsedTime().asSeconds() >= 5) {
            //     enemies.push_back(std::make_unique<Enemy>());
            //     spawnClock.restart();
            // }
            // for (auto it = enemies.begin(); it != enemies.end();) {
            //     if ((*it)->isDead()) {
            //         it = enemies.erase(it);
            //     } else {
            //         (*it)->move(window, heroi.getPosition());
            //         ++it;
            //     }
            // }

            sf::Time deltaTime = clock.restart();
            float dt = deltaTime.asSeconds();

            sf::Vector2f direction = targetPosition - heroi.getPosition();
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (distance > 1.0f) {
                direction /= distance;
                heroi.andar(direction * heroiSpeed * dt);
            }

            for (auto& projectile : projectiles) {
                projectile.update(dt);
            }

            // verificação de colisão com a base
            for (auto it = projectiles.begin(); it != projectiles.end();) {
                // corrigir para tamanho do projétil (está em 25x25)
                sf::FloatRect projectileBounds(it->getPosition(), sf::Vector2f(25, 25));
                if (base.checkCollision(it->getPosition(), sf::Vector2f(25, 25))) {
                    base.damage(10);             // aplicar dano à base
                    it = projectiles.erase(it);  // remover projétil da lista
                } else {
                    ++it;
                }
            }

            hpText.setString("HP: " + std::to_string(heroi.getHP()));
            ammoText.setString("Ammo: " + std::to_string(heroi.getMunicao()));

            sf::Vector2f heroiPos = heroi.getPosition();
            hpText.setPosition(heroiPos.x, heroiPos.y - 30);
            ammoText.setPosition(heroiPos.x, heroiPos.y - 60);

            window.clear(sf::Color::Black);
            base.showBase(window);
            heroi.draw(window);
            for (auto& projectile : projectiles) {
                projectile.draw(window);
            }
            // INIMIGOS DESATIVADOS POR ENQUANTO
            // for (const auto& enemy : enemies) {
            //     enemy->draw(window);
            // }
            window.draw(hpText);
            window.draw(ammoText);
            window.display();
        }
    }

    return 0;
}