#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Enemy {
   private:
    GameContext& resources;
    sf::Sprite sprite;
    float speed;

    sf::Vector2f randomPositionOutside();

   public:
    Enemy(GameContext& r) : resources(r) { init(); }
    void init();
    void move(sf::Vector2f targetPosition, float dt);
    void render();
    void rotate(sf::Vector2f targetPosition);
};

#endif