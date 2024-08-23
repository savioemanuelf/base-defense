#include "../Headers/Heroi.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Heroi::Heroi(sf::Font font) : HP(100), Municao(50), speed(200.0f) {
    // Texture
    if (!texture.loadFromFile("Assets/Texture/Heroes/mage.png")) {
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

    // Load and Set Up Health Bar Textures

    if(!vida.loadFromFile("Assets/Texture/Backgrounds/vida.png")) {
        std::cerr << "Erro ao carregar a textura da máscara de vida" << std::endl;
    }
    spritevida.setTexture(vida);
    spritevida.setPosition(-80, 0);

    if (!Borda.loadFromFile("Assets/Texture/Backgrounds/Borda.png")) {
        std::cerr << "Erro ao carregar a textura da barra de vida" << std::endl;
    }
    spriteBorda.setTexture(Borda);
    spriteBorda.setPosition(-80, 0);

    if(!BordaMana.loadFromFile("Assets/Texture/Backgrounds/BordaMana.png")) {
        std::cerr << "Erro ao carregar a textura da barra de mana" << std::endl;
    }
    spriteBordaMana.setTexture(BordaMana);
    spriteBordaMana.setPosition(0, 10);

    if(!Mana.loadFromFile("Assets/Texture/Backgrounds/Mana.png")) {
        std::cerr << "Erro ao carregar a textura da máscara de mana" << std::endl;
    }
    spriteMana.setTexture(Mana);
    spriteMana.setPosition(0, 10);

    spritevida.setTextureRect(sf::IntRect(0, 0, vida.getSize().x, vida.getSize().y));
    spriteMana.setTextureRect(sf::IntRect(0, 0, Mana.getSize().x, Mana.getSize().y));
}

Heroi::~Heroi() {
    
}

void Heroi::desenharBarras(sf::RenderWindow& window) {
    window.draw(spriteBorda);
    window.draw(spritevida);
    window.draw(spriteBordaMana);
    window.draw(spriteMana);
    
}

void Heroi::atualizarSpriteBarras() {
    float percentVida = static_cast<float>(HP) / 100.0f;
    sf::IntRect vidaRect = spritevida.getTextureRect();
    vidaRect.width = static_cast<int>(vida.getSize().x * percentVida);
    spritevida.setTextureRect(vidaRect);

    float percentMana = static_cast<float>(Municao) / 50.0f;
    sf::IntRect manaRect = spriteMana.getTextureRect();
    manaRect.width = static_cast<int>(Mana.getSize().x * percentMana);
    spriteMana.setTextureRect(manaRect);
}

void Heroi::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    desenharBarras(window); // Draw the health and mana bars here
}

void Heroi::andar(const sf::Vector2f& direction) {
    if (!this->isDead()) {
        sprite.move(direction);
    }
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
    if (!this->isDead()) {
        if (Municao > 0) {
            Municao--;
            playFireballSound();
            sf::Vector2f position = sprite.getPosition();
            sf::Vector2f direction = target - position;
            projectiles.emplace_back(projectileTexture, position, direction);
            atualizarSpriteBarras(); // Update the ammo bar here
        }
    }
}

void Heroi::dano_tomado(std::vector<Projectile>& projectiles) {
    int dano = 10;
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if (it->getBounds().intersects(sprite.getGlobalBounds())) {
            it = projectiles.erase(it);
            if (!this->isDead()) {
                HP -= dano;
                atualizarSpriteBarras(); // Update the health bar here
                if (HP <= 0) {
                    this->setDead(true);
                    this->sprite.setColor(sf::Color(255, 0, 0, 255));
                }
            }
        } else {
            ++it;
        }
    }
}

void Heroi::heroRegen(int regen) {
    if (!this->isDead() && HP < 100) {
        HP = std::min(HP + regen, 100);
        atualizarSpriteBarras(); // Update the health bar here
    }
}

void Heroi::restoreAmmo(int ammo) {
    Municao = std::min(Municao + ammo, 50);
    atualizarSpriteBarras(); // Update the ammo bar here
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

sf::Sprite Heroi::getSprite() { return this->sprite; }

void Heroi::setTargetPosition(sf::Vector2f target) { this->targetPosition = target; }

void Heroi::setMunicao(int municao) { this->Municao = municao; }

void Heroi::setHP(int life) { this->HP = life; }
