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
}

Heroi::~Heroi() {
    delete this->healthBar;
    delete this->ammoBar;
}

void Heroi::initializeHealthBar(sf::Window& window){
    int barHeight = 8;

    int maxHealth = this->getHP();
    int currentHealth = this->getHP();
    
    sf::Vector2f windowSize = sf::Vector2f(window.getSize());
    sf::Vector2f size = sf::Vector2f(windowSize.x * 0.2f, barHeight);
    sf::Vector2f pos = sf::Vector2f(0, 5); //
    
    sf::Color backgroundColor = sf::Color::Transparent; 
    sf::Color color = sf::Color::Red;
    sf::Color outlineColor = sf::Color::Red;
    int thickness = 2;

    this->healthBar = new Bar(pos, size, backgroundColor, color, outlineColor, thickness, currentHealth, maxHealth);
}

void Heroi::initializeAmmoBar(sf::Window& window){
    int barHeight = 8;
    int maxAmmo = this->getMunicao();
    int currentAmmo = this->getMunicao();
    sf::Vector2f windowSize = sf::Vector2f(window.getSize());
    sf::Vector2f size = sf::Vector2f(windowSize.x * 0.2f, barHeight);
    sf::Vector2f pos = sf::Vector2f(0, barHeight + 10);

    sf::Color backgroundColor = sf::Color::Transparent;
    sf::Color color = sf::Color::Blue;
    sf::Color outlineColor = sf::Color::Blue;
    int thickness = 2;

    this->ammoBar = new Bar(pos, size, backgroundColor, color, outlineColor, thickness, currentAmmo, maxAmmo);
}

void Heroi::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Heroi::andar(const sf::Vector2f& direction) {  // Direção x e y
    if(!this->isDead()) {
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
    if(!this->isDead()) {
        if (Municao > 0) {
            Municao--;
            playFireballSound();
            sf::Vector2f position = sprite.getPosition();
            sf::Vector2f direction = target - position;
            projectiles.emplace_back(projectileTexture, position, direction);
            ammoBar->updateBar(Municao, sf::Color::Blue);
        }
    }
}

void Heroi::dano_tomado(std::vector<Projectile>& projectiles) {
    int dano = 10;
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if (it->getBounds().intersects(sprite.getGlobalBounds())) {
            it = projectiles.erase(it);
            if(!this->isDead()) {
                HP -= dano;
            }
            healthBar->updateBar(HP, sf::Color::Red);
            if (HP == 0) {
                this->setDead(true);
                this->sprite.setColor(sf::Color(255,0,0,255));
                healthBar->updateBar(HP, sf::Color::Red);
            }
        } else {
            it++;
            healthBar->updateBar(HP, sf::Color::Red);
        }
    }
}

void Heroi::heroRegen(int regen) {
    if(!this->isDead()) {
        if (this->getHP() < 100) {
            this->setHP(this->getHP() + regen);
        }
    }
}

void Heroi::restoreAmmo(int ammo) {
    if(this->getMunicao() + ammo <= 50) {
        this->setMunicao(this->getMunicao() + ammo);
    } else {
        this->setMunicao(50);
    }
    this->ammoBar->updateBar(Municao, sf::Color::Blue);
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