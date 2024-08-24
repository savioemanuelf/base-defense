#ifndef DROP_H
#define DROP_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Drop {
   private:
    // global resources
    GameContext& resources;
    // components
    sf::Sprite sprite;
    sf::RectangleShape hitbox;
    sf::Clock despawnClock;
    // attributes
    int dropType;

   public:
    // constructor
    Drop(GameContext& r, int type, sf::Vector2f enemyPosition) : resources(r) { init(type, enemyPosition); }
    // functions
    void init(int type, sf::Vector2f spawnPosition);
    void render();
    // getters
    sf::FloatRect getHitbox();
    int getType();
    float getDespawnTime();
};

#endif