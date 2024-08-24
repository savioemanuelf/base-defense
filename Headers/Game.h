#ifndef GAME_H
#define GAME_H

#include "Base.h"
#include "Drop.h"
#include "Enemy.h"
#include "Gameover.h"
#include "Hero.h"
#include "Hud.h"
#include "Pause.h"
#include "Projectile.h"
#include "State.h"

class Game : public State {
   private:
    StateType next;
    Hero player;
    std::vector<std::unique_ptr<Projectile>> heroProjectiles;
    std::vector<std::unique_ptr<Projectile>> enemiesProjectiles;
    std::vector<std::unique_ptr<Enemy>> enemies;
    sf::Clock enemySpawnClock;
    sf::Color primary, secondary;
    int outlineSize;
    bool isPaused;
    Base base;
    Pause pauseMenu;
    sf::Sprite background;
    Hud gameHud;
    std::vector<std::unique_ptr<Drop>> drops;
    Gameover gameover;
    bool endGame;
    float enemyCooldown;
    float enemySpeed;
    int dropCooldown;
    int droppedLifeAmount;
    int droppedAmmoAmount;

   public:
    Game(GameContext& resources)
        : State(resources),
          next(StateType::Game),
          player(resources),
          base(resources),
          pauseMenu(resources),
          gameHud(resources),
          gameover(resources) {
        init();
    }
    ~Game() override {}
    void init() override;
    void handleEvents(sf::Event& event) override;
    void update(float dt) override;
    void render() override;
    virtual StateType getType() { return StateType::Game; }
    virtual StateType nextState() { return next; }
};

#endif