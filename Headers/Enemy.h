#include <SFML/Graphics.hpp>

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
    // Getters
    bool isDead();
    float shootTime();
    sf::Vector2f getPosition();
    // Setters
    void resetShootTime();
};