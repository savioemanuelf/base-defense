#ifndef DROP_H
#define DROP_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Drop {
   private:
    GameContext& resources;
    sf::Sprite sprite;
    sf::RectangleShape hitbox;
    int dropType;
    sf::Clock despawnClock;

   public:
    Drop(GameContext& r, int type, sf::Vector2f enemyPosition) : resources(r) { init(type, enemyPosition); }
    void init(int type, sf::Vector2f spawnPosition);
    void render();
    sf::FloatRect getHitbox();
    int getType();
    float getDespawnTime();
};

#endif