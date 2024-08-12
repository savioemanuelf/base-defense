#ifndef HERO_H
#define HERO_H

#include "GameContext.h"

class Hero {
   private:
    GameContext& resources;
    sf::Sprite sprite;
    sf::Vector2f targetPosition;
    float speed;
    int mana;

   public:
    Hero(GameContext& r) : resources(r) {}
    void init();
    void walk(const sf::Vector2f& direction);
    void render();
    sf::Vector2f getPosition() { return sprite.getPosition(); }
    sf::Vector2f getTargetPosition() { return targetPosition; }
    void setTargetPosition(sf::Vector2f target);
    void rotate(sf::Vector2f targetPosition);
};

#endif