#include "../Headers/Projectile.h"

#include <cmath>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction) : speed(300.0f) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.05f, 0.05f);  // Tamanho de acordo com a imagem
    direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = speed * direction;
}

void Projectile::update(float dt) { sprite.move(velocity * dt); }
void Projectile::draw(sf::RenderWindow& window) { window.draw(sprite); }

sf::Vector2f Projectile::getPosition() const { return sprite.getPosition(); }