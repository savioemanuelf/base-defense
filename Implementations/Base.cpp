#include "../Headers/Base.h"

void Base::init() {
    hp = 100;

    sf::Vector2f size((resources.window->getSize().x) * 0.29f, (resources.window->getSize().y) * 0.29f);
    shape.setSize(size);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    sf::Vector2f positions((resources.window->getSize().x) / 2, (resources.window->getSize().y) / 2);
    shape.setPosition(positions);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color::Green);
}

void Base::render() { resources.window->draw(shape); }

void Base::checkHit(std::vector<std::unique_ptr<Projectile>>& projectiles) {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if ((*it)->getHitbox().intersects(shape.getGlobalBounds())) {
            it = projectiles.erase(it);
            if (hp) {
                hp -= 50;
            } else {
                baseDestroy();
            }
        } else {
            ++it;
        }
    }
}

void Base::baseDestroy() { shape.setOutlineColor(sf::Color::Red); }