#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

#include "Bar.h"
#include "GameContext.h"

class Hud {
   private:
    GameContext& resources;
    Bar heroLife, heroAmmo, baseLife;

   public:
    Hud(GameContext& r) : resources(r), heroLife(r), heroAmmo(r), baseLife(r) { init(); }
    void init();
    void update();
    void render();

    void setHeroLife(int life);
    void setHeroAmmo(int ammo);
    void setBaseLife(int life);
};

#endif