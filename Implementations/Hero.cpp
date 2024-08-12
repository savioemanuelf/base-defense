#include "../Headers/Hero.h"

#include <cmath>

void Hero::init() {
    sf::Texture& texture = resources.assets->getHeroTexture(Heroes::mage);

    switch (resources.heroType) {
        case Heroes::mage:
            texture = resources.assets->getHeroTexture(Heroes::mage);
            break;
        case Heroes::bard:
            texture = resources.assets->getHeroTexture(Heroes::bard);
            break;
    }

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(resources.window->getSize().x / 2.0f, resources.window->getSize().y / 2.0f);

    targetPosition = sprite.getPosition();

    speed = 200.0f;
    mana = 50;
}

void Hero::walk(const sf::Vector2f& direction) { sprite.move(direction * speed); }

void Hero::render() { resources.window->draw(sprite); }

void Hero::setTargetPosition(sf::Vector2f target) { targetPosition = target; }

void Hero::rotate(sf::Vector2f targetPosition) {
    sf::Vector2f direction = targetPosition - sprite.getPosition();
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
    sprite.setRotation(angle);
}

void Hero::shoot(std::vector<Projectile>& projectiles, sf::Vector2f target) {
    projectiles.emplace_back(resources, sprite.getPosition(), target);
}
