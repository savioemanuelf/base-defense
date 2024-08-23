#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"
#include "Projectile.h"

class Base {
   private:
    GameContext& resources;
    sf::Sprite sprite;
    sf::CircleShape hitbox;
    int hp;

   public:
    Base(GameContext& r) : resources(r) {}
    void init();
    void render();
    void checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles);
    void baseDestroy();
    sf::Vector2f getPosition();
    int getHP();
};

#endif