#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Bar {
   private:
    // global assets
    GameContext& resources;
    // assets
    sf::RectangleShape bar;
    sf::RectangleShape border;
    sf::Text content;
    int maxContentValue;
    int currentContentValue;

   public:
    // constructor
    Bar(GameContext& r) : resources(r) {}
    // functions
    void init(sf::Vector2f positions = sf::Vector2f(20, 20), sf::Vector2f size = sf::Vector2f(100, 20),
              sf::Color barColor = sf::Color::White, sf::Color outlineColor = sf::Color::Black, int maxValue = 100,
              int currentValue = 100);
    void render();
    // setters
    void setContent(int value);
};

#endif