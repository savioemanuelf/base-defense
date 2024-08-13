#include "../Headers/Projectile.h"

#include <cmath>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction) : speed(300.0f) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = speed * direction;
    sprite.setOrigin(sprite.getGlobalBounds().width / 2,
                     sprite.getGlobalBounds().height / 2);  // Origem no centro da imagem
    rotacao(direction);
}

void Projectile::rotacao(sf::Vector2f direction) {
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
    sprite.setRotation(angle);
}

sf::FloatRect Projectile::getBounds() { return sprite.getGlobalBounds(); }
void Projectile::update(float dt) { sprite.move(velocity * dt); }
void Projectile::draw(sf::RenderWindow& window) { window.draw(sprite); }

sf::Vector2f Projectile::getPosition() const { return sprite.getPosition(); }