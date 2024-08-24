#include "../Headers/Hud.h"

void Hud::init(int heroMaxHP, int heroMaxAmmo, int baseMaxHP, int progressValue) {
    // assets
    float width = resources.window->getSize().x;
    float height = resources.window->getSize().y;
    sf::Vector2f positions, size;
    sf::Color barColor, outlineColor;
    int maxValue, currentValue;

    // base life bar settings
    positions = sf::Vector2f(width / 2, height / 1.030);
    size = sf::Vector2f(width / 2.3, height / 30);
    barColor = sf::Color(0, 138, 14);
    outlineColor = sf::Color::Black;
    maxValue = currentValue = baseMaxHP;

    baseLife.init(positions, size, barColor, outlineColor, maxValue, currentValue);

    // hero life bar settings
    positions = sf::Vector2f(width / 2.611, height / 1.075);
    size = sf::Vector2f(width / 5, height / 30);
    barColor = sf::Color(232, 19, 19);
    maxValue = currentValue = heroMaxHP;

    heroLife.init(positions, size, barColor, outlineColor, maxValue, currentValue);

    // hero mana bar settings
    positions = sf::Vector2f(width / 1.578, height / 1.075);
    size = sf::Vector2f(width / 6, height / 30);
    barColor = sf::Color(252, 206, 20);
    maxValue = currentValue = heroMaxAmmo;

    heroAmmo.init(positions, size, barColor, outlineColor, maxValue, currentValue);

    // progress bar settings
    positions = sf::Vector2f(width / 2, height / 30);
    size = sf::Vector2f(width / 2, height / 30);
    barColor = sf::Color::White;
    maxValue = progressValue;
    currentValue = 0;

    progress.init(positions, size, barColor, outlineColor, maxValue, currentValue);
}

void Hud::update() {}

void Hud::render() {
    baseLife.render();
    heroLife.render();
    heroAmmo.render();
    progress.render();
}

void Hud::setHeroLife(int life) { heroLife.setContent(life); }

void Hud::setHeroAmmo(int ammo) { heroAmmo.setContent(ammo); }

void Hud::setBaseLife(int life) { baseLife.setContent(life); }

void Hud::setProgress(int kills) { progress.setContent(kills); }
