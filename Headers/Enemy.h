#include <SFML/Graphics.hpp>

#include "Projectile.h"

class Enemy {
   private:
    // Attributes
    sf::RectangleShape rect;
    sf::Clock shootClock;
    float speed;
    float size;
    bool dead;
    // Functions
    sf::Vector2f randomPositionOutside();

   public:
    // Constructor
    Enemy();
    // Functions
    void draw(sf::RenderWindow& window);
    void move(sf::RenderWindow& window, sf::Vector2f player_position);
    bool checkHit(std::vector<Projectile> projectiles);
    // Getters
    bool isDead();
    float shootTime();
    sf::Vector2f getPosition();
    // Setters
    void resetShootTime();
};