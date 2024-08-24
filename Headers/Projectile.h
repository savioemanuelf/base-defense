#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "GameContext.h"

class Enemy;

class Projectile {
   private:
    // global resources
    GameContext &resources;
    // components
    sf::RectangleShape hitbox;
    sf::Sprite sprite;
    // attributes
    sf::Vector2f initialPosition;
    sf::Vector2f velocity;
    bool outOfRange;
    float maxRange;
    Enemy *owner;
    float speed;

   public:
    // constructor
    Projectile(GameContext &r, sf::Vector2f sp, sf::Vector2f t, Enemy *s = nullptr) : resources(r) { init(sp, t, s); }
    // functions
    void init(sf::Vector2f spawnPosition, sf::Vector2f direction, Enemy *shooter);
    void render();
    void update(float dt);
    void rotate(sf::Vector2f direction);
    // getters
    bool isOutOfRange();
    sf::FloatRect getHitbox();
    Enemy *getOwner();
};

#endif