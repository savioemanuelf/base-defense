#ifndef HERO_H
#define HERO_H

#include "GameContext.h"
#include "Projectile.h"

class Hero {
   private:
    // global resources
    GameContext& resources;
    // components
    sf::Vector2f targetPosition;
    sf::RectangleShape hitbox;
    sf::Sprite sprite;
    // attributes
    float speed;
    int maxAmmo;
    int maxHp;
    int ammo;
    int hp;

    void playProjectileSound();
    sf::SoundBuffer projectileSoundBuffer;
    std::vector<sf::Sound> projectileSouds;
   public:
    // constructor
    Hero(GameContext& r) : resources(r) {}
    // functions
    void init();
    void walk(float dt);
    void render();
    void rotate(sf::Vector2f targetPosition);
    void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles, sf::Vector2f target);
    void checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles);
    // getters
    sf::Vector2f getPosition() { return sprite.getPosition(); }
    sf::Vector2f getTargetPosition() { return targetPosition; }
    bool isDead();
    int getHP();
    int getAmmo();
    sf::FloatRect getHitbox();
    // setters
    void setTargetPosition(sf::Vector2f target);
    void increaseHP(int value);
    void increaseAmmo(int value);
    void setHp(int value);
    void setAmmo(int value);
    void setSpeed(int value);
};

#endif