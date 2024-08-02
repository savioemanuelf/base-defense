#include "../Headers/Heroi.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Heroi::Heroi(sf::Font font) : HP(100), Municao(50), speed(200.0f) {
    // Texture
    if (!texture.loadFromFile("Assets/Texture/personagem.png")) {
        std::cerr << "Erro ao carregar a imagem" << std::endl;
    }

    // Setting Up Sprite
    sprite.setTexture(texture);
    sprite.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
    targetPosition = sprite.getPosition();
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    // Attributes Text
    this->font = font;
    hpText.setFont(this->font);
    hpText.setCharacterSize(12);
    hpText.setFillColor(sf::Color::Red);
    ammoText.setFont(this->font);
    ammoText.setCharacterSize(12);
    ammoText.setFillColor(sf::Color::White);
    hpText.setPosition(10, 10);
    ammoText.setPosition(10, 30);
}

void Heroi::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    hpText.setString("HP: " + std::to_string(HP));           // Atualizar sempre na tela
    ammoText.setString("Ammo: " + std::to_string(Municao));  // Atualizar sempre na tela
    window.draw(hpText);
    window.draw(ammoText);
}

void Heroi::andar(sf::Vector2f direction) {  // Direção x e y
    sprite.move(direction * speed);
    rotate(direction);
}

void Heroi::atirar(std::vector<Projectile>& projectiles, sf::Texture& projectileTexture, sf::Vector2f target) {
    if (Municao > 0) {
        Municao--;
        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f direction = target - position;
        projectiles.emplace_back(projectileTexture, position, direction);
    }
}

void Heroi::dano_tomado(int dano) {
    HP -= dano;
    if (HP < 0) {
        HP = 0;
    }
}

void Heroi::rotate(sf::Vector2f direction) {
    float angle =
        std::atan2(direction.y, direction.x) * 180 / 3.14159265;  // Calcula com base na tangente e gira o herói
    float currentAngle = sprite.getRotation();                    // Pega a rotação atual
    float deltaAngle = angle - currentAngle;

    if (deltaAngle > 180.0f) {
        deltaAngle -= 360.0f;
    } else if (deltaAngle < -180.0f) {
        deltaAngle += 360.0f;
    }

    float rotationSpeed = 4.0f;  // Velocidade da rotação
    if (std::abs(deltaAngle) > rotationSpeed) {
        if (deltaAngle > 0) {
            sprite.setRotation(currentAngle + rotationSpeed);
        } else {
            sprite.setRotation(currentAngle - rotationSpeed);
        }
    } else {
        sprite.setRotation(angle);  // Rotação final
    }
}

int Heroi::getHP() const { return HP; }

int Heroi::getMunicao() const { return Municao; }

sf::Vector2f Heroi::getPosition() const { return sprite.getPosition(); }

sf::Vector2f Heroi::getTargetPosition() { return this->targetPosition; }

void Heroi::setTargetPosition(sf::Vector2f target) { this->targetPosition = target; }
