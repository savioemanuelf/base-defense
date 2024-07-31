#include "../Headers/ProjectileEnemy.h"

ProjectileEnemy::ProjectileEnemy(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction, float speed) : e_direction(direction), e_velocity(speed) {
    e_sprite.setTexture(texture);
    e_sprite.setPosition(position);
    e_sprite.setScale(0.5f, 0.5f);
}

void ProjectileEnemy::shoot(sf::Texture& projectilTextureEnemy) {
    sf::Vector2f position = e_sprite.getPosition();
    sf::Vector2f direction(-1.0f, 0.0f);
    float speed = 400.0f;
    e_sprite.setTexture(projectilTextureEnemy);
    e_sprite.setPosition(position);
    e_direction = direction;
    e_velocity = speed;
}

void ProjectileEnemy::update(float dT) {
    e_sprite.move(e_direction * e_velocity * dT);
}

void ProjectileEnemy::draw(sf::RenderWindow& window) {
    window.draw(e_sprite);
}
