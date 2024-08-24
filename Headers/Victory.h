#ifndef VICTORY_H
#define VICTORY_H

#include <SFML/Graphics.hpp>

#include "GameContext.h"

class Victory {
   private:
    GameContext& resources;
    sf::Text youWin, backToMenu;
    sf::Color primary, secondary;
    sf::RectangleShape darkOverlay;
    int optionSelected;

   public:
    Victory(GameContext& r) : resources(r) { init(); }
    void init();
    void handleEvents(sf::Event& event);
    void update();
    void render();

    void resize();
    int getSelectedOption();
};

#endif