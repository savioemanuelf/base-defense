#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

#include "../Headers/Bar.h"

class Base {
   private:
    sf::RectangleShape shape;
    sf::Vector2f positions;

    int maxHealth;
    int currentHealth;
    bool destroyed;

    Bar* baseHealthBar;  // implementado para o jogador ter noção do quanto de vida já perdeu

   public:
    Base(sf::Window& window);
    ~Base();

    void showBase(sf::RenderWindow& window) const;
    void damage(int damage);
    bool checkCollision(const sf::Vector2f& position, const sf::Vector2f& size) const;
    void initializeHealthBar(sf::Window& window);

    // GETTERS AND SETTERS

    bool isDestroyed() { return this->destroyed; }
    void setDestroyed(bool destroyed) { this->destroyed = destroyed; }

    int getHealth() { return this->currentHealth; }
    void setHealth(int health) { this->currentHealth = health; }

    sf::Vector2f getPos() { return this->positions; }
    void setPos(sf::Vector2f pos) { this->positions = pos; }

    int getMaxHealth() { return this->maxHealth; }

    Bar getBaseHealthBar() { return *this->baseHealthBar;}
    void setBaseHealthBar(Bar bar) { *this->baseHealthBar = bar;}
};

#endif  // BASE_H
