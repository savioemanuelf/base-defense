#include "../Headers/Heroi.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Heroi::Heroi(sf::Font font) : HP(100), Municao(50), speed(200.0f) {
    // Texture
    if (!texture.loadFromFile("Assets/Texture/Heroes/personagem.png")) {
        std::cerr << "Erro ao carregar a imagem" << std::endl;
    }
    // Sound
    if (!fireBallBuffer.loadFromFile("Assets/SFX/fireball.wav")) {
        std::cerr << "Erro ao carregar o som da bola de fogo" << std::endl;
    }
    int maxSounds = 25;
    for (int i = 0; i < maxSounds; ++i) {
        fireBallSounds.emplace_back(fireBallBuffer);
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

void Heroi::andar(const sf::Vector2f& direction) {  // Direção x e y
    sprite.move(direction);
}
void Heroi::playFireballSound() {
    for (auto& sound : fireBallSounds) {
        if (sound.getStatus() != sf::Sound::Playing) {
            sound.play();
            break;
        }
    }
}

void Heroi::atirar(std::vector<Projectile>& projectiles, sf::Texture& projectileTexture, sf::Vector2f target) {
    if (Municao > 0) {
        Municao--;
        playFireballSound();
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

void Heroi::rotate(const sf::Vector2f& targetPosition) {
    sf::Vector2f direction = targetPosition - sprite.getPosition();
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
    sprite.setRotation(angle);
}

int Heroi::getHP() const { return HP; }

int Heroi::getMunicao() const { return Municao; }

sf::Vector2f Heroi::getPosition() const { return sprite.getPosition(); }

sf::Vector2f Heroi::getTargetPosition() { return this->targetPosition; }

void Heroi::setTargetPosition(sf::Vector2f target) { this->targetPosition = target; }
