#include "Projectile.h"

Projectile::Projectile(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction, float speed) : direction(direction), speed(speed) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.5f,0.5f); //Tamanho de acordo com a imagem
}

void Projectile::update(float dt){
    sprite.move(direction * speed * dt);
}

void Projectile::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

sf::Vector2f Projectile::getPosition() const{
    return sprite.getPosition();
}