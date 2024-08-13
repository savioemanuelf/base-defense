#include "../Headers/Hero.h"

#include <cmath>

void Hero::init() {
    sf::Texture* texture = nullptr;

    switch (resources.heroType) {
        case Heroes::mage:
            texture = &resources.assets->getHeroTexture(Heroes::mage);
            break;
        case Heroes::bard:
            texture = &resources.assets->getHeroTexture(Heroes::bard);
            break;
    }

    sprite.setTexture(*texture);
    sprite.setOrigin((*texture).getSize().x / 2.0f, (*texture).getSize().y / 2.0f);
    sprite.setPosition(resources.window->getSize().x / 2.0f, resources.window->getSize().y / 2.0f);

    targetPosition = sprite.getPosition();

    speed = 200.0f;
    ammo = 50;
    hp = 100;
}

void Hero::walk(float dt) {
    sf::Vector2f direction = targetPosition - sprite.getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance > 1.0f) {
        direction /= distance;
        sprite.move(direction * speed * dt);
    }
}

void Hero::render() { resources.window->draw(sprite); }

void Hero::setTargetPosition(sf::Vector2f target) { targetPosition = target; }

void Hero::rotate(sf::Vector2f targetPosition) {
    sf::Vector2f direction = targetPosition - sprite.getPosition();
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
    sprite.setRotation(angle);
}

void Hero::shoot(std::vector<std::unique_ptr<Projectile>>& projectiles, sf::Vector2f target) {
    if (hp) {
        if (ammo) {
            ammo--;
            sf::Vector2f spawnPosition = sprite.getPosition();
            sf::Vector2f direction = target - spawnPosition;
            projectiles.emplace_back(std::make_unique<Projectile>(resources, spawnPosition, direction));
        }
    }
}

void Hero::checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles) {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if ((*it)->getBounds().intersects(sprite.getGlobalBounds())) {
            it = projectiles.erase(it);
            if (hp) {
                hp -= 50;
            }

        } else {
            ++it;
        }
    }
}

bool Hero::isDead() {
    if (hp) {
        return false;
    }
    return true;
}