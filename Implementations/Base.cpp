#include "../Headers/Base.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Base::Base(sf::Window& window) : maxHealth(100), currentHealth(maxHealth), destroyed(false){
    sf::Vector2u windowSize = window.getSize();

    float width = windowSize.x * 0.3f;   // largura da base é 30% da tela
    float height = windowSize.y * 0.3f;  // altura da base é 30% da tela

    sf::Vector2f positions(((windowSize.x - width) / 2),
                           (windowSize.y - height) / 2);  // posições da base

    setPos(this->positions);

    shape.setPosition(positions.x, positions.y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color::Green);

}

void Base::initializeHealthBar(sf::Window& window) {
    int barHeight = 16;

    int maxHealth = this->getMaxHealth();
    int currentHealth = this->getHealth();
    
    sf::Vector2f windowSize = sf::Vector2f(window.getSize());
    sf::Vector2f size = sf::Vector2f(windowSize.x * 0.3f, barHeight);
    sf::Vector2f pos = sf::Vector2f((windowSize.x - size.x)/2, (windowSize.y - size.y) -7 ); // 7 pixels acima do canto inferior central
    
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
    window.draw(this->shape);
}

void Base::damage(int damage) {
    setHealth(this->getHealth() - damage);

    if (getHealth() < 0) {
        this->setHealth(0);
    } 
    if (getHealth() == 0) {
        this->setDestroyed(true);
        this->shape.setOutlineColor(sf::Color::Red);
        baseHealthBar->updateBar(this->getHealth(), sf::Color::Red);
    } else if( getHealth() <= 10) {
        baseHealthBar->updateBar(this->getHealth(), sf::Color::Red);
    } else if (getHealth() <= 50) {
        baseHealthBar->updateBar(this->getHealth(), sf::Color(255, 200, 0));
    } else {
        baseHealthBar->updateBar(this->getHealth(), sf::Color(0, 160, 0)); // -> deve ser utilizado porque retorna um ponteiro
    }
}

void Base::baseRegen(int regen) {
    sf::Color color;
    sf::Time deltaTime = regenClock.restart();
    static float timePerFrame = 0;
    timePerFrame += deltaTime.asSeconds();
    // Set da cor da barra de vida para a regeneração
    if( getHealth() <= 10) {
        color = sf::Color::Red;
    } else if (getHealth() <= 50) {
        color =  sf::Color(255, 200, 0);
    } else {
        color =  sf::Color(0, 160, 0);
    }
    if (timePerFrame >= 3.0f) {
        if (this->getHealth() + regen <= this->getMaxHealth() && !(this->isDestroyed())) {
            this->baseHealthBar->updateBar(this->getHealth(), color); // realizar última alteração da barra de vida
            this->setHealth(this->getHealth() + regen);
            this->baseHealthBar->updateBar(this->getHealth(), color); // alterar pós cura
        }
        timePerFrame = 0;
    }
}

bool Base::checkCollision(const sf::Vector2f& position, const sf::Vector2f& size) const {
    sf::FloatRect projectileRect(position, size);
    return shape.getGlobalBounds().intersects(projectileRect); 
}
