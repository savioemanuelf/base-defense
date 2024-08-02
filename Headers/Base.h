#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

class Base {
   private:
    sf::RectangleShape shape;
    sf::Vector2f positions;

    int maxHealth;
    int currentHealth;
    bool destroyed;

    sf::Text healthText;
    sf::Font font;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarOutline;  // implementado para o jogador ter noção do quanto de vida já perdeu

   public:
    Base(sf::Window& window);
    ~Base();

    void showBase(sf::RenderWindow& window) const;
    void damage(int damage);
    bool checkCollision(const sf::Vector2f& position, const sf::Vector2f& size) const;

    void updateWindowSize(
        sf::RenderWindow& window);  // para posicionar a lifebar na parte inferior da janela dinamicamente

    // GETTERS AND SETTERS

    bool isDestroyed() { return this->destroyed; }
    void setDestroyed(bool destroyed) { this->destroyed = destroyed; }

    int getHealth() { return this->currentHealth; }
    void setHealth(int health) { this->currentHealth = health; }

    sf::Vector2f getPos() { return this->positions; }
    void setPos(sf::Vector2f pos) { this->positions = pos; }

    sf::Text getHealthText() { return this->healthText; }
    void setHealthText(sf::Text text) { this->healthText = text; }

    int getMaxHealth() { return this->maxHealth; }
};

#endif  // BASE_H
