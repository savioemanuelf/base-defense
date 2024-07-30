#include "../Headers/Base.h"

#include <iostream>

#include <SFML/Graphics.hpp>

Base::Base(sf::Window& window)
    : maxHealth(100), currentHealth(maxHealth), destroyed(false) {
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

    // lifebar
    float barHeight = 12;  // altura da lifebar
    healthBar.setSize(sf::Vector2f(width, barHeight));
    healthBar.setFillColor(sf::Color::Red);

    healthBar.setPosition(positions.x, positions.y + height + 5);  // largura inicial que será ajustada dinamicamente

    // outline da health bar, implementado para que o jogador tenha noção de quanto de vida já perdeu
    healthBarOutline.setSize(sf::Vector2f(width, barHeight));
    healthBarOutline.setFillColor(sf::Color::Transparent);
    healthBarOutline.setOutlineThickness(2);
    healthBarOutline.setOutlineColor(sf::Color::White);
    healthBarOutline.setPosition(positions.x, positions.y + height + 5);  // largura inicial que será ajustada dinamicamente
}

Base::~Base() {
    // destrutor vazio
}

void Base::showBase(sf::RenderWindow& window) const {
    window.draw(this->shape);
    window.draw(this -> healthBarOutline);
    window.draw(this -> healthBar);
}

void Base::damage(int damage) {
    this -> setHealth(this->getHealth() - damage);

    if (currentHealth < 0) {
        this->setHealth(0);
    }

    if (currentHealth == 0) {
        this->setDestroyed(true);
        shape.setOutlineColor(sf::Color::Red);
    }
    
    float healthPercentage = static_cast<float>(currentHealth) / maxHealth;
    healthBar.setSize(sf::Vector2f((shape.getSize().x * healthPercentage), healthBar.getSize().y));
}

bool Base::checkCollision(const sf::Vector2f& position,
                          const sf::Vector2f& size) const {
    sf::FloatRect projectileRect(position, size);
    return shape.getGlobalBounds().intersects(projectileRect);
}

void Base::updateWindowSize(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    healthBar.setPosition(shape.getPosition().x, windowSize.y - healthBar.getSize().y - 10);
    healthBarOutline.setPosition(shape.getPosition().x, windowSize.y - healthBarOutline.getSize().y - 10);
}