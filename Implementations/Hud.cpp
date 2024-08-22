#include "../Headers/Hud.h"

void Hud::init() {
    heroLife.setFont(resources.assets->getFont(Fonts::arial));
    heroLife.setCharacterSize(100);
    heroLife.setColor(sf::Color::Red);
    heroLife.setPosition(0, 0);

    heroAmmo.setFont(resources.assets->getFont(Fonts::arial));
    heroAmmo.setCharacterSize(100);
    heroAmmo.setColor(sf::Color::Yellow);
    heroAmmo.setPosition(0, 200);

    baseLife.setFont(resources.assets->getFont(Fonts::arial));
    baseLife.setCharacterSize(100);
    baseLife.setColor(sf::Color::Green);
    baseLife.setPosition(0, 400);
}

void Hud::update() {}

void Hud::render() {
    resources.window->draw(heroLife);
    resources.window->draw(heroAmmo);
    resources.window->draw(baseLife);
}

void Hud::setHeroLife(int life) { heroLife.setString(std::to_string(life)); }

void Hud::setHeroAmmo(int ammo) { heroAmmo.setString(std::to_string(ammo)); }

void Hud::setBaseLife(int life) { baseLife.setString(std::to_string(life)); }
