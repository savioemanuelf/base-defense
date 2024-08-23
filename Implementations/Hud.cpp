#include "../Headers/Hud.h"

void Hud::init() {
    float width = resources.window->getSize().x;
    float height = resources.window->getSize().y;
    sf::Vector2f positions, size;
    sf::Color barColor, outlineColor;
    int maxValue, currentValue;

    positions = sf::Vector2f(width / 2, height / 1.030);
    size = sf::Vector2f(width / 2.3, height / 30);
    barColor = sf::Color(0, 138, 14);
    outlineColor = sf::Color::Black;
    maxValue = currentValue = 100;

    baseLife.init(positions, size, barColor, outlineColor, maxValue, currentValue);

    positions = sf::Vector2f(width / 2.611, height / 1.075);
    size = sf::Vector2f(width / 5, height / 30);
    barColor = sf::Color(232, 19, 19);

    heroLife.init(positions, size, barColor, outlineColor, maxValue, currentValue);

    positions = sf::Vector2f(width / 1.578, height / 1.075);
    size = sf::Vector2f(width / 6, height / 30);
    barColor = sf::Color(252, 206, 20);
    maxValue = currentValue = 50;

    heroAmmo.init(positions, size, barColor, outlineColor, maxValue, currentValue);
}

void Hud::update() {}

void Hud::render() {
    baseLife.render();
    heroLife.render();
    heroAmmo.render();
}

void Hud::setHeroLife(int life) { heroLife.setContent(life); }

void Hud::setHeroAmmo(int ammo) { heroAmmo.setContent(ammo); }

void Hud::setBaseLife(int life) { baseLife.setContent(life); }
