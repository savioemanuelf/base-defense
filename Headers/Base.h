#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>
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
    // Destructor
    ~Base();
    // functions
    void init();
    void render();
    void update();
    void checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles);
    void baseDestroy();
    // GETTERS
    bool isDestroyed() { return this->destroyed; }
    int getHP() { return this->hp; }
    sf::Vector2f getPos() { return this->positions; }
    int getMaxHealth() { return this->maxHealth; }
    sf::Texture& getBaseTexture() { return this->baseTexture; }
    sf::Sprite& getBaseSprite() { return this->baseSprite; }
    sf::Vector2f getPosition() { return sprite.getPosition(); }
    // Setters
    void setDestroyed(bool destroyed) { this->destroyed = destroyed; }
    void setHealth(int health) { this->currentHealth = health; }
    void setPos(sf::Vector2f pos) { this->positions = pos; }
    void setHp(int value) { maxHp = hp = value; }
    void setRegenCooldown(int value) { regenCooldown = value; }
};

#endif