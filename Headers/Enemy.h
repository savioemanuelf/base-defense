#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"
#include "Projectile.h"

class Projectile;

class Enemy {
   private:
    // global resources
    GameContext& resources;
    // components
    sf::Sprite sprite;
    sf::Clock shootCooldown;
    sf::RectangleShape hitbox;
    // attributes
    float speed;
    int hp;
    // functions
    sf::Vector2f randomPositionOutside();

   public:
    // constructor
    Enemy(GameContext& r) : resources(r) { init(); }
    // functions
    void init();
    void move(sf::Vector2f targetPosition, float dt);
    void render();
    void rotate(sf::Vector2f targetPosition);
    void checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles);
    void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles, sf::Vector2f target);
    // getters
    bool isDead();
    sf::Vector2f getPosition();
    // setters
    void setSpeed(int value);
};

#endif