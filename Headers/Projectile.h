#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Projectile {
   private:
    GameContext& resources;
    sf::Sprite sprite;

   public:
    Projectile(GameContext& r, sf::Vector2f sp, sf::Vector2f t) : resources(r) { init(sp, t); }
    void init(sf::Vector2f spawnPosition, sf::Vector2f target);
    void render();
};

#endif