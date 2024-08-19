#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"
#include "Enemy.h"

class Enemy;

class Projectile {
   private:
    GameContext& resources;
    sf::Sprite sprite;
    float speed;
    sf::Vector2f velocity;
    bool outOfRange;
    float maxRange;
    sf::Vector2f initialPosition;
    Enemy *owner;

   public:
    Projectile(GameContext& r, sf::Vector2f sp, sf::Vector2f t, Enemy *s = nullptr) : resources(r) { init(sp, t,s); }
    void init(sf::Vector2f spawnPosition, sf::Vector2f direction,Enemy *shooter);
    void render();
    void update(float dt);
    void rotate(sf::Vector2f direction);
    bool isOutOfRange();
    sf::FloatRect getBounds();
    Enemy *getOwner();
};

#endif