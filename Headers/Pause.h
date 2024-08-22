#ifndef PAUSE_H
#define PAUSE_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Pause {
   private:
    GameContext& resources;
    sf::Text pauseTitle, backToGame, restartGame, backToMenu;
    sf::Color primary, secondary;
    sf::RectangleShape darkOverlay;
    int optionSelected;

   public:
    Pause(GameContext& r) : resources(r) {
        init();
        resize();
    }
    void init();
    void handleEvents(sf::Event& event);
    void update();
    void render();

    void resize();
    int getSelectedOption();
};

#endif