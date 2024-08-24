#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameContext.h"
#include "Projectile.h"

class Base {
   private:
    // global assets
    GameContext& resources;
    // components
    sf::Sprite sprite;
    sf::CircleShape hitbox;
    sf::Clock regenTimer;
    // attributes
    int hp;
    int maxHp;
    int regenCooldown;
    // Attributes
    sf::CircleShape shape;
    sf::Texture baseTexture;
    sf::Sprite baseSprite;
    sf::Texture destroyedBaseTexture;
    sf::Sprite destroyedBaseSprite;
    sf::Vector2f positions;
    int maxHealth;
    int currentHealth;
    bool destroyed;

    sf::SoundBuffer manaDrainBuffer;
    sf::Sound manaDrainSound;
   public:
    // constructor
    Base(GameContext& r) : resources(r) {}
    // functions
    void init();
    void render();
    void update();
    void checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles);
    void baseDestroy();
    // getters
    sf::Vector2f getPosition();
    int getHP();
    bool isDestroyed();
    // setters
    void setHp(int value);
    void setRegenCooldown(int value);
    // Constructor
    Base(sf::Window& window);
    // Destructor
    ~Base();
    // Functions
    void showBase(sf::RenderWindow& window) const;
    void damage(int damage);
    bool checkCollision(const sf::Vector2f& position, const sf::Vector2f& size) const;
    void updateSprite(sf::Window& window, sf::Texture& texture, sf::Sprite& sprite);
    void initializeHealthBar(sf::Window& window);
    void baseRegen(int regen);
    // GETTERS
    bool isDestroyed() { return this->destroyed; }
    int getHealth() { return this->currentHealth; }
    sf::Vector2f getPos() { return this->positions; }
    int getMaxHealth() { return this->maxHealth; }
    Bar getBaseHealthBar() { return *this->baseHealthBar; }
    sf::Texture& getBaseTexture() { return this->baseTexture; }
    sf::Sprite& getBaseSprite() { return this->baseSprite; }
    // Setters
    void setDestroyed(bool destroyed) { this->destroyed = destroyed; }
    void setHealth(int health) { this->currentHealth = health; }
    void setPos(sf::Vector2f pos) { this->positions = pos; }
    void setBaseHealthBar(Bar bar) { *this->baseHealthBar = bar; }
};

#endif