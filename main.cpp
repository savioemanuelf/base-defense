#include <SFML/Graphics.hpp>

#include "Headers/Game.h"
#include "Headers/GameContext.h"
#include "Headers/Menu.h"
#include "Headers/Settings.h"
#include "Headers/StateManager.h"

int main() {
    GameContext resources;
    resources.window->create(sf::VideoMode::getDesktopMode(), "Base Defense", sf::Style::Fullscreen);
    resources.window->setFramerateLimit(60);
    resources.assets->addFont(Fonts::arial, "arial.ttf");
    resources.assets->addCursor(Cursors::hand, "hand");
    resources.isFullscreen = true;
    resources.heroType = Heroes::mage;
    resources.debug = false;
    resources.difficult = Difficulties::normal;

    StateManager StateManager;
    StateManager.changeState(std::make_unique<Menu>(resources));

    sf::Clock clock;
    while (resources.window->isOpen()) {
        sf::Event event;
        while (resources.window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                resources.window->close();
            }
            StateManager.getState()->handleEvents(event);

            if (StateManager.getState()->nextState() != StateManager.getState()->getType()) {
                switch (StateManager.getState()->nextState()) {
                    case StateType::Menu:
                        StateManager.changeState(std::make_unique<Menu>(resources));
                        break;
                    case StateType::Settings:
                        StateManager.changeState(std::make_unique<Settings>(resources));
                        break;
                    case StateType::Game:
                        StateManager.changeState(std::make_unique<Game>(resources));
                        break;
                    case StateType::Restart:
                        StateManager.changeState(std::make_unique<Game>(resources));
                        break;
                }
            }
        }
        StateManager.getState()->update(clock.restart().asSeconds());

        StateManager.getState()->render();
    }

    return 0;
}