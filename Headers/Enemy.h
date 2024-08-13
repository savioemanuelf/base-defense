#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"
#include "Projectile.h"

class Enemy {
   private:
    GameContext& resources;
    sf::Sprite sprite;
    float speed;
    int hp;
    sf::Clock shootCooldown;

    sf::Vector2f randomPositionOutside();

   public:
    Enemy(GameContext& r) : resources(r) { init(); }
    void init();
    void move(sf::Vector2f targetPosition, float dt);
    void render();
    void rotate(sf::Vector2f targetPosition);
    void checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles);
    bool isDead();
    void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles, sf::Vector2f target);
};

#endif