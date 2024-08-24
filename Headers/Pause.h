#ifndef PAUSE_H
#define PAUSE_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Pause {
   private:
    // global resources
    GameContext& resources;
    // components
    sf::Text pauseTitle, backToGame, restartGame, backToMenu;
    sf::Color primary, secondary;
    sf::RectangleShape darkOverlay;
    // attributes
    int optionSelected;

   public:
    // constructor
    Pause(GameContext& r) : resources(r) { init(); }
    // functions
    void init();
    void handleEvents(sf::Event& event);
    void update();
    void render();
    void resize();
    // getters
    int getSelectedOption();
};

#endif