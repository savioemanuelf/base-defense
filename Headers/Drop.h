#ifndef DROP_H
#define DROP_H

#include <SFML/Graphics.hpp>

class Heroi;  // Forward declaration

enum class DropType {
    manaPotion,
    lifePotion
};

class Drop {
   private:
    sf::Sprite dropSprite;
    sf::Vector2f position;
    DropType type;
   public:
    // Constructor
    Drop(const sf::Sprite& dropSprite, const sf::Vector2f& position, Heroi *heroi, DropType type);
    // Destructor
    ~Drop();
    // Functions
    bool checkCollision(const sf::Sprite& sprite) const;
    void showDrop(sf::RenderWindow& window);
    // Getters
    sf::Vector2f getPosition() { return this->dropSprite.getPosition(); }
    sf::Sprite getSprite() const { return this->dropSprite; }
    DropType getDropType() { return this->type; }
    // Setters
    void setPosition(const sf::Vector2f& pos) { this-> position = pos; }
};

#endif // DROP_H
