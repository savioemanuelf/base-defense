#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "AssetsManager.h"

// global enums
enum Fonts { arial };
enum Cursors { hand };
enum Heroes { mage, bard };
enum Projectiles { fireball, note, bluefireball };
enum Enemies { goblin };
enum Backgrounds { menu, rocks };
enum Drops { life, ammo };
enum Bases { intact, destroyed };
enum Bars { heroLifeBar, heroLifeBorder, heroManaBar, heroManaBorder, baseLifeBar, baseLifeBorder };
enum Difficulties { easy, normal, hard };

struct GameContext {
    // global assets
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<AssetsManager> assets;
    bool isFullscreen;
    bool debug;
    Heroes heroType;
    Difficulties difficult;

    // constructor
    GameContext() {
        assets = std::make_unique<AssetsManager>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

#endif