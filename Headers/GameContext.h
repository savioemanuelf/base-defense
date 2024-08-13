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

struct GameContext {
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<AssetsManager> assets;
    bool isFullscreen;
    Heroes heroType;

    GameContext() {
        assets = std::make_unique<AssetsManager>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

#endif