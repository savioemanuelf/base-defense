#include "../Headers/Projectile.h"

void Projectile::render() { resources.window->draw(sprite); }

void Projectile::init(sf::Vector2f spawnPosition, sf::Vector2f target) {
    sprite.setTexture(resources.assets->getProjectileTexture(Projectiles::fireball));
    sprite.setScale(0.07f, 0.07f);
    sprite.setPosition(spawnPosition);
    // FAZER PROJETIL ANDAR
}