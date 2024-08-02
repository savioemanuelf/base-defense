#ifndef PROJECTILEENEMY_H
#define PROJECTILEENEMY_H

#include <SFML/Graphics.hpp>

class ProjectileEnemy {
   public:
    ProjectileEnemy(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction, float speed);
    ~ProjectileEnemy();
    void update(float dT);
    void draw(sf::RenderWindow& window);
    void shoot(sf::Texture& projectilTextureEnemy);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds();

   private:
    sf::Sprite e_sprite;
    sf::Vector2f e_direction;
    float e_velocity;
};

#endif