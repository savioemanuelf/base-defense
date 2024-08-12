#include "../Headers/Drop.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Drop::Drop(const sf::Sprite& dropSprite, const sf::Vector2f& position, Heroi *heroi, DropType type) : dropSprite(dropSprite), position(position), type(type) {    
    sf::FloatRect bounds = this->dropSprite.getLocalBounds();
    this->dropSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    this->dropSprite.setPosition(position);
}

Drop::~Drop() {
    // Empty destructor
}

bool Drop::checkCollision(const sf::Sprite& sprite) const{
    sf::FloatRect dropBounds = this->dropSprite.getGlobalBounds();
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    return dropBounds.intersects(spriteBounds);
}

void Drop::showDrop(sf::RenderWindow& window) {
    window.draw(this->dropSprite);
}
