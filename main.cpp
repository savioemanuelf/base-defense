#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "Heroi.h"
#include "Projectile.h"

int main() {
    bool isFullscreen = true;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Hero Game", sf::Style::Fullscreen);

    Heroi heroi;

    sf::Texture projectileTexture;
    if(!projectileTexture.loadFromFile("images/projetil.png")){
        std::cerr << "Erro ao abrir a textura do projétil" << std::endl;
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erro ao abrir a fonte" << std::endl;
        return -1;
    }

    float heroiSpeed = 200.0f;
    sf::Vector2f targetPosition = heroi.getPosition();
    std::vector<Projectile> projectiles;

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
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11) {
                isFullscreen = !isFullscreen;
                window.close();
                if (isFullscreen) {
                    window.create(sf::VideoMode::getDesktopMode(), "Hero Game", sf::Style::Fullscreen);
                } else {
                    window.create(sf::VideoMode(800, 600), "Hero Game", sf::Style::Default);
                }
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                targetPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            }

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q){
                heroi.atirar(projectiles, projectileTexture);
            }
        }

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Vector2f direction = targetPosition - heroi.getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if(distance > 1.0f){
            direction /= distance;
            heroi.andar(direction * heroiSpeed * dt);
        }
        
        for(auto& projectile : projectiles){
            projectile.update(dt);
        }

    
        hpText.setString("HP: " + std::to_string(heroi.getHP()));
        ammoText.setString("Ammo: " + std::to_string(heroi.getMunicao()));

        
        sf::Vector2f heroiPos = heroi.getPosition();
        hpText.setPosition(heroiPos.x, heroiPos.y - 30);
        ammoText.setPosition(heroiPos.x, heroiPos.y - 60);

        window.clear(sf::Color::Black);
        heroi.draw(window);
        for(auto& projectile : projectiles){
            projectile.draw(window);
        }
        window.draw(hpText);
        window.draw(ammoText);
        window.display();
    }

    return 0;
}