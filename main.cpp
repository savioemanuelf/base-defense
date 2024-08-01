#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "Headers/Base.h"
#include "Headers/Enemy.h"
#include "Headers/Heroi.h"
#include "Headers/Projectile.h"

int main() {
    bool isFullscreen = true;
    bool menu = true;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Hero Game",
                            sf::Style::Fullscreen);

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

    float heroiSpeed = 200.0f;
    sf::Vector2f targetPosition = heroi.getPosition();
    std::vector<Projectile> projectiles;

    // std::vector<std::unique_ptr<Enemy>> enemies;

    // Menu Texts
    sf::Text gameName("Base Defense", font), play("Jogar", font),
        exit("Sair", font);

    // Title
    gameName.setCharacterSize(100);
    gameName.setOutlineThickness(2);
    gameName.setFillColor(sf::Color(166, 166, 166));
    gameName.setOutlineColor(sf::Color::White);
    gameName.setPosition(
        (window.getSize().x - gameName.getGlobalBounds().width) / 2, 50);
    // Play
    play.setCharacterSize(50);
    play.setOutlineThickness(2);
    play.setFillColor(sf::Color(166, 166, 166));
    play.setOutlineColor(sf::Color::White);
    play.setPosition((window.getSize().x - play.getGlobalBounds().width) / 2,
                     280);

    // Exit
    exit.setCharacterSize(50);
    exit.setOutlineThickness(2);
    exit.setFillColor(sf::Color(166, 166, 166));
    exit.setOutlineColor(sf::Color::White);
    exit.setPosition((window.getSize().x - exit.getGlobalBounds().width) / 2,
                     400);

    // Cursor
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
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::F11) {
                isFullscreen = !isFullscreen;
                window.close();
                if (isFullscreen) {
                    window.create(sf::VideoMode::getDesktopMode(), "Hero Game",
                                  sf::Style::Fullscreen);
                } else {
                    window.create(sf::VideoMode(800, 600), "Hero Game",
                                  sf::Style::Default);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                // Right click
                if (event.mouseButton.button == sf::Mouse::Right) {
                    targetPosition =
                        window.mapPixelToCoords(sf::Mouse::getPosition(window));
                }
                // Left click
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // On play Button
                    if (play.getGlobalBounds().contains(
                            static_cast<sf::Vector2f>(
                                sf::Mouse::getPosition(window)))) {
                        menu = false;
                    }
                    // On exit Button
                    if (exit.getGlobalBounds().contains(
                            static_cast<sf::Vector2f>(
                                sf::Mouse::getPosition(window)))) {
                        window.close();
                    }
                }
                base.updateWindowSize(window);
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Q) {
                sf::Vector2f mousePosition =
                    window.mapPixelToCoords(sf::Mouse::getPosition(window));
                heroi.atirar(projectiles, projectileTexture, mousePosition);
            }
        }

        if (menu) {
            // Update

            // Cursor change on hover buttons
            if (play.getGlobalBounds().contains(static_cast<sf::Vector2f>(
                    sf::Mouse::getPosition(window))) ||
                exit.getGlobalBounds().contains(static_cast<sf::Vector2f>(
                    sf::Mouse::getPosition(window)))) {
                window.setMouseCursor(cursor);
            } else {
                window.setMouseCursor(sf::Cursor());
            }

            // Render
            window.clear();
            window.draw(gameName);
            window.draw(play);
            window.draw(exit);
            window.display();
        } else {
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
            float distance = std::sqrt(direction.x * direction.x +
                                       direction.y * direction.y);
            if (distance > 1.0f) {
                direction /= distance;
                heroi.andar(direction * heroiSpeed * dt);
            }

            for (auto& projectile : projectiles) {
                projectile.update(dt);
            }

            // verificação de colisão com a base
            for (auto it = projectiles.begin(); it != projectiles.end();) {
                sf::FloatRect projectileBounds(
                    it->getPosition(),
                    sf::Vector2f(25,
                                 25));  // corrigir para tamanho do projétil
                                        // (está em 25x25)
                if (base.checkCollision(it->getPosition(),
                                        sf::Vector2f(25, 25))) {
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