#include "../Headers/Base.h"

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
}

Base::~Base() {
    // destrutor vazio
}

void Base::showBase(sf::RenderWindow& window) const {
    window.draw(this->shape);
}

void Base::damage(int damage) {
    this->setHealth(this->getHealth() - damage);

    if (currentHealth < 0) {
        this->setHealth(0);
    }

    if (currentHealth == 0) {
        this->setDestroyed(true);
        shape.setOutlineColor(sf::Color::Red);
    }
}

bool Base::checkCollision(const sf::Vector2f& position,
                          const sf::Vector2f& size) const {
    sf::FloatRect projectileRect(position, size);
    return shape.getGlobalBounds().intersects(projectileRect);
}
