#include "../Headers/Base.h"

void Base::init() {
    sf::Texture& texture = resources.assets->getBaseTexture(Bases::intact);
    sf::Vector2f windowSize(resources.window->getSize());

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    hitbox.setRadius(texture.getSize().x / 2.01f);
    hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
    hitbox.setPosition(sprite.getPosition());
    hitbox.setFillColor(sf::Color::Red);

    hp = maxHp = 100;
}

void Base::render() {
    if (resources.debug) {
        resources.window->draw(hitbox);
    }
    resources.window->draw(sprite);
}

void Base::update() {
    if (regenTimer.getElapsedTime().asSeconds() >= 1) {
        if (hp < maxHp) {
            hp += 1;
        }
        regenTimer.restart();
    }
}

void Base::checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles) {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        sf::FloatRect rect = (*it)->getHitbox();
        float closestX = std::clamp(hitbox.getPosition().x, rect.left, rect.left + rect.width);
        float closestY = std::clamp(hitbox.getPosition().y, rect.top, rect.top + rect.height);
        float dx = hitbox.getPosition().x - closestX;
        float dy = hitbox.getPosition().y - closestY;

        if ((dx * dx + dy * dy) < (hitbox.getRadius() * hitbox.getRadius())) {
            if (hp - 10 >= 0) {
                hp -= 10;
            } else {
                hp = 0;
            }
            if (hp == 0) {
                baseDestroy();
            }
            it = projectiles.erase(it);
        } else {
            it++;
        }
    }
}

void Base::baseDestroy() {
    sprite.setTexture(resources.assets->getBaseTexture(Bases::destroyed));
    destroyed = true;
}

sf::Vector2f Base::getPosition() { return sprite.getPosition(); }

int Base::getHP() { return hp; }

bool Base::isDestroyed() { return destroyed; }
