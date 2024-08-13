#include "../Headers/Projectile.h"

#include <cmath>

void Projectile::render() { resources.window->draw(sprite); }

void Projectile::init(sf::Vector2f spawnPosition, sf::Vector2f direction) {
    sf::Texture& texture = resources.assets->getProjectileTexture(Projectiles::fireball);
    speed = 300.0f;
    outOfRange = false;
    maxRange = 500.0f;
    initialPosition = spawnPosition;

    sprite.setTexture(texture);
    sprite.setScale(0.07f, 0.07f);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(spawnPosition);
    direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = speed * direction;

    rotate(direction);
}

void Projectile::update(float dt) {
    sprite.move(velocity * dt);

    sf::Vector2f currentPosition = sprite.getPosition();
    float distance = std::sqrt(std::pow(currentPosition.x - initialPosition.x, 2) +
                               std::pow(currentPosition.y - initialPosition.y, 2));

    if (distance > maxRange) {
        outOfRange = true;
    }
}

void Projectile::rotate(sf::Vector2f direction) {
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
    sprite.setRotation(angle);
}

bool Projectile::isOutOfRange() { return outOfRange; }
sf::FloatRect Projectile::getBounds() { return sprite.getGlobalBounds(); }