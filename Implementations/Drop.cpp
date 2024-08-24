#include "../Headers/Drop.h"

void Drop::init(int type, sf::Vector2f spawnPosition) {
    // texture acess
    dropType = type;
    sf::Texture& texture = resources.assets->getDropTexture(dropType);

    // sprite settings
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(spawnPosition);

    // hitbox settings
    hitbox.setSize(sf::Vector2f(texture.getSize().x - 20, texture.getSize().y - 20));
    hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
    hitbox.setPosition(sprite.getPosition());
    hitbox.setFillColor(sf::Color::Red);
}

void Drop::render() {
    // render hitbox if debug on
    if (resources.debug) {
        resources.window->draw(hitbox);
    }
    resources.window->draw(sprite);
}

sf::FloatRect Drop::getHitbox() { return hitbox.getGlobalBounds(); }

int Drop::getType() { return dropType; }

float Drop::getDespawnTime() { return despawnClock.getElapsedTime().asSeconds(); }