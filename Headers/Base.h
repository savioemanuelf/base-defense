#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"
#include "Projectile.h"

class Base {
   private:
    GameContext& resources;
    sf::RectangleShape shape;
    int hp;

   public:
    Base(GameContext& r) : resources(r) {
        init();
    }
    void init();
    void render();
    void checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles);
    void baseDestroy();
};

#endif