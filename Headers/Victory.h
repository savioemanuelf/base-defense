#ifndef VICTORY_H
#define VICTORY_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Victory {
   private:
    // global resources
    GameContext& resources;
    // components
    sf::Text youWin, backToMenu;
    sf::Color primary, secondary;
    sf::RectangleShape darkOverlay;
    // attributes
    int optionSelected;

   public:
    // constructor
    Victory(GameContext& r) : resources(r) { init(); }
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