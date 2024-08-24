#include "../Headers/Projectile.h"

#include <cmath>

void Projectile::render() {
    resources.window->draw(sprite);
    if (resources.debug) {
        resources.window->draw(hitbox);
    }
}

void Projectile::init(sf::Vector2f spawnPosition, sf::Vector2f direction, Enemy* shooter) {
    // assets
    sf::Texture& texture = resources.assets->getProjectileTexture(Projectiles::fireball);

    // default settings
    speed = 300.0f;
    owner = shooter;
    outOfRange = false;
    maxRange = 500.0f;
    initialPosition = spawnPosition;

    // sprite settnigs
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(spawnPosition);
    direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = speed * direction;
    rotate(direction);

    // hitbox settings
    hitbox.setSize(sf::Vector2f(texture.getSize().x - 20, texture.getSize().y - 20));
    hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
    hitbox.setPosition(sprite.getPosition());
    hitbox.setFillColor(sf::Color::Red);
}

void Projectile::update(float dt) {
    sprite.move(velocity * dt);
    hitbox.move(velocity * dt);

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
    hitbox.setRotation(angle);
}

bool Projectile::isOutOfRange() { return outOfRange; }

sf::FloatRect Projectile::getHitbox() { return hitbox.getGlobalBounds(); }

Enemy* Projectile::getOwner() { return owner; }