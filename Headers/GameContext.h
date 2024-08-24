#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "AssetsManager.h"

enum Fonts { arial };
enum Cursors { hand };
enum Heroes { mage, ranger, bard };
enum Projectiles { fireball };
enum Enemies { goblin };
enum Backgrounds { rocks };
enum Drops { life, ammo };
enum Bases { intact, destroyed };
enum Bars { heroLifeBar, heroLifeBorder, heroManaBar, heroManaBorder, baseLifeBar, baseLifeBorder };
enum Difficulties { easy, normal, hard };

struct GameContext {
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<AssetsManager> assets;
    bool isFullscreen;
    bool debug;
    Heroes heroType;
    Difficulties difficult;

    GameContext() {
        assets = std::make_unique<AssetsManager>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

#endif