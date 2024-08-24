#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Gameover {
   private:
    GameContext& resources;
    sf::Text youLose, playAgain, backToMenu;
    sf::Color primary, secondary;
    sf::RectangleShape darkOverlay;
    int optionSelected;

   public:
    Gameover(GameContext& r) : resources(r) { init(); }
    void init();
    void handleEvents(sf::Event& event);
    void update();
    void render();

    void resize();
    int getSelectedOption();
};

#endif