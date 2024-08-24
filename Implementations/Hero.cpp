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
    ammo = maxAmmo = 50;
    hp = maxHp = 100;

    hitbox.setSize(sf::Vector2f(texture->getSize().x - 35, texture->getSize().y - 35));
    hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
    hitbox.setPosition(sprite.getPosition());
    hitbox.setFillColor(sf::Color::Transparent);

    if (resources.debug) {
        hitbox.setOutlineThickness(1);
        hitbox.setFillColor(sf::Color::Red);
        hitbox.setOutlineColor(sf::Color::Red);
    }
}

void Hero::walk(float dt) {
    sf::Vector2f direction = targetPosition - sprite.getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance > 1.0f) {
        direction /= distance;
        sprite.move(direction * speed * dt);
        hitbox.move(direction * speed * dt);
    }
}

void Hero::render() {
    resources.window->draw(hitbox);
    resources.window->draw(sprite);
}

void Hero::setTargetPosition(sf::Vector2f target) { targetPosition = target; }

void Hero::rotate(sf::Vector2f targetPosition) {
    sf::Vector2f direction = targetPosition - sprite.getPosition();
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
    sprite.setRotation(angle);
    hitbox.setRotation(angle);
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
        if ((*it)->getHitbox().intersects(hitbox.getGlobalBounds())) {
            it = projectiles.erase(it);
            if (hp) {
                hp -= 10;
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
int Hero::getHP() { return hp; }

int Hero::getAmmo() { return ammo; }

sf::FloatRect Hero::getHitbox() { return hitbox.getGlobalBounds(); }

void Hero::increaseHP(int value) {
    if (hp + value > maxHp) {
        hp = maxHp;
    } else {
        hp += value;
    }
}

void Hero::increaseAmmo(int value) {
    if (ammo + value > maxAmmo) {
        ammo = maxAmmo;
    } else {
        ammo += value;
    }
}
void Hero::setHp(int value) { maxHp = hp = value; }

void Hero::setAmmo(int value) { maxAmmo = ammo = value; }

void Hero::setSpeed(int value) { speed = value; }
