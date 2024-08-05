#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

#include "../Headers/Bar.h"

class Base {
   private:
    // Attributes
    sf::RectangleShape shape;
    sf::Vector2f positions;
    int maxHealth;
    int currentHealth;
    bool destroyed;

    Bar* baseHealthBar;  
    sf::Clock regenClock;
   public:
    // Constructor
    Base(sf::Window& window);
    // Destructor
    ~Base();
    // Functions
    void showBase(sf::RenderWindow& window) const;
    void damage(int damage);
    bool checkCollision(const sf::Vector2f& position, const sf::Vector2f& size) const;
    void initializeHealthBar(sf::Window& window);
    void baseRegen(int regen);
    // GETTERS
    bool isDestroyed() { return this->destroyed; }
    int getHealth() { return this->currentHealth; }
    sf::Vector2f getPos() { return this->positions; }
    int getMaxHealth() { return this->maxHealth; }
    Bar getBaseHealthBar() { return *this->baseHealthBar; }
    // Setters
    void setDestroyed(bool destroyed) { this->destroyed = destroyed; }
    void setHealth(int health) { this->currentHealth = health; }
    void setPos(sf::Vector2f pos) { this->positions = pos; }
    void setBaseHealthBar(Bar bar) { *this->baseHealthBar = bar; }
};

#endif  // BASE_H
