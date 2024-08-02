#include "../Headers/Base.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Base::Base(sf::Window& window) : maxHealth(100), currentHealth(maxHealth), destroyed(false) {
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
    float barHeight = 16;  // altura da lifebar
    healthBar.setSize(sf::Vector2f(width, barHeight));
    healthBar.setFillColor(sf::Color(0, 160, 0));

    healthBar.setPosition(positions.x,
                          windowSize.y - barHeight - 10);  // largura inicial que será ajustada dinamicamente

    // outline da health bar, implementado para que o jogador tenha noção de quanto de vida já perdeu
    healthBarOutline.setSize(sf::Vector2f(width, barHeight));
    healthBarOutline.setFillColor(sf::Color::Transparent);
    healthBarOutline.setOutlineThickness(2);
    healthBarOutline.setOutlineColor(sf::Color::White);
    healthBarOutline.setPosition(positions.x,
                                 windowSize.y - barHeight - 10);  // largura inicial que será ajustada dinamicamente

    if (!font.loadFromFile("Assets/arial.ttf")) {
        std::cerr << "Erro ao carregar a fonte" << std::endl;
    } else {
        healthText.setFont(font);
        healthText.setCharacterSize(14);
        healthText.setFillColor(sf::Color::White);
        healthText.Bold;
        healthText.setString(std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
        sf::FloatRect textRect = healthText.getLocalBounds();
        healthText.setOrigin(textRect.width / 2, textRect.height / 2);
        healthText.setPosition(positions.x + width / 2,
                               windowSize.y - (barHeight / 2) - 10);  // Centraliza verticalmente com a healthBar
    }
}

Base::~Base() {
    // destrutor vazio
}

void Base::showBase(sf::RenderWindow& window) const {
    window.draw(this->shape);
    window.draw(this->healthBarOutline);
    window.draw(this->healthBar);
    window.draw(this->healthText);
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

    float healthPercentage = static_cast<float>(currentHealth) / maxHealth;
    healthBar.setSize(sf::Vector2f((shape.getSize().x * healthPercentage), healthBar.getSize().y));

    healthText.setString(std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
}

bool Base::checkCollision(const sf::Vector2f& position, const sf::Vector2f& size) const {
    sf::FloatRect projectileRect(position, size);
    return shape.getGlobalBounds().intersects(projectileRect);  // Mudar para o projétil inimigo apenas
}

void Base::updateWindowSize(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    float barHeight = healthBar.getSize().y;
    float barYPosition = windowSize.y - barHeight - 10;  // posição y da healthbar

    healthBar.setPosition(shape.getPosition().x, barYPosition);
    healthBarOutline.setPosition(shape.getPosition().x, barYPosition);

    sf::FloatRect textRect = healthText.getLocalBounds();
    float textHeight = textRect.height;  // altura do texto da vida
    float textYPosition = barYPosition + (barHeight / 2) - (textHeight / 2) + textRect.top;

    healthText.setPosition(shape.getPosition().x + shape.getSize().x / 2, textYPosition);
}
