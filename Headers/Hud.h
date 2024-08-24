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
    Bar heroLife, heroAmmo, baseLife, progress;

   public:
    // constructor
    Hud(GameContext& r) : resources(r), heroLife(r), heroAmmo(r), baseLife(r), progress(r) {}
    // functions
    void init(int heroMaxHP, int heroMaxAmmo, int baseMaxHP, int progressValue);
    void update();
    void render();
    // setters
    void setHeroLife(int life);
    void setHeroAmmo(int ammo);
    void setBaseLife(int life);
    void setProgress(int kills);
};

#endif