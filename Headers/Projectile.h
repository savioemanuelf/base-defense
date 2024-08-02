#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

class Projectile {
   public:
    Projectile(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    void rotacao(sf::Vector2f direction);

   private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float speed;
};

#endif