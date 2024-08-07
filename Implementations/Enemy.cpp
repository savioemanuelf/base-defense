#include "../Headers/Enemy.h"

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

Enemy::Enemy() : speed(1.0f), dead(false), size(50) {
    // Size Origin Position Color
    rect.setSize(sf::Vector2f(size, size));
    rect.setOrigin(size / 2.f, size / 2.f);
    rect.setPosition(randomPositionOutside());
    rect.setFillColor(sf::Color::Red);
    shootClock.restart();
}

void Enemy::draw(sf::RenderWindow& window) { window.draw(rect); }

void Enemy::move(sf::RenderWindow& window, sf::Vector2f player_position) {
    // Move while not touching
    if (rect.getGlobalBounds().contains(player_position)) {
        dead = true;
    } else {
        // Enemy position
        float x = rect.getPosition().x;
        float y = rect.getPosition().y;

        // Direction to player
        float direction_x = player_position.x - x;
        float direction_y = player_position.y - y;

        // Distance Normalized
        float distance = std::sqrt(direction_x * direction_x + direction_y * direction_y);
        if (distance > 0) {
            direction_x /= distance;
            direction_y /= distance;
        }

        // Enemy position incriase or decrease
        x += direction_x * speed;
        y += direction_y * speed;

        rect.setPosition(x, y);
    }
}

bool Enemy::checkHit(std::vector<Projectile>& projectiles) {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if ((*it).getBounds().intersects(rect.getGlobalBounds())) {
            it = projectiles.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

bool Enemy::isDead() { return this->dead; }

float Enemy::shootTime() { return this->shootClock.getElapsedTime().asSeconds(); }

void Enemy::resetShootTime() { this->shootClock.restart(); }

sf::Vector2f Enemy::getPosition() { return rect.getPosition(); }