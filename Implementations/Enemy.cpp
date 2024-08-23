#include "../Headers/Enemy.h"

#include <stdlib.h>

#include <cmath>

sf::Vector2f Enemy::randomPositionOutside() {
    float x, y;
    srand(time(NULL));

    // Window size
    int windowWidth = sf::VideoMode::getDesktopMode().width;
    int windowHeight = sf::VideoMode::getDesktopMode().height;

    // Sort side spawn (up down left right)
    bool horizontal = rand() % 2;
    bool down = rand() % 2;
    bool right = rand() % 2;

    // Sort random position outside window
    if (horizontal) {
        if (right) {
            x = windowWidth + 50;
            y = rand() % (windowHeight + 101) - 50;
        } else {
            x = -50;
            y = rand() % (windowHeight + 101) - 50;
        }

    } else {
        if (down) {
            x = rand() % (windowWidth + 101) - 50;
            y = windowHeight + 50;
        } else {
            x = rand() % (windowWidth + 101) - 50;
            y = -50;
        }
    }

    return sf::Vector2f(x, y);
}

void Enemy::init() {
    sf::Texture& texture = resources.assets->getEnemyTexture(Enemies::goblin);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(randomPositionOutside());
    speed = 130.0f;
    hp = 10;

    hitbox.setSize(sf::Vector2f(texture.getSize().x - 40, texture.getSize().y - 40));
    hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
    hitbox.setPosition(sprite.getPosition());
    hitbox.setFillColor(sf::Color::Transparent);

    if (resources.debug) {
        hitbox.setOutlineThickness(1);
        hitbox.setFillColor(sf::Color::Red);
        hitbox.setOutlineColor(sf::Color::Red);
    }
}

void Enemy::move(sf::Vector2f targetPosition, float dt) {
    // Enemy position
    float x = sprite.getPosition().x;
    float y = sprite.getPosition().y;

    // Direction to player
    float direction_x = targetPosition.x - x;
    float direction_y = targetPosition.y - y;

    // Distance Normalized
    float distance = std::sqrt(direction_x * direction_x + direction_y * direction_y);
    if (distance > 0) {
        direction_x /= distance;
        direction_y /= distance;
    }

    // Enemy position incriase or decrease
    x += direction_x * speed * dt;
    y += direction_y * speed * dt;

    sprite.setPosition(x, y);
    hitbox.setPosition(sprite.getPosition());
}

void Enemy::render() {
    resources.window->draw(hitbox);
    resources.window->draw(sprite);
}

void Enemy::rotate(sf::Vector2f targetPosition) {
    float dx = targetPosition.x - sprite.getPosition().x;
    float dy = targetPosition.y - sprite.getPosition().y;
    float angle = std::atan2(dy, dx) * 180 / M_PI;
    sprite.setRotation(angle);
    hitbox.setRotation(angle);
}

void Enemy::checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles) {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if ((*it)->getHitbox().intersects(hitbox.getGlobalBounds()) && (this != (*it)->getOwner())) {
            it = projectiles.erase(it);
            hp = 0;
        } else {
            ++it;
        }
    }
}

bool Enemy::isDead() {
    if (hp) {
        return false;
    }
    return true;
}
void Enemy::shoot(std::vector<std::unique_ptr<Projectile>>& projectiles, sf::Vector2f target) {
    if (shootCooldown.getElapsedTime().asSeconds() >= 2) {
        sf::Vector2f spawnPosition = sprite.getPosition();
        sf::Vector2f direction = target - spawnPosition;
        projectiles.emplace_back(std::make_unique<Projectile>(resources, spawnPosition, direction, this));
        shootCooldown.restart();
    }
}

sf::Vector2f Enemy::getPosition() { return sprite.getPosition(); }