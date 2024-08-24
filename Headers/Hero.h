#ifndef HERO_H
#define HERO_H

#include "GameContext.h"
#include "Projectile.h"

class Hero {
   private:
    GameContext& resources;
    sf::Sprite sprite;
    sf::Vector2f targetPosition;
    float speed;
    int ammo;
    int hp;
    sf::RectangleShape hitbox;
    int maxHp;
    int maxAmmo;

   public:
    Hero(GameContext& r) : resources(r) {}
    void init();
    void walk(float dt);
    void render();
    sf::Vector2f getPosition() { return sprite.getPosition(); }
    sf::Vector2f getTargetPosition() { return targetPosition; }
    void setTargetPosition(sf::Vector2f target);
    void rotate(sf::Vector2f targetPosition);
    void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles, sf::Vector2f target);
    void checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles);
    bool isDead();
    int getHP();
    int getAmmo();
    sf::FloatRect getHitbox();
    void increaseHP(int value);
    void increaseAmmo(int value);
};

#endif