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
}

void Enemy::render() { resources.window->draw(sprite); }

void Enemy::rotate(sf::Vector2f targetPosition) {
    float dx = targetPosition.x - sprite.getPosition().x;
    float dy = targetPosition.y - sprite.getPosition().y;
    float angle = std::atan2(dy, dx) * 180 / M_PI;
    sprite.setRotation(angle);
}