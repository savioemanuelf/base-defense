#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

#include "Bar.h"
#include "GameContext.h"

class Hud {
   private:
    // global resources
    GameContext& resources;
    // components
    Bar heroLife, heroAmmo, baseLife;

   public:
    // constructor
    Hud(GameContext& r) : resources(r), heroLife(r), heroAmmo(r), baseLife(r) {}
    // functions
    void init(int heroMaxHP, int heroMaxAmmo, int baseMaxHP);
    void update();
    void render();
    // setters
    void setHeroLife(int life);
    void setHeroAmmo(int ammo);
    void setBaseLife(int life);
};

#endif