#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Gameover {
   private:
    // components
    GameContext& resources;
    sf::Text youLose, playAgain, backToMenu;
    sf::Color primary, secondary;
    sf::RectangleShape darkOverlay;
    // attributes
    int optionSelected;

   public:
    // constructor
    Gameover(GameContext& r) : resources(r) { init(); }
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