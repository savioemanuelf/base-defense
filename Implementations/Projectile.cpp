#include "../Headers/Projectile.h"

#include <cmath>

void Projectile::render() { resources.window->draw(sprite); }

void Projectile::init(sf::Vector2f spawnPosition, sf::Vector2f direction) {
    sf::Texture& texture = resources.assets->getProjectileTexture(Projectiles::fireball);
    speed = 300.0f;

    sprite.setTexture(texture);
    sprite.setScale(0.07f, 0.07f);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(spawnPosition);
    direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = speed * direction;

    rotate(direction);
}

void Projectile::update(float dt) { sprite.move(velocity * dt); }

void Projectile::rotate(sf::Vector2f direction) {
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
    sprite.setRotation(angle);
}
