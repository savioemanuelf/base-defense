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
    bool destroyed;

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
};

#endif