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
#include "Victory.h"

class Game : public State {
   private:
    // components
    std::vector<std::unique_ptr<Projectile>> enemiesProjectiles;
    std::vector<std::unique_ptr<Projectile>> heroProjectiles;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Drop>> drops;
    sf::Color primary, secondary;
    sf::Clock enemySpawnClock;
    sf::Sprite background;
    Gameover gameover;
    Victory gamewin;
    Pause pauseMenu;
    StateType next;
    Hero player;
    Hud gameHud;
    Base base;
    // attributes
    int droppedAmmoAmount;
    int droppedLifeAmount;
    float enemyCooldown;
    int enemiesToKill;
    int dropCooldown;
    float enemySpeed;
    int killCount;
    bool isPaused;
    bool endGame;
    bool victory;

   public:
    // constructor
    Game(GameContext& resources)
        : State(resources),
          next(StateType::Game),
          player(resources),
          base(resources),
          pauseMenu(resources),
          gameHud(resources),
          gameover(resources),
          gamewin(resources) {
        init();
    }
    // destructor
    ~Game() override {}
    // functions
    void init() override;
    void handleEvents(sf::Event& event) override;
    void update(float dt) override;
    void render() override;
    // getters
    virtual StateType getType() { return StateType::Game; }
    virtual StateType nextState() { return next; }
};

#endif