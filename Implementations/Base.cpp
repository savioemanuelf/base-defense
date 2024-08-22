#include "../Headers/Base.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Base::Base(sf::Window& window) : maxHealth(100), currentHealth(maxHealth), destroyed(false) {
    // Texture
    if (!this->baseTexture.loadFromFile("Assets/Texture/Base/base.png")) {
        std::cerr << "Erro ao carregar a imagem da base" << std::endl;
    }
    if (!this->destroyedBaseTexture.loadFromFile("Assets/Texture/Base/destroyed-base.png")) {
        std::cerr << "Erro ao carregar a imagem da base destruída" << std::endl;
    }
    sf::Vector2u windowSize = window.getSize();

    // Setting Up Sprite
    this->baseSprite.setTexture(this->baseTexture);
    this->baseSprite.setOrigin(baseTexture.getSize().x / 2.0f, baseTexture.getSize().y / 2.0f);
    this->baseSprite.setPosition(windowSize.x / 2, windowSize.y / 2);

    sf::Vector2u textureSize = baseTexture.getSize();
    float radius = std::min(textureSize.x, textureSize.y) / 2.0f;  // Raio é metade do menor tamanho da textura
    sf::Vector2f position((windowSize.x - 2 * radius) / 2,
                          (windowSize.y - 2 * radius) / 2);  // posição centralizada do círculo

    shape.setPosition(position.x, position.y);
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Transparent);


    if (!manaDrainBuffer.loadFromFile("Assets/SFX/mana-drain.ogg")) {
        std::cerr << "Erro ao carregar o áudio mana-drain.ogg" << std::endl;
    }
    manaDrainSound.setBuffer(manaDrainBuffer);
}

void Base::initializeHealthBar(sf::Window& window) {
    int barHeight = 16;

    int maxHealth = this->getMaxHealth();
    int currentHealth = this->getHealth();
    
    sf::Vector2f windowSize = sf::Vector2f(window.getSize());
    sf::Vector2f size = sf::Vector2f(windowSize.x * 0.3f, barHeight);
    sf::Vector2f pos = sf::Vector2f((windowSize.x - size.x) / 2, (windowSize.y - size.y) - 7); // 7 pixels acima do canto inferior central
    
    sf::Color backgroundColor = sf::Color::Transparent;
    sf::Color color = sf::Color(0, 160, 0);
    sf::Color outlineColor = sf::Color::White;
    int thickness = 2;

    this->baseHealthBar = new Bar(pos, size, backgroundColor, color, outlineColor, thickness, currentHealth, maxHealth);
}

Base::~Base() {
    delete this->baseHealthBar;
}

void Base::showBase(sf::RenderWindow& window) const {
    window.draw(this->baseSprite);
}

void Base::damage(int damage) {
    setHealth(this->getHealth() - damage);

    if (getHealth() < 0) {
        this->setHealth(0);
    } 
    if (getHealth() == 0) {
        if(!isDestroyed()) {
            this->manaDrainSound.play();
        }
        this->setDestroyed(true);
        baseHealthBar->updateBar(this->getHealth(), sf::Color::Red);
        this->baseSprite.setTexture(this->destroyedBaseTexture);
    } else if (getHealth() <= 10) {
        baseHealthBar->updateBar(this->getHealth(), sf::Color::Red);
    } else if (getHealth() <= 50) {
        baseHealthBar->updateBar(this->getHealth(), sf::Color(255, 200, 0));
    } else {
        baseHealthBar->updateBar(this->getHealth(), sf::Color(0, 160, 0));
    }
}

void Base::baseRegen(int regen) {
    sf::Color color;
    sf::Time deltaTime = regenClock.restart();
    static float timePerFrame = 0;
    timePerFrame += deltaTime.asSeconds();

    if (getHealth() <= 10) {
        color = sf::Color::Red;
    } else if (getHealth() <= 50) {
        color = sf::Color(255, 200, 0);
    } else {
        color = sf::Color(0, 160, 0);
    }

    if (timePerFrame >= 3.0f) {
        if (this->getHealth() + regen <= this->getMaxHealth() && !(this->isDestroyed())) {
            this->baseHealthBar->updateBar(this->getHealth(), color);
            this->setHealth(this->getHealth() + regen);
            this->baseHealthBar->updateBar(this->getHealth(), color);
        }
        timePerFrame = 0;
    }
}

bool Base::checkCollision(const sf::Vector2f& position, const sf::Vector2f& size) const {
    sf::FloatRect projectileRect(position, size);
    return shape.getGlobalBounds().intersects(projectileRect);
}
